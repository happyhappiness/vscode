static int swap_init (void)
{
#if KERNEL_LINUX
	/* No init stuff */
/* #endif KERNEL_LINUX */

#elif HAVE_SWAPCTL && HAVE_SWAPCTL_TWO_ARGS
	/* getpagesize(3C) tells me this does not fail.. */
	pagesize = (derive_t) getpagesize ();
/* #endif HAVE_SWAPCTL */

#elif defined(VM_SWAPUSAGE)
	/* No init stuff */
/* #endif defined(VM_SWAPUSAGE) */

#elif HAVE_LIBKVM_GETSWAPINFO
	if (kvm_obj != NULL)
	{
		kvm_close (kvm_obj);
		kvm_obj = NULL;
	}

	kvm_pagesize = getpagesize ();

	if ((kvm_obj = kvm_open (NULL, /* execfile */
					NULL, /* corefile */
					NULL, /* swapfile */
					O_RDONLY, /* flags */
					NULL)) /* errstr */
			== NULL)
	{
		ERROR ("swap plugin: kvm_open failed.");
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