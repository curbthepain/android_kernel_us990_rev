/*
 * YAFFS: Yet Another Flash File System. A NAND-flash specific file system.
 *
 * Copyright (C) 2002-2010 Aleph One Ltd.
 *   for Toby Churchill Ltd and Brightstar Engineering
 *
 * Created by Charles Manning <charles@aleph1.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

/*
                                                             
  
                                                                               
                                   
                                                                                       
                                           
  
 */

/*                             
                                                                      
                                                                            
                                                                                           
                                           
 */

#include "yportenv.h"

#include "yaffs_ecc.h"

static const unsigned char column_parity_table[] = {
	0x00, 0x55, 0x59, 0x0c, 0x65, 0x30, 0x3c, 0x69,
	0x69, 0x3c, 0x30, 0x65, 0x0c, 0x59, 0x55, 0x00,
	0x95, 0xc0, 0xcc, 0x99, 0xf0, 0xa5, 0xa9, 0xfc,
	0xfc, 0xa9, 0xa5, 0xf0, 0x99, 0xcc, 0xc0, 0x95,
	0x99, 0xcc, 0xc0, 0x95, 0xfc, 0xa9, 0xa5, 0xf0,
	0xf0, 0xa5, 0xa9, 0xfc, 0x95, 0xc0, 0xcc, 0x99,
	0x0c, 0x59, 0x55, 0x00, 0x69, 0x3c, 0x30, 0x65,
	0x65, 0x30, 0x3c, 0x69, 0x00, 0x55, 0x59, 0x0c,
	0xa5, 0xf0, 0xfc, 0xa9, 0xc0, 0x95, 0x99, 0xcc,
	0xcc, 0x99, 0x95, 0xc0, 0xa9, 0xfc, 0xf0, 0xa5,
	0x30, 0x65, 0x69, 0x3c, 0x55, 0x00, 0x0c, 0x59,
	0x59, 0x0c, 0x00, 0x55, 0x3c, 0x69, 0x65, 0x30,
	0x3c, 0x69, 0x65, 0x30, 0x59, 0x0c, 0x00, 0x55,
	0x55, 0x00, 0x0c, 0x59, 0x30, 0x65, 0x69, 0x3c,
	0xa9, 0xfc, 0xf0, 0xa5, 0xcc, 0x99, 0x95, 0xc0,
	0xc0, 0x95, 0x99, 0xcc, 0xa5, 0xf0, 0xfc, 0xa9,
	0xa9, 0xfc, 0xf0, 0xa5, 0xcc, 0x99, 0x95, 0xc0,
	0xc0, 0x95, 0x99, 0xcc, 0xa5, 0xf0, 0xfc, 0xa9,
	0x3c, 0x69, 0x65, 0x30, 0x59, 0x0c, 0x00, 0x55,
	0x55, 0x00, 0x0c, 0x59, 0x30, 0x65, 0x69, 0x3c,
	0x30, 0x65, 0x69, 0x3c, 0x55, 0x00, 0x0c, 0x59,
	0x59, 0x0c, 0x00, 0x55, 0x3c, 0x69, 0x65, 0x30,
	0xa5, 0xf0, 0xfc, 0xa9, 0xc0, 0x95, 0x99, 0xcc,
	0xcc, 0x99, 0x95, 0xc0, 0xa9, 0xfc, 0xf0, 0xa5,
	0x0c, 0x59, 0x55, 0x00, 0x69, 0x3c, 0x30, 0x65,
	0x65, 0x30, 0x3c, 0x69, 0x00, 0x55, 0x59, 0x0c,
	0x99, 0xcc, 0xc0, 0x95, 0xfc, 0xa9, 0xa5, 0xf0,
	0xf0, 0xa5, 0xa9, 0xfc, 0x95, 0xc0, 0xcc, 0x99,
	0x95, 0xc0, 0xcc, 0x99, 0xf0, 0xa5, 0xa9, 0xfc,
	0xfc, 0xa9, 0xa5, 0xf0, 0x99, 0xcc, 0xc0, 0x95,
	0x00, 0x55, 0x59, 0x0c, 0x65, 0x30, 0x3c, 0x69,
	0x69, 0x3c, 0x30, 0x65, 0x0c, 0x59, 0x55, 0x00,
};


/*                                                */
void yaffs_ecc_cacl(const unsigned char *data, unsigned char *ecc)
{
	unsigned int i;

	unsigned char col_parity = 0;
	unsigned char line_parity = 0;
	unsigned char line_parity_prime = 0;
	unsigned char t;
	unsigned char b;

	for (i = 0; i < 256; i++) {
		b = column_parity_table[*data++];
		col_parity ^= b;

		if (b & 0x01) {	/*                                */
			line_parity ^= i;
			line_parity_prime ^= ~i;
		}
	}

	ecc[2] = (~col_parity) | 0x03;

	t = 0;
	if (line_parity & 0x80)
		t |= 0x80;
	if (line_parity_prime & 0x80)
		t |= 0x40;
	if (line_parity & 0x40)
		t |= 0x20;
	if (line_parity_prime & 0x40)
		t |= 0x10;
	if (line_parity & 0x20)
		t |= 0x08;
	if (line_parity_prime & 0x20)
		t |= 0x04;
	if (line_parity & 0x10)
		t |= 0x02;
	if (line_parity_prime & 0x10)
		t |= 0x01;
	ecc[1] = ~t;

	t = 0;
	if (line_parity & 0x08)
		t |= 0x80;
	if (line_parity_prime & 0x08)
		t |= 0x40;
	if (line_parity & 0x04)
		t |= 0x20;
	if (line_parity_prime & 0x04)
		t |= 0x10;
	if (line_parity & 0x02)
		t |= 0x08;
	if (line_parity_prime & 0x02)
		t |= 0x04;
	if (line_parity & 0x01)
		t |= 0x02;
	if (line_parity_prime & 0x01)
		t |= 0x01;
	ecc[0] = ~t;

#ifdef CONFIG_YAFFS_ECC_WRONG_ORDER
	/*                                     */
	t = ecc[0];
	ecc[0] = ecc[1];
	ecc[1] = t;
#endif
}

/*                                             */

int yaffs_ecc_correct(unsigned char *data, unsigned char *read_ecc,
		      const unsigned char *test_ecc)
{
	unsigned char d0, d1, d2;	/*        */

	d0 = read_ecc[0] ^ test_ecc[0];
	d1 = read_ecc[1] ^ test_ecc[1];
	d2 = read_ecc[2] ^ test_ecc[2];

	if ((d0 | d1 | d2) == 0)
		return 0;	/*          */

	if (((d0 ^ (d0 >> 1)) & 0x55) == 0x55 &&
	    ((d1 ^ (d1 >> 1)) & 0x55) == 0x55 &&
	    ((d2 ^ (d2 >> 1)) & 0x54) == 0x54) {
		/*                                        */

		unsigned byte;
		unsigned bit;

#ifdef CONFIG_YAFFS_ECC_WRONG_ORDER
		/*                                               */
		unsigned char t;

		t = d0;
		d0 = d1;
		d1 = t;
#endif

		bit = byte = 0;

		if (d1 & 0x80)
			byte |= 0x80;
		if (d1 & 0x20)
			byte |= 0x40;
		if (d1 & 0x08)
			byte |= 0x20;
		if (d1 & 0x02)
			byte |= 0x10;
		if (d0 & 0x80)
			byte |= 0x08;
		if (d0 & 0x20)
			byte |= 0x04;
		if (d0 & 0x08)
			byte |= 0x02;
		if (d0 & 0x02)
			byte |= 0x01;

		if (d2 & 0x80)
			bit |= 0x04;
		if (d2 & 0x20)
			bit |= 0x02;
		if (d2 & 0x08)
			bit |= 0x01;

		data[byte] ^= (1 << bit);

		return 1;	/*                     */
	}

	if ((hweight8(d0) + hweight8(d1) + hweight8(d2)) == 1) {
		/*                           */

		read_ecc[0] = test_ecc[0];
		read_ecc[1] = test_ecc[1];
		read_ecc[2] = test_ecc[2];

		return 1;	/*                     */
	}

	/*                     */

	return -1;

}

/*
                                                          
 */
void yaffs_ecc_calc_other(const unsigned char *data, unsigned n_bytes,
			  struct yaffs_ecc_other *ecc_other)
{
	unsigned int i;

	unsigned char col_parity = 0;
	unsigned line_parity = 0;
	unsigned line_parity_prime = 0;
	unsigned char b;

	for (i = 0; i < n_bytes; i++) {
		b = column_parity_table[*data++];
		col_parity ^= b;

		if (b & 0x01) {
			/*                                */
			line_parity ^= i;
			line_parity_prime ^= ~i;
		}

	}

	ecc_other->col_parity = (col_parity >> 2) & 0x3f;
	ecc_other->line_parity = line_parity;
	ecc_other->line_parity_prime = line_parity_prime;
}

int yaffs_ecc_correct_other(unsigned char *data, unsigned n_bytes,
			    struct yaffs_ecc_other *read_ecc,
			    const struct yaffs_ecc_other *test_ecc)
{
	unsigned char delta_col;	/*                     */
	unsigned delta_line;	/*                   */
	unsigned delta_line_prime;	/*                   */
	unsigned bit;

	delta_col = read_ecc->col_parity ^ test_ecc->col_parity;
	delta_line = read_ecc->line_parity ^ test_ecc->line_parity;
	delta_line_prime =
	    read_ecc->line_parity_prime ^ test_ecc->line_parity_prime;

	if ((delta_col | delta_line | delta_line_prime) == 0)
		return 0;	/*          */

	if (delta_line == ~delta_line_prime &&
	    (((delta_col ^ (delta_col >> 1)) & 0x15) == 0x15)) {
		/*                                        */

		bit = 0;

		if (delta_col & 0x20)
			bit |= 0x04;
		if (delta_col & 0x08)
			bit |= 0x02;
		if (delta_col & 0x02)
			bit |= 0x01;

		if (delta_line >= n_bytes)
			return -1;

		data[delta_line] ^= (1 << bit);

		return 1;	/*           */
	}

	if ((hweight32(delta_line) +
	     hweight32(delta_line_prime) +
	     hweight8(delta_col)) == 1) {
		/*                           */

		*read_ecc = *test_ecc;
		return 1;	/*           */
	}

	/*                     */

	return -1;
}
