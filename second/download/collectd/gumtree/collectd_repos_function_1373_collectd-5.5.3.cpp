static int uptime_init (void) /* {{{ */
{
	/*
	 * On most unix systems the uptime is calculated by looking at the boot
	 * time (stored in unix time, since epoch) and the current one. We are
	 * going to do the same, reading the boot time value while executing
	 * the uptime_init function (there is no need to read, every time the
	 * plugin_read is called, a value that won't change). However, since
	 * uptime_init is run only once, if the function fails in retrieving
	 * the boot time, the plugin is unregistered and there is no chance to
	 * try again later. Nevertheless, this is very unlikely to happen.
	 */

#if KERNEL_LINUX
	unsigned long starttime;
	char buffer[1024];
	int ret;
	FILE *fh;

	ret = 0;

	fh = fopen (STAT_FILE, "r");

	if (fh == NULL)
	{
		char errbuf[1024];
		ERROR ("uptime plugin: Cannot open "STAT_FILE": %s",
			sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	while (fgets (buffer, 1024, fh) != NULL)
	{
		/* look for the btime string and read the value */
		ret = sscanf (buffer, "btime %lu", &starttime);
		/* avoid further loops if btime has been found and read
		 * correctly (hopefully) */
		if (ret == 1)
			break;
	}

	fclose (fh);

	/* loop done, check if no value has been found/read */
	if (ret != 1)
	{
		ERROR ("uptime plugin: No value read from "STAT_FILE"");
		return (-1);
	}

	boottime = (time_t) starttime;

	if (boottime == 0)
	{
		ERROR ("uptime plugin: btime read from "STAT_FILE", "
				"but `boottime' is zero!");
		return (-1);
	}
/* #endif KERNEL_LINUX */

#elif HAVE_LIBKSTAT
	kstat_t *ksp;
	kstat_named_t *knp;

	ksp = NULL;
	knp = NULL;

	/* kstats chain already opened by update_kstat (using *kc), verify everything went fine. */
	if (kc == NULL)
	{
		ERROR ("uptime plugin: kstat chain control structure not available.");
		return (-1);
	}

	ksp = kstat_lookup (kc, "unix", 0, "system_misc");
	if (ksp == NULL)
	{
		ERROR ("uptime plugin: Cannot find unix:0:system_misc kstat.");
		return (-1);
	}

	if (kstat_read (kc, ksp, NULL) < 0)
	{
		ERROR ("uptime plugin: kstat_read failed.");
		return (-1);
	}

	knp = (kstat_named_t *) kstat_data_lookup (ksp, "boot_time");
	if (knp == NULL)
	{
		ERROR ("uptime plugin: kstat_data_lookup (boot_time) failed.");
		return (-1);
	}

	boottime = (time_t) knp->value.ui32;

	if (boottime == 0)
	{
		ERROR ("uptime plugin: kstat_data_lookup returned success, "
			"but `boottime' is zero!");
		return (-1);
	}
/* #endif HAVE_LIBKSTAT */

# elif HAVE_SYS_SYSCTL_H
	struct timeval boottv;
	size_t boottv_len;
	int status;

	int mib[2];

	mib[0] = CTL_KERN;
	mib[1] = KERN_BOOTTIME;

	boottv_len = sizeof (boottv);
	memset (&boottv, 0, boottv_len);

	status = sysctl (mib, STATIC_ARRAY_SIZE (mib), &boottv, &boottv_len,
			/* new_value = */ NULL, /* new_length = */ 0);
	if (status != 0)
	{
		char errbuf[1024];
		ERROR ("uptime plugin: No value read from sysctl interface: %s",
			sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	boottime = boottv.tv_sec;

	if (boottime == 0)
	{
		ERROR ("uptime plugin: sysctl(3) returned success, "
				"but `boottime' is zero!");
		return (-1);
	}
/* #endif HAVE_SYS_SYSCTL_H */

#elif HAVE_PERFSTAT
	int status;
	perfstat_cpu_total_t cputotal;
	int hertz;

	status = perfstat_cpu_total(NULL, &cputotal,
		sizeof(perfstat_cpu_total_t), 1);
	if (status < 0)
	{
		char errbuf[1024];
		ERROR ("uptime plugin: perfstat_cpu_total: %s",
			sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	hertz = sysconf(_SC_CLK_TCK);
	if (hertz <= 0)
		hertz = HZ;

	boottime = time(NULL) - cputotal.lbolt / hertz;
#endif /* HAVE_PERFSTAT */

	return (0);
}