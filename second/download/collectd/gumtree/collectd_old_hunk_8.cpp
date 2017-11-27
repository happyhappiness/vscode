
	if (sd == -1)
		return (-1);

	if ((buflen = snprintf (buf, BUFF_SIZE, "%s %s %s", type, instance, value)) >= BUFF_SIZE)
	{
		fprintf (stderr, "Output truncated..");
		return (-1);
	}
	buf[buflen++] = '\0';

	memset(&addr, '\0', sizeof (addr));
	addr.sin_family = AF_INET;
