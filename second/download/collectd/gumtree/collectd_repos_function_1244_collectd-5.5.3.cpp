static int swap_init (void) /* {{{ */
{
#if KERNEL_LINUX
	pagesize = (derive_t) sysconf (_SC_PAGESIZE);
/* #endif KERNEL_LINUX */

#elif HAVE_SWAPCTL && HAVE_SWAPCTL_TWO_ARGS
	/* getpagesize(3C) tells me this does not fail.. */
	pagesize = (derive_t) getpagesize ();
/* #endif HAVE_SWAPCTL */

#elif defined(VM_SWAPUSAGE)
	/* No init stuff */
/* #endif defined(VM_SWAPUSAGE) */

#elif HAVE_LIBKVM_GETSWAPINFO
	char errbuf[_POSIX2_LINE_MAX];

	if (kvm_obj != NULL)
	{
		kvm_close (kvm_obj);
		kvm_obj = NULL;
	}

	kvm_pagesize = getpagesize ();

	kvm_obj = kvm_openfiles (NULL, "/dev/null", NULL, O_RDONLY, errbuf);

	if (kvm_obj == NULL)
	{
		ERROR ("swap plugin: kvm_openfiles failed, %s", errbuf);
		return (-1);
	}
/* #endif HAVE_LIBKVM_GETSWAPINFO */

#elif HAVE_LIBSTATGRAB
	/* No init stuff */
/* #endif HAVE_LIBSTATGRAB */

#elif HAVE_PERFSTAT
	pagesize = getpagesize();
#endif /* HAVE_PERFSTAT */

	return (0);
}