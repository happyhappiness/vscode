static int cs_read (void)
{
	FILE *fh;
	char buffer[64];
	int numfields;
	char *fields[3];
	derive_t result = 0;
	int status = -2;

	fh = fopen ("/proc/stat", "r");
	if (fh == NULL) {
		ERROR ("contextswitch plugin: unable to open /proc/stat: %s",
				sstrerror (errno, buffer, sizeof (buffer)));
		return (-1);
	}

	while (fgets(buffer, sizeof(buffer), fh) != NULL)
	{
		char *endptr;

		numfields = strsplit(buffer, fields, STATIC_ARRAY_SIZE (fields));
		if (numfields != 2)
			continue;

		if (strcmp("ctxt", fields[0]) != 0)
			continue;

		errno = 0;
		endptr = NULL;
		result = (derive_t) strtoll (fields[1], &endptr, /* base = */ 10);
		if ((endptr == fields[1]) || (errno != 0)) {
			ERROR ("contextswitch plugin: Cannot parse ctxt value: %s",
					fields[1]);
			status = -1;
			break;
		}

		cs_submit(result);
		status = 0;
		break;
	}
	fclose(fh);

	if (status == -2)
		ERROR ("contextswitch plugin: Unable to find context switch value.");

	return status;
}