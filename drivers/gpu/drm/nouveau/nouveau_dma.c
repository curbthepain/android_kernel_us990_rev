/*
 * Copyright (C) 2007 Ben Skeggs.
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "drmP.h"
#include "drm.h"
#include "nouveau_drv.h"
#include "nouveau_dma.h"
#include "nouveau_ramht.h"

void
nouveau_dma_init(struct nouveau_channel *chan)
{
	struct drm_nouveau_private *dev_priv = chan->dev->dev_private;
	struct nouveau_bo *pushbuf = chan->pushbuf_bo;

	if (dev_priv->card_type >= NV_50) {
		const int ib_size = pushbuf->bo.mem.size / 2;

		chan->dma.ib_base = (pushbuf->bo.mem.size - ib_size) >> 2;
		chan->dma.ib_max = (ib_size / 8) - 1;
		chan->dma.ib_put = 0;
		chan->dma.ib_free = chan->dma.ib_max - chan->dma.ib_put;

		chan->dma.max = (pushbuf->bo.mem.size - ib_size) >> 2;
	} else {
		chan->dma.max  = (pushbuf->bo.mem.size >> 2) - 2;
	}

	chan->dma.put  = 0;
	chan->dma.cur  = chan->dma.put;
	chan->dma.free = chan->dma.max - chan->dma.cur;
}

void
OUT_RINGp(struct nouveau_channel *chan, const void *data, unsigned nr_dwords)
{
	bool is_iomem;
	u32 *mem = ttm_kmap_obj_virtual(&chan->pushbuf_bo->kmap, &is_iomem);
	mem = &mem[chan->dma.cur];
	if (is_iomem)
		memcpy_toio((void __force __iomem *)mem, data, nr_dwords * 4);
	else
		memcpy(mem, data, nr_dwords * 4);
	chan->dma.cur += nr_dwords;
}

/*                                 
  
           
                                        
                                                             
                              
 */
static inline int
READ_GET(struct nouveau_channel *chan, uint64_t *prev_get, int *timeout)
{
	uint64_t val;

	val = nvchan_rd32(chan, chan->user_get);
        if (chan->user_get_hi)
                val |= (uint64_t)nvchan_rd32(chan, chan->user_get_hi) << 32;

	/*                                                         
                                                            
                                                          
  */
	if (val != *prev_get) {
		*prev_get = val;
		*timeout = 0;
	}

	if ((++*timeout & 0xff) == 0) {
		DRM_UDELAY(1);
		if (*timeout > 100000)
			return -EBUSY;
	}

	if (val < chan->pushbuf_base ||
	    val > chan->pushbuf_base + (chan->dma.max << 2))
		return -EINVAL;

	return (val - chan->pushbuf_base) >> 2;
}

void
nv50_dma_push(struct nouveau_channel *chan, struct nouveau_bo *bo,
	      int delta, int length)
{
	struct nouveau_bo *pb = chan->pushbuf_bo;
	struct nouveau_vma *vma;
	int ip = (chan->dma.ib_put * 2) + chan->dma.ib_base;
	u64 offset;

	vma = nouveau_bo_vma_find(bo, chan->vm);
	BUG_ON(!vma);
	offset = vma->offset + delta;

	BUG_ON(chan->dma.ib_free < 1);
	nouveau_bo_wr32(pb, ip++, lower_32_bits(offset));
	nouveau_bo_wr32(pb, ip++, upper_32_bits(offset) | length << 8);

	chan->dma.ib_put = (chan->dma.ib_put + 1) & chan->dma.ib_max;

	DRM_MEMORYBARRIER();
	/*               */
	nouveau_bo_rd32(pb, 0);

	nvchan_wr32(chan, 0x8c, chan->dma.ib_put);
	chan->dma.ib_free--;
}

static int
nv50_dma_push_wait(struct nouveau_channel *chan, int count)
{
	uint32_t cnt = 0, prev_get = 0;

	while (chan->dma.ib_free < count) {
		uint32_t get = nvchan_rd32(chan, 0x88);
		if (get != prev_get) {
			prev_get = get;
			cnt = 0;
		}

		if ((++cnt & 0xff) == 0) {
			DRM_UDELAY(1);
			if (cnt > 100000)
				return -EBUSY;
		}

		chan->dma.ib_free = get - chan->dma.ib_put;
		if (chan->dma.ib_free <= 0)
			chan->dma.ib_free += chan->dma.ib_max;
	}

	return 0;
}

static int
nv50_dma_wait(struct nouveau_channel *chan, int slots, int count)
{
	uint64_t prev_get = 0;
	int ret, cnt = 0;

	ret = nv50_dma_push_wait(chan, slots + 1);
	if (unlikely(ret))
		return ret;

	while (chan->dma.free < count) {
		int get = READ_GET(chan, &prev_get, &cnt);
		if (unlikely(get < 0)) {
			if (get == -EINVAL)
				continue;

			return get;
		}

		if (get <= chan->dma.cur) {
			chan->dma.free = chan->dma.max - chan->dma.cur;
			if (chan->dma.free >= count)
				break;

			FIRE_RING(chan);
			do {
				get = READ_GET(chan, &prev_get, &cnt);
				if (unlikely(get < 0)) {
					if (get == -EINVAL)
						continue;
					return get;
				}
			} while (get == 0);
			chan->dma.cur = 0;
			chan->dma.put = 0;
		}

		chan->dma.free = get - chan->dma.cur - 1;
	}

	return 0;
}

int
nouveau_dma_wait(struct nouveau_channel *chan, int slots, int size)
{
	uint64_t prev_get = 0;
	int cnt = 0, get;

	if (chan->dma.ib_max)
		return nv50_dma_wait(chan, slots, size);

	while (chan->dma.free < size) {
		get = READ_GET(chan, &prev_get, &cnt);
		if (unlikely(get == -EBUSY))
			return -EBUSY;

		/*                                                    
                                                         
                                                            
                                                           
    
                                                               
                                                                
                                
   */
		if (unlikely(get == -EINVAL) || get < NOUVEAU_DMA_SKIPS)
			continue;

		if (get <= chan->dma.cur) {
			/*                                               
                                                      
                                
     
                                                    
                                                       
                                                       
               
     
                                                    
                                                        
                                                       
    */
			chan->dma.free = chan->dma.max - chan->dma.cur;
			if (chan->dma.free >= size)
				break;

			/*                                                     
                                                      
                                                      
    */
			OUT_RING(chan, chan->pushbuf_base | 0x20000000);

			/*                                            
                                                  
                                                  
                         
    */
			do {
				get = READ_GET(chan, &prev_get, &cnt);
				if (unlikely(get == -EBUSY))
					return -EBUSY;
				if (unlikely(get == -EINVAL))
					continue;
			} while (get <= NOUVEAU_DMA_SKIPS);
			WRITE_PUT(NOUVEAU_DMA_SKIPS);

			/*                                              
                      
    */
			chan->dma.cur  =
			chan->dma.put  = NOUVEAU_DMA_SKIPS;
		}

		/*                                                        
                                                         
                                                           
                                                               
                           
   */
		chan->dma.free = get - chan->dma.cur - 1;
	}

	return 0;
}

