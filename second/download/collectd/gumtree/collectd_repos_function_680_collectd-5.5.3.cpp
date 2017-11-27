static int read_fork_rate (void)
{
	FILE *proc_stat;
	char buffer[1024];
	value_t value;
	_Bool value_valid = 0;

	proc_stat = fopen ("/proc/stat", "r");
	if (proc_stat == NULL)
	{
		char errbuf[1024];
		ERROR ("processes plugin: fopen (/proc/stat) failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	while (fgets (buffer, sizeof (buffer), proc_stat) != NULL)
	{
		int status;
		char *fields[3];
		int fields_num;

		fields_num = strsplit (buffer, fields,
				STATIC_ARRAY_SIZE (fields));
		if (fields_num != 2)
			continue;

		if (strcmp ("processes", fields[0]) != 0)
			continue;

		status = parse_value (fields[1], &value, DS_TYPE_DERIVE);
		if (status == 0)
			value_valid = 1;

		break;
	}
	fclose(proc_stat);

	if (!value_valid)
		return (-1);

	ps_submit_fork_rate (value.derive);
	return (0);
}