static int ps_init (void)
{
#if HAVE_THREAD_INFO
	kern_return_t status;

	port_host_self = mach_host_self ();
	port_task_self = mach_task_self ();

	if (pset_list != NULL)
	{
		vm_deallocate (port_task_self,
				(vm_address_t) pset_list,
				pset_list_len * sizeof (processor_set_t));
		pset_list = NULL;
		pset_list_len = 0;
	}

	if ((status = host_processor_sets (port_host_self,
					&pset_list,
				       	&pset_list_len)) != KERN_SUCCESS)
	{
		ERROR ("host_processor_sets failed: %s\n",
			       	mach_error_string (status));
		pset_list = NULL;
		pset_list_len = 0;
		return (-1);
	}
/* #endif HAVE_THREAD_INFO */

#elif KERNEL_LINUX
	pagesize_g = sysconf(_SC_PAGESIZE);
	DEBUG ("pagesize_g = %li; CONFIG_HZ = %i;",
			pagesize_g, CONFIG_HZ);
/* #endif KERNEL_LINUX */

#elif HAVE_LIBKVM_GETPROCS && HAVE_STRUCT_KINFO_PROC_FREEBSD
/* no initialization */
/* #endif HAVE_LIBKVM_GETPROCS && HAVE_STRUCT_KINFO_PROC_FREEBSD */

#elif HAVE_PROCINFO_H
	pagesize = getpagesize();
#endif /* HAVE_PROCINFO_H */

	return (0);
}