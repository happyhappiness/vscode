static int cpufreq_init (void)
{
        int status;
	char filename[256];

	num_cpu = 0;

	while (1)
	{
		status = ssnprintf (filename, sizeof (filename),
				"/sys/devices/system/cpu/cpu%d/cpufreq/"
				"scaling_cur_freq", num_cpu);
		if ((status < 1) || ((unsigned int)status >= sizeof (filename)))
			break;

		if (access (filename, R_OK))
			break;

		num_cpu++;
	}

	INFO ("cpufreq plugin: Found %d CPU%s", num_cpu,
			(num_cpu == 1) ? "" : "s");

	if (num_cpu == 0)
		plugin_unregister_read ("cpufreq");

	return (0);
}