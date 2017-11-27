static int memory_init (void)
{
#if defined(HOST_VM_INFO)
	port_host = mach_host_self ();
	host_page_size (port_host, &pagesize);
/* #endif HOST_VM_INFO */

#elif HAVE_SYSCTLBYNAME
/* no init stuff */
/* #endif HAVE_SYSCTLBYNAME */

#elif defined(KERNEL_LINUX)
/* no init stuff */
/* #endif KERNEL_LINUX */

#elif defined(HAVE_LIBKSTAT)
	/* getpagesize(3C) tells me this does not fail.. */
	pagesize = getpagesize ();
	if (get_kstat (&ksp, "unix", 0, "system_pages"))
		ksp = NULL;
#endif /* HAVE_LIBKSTAT */

	return (0);
}