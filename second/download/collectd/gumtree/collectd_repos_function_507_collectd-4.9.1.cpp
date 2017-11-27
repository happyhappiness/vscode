static unsigned long read_fork_rate ()
{
	FILE *proc_stat;
	char buf[1024];
	unsigned long result = 0;
	int numfields;
	char *fields[3];

	proc_stat = fopen("/proc/stat", "r");
	if (proc_stat == NULL) {
		char errbuf[1024];
		ERROR ("processes plugin: fopen (/proc/stat) failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return ULONG_MAX;
	}

	while (fgets (buf, sizeof(buf), proc_stat) != NULL)
	{
		char *endptr;

		numfields = strsplit(buf, fields, STATIC_ARRAY_SIZE (fields));
		if (numfields != 2)
			continue;

		if (strcmp ("processes", fields[0]) != 0)
			continue;

		errno = 0;
		endptr = NULL;
		result = strtoul(fields[1], &endptr, 10);
		if ((endptr == fields[1]) || (errno != 0)) {
			ERROR ("processes plugin: Cannot parse fork rate: %s",
					fields[1]);
			result = ULONG_MAX;
			break;
		}

		break;
	}

	fclose(proc_stat);

	return result;
}