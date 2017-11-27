static int battery_read_acpi (const char *dir, const char *name,
		void *user_data)
{
	double  current = INVALID_VALUE;
	double  voltage = INVALID_VALUE;
	double  charge  = INVALID_VALUE;
	double *valptr = NULL;
	int charging = 0;

	char filename[256];
	FILE *fh;

	char buffer[1024];
	char *fields[8];
	int numfields;
	char *endptr;
	int len;

	len = ssnprintf (filename, sizeof (filename), "%s/%s/state", battery_acpi_dir, name);

	if ((len < 0) || ((unsigned int)len >= sizeof (filename)))
		return -1;

	if ((fh = fopen (filename, "r")) == NULL) {
		char errbuf[1024];
		ERROR ("Cannot open `%s': %s", filename,
			sstrerror (errno, errbuf, sizeof (errbuf)));
		return -1;
	}

	/*
	 * [11:00] <@tokkee> $ cat /proc/acpi/battery/BAT1/state
	 * [11:00] <@tokkee> present:                 yes
	 * [11:00] <@tokkee> capacity state:          ok
	 * [11:00] <@tokkee> charging state:          charging
	 * [11:00] <@tokkee> present rate:            1724 mA
	 * [11:00] <@tokkee> remaining capacity:      4136 mAh
	 * [11:00] <@tokkee> present voltage:         12428 mV
	 */
	while (fgets (buffer, sizeof (buffer), fh) != NULL)
	{
		numfields = strsplit (buffer, fields, 8);

		if (numfields < 3)
			continue;

		if ((strcmp (fields[0], "charging") == 0)
				&& (strcmp (fields[1], "state:") == 0))
		{
			if (strcmp (fields[2], "charging") == 0)
				charging = 1;
			else
				charging = 0;
			continue;
		}

		if ((strcmp (fields[0], "present") == 0)
				&& (strcmp (fields[1], "rate:") == 0))
			valptr = &current;
		else if ((strcmp (fields[0], "remaining") == 0)
				&& (strcmp (fields[1], "capacity:") == 0))
			valptr = &charge;
		else if ((strcmp (fields[0], "present") == 0)
				&& (strcmp (fields[1], "voltage:") == 0))
			valptr = &voltage;
		else
			continue;

		endptr = NULL;
		errno  = 0;
		*valptr = strtod (fields[2], &endptr) / 1000.0;

		if ((fields[2] == endptr) || (errno != 0))
			*valptr = INVALID_VALUE;
	} /* while (fgets (buffer, sizeof (buffer), fh) != NULL) */

	fclose (fh);

	if ((current != INVALID_VALUE) && (charging == 0))
			current *= -1;

	if (charge != INVALID_VALUE)
		battery_submit ("0", "charge", charge);
	if (current != INVALID_VALUE)
		battery_submit ("0", "current", current);
	if (voltage != INVALID_VALUE)
		battery_submit ("0", "voltage", voltage);

	return 0;
}