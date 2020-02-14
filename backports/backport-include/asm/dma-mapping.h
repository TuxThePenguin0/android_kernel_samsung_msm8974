#ifndef __BACKPORT_ASM_DMA_MAPPING_H
#define __BACKPORT_ASM_DMA_MAPPING_H
#include_next <asm/dma-mapping.h>
#include <linux/version.h>

#if defined(CONFIG_BACKPORT_BPAUTO_BUILD_DMA_SHARED_HELPERS)
#define dma_common_get_sgtable LINUX_BACKPORT(dma_common_get_sgtable)
int dma_common_get_sgtable(struct device *dev, struct sg_table *sgt, void *cpu_addr, dma_addr_t dma_addr, size_t size);
#endif /* defined(CONFIG_BACKPORT_BPAUTO_BUILD_DMA_SHARED_HELPERS) */

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,6,0)

#define dma_get_sgtable_attrs LINUX_BACKPORT(dma_get_sgtable_attrs)
struct dma_attrs;
static inline int
dma_get_sgtable_attrs(struct device *dev, struct sg_table *sgt, void *cpu_addr,
		      dma_addr_t dma_addr, size_t size, struct dma_attrs *attrs)
{
	struct page *page = virt_to_page(cpu_addr);
	int ret;

	ret = sg_alloc_table(sgt, 1, GFP_KERNEL);
	if (unlikely(ret))
		return ret;

	sg_set_page(sgt->sgl, page, PAGE_ALIGN(size), 0);
	return 0;
}

#define dma_get_sgtable(d, t, v, h, s) dma_get_sgtable_attrs(d, t, v, h, s, NULL)
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(3,6,0) */

#endif /* __BACKPORT_ASM_DMA_MAPPING_H */
