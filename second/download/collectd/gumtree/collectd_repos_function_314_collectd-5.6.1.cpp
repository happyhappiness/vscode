static int cpu_read (void)
{
	cdtime_t now = cdtime ();

#if PROCESSOR_CPU_LOAD_INFO /* {{{ */
	kern_return_t status;

	processor_cpu_load_info_data_t cpu_info;
	mach_msg_type_number_t         cpu_info_len;

	host_t cpu_host;

	for (mach_msg_type_number_t cpu = 0; cpu < cpu_list_len; cpu++)
	{
		cpu_host = 0;
		cpu_info_len = PROCESSOR_BASIC_INFO_COUNT;

		status = processor_info (cpu_list[cpu], PROCESSOR_CPU_LOAD_INFO, &cpu_host,
				(processor_info_t) &cpu_info, &cpu_info_len);
		if (status != KERN_SUCCESS)
		{
			ERROR ("cpu plugin: processor_info (PROCESSOR_CPU_LOAD_INFO) failed: %s",
					mach_error_string (status));
			continue;
		}

		if (cpu_info_len < CPU_STATE_MAX)
		{
			ERROR ("cpu plugin: processor_info returned only %i elements..", cpu_info_len);
			continue;
		}

		cpu_stage (cpu, COLLECTD_CPU_STATE_USER,   (derive_t) cpu_info.cpu_ticks[CPU_STATE_USER],   now);
		cpu_stage (cpu, COLLECTD_CPU_STATE_NICE,   (derive_t) cpu_info.cpu_ticks[CPU_STATE_NICE],   now);
		cpu_stage (cpu, COLLECTD_CPU_STATE_SYSTEM, (derive_t) cpu_info.cpu_ticks[CPU_STATE_SYSTEM], now);
		cpu_stage (cpu, COLLECTD_CPU_STATE_IDLE,   (derive_t) cpu_info.cpu_ticks[CPU_STATE_IDLE],   now);
	}
/* }}} #endif PROCESSOR_CPU_LOAD_INFO */

#elif defined(KERNEL_LINUX) /* {{{ */
	int cpu;
	FILE *fh;
	char buf[1024];

	char *fields[9];
	int numfields;

	if ((fh = fopen ("/proc/stat", "r")) == NULL)
	{
		char errbuf[1024];
		ERROR ("cpu plugin: fopen (/proc/stat) failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	while (fgets (buf, 1024, fh) != NULL)
	{
		if (strncmp (buf, "cpu", 3))
			continue;
		if ((buf[3] < '0') || (buf[3] > '9'))
			continue;

		numfields = strsplit (buf, fields, 9);
		if (numfields < 5)
			continue;

		cpu = atoi (fields[0] + 3);

		cpu_stage (cpu, COLLECTD_CPU_STATE_USER,   (derive_t) atoll(fields[1]), now);
		cpu_stage (cpu, COLLECTD_CPU_STATE_NICE,   (derive_t) atoll(fields[2]), now);
		cpu_stage (cpu, COLLECTD_CPU_STATE_SYSTEM, (derive_t) atoll(fields[3]), now);
		cpu_stage (cpu, COLLECTD_CPU_STATE_IDLE,   (derive_t) atoll(fields[4]), now);

		if (numfields >= 8)
		{
			cpu_stage (cpu, COLLECTD_CPU_STATE_WAIT,      (derive_t) atoll(fields[5]), now);
			cpu_stage (cpu, COLLECTD_CPU_STATE_INTERRUPT, (derive_t) atoll(fields[6]), now);
			cpu_stage (cpu, COLLECTD_CPU_STATE_SOFTIRQ,   (derive_t) atoll(fields[7]), now);

			if (numfields >= 9)
				cpu_stage (cpu, COLLECTD_CPU_STATE_STEAL, (derive_t) atoll(fields[8]), now);
		}
	}
	fclose (fh);
/* }}} #endif defined(KERNEL_LINUX) */

#elif defined(HAVE_LIBKSTAT) /* {{{ */
	static cpu_stat_t cs;

	if (kc == NULL)
		return (-1);

	for (int cpu = 0; cpu < numcpu; cpu++)
	{
		if (kstat_read (kc, ksp[cpu], &cs) == -1)
			continue; /* error message? */

		cpu_stage (ksp[cpu]->ks_instance, COLLECTD_CPU_STATE_IDLE,   (derive_t) cs.cpu_sysinfo.cpu[CPU_IDLE],   now);
		cpu_stage (ksp[cpu]->ks_instance, COLLECTD_CPU_STATE_USER,   (derive_t) cs.cpu_sysinfo.cpu[CPU_USER],   now);
		cpu_stage (ksp[cpu]->ks_instance, COLLECTD_CPU_STATE_SYSTEM, (derive_t) cs.cpu_sysinfo.cpu[CPU_KERNEL], now);
		cpu_stage (ksp[cpu]->ks_instance, COLLECTD_CPU_STATE_WAIT,   (derive_t) cs.cpu_sysinfo.cpu[CPU_WAIT],   now);
	}
/* }}} #endif defined(HAVE_LIBKSTAT) */

#elif CAN_USE_SYSCTL /* {{{ */
	uint64_t cpuinfo[numcpu][CPUSTATES];
	size_t cpuinfo_size;
	int status;

	if (numcpu < 1)
	{
		ERROR ("cpu plugin: Could not determine number of "
				"installed CPUs using sysctl(3).");
		return (-1);
	}

	memset (cpuinfo, 0, sizeof (cpuinfo));

#if defined(KERN_CPTIME2)
	if (numcpu > 1) {
		for (int i = 0; i < numcpu; i++) {
			int mib[] = {CTL_KERN, KERN_CPTIME2, i};

			cpuinfo_size = sizeof (cpuinfo[0]);

			status = sysctl (mib, STATIC_ARRAY_SIZE (mib),
					cpuinfo[i], &cpuinfo_size, NULL, 0);
			if (status == -1) {
				char errbuf[1024];
				ERROR ("cpu plugin: sysctl failed: %s.",
						sstrerror (errno, errbuf, sizeof (errbuf)));
				return (-1);
			}
		}
	}
	else
#endif /* defined(KERN_CPTIME2) */
	{
		int mib[] = {CTL_KERN, KERN_CPTIME};
		long cpuinfo_tmp[CPUSTATES];

		cpuinfo_size = sizeof(cpuinfo_tmp);

		status = sysctl (mib, STATIC_ARRAY_SIZE (mib),
					&cpuinfo_tmp, &cpuinfo_size, NULL, 0);
		if (status == -1)
		{
			char errbuf[1024];
			ERROR ("cpu plugin: sysctl failed: %s.",
					sstrerror (errno, errbuf, sizeof (errbuf)));
			return (-1);
		}

		for(int i = 0; i < CPUSTATES; i++) {
			cpuinfo[0][i] = cpuinfo_tmp[i];
		}
	}

	for (int i = 0; i < numcpu; i++) {
		cpu_stage (i, COLLECTD_CPU_STATE_USER,      (derive_t) cpuinfo[i][CP_USER], now);
		cpu_stage (i, COLLECTD_CPU_STATE_NICE,      (derive_t) cpuinfo[i][CP_NICE], now);
		cpu_stage (i, COLLECTD_CPU_STATE_SYSTEM,    (derive_t) cpuinfo[i][CP_SYS], now);
		cpu_stage (i, COLLECTD_CPU_STATE_IDLE,      (derive_t) cpuinfo[i][CP_IDLE], now);
		cpu_stage (i, COLLECTD_CPU_STATE_INTERRUPT, (derive_t) cpuinfo[i][CP_INTR], now);
	}
/* }}} #endif CAN_USE_SYSCTL */

#elif defined(HAVE_SYSCTLBYNAME) && defined(HAVE_SYSCTL_KERN_CP_TIMES) /* {{{ */
	long cpuinfo[maxcpu][CPUSTATES];
	size_t cpuinfo_size;

	memset (cpuinfo, 0, sizeof (cpuinfo));

	cpuinfo_size = sizeof (cpuinfo);
	if (sysctlbyname("kern.cp_times", &cpuinfo, &cpuinfo_size, NULL, 0) < 0)
	{
		char errbuf[1024];
		ERROR ("cpu plugin: sysctlbyname failed: %s.",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	for (int i = 0; i < numcpu; i++) {
		cpu_stage (i, COLLECTD_CPU_STATE_USER,      (derive_t) cpuinfo[i][CP_USER], now);
		cpu_stage (i, COLLECTD_CPU_STATE_NICE,      (derive_t) cpuinfo[i][CP_NICE], now);
		cpu_stage (i, COLLECTD_CPU_STATE_SYSTEM,    (derive_t) cpuinfo[i][CP_SYS], now);
		cpu_stage (i, COLLECTD_CPU_STATE_IDLE,      (derive_t) cpuinfo[i][CP_IDLE], now);
		cpu_stage (i, COLLECTD_CPU_STATE_INTERRUPT, (derive_t) cpuinfo[i][CP_INTR], now);
	}
/* }}} #endif HAVE_SYSCTL_KERN_CP_TIMES */

#elif defined(HAVE_SYSCTLBYNAME) /* {{{ */
	long cpuinfo[CPUSTATES];
	size_t cpuinfo_size;

	cpuinfo_size = sizeof (cpuinfo);

	if (sysctlbyname("kern.cp_time", &cpuinfo, &cpuinfo_size, NULL, 0) < 0)
	{
		char errbuf[1024];
		ERROR ("cpu plugin: sysctlbyname failed: %s.",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	cpu_stage (0, COLLECTD_CPU_STATE_USER,      (derive_t) cpuinfo[CP_USER], now);
	cpu_stage (0, COLLECTD_CPU_STATE_NICE,      (derive_t) cpuinfo[CP_NICE], now);
	cpu_stage (0, COLLECTD_CPU_STATE_SYSTEM,    (derive_t) cpuinfo[CP_SYS], now);
	cpu_stage (0, COLLECTD_CPU_STATE_IDLE,      (derive_t) cpuinfo[CP_IDLE], now);
	cpu_stage (0, COLLECTD_CPU_STATE_INTERRUPT, (derive_t) cpuinfo[CP_INTR], now);
/* }}} #endif HAVE_SYSCTLBYNAME */

#elif defined(HAVE_LIBSTATGRAB) /* {{{ */
	sg_cpu_stats *cs;
	cs = sg_get_cpu_stats ();

	if (cs == NULL)
	{
		ERROR ("cpu plugin: sg_get_cpu_stats failed.");
		return (-1);
	}

	cpu_state (0, COLLECTD_CPU_STATE_IDLE,   (derive_t) cs->idle);
	cpu_state (0, COLLECTD_CPU_STATE_NICE,   (derive_t) cs->nice);
	cpu_state (0, COLLECTD_CPU_STATE_SWAP,   (derive_t) cs->swap);
	cpu_state (0, COLLECTD_CPU_STATE_SYSTEM, (derive_t) cs->kernel);
	cpu_state (0, COLLECTD_CPU_STATE_USER,   (derive_t) cs->user);
	cpu_state (0, COLLECTD_CPU_STATE_WAIT,   (derive_t) cs->iowait);
/* }}} #endif HAVE_LIBSTATGRAB */

#elif defined(HAVE_PERFSTAT) /* {{{ */
	perfstat_id_t id;
	int cpus;

	numcpu =  perfstat_cpu(NULL, NULL, sizeof(perfstat_cpu_t), 0);
	if(numcpu == -1)
	{
		char errbuf[1024];
		WARNING ("cpu plugin: perfstat_cpu: %s",
			sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	if (pnumcpu != numcpu || perfcpu == NULL)
	{
		free(perfcpu);
		perfcpu = malloc(numcpu * sizeof(perfstat_cpu_t));
	}
	pnumcpu = numcpu;

	id.name[0] = '\0';
	if ((cpus = perfstat_cpu(&id, perfcpu, sizeof(perfstat_cpu_t), numcpu)) < 0)
	{
		char errbuf[1024];
		WARNING ("cpu plugin: perfstat_cpu: %s",
			sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	for (int i = 0; i < cpus; i++)
	{
		cpu_stage (i, COLLECTD_CPU_STATE_IDLE,   (derive_t) perfcpu[i].idle, now);
		cpu_stage (i, COLLECTD_CPU_STATE_SYSTEM, (derive_t) perfcpu[i].sys,  now);
		cpu_stage (i, COLLECTD_CPU_STATE_USER,   (derive_t) perfcpu[i].user, now);
		cpu_stage (i, COLLECTD_CPU_STATE_WAIT,   (derive_t) perfcpu[i].wait, now);
	}
#endif /* }}} HAVE_PERFSTAT */

	cpu_commit ();
	cpu_reset ();
	return (0);
}