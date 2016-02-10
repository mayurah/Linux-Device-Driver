#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>
#include <linux/mm.h>

static inline int valid_phys_addr_range(phys_addr_t addr, size_t count)
{
            return addr + count <= __pa(high_memory);
}

static uint64_t hpe_kaddr;
int hackon_mmap(struct file *filp, struct vm_area_struct *vma) {

	uint64_t pfn;


	if ((vma->vm_end - vma->vm_start) != 4096) {
		pr_info("hpe_hackon: 2\n");
			return -EINVAL;
	}

	if (vma->vm_flags & (VM_WRITE|VM_EXEC)) {
		pr_info("hpe_hackon: 5\n");
                return -EPERM;
	}

	pfn = vmalloc_to_pfn((const void *)hpe_kaddr);
	if (!valid_phys_addr_range(pfn<<PAGE_SHIFT, PAGE_SIZE)) {
		pr_info("hpe_hackon: 3\n");
		return -EINVAL;
	}


	if (remap_pfn_range(vma, vma->vm_start, pfn,PAGE_SIZE, vma->vm_page_prot)) {
		pr_info("hpe_hackon: 4\n");
		return -EAGAIN; 
	}

	return 0;
}

static const struct file_operations hackon_fops = {
	.owner		= THIS_MODULE,
	.mmap		= hackon_mmap,
};

static struct miscdevice hackon_dev = {
	MISC_DYNAMIC_MINOR,
	"hpehackon",
	&hackon_fops
};

static int __init hackon_init(void)
{
	int ret;

	hpe_kaddr = (uint64_t)vmalloc(4096);
	if(!hpe_kaddr) {
		pr_info("no memory\n");
		return -ENOMEM;
	}

	strcpy((char *)hpe_kaddr,"HPE HACKATHON 2016!!");

	ret = misc_register(&hackon_dev);
	if (ret)
		pr_info("Unable to register eudyptula misc device\n");
	return ret;
}

static void __exit hackon_cleanup(void)
{
	misc_deregister(&hackon_dev);
}

module_init(hackon_init);
module_exit(hackon_cleanup);

MODULE_DESCRIPTION("HPE hackon module");
MODULE_AUTHOR("HPE");
MODULE_LICENSE("GPL");
