static procstat_t *ps_read_status (long pid, procstat_t *ps)
{
	FILE *fh;
	char buffer[1024];
	char filename[64];
	unsigned long lib = 0;
	unsigned long exe = 0;
	unsigned long data = 0;
	unsigned long threads = 0;
	char *fields[8];
	int numfields;

	ssnprintf (filename, sizeof (filename), "/proc/%li/status", pid);
	if ((fh = fopen (filename, "r")) == NULL)
		return (NULL);

	while (fgets (buffer, sizeof(buffer), fh) != NULL)
	{
		unsigned long tmp;
		char *endptr;

		if (strncmp (buffer, "Vm", 2) != 0
				&& strncmp (buffer, "Threads", 7) != 0)
			continue;

		numfields = strsplit (buffer, fields,
				STATIC_ARRAY_SIZE (fields));

		if (numfields < 2)
			continue;

		errno = 0;
		endptr = NULL;
		tmp = strtoul (fields[1], &endptr, /* base = */ 10);
		if ((errno == 0) && (endptr != fields[1]))
		{
			if (strncmp (buffer, "VmData", 6) == 0)
			{
				data = tmp;
			}
			else if (strncmp (buffer, "VmLib", 5) == 0)
			{
				lib = tmp;
			}
			else if  (strncmp(buffer, "VmExe", 5) == 0)
			{
				exe = tmp;
			}
			else if  (strncmp(buffer, "Threads", 7) == 0)
			{
				threads = tmp;
			}
		}
	} /* while (fgets) */

	if (fclose (fh))
	{
		char errbuf[1024];
		WARNING ("processes: fclose: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
	}

	ps->vmem_data = data * 1024;
	ps->vmem_code = (exe + lib) * 1024;
	if (threads != 0)
		ps->num_lwp = threads;

	return (ps);
}