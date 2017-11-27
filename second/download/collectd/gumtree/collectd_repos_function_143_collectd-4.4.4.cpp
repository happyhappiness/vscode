static int init (void)
{
#if PROCESSOR_CPU_LOAD_INFO || PROCESSOR_TEMPERATURE
	kern_return_t status;

	port_host = mach_host_self ();

	/* FIXME: Free `cpu_list' if it's not NULL */
	if ((status = host_processors (port_host, &cpu_list, &cpu_list_len)) != KERN_SUCCESS)
	{
		ERROR ("cpu plugin: host_processors returned %i", (int) status);
		cpu_list_len = 0;
		return (-1);
	}

	DEBUG ("host_processors returned %i %s", (int) cpu_list_len, cpu_list_len == 1 ? "processor" : "processors");
	INFO ("cpu plugin: Found %i processor%s.", (int) cpu_list_len, cpu_list_len == 1 ? "" : "s");

	cpu_temp_retry_max = 86400 / interval_g;
/* #endif PROCESSOR_CPU_LOAD_INFO */

#elif defined(HAVE_LIBKSTAT)
	kstat_t *ksp_chain;

	numcpu = 0;

	if (kc == NULL)
		return (-1);

	/* Solaris doesn't count linear.. *sigh* */
	for (numcpu = 0, ksp_chain = kc->kc_chain;
			(numcpu < MAX_NUMCPU) && (ksp_chain != NULL);
			ksp_chain = ksp_chain->ks_next)
		if (strncmp (ksp_chain->ks_module, "cpu_stat", 8) == 0)
			ksp[numcpu++] = ksp_chain;
/* #endif HAVE_LIBKSTAT */

#elif defined (HAVE_SYSCTLBYNAME)
	size_t numcpu_size;

	numcpu_size = sizeof (numcpu);

	if (sysctlbyname ("hw.ncpu", &numcpu, &numcpu_size, NULL, 0) < 0)
	{
		char errbuf[1024];
		WARNING ("cpu plugin: sysctlbyname: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	if (numcpu != 1)
		NOTICE ("cpu: Only one processor supported when using `sysctlbyname' (found %i)", numcpu);
/* #endif HAVE_SYSCTLBYNAME */

#elif defined(HAVE_LIBSTATGRAB)
	/* nothing to initialize */
#endif /* HAVE_LIBSTATGRAB */

	return (0);
}