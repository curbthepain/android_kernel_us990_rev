/*
 *  fs/partitions/amiga.c
 *
 *  Code extracted from drivers/block/genhd.c
 *
 *  Copyright (C) 1991-1998  Linus Torvalds
 *  Re-organised Feb 1998 Russell King
 */

#include <linux/types.h>
#include <linux/affs_hardblocks.h>

#include "check.h"
#include "amiga.h"

static __inline__ u32
checksum_block(__be32 *m, int size)
{
	u32 sum = 0;

	while (size--)
		sum += be32_to_cpu(*m++);
	return sum;
}

int amiga_partition(struct parsed_partitions *state)
{
	Sector sect;
	unsigned char *data;
	struct RigidDiskBlock *rdb;
	struct PartitionBlock *pb;
	int start_sect, nr_sects, blk, part, res = 0;
	int blksize = 1;	/*                                */
	int slot = 1;
	char b[BDEVNAME_SIZE];

	for (blk = 0; ; blk++, put_dev_sector(sect)) {
		if (blk == RDB_ALLOCATION_LIMIT)
			goto rdb_done;
		data = read_part_sector(state, blk, &sect);
		if (!data) {
			if (warn_no_part)
				printk("Dev %s: unable to read RDB block %d\n",
				       bdevname(state->bdev, b), blk);
			res = -1;
			goto rdb_done;
		}
		if (*(__be32 *)data != cpu_to_be32(IDNAME_RIGIDDISK))
			continue;

		rdb = (struct RigidDiskBlock *)data;
		if (checksum_block((__be32 *)data, be32_to_cpu(rdb->rdb_SummedLongs) & 0x7F) == 0)
			break;
		/*                                                     
                
   */
		*(__be32 *)(data+0xdc) = 0;
		if (checksum_block((__be32 *)data,
				be32_to_cpu(rdb->rdb_SummedLongs) & 0x7F)==0) {
			printk("Warning: Trashed word at 0xd0 in block %d "
				"ignored in checksum calculation\n",blk);
			break;
		}

		printk("Dev %s: RDB in block %d has bad checksum\n",
		       bdevname(state->bdev, b), blk);
	}

	/*                                               */
	blksize = be32_to_cpu( rdb->rdb_BlockBytes ) / 512;

	{
		char tmp[7 + 10 + 1 + 1];

		/*                     */
		snprintf(tmp, sizeof(tmp), " RDSK (%d)", blksize * 512);
		strlcat(state->pp_buf, tmp, PAGE_SIZE);
	}
	blk = be32_to_cpu(rdb->rdb_PartitionList);
	put_dev_sector(sect);
	for (part = 1; blk>0 && part<=16; part++, put_dev_sector(sect)) {
		blk *= blksize;	/*                                           */
		data = read_part_sector(state, blk, &sect);
		if (!data) {
			if (warn_no_part)
				printk("Dev %s: unable to read partition block %d\n",
				       bdevname(state->bdev, b), blk);
			res = -1;
			goto rdb_done;
		}
		pb  = (struct PartitionBlock *)data;
		blk = be32_to_cpu(pb->pb_Next);
		if (pb->pb_ID != cpu_to_be32(IDNAME_PARTITION))
			continue;
		if (checksum_block((__be32 *)pb, be32_to_cpu(pb->pb_SummedLongs) & 0x7F) != 0 )
			continue;

		/*                      */

		nr_sects = (be32_to_cpu(pb->pb_Environment[10]) + 1 -
			    be32_to_cpu(pb->pb_Environment[9])) *
			   be32_to_cpu(pb->pb_Environment[3]) *
			   be32_to_cpu(pb->pb_Environment[5]) *
			   blksize;
		if (!nr_sects)
			continue;
		start_sect = be32_to_cpu(pb->pb_Environment[9]) *
			     be32_to_cpu(pb->pb_Environment[3]) *
			     be32_to_cpu(pb->pb_Environment[5]) *
			     blksize;
		put_partition(state,slot++,start_sect,nr_sects);
		{
			/*                                          */
			char dostype[4];
			char tmp[42];

			__be32 *dt = (__be32 *)dostype;
			*dt = pb->pb_Environment[16];
			if (dostype[3] < ' ')
				snprintf(tmp, sizeof(tmp), " (%c%c%c^%c)",
					dostype[0], dostype[1],
					dostype[2], dostype[3] + '@' );
			else
				snprintf(tmp, sizeof(tmp), " (%c%c%c%c)",
					dostype[0], dostype[1],
					dostype[2], dostype[3]);
			strlcat(state->pp_buf, tmp, PAGE_SIZE);
			snprintf(tmp, sizeof(tmp), "(res %d spb %d)",
				be32_to_cpu(pb->pb_Environment[6]),
				be32_to_cpu(pb->pb_Environment[4]));
			strlcat(state->pp_buf, tmp, PAGE_SIZE);
		}
		res = 1;
	}
	strlcat(state->pp_buf, "\n", PAGE_SIZE);

rdb_done:
	return res;
}