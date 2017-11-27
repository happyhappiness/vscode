static int za_init (void) /* {{{ */
{
#if !defined(__FreeBSD__) && !defined(KERNEL_LINUX) // Solaris
	/* kstats chain already opened by update_kstat (using *kc), verify everything went fine. */
	if (kc == NULL)
	{
		ERROR ("zfs_arc plugin: kstat chain control structure not available.");
		return (-1);
	}
#endif

	return (0);
}