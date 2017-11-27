static int irq_read (void)
{
	FILE *fh;
	char buffer[1024];

	fh = fopen ("/proc/interrupts", "r");
	if (fh == NULL)
	{
		char errbuf[1024];
		ERROR ("irq plugin: fopen (/proc/interrupts): %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	while (fgets (buffer, sizeof (buffer), fh) != NULL)
	{
		char *irq_name;
		size_t irq_name_len;
		derive_t irq_value;
		int i;

		char *fields[64];
		int fields_num;

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
			/* Per-CPU value */
			value_t v;
			int status;

			status = parse_value (fields[i], &v, DS_TYPE_DERIVE);
			if (status != 0)
				break;

			irq_value += v.derive;
		} /* for (i) */

		/* No valid fields -> do not submit anything. */
		if (i <= 1)
			continue;

		irq_submit (irq_name, irq_value);
	}

	fclose (fh);

	return (0);
}