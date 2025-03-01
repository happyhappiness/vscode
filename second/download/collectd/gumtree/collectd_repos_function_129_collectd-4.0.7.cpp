static int irq_read (void)
{
#if KERNEL_LINUX

#undef BUFSIZE
#define BUFSIZE 256

	FILE *fh;
	char buffer[BUFSIZE];
	unsigned int irq;
	unsigned int irq_value;
	long value;
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
	while (fgets (buffer, BUFSIZE, fh) != NULL)
	{
		fields_num = strsplit (buffer, fields, 64);
		if (fields_num < 2)
			continue;

		errno = 0;    /* To distinguish success/failure after call */
		irq = strtol (fields[0], &endptr, 10);

		if ((endptr == fields[0]) || (errno != 0) || (*endptr != ':'))
			continue;

		irq_value = 0;
		for (i = 1; i < fields_num; i++)
		{
			errno = 0;
			value = strtol (fields[i], &endptr, 10);

			if ((*endptr != '\0') || (errno != 0))
				break;

			irq_value += value;
		} /* for (i) */

		irq_submit (irq, irq_value);
	}
	fclose (fh);
#endif /* KERNEL_LINUX */

	return (0);
}