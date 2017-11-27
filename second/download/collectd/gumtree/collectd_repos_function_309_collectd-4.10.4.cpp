static int disk_init (void)
{
#if HAVE_IOKIT_IOKITLIB_H
	kern_return_t status;

	if (io_master_port != MACH_PORT_NULL)
	{
		mach_port_deallocate (mach_task_self (),
				io_master_port);
		io_master_port = MACH_PORT_NULL;
	}

	status = IOMasterPort (MACH_PORT_NULL, &io_master_port);
	if (status != kIOReturnSuccess)
	{
		ERROR ("IOMasterPort failed: %s",
				mach_error_string (status));
		io_master_port = MACH_PORT_NULL;
		return (-1);
	}
/* #endif HAVE_IOKIT_IOKITLIB_H */

#elif KERNEL_LINUX
	/* do nothing */
/* #endif KERNEL_LINUX */

#elif HAVE_LIBKSTAT
	kstat_t *ksp_chain;

	numdisk = 0;

	if (kc == NULL)
		return (-1);

	for (numdisk = 0, ksp_chain = kc->kc_chain;
			(numdisk < MAX_NUMDISK) && (ksp_chain != NULL);
			ksp_chain = ksp_chain->ks_next)
	{
		if (strncmp (ksp_chain->ks_class, "disk", 4)
				&& strncmp (ksp_chain->ks_class, "partition", 9))
			continue;
		if (ksp_chain->ks_type != KSTAT_TYPE_IO)
			continue;
		ksp[numdisk++] = ksp_chain;
	}
#endif /* HAVE_LIBKSTAT */

	return (0);
}