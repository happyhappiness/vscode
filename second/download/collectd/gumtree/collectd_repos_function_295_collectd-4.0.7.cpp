static int serial_read (void)
{
#ifdef KERNEL_LINUX
	FILE *fh;
	char buffer[1024];

	counter_t rx = 0;
	counter_t tx = 0;
	
	char *fields[16];
	int i, numfields;
	int len;

	/* there are a variety of names for the serial device */
	if ((fh = fopen ("/proc/tty/driver/serial", "r")) == NULL &&
		(fh = fopen ("/proc/tty/driver/ttyS", "r")) == NULL)
	{
		char errbuf[1024];
		WARNING ("serial: fopen: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	while (fgets (buffer, sizeof (buffer), fh) != NULL)
	{
		int have_rx = 0, have_tx = 0;

		numfields = strsplit (buffer, fields, 16);

		if (numfields < 6)
			continue;

		/*
		 * 0: uart:16550A port:000003F8 irq:4 tx:0 rx:0
		 * 1: uart:16550A port:000002F8 irq:3 tx:0 rx:0
		 */
		len = strlen (fields[0]) - 1;
		if (len < 1)
			continue;
		if (fields[0][len] != ':')
			continue;
		fields[0][len] = '\0';

		for (i = 1; i < numfields; i++)
		{
			len = strlen (fields[i]);
			if (len < 4)
				continue;

			if (strncmp (fields[i], "tx:", 3) == 0)
			{
				tx = atoll (fields[i] + 3);
				have_tx++;
			}
			else if (strncmp (fields[i], "rx:", 3) == 0)
			{
				rx = atoll (fields[i] + 3);
				have_rx++;
			}
		}

		if ((have_rx == 0) || (have_tx == 0))
			continue;

		serial_submit (fields[0], rx, tx);
	}

	fclose (fh);
	return (0);
#endif /* KERNEL_LINUX */
}