static int cpufreq_read (void)
{
        int status;
	unsigned long long val;
	int i = 0;
	FILE *fp;
	char filename[256];
	char buffer[16];

	for (i = 0; i < num_cpu; i++)
	{
		status = ssnprintf (filename, sizeof (filename),
				"/sys/devices/system/cpu/cpu%d/cpufreq/"
				"scaling_cur_freq", i);
		if ((status < 1) || ((unsigned int)status >= sizeof (filename)))
			return (-1);

		if ((fp = fopen (filename, "r")) == NULL)
		{
			char errbuf[1024];
			WARNING ("cpufreq: fopen (%s): %s", filename,
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
			return (-1);
		}

		if (fgets (buffer, 16, fp) == NULL)
		{
			char errbuf[1024];
			WARNING ("cpufreq: fgets: %s",
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
			fclose (fp);
			return (-1);
		}

		if (fclose (fp))
		{
			char errbuf[1024];
			WARNING ("cpufreq: fclose: %s",
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
		}


		/* You're seeing correctly: The file is reporting kHz values.. */
		val = atoll (buffer) * 1000;

		cpufreq_submit (i, val);
	}

	return (0);
}