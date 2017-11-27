static int irq_read (void)
{
	FILE *fh;
	char buffer[1024];
	unsigned long long irq_value;
	unsigned long long value;
	char *endptr;
	int i;

	char *fields[64];
	int fields_num;

	if ((fh = fopen ("/proc/interrupts", "r")) == NULL)
	{
		char errbuf[1024];
		WARNING ("irq plugin: fopen (/proc/interrupts): %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}
	while (fgets (buffer, sizeof (buffer), fh) != NULL)
	{
		char *irq_name;
		size_t irq_name_len;

		fields_num = strsplit (buffer, fields, 64);
		if (fields_num < 2)
			continue;

		irq_name = fields[0];
		irq_name_len = strlen (irq_name);
		if (irq_name_len < 2)
			continue;

		/* Check if irq name ends with colon.
		 * Otherwise it's a header. */
		if (irq_name[irq_name_len - 1] != ':')
			continue;

		irq_name[irq_name_len - 1] = 0;
		irq_name_len--;

		irq_value = 0;
		for (i = 1; i < fields_num; i++)
		{
			errno = 0;
			endptr = NULL;
			value = strtoull (fields[i], &endptr, 10);

			/* Ignore all fields following a non-numeric field. */
			if ((errno != 0) || (endptr == NULL) || (*endptr != 0))
				break;

			irq_value += value;
		} /* for (i) */

		/* No valid fields -> do not submit anything. */
		if (i <= 1)
			continue;

		/* Force 32bit wrap-around */
		irq_submit (irq_name, irq_value % 4294967296ULL);
	}

	fclose (fh);

	return (0);
}