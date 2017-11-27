static int memory_init (void)
{
#if HAVE_HOST_STATISTICS
	port_host = mach_host_self ();
	host_page_size (port_host, &pagesize);
/* #endif HAVE_HOST_STATISTICS */

#elif HAVE_SYSCTLBYNAME
/* no init stuff */
/* #endif HAVE_SYSCTLBYNAME */

#elif defined(KERNEL_LINUX)
/* no init stuff */
/* #endif KERNEL_LINUX */

#elif defined(HAVE_LIBKSTAT)
	/* getpagesize(3C) tells me this does not fail.. */
	pagesize = getpagesize ();
	if (get_kstat (&ksp, "unix", 0, "system_pages") != 0)
	{
		ksp = NULL;
		return (-1);
	}
/* #endif HAVE_LIBKSTAT */

#elif HAVE_SYSCTL
	pagesize = getpagesize ();
	if (pagesize <= 0)
	{
		ERROR ("memory plugin: Invalid pagesize: %i", pagesize);
		return (-1);
	}
/* #endif HAVE_SYSCTL */

#elif HAVE_LIBSTATGRAB
/* no init stuff */
#endif /* HAVE_LIBSTATGRAB */

	return (0);
}