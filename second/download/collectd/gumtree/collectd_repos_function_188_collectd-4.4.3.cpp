static int battery_read (void)
{
#if HAVE_IOKIT_IOKITLIB_H || HAVE_IOKIT_PS_IOPOWERSOURCES_H
	double charge  = INVALID_VALUE; /* Current charge in Ah */
	double current = INVALID_VALUE; /* Current in A */
	double voltage = INVALID_VALUE; /* Voltage in V */

	double charge_rel = INVALID_VALUE; /* Current charge in percent */
	double charge_abs = INVALID_VALUE; /* Total capacity */

#if HAVE_IOKIT_PS_IOPOWERSOURCES_H
	get_via_io_power_sources (&charge_rel, &current, &voltage);
#endif
#if HAVE_IOKIT_IOKITLIB_H
	get_via_generic_iokit (&charge_abs, &current, &voltage);
#endif

	if ((charge_rel != INVALID_VALUE) && (charge_abs != INVALID_VALUE))
		charge = charge_abs * charge_rel / 100.0;

	if (charge != INVALID_VALUE)
		battery_submit ("0", "charge", charge);
	if (current != INVALID_VALUE)
		battery_submit ("0", "current", current);
	if (voltage != INVALID_VALUE)
		battery_submit ("0", "voltage", voltage);
/* #endif HAVE_IOKIT_IOKITLIB_H || HAVE_IOKIT_PS_IOPOWERSOURCES_H */

#elif KERNEL_LINUX
	FILE *fh;
	char buffer[1024];
	char filename[256];
	
	char *fields[8];
	int numfields;

	int i;
	int len;

	for (i = 0; i < battery_pmu_num; i++)
	{
		char    batnum_str[256];
		double  current = INVALID_VALUE;
		double  voltage = INVALID_VALUE;
		double  charge  = INVALID_VALUE;
		double *valptr = NULL;

		len = snprintf (filename, sizeof (filename), battery_pmu_file, i);
		if ((len < 0) || ((unsigned int)len >= sizeof (filename)))
			continue;

		len = snprintf (batnum_str, sizeof (batnum_str), "%i", i);
		if ((len < 0) || ((unsigned int)len >= sizeof (batnum_str)))
			continue;

		if ((fh = fopen (filename, "r")) == NULL)
			continue;

		while (fgets (buffer, sizeof (buffer), fh) != NULL)
		{
			numfields = strsplit (buffer, fields, 8);

			if (numfields < 3)
				continue;

			if (strcmp ("current", fields[0]) == 0)
				valptr = &current;
			else if (strcmp ("voltage", fields[0]) == 0)
				valptr = &voltage;
			else if (strcmp ("charge", fields[0]) == 0)
				valptr = &charge;
			else
				valptr = NULL;

			if (valptr != NULL)
			{
				char *endptr;

				endptr = NULL;
				errno  = 0;

				*valptr = strtod (fields[2], &endptr) / 1000.0;

				if ((fields[2] == endptr) || (errno != 0))
					*valptr = INVALID_VALUE;
			}
		}

		fclose (fh);
		fh = NULL;

		if (charge != INVALID_VALUE)
			battery_submit ("0", "charge", charge);
		if (current != INVALID_VALUE)
			battery_submit ("0", "current", current);
		if (voltage != INVALID_VALUE)
			battery_submit ("0", "voltage", voltage);
	}

	if (access ("/proc/acpi/battery", R_OK | X_OK) == 0)
	{
		double  current = INVALID_VALUE;
		double  voltage = INVALID_VALUE;
		double  charge  = INVALID_VALUE;
		double *valptr = NULL;
		int charging = 0;

		struct dirent *ent;
		DIR *dh;

		if ((dh = opendir ("/proc/acpi/battery")) == NULL)
		{
			char errbuf[1024];
			ERROR ("Cannot open `/proc/acpi/battery': %s",
					sstrerror (errno, errbuf, sizeof (errbuf)));
			return (-1);
		}

		while ((ent = readdir (dh)) != NULL)
		{
			if (ent->d_name[0] == '.')
				continue;

			len = snprintf (filename, sizeof (filename),
					"/proc/acpi/battery/%s/state",
					ent->d_name);
			if ((len < 0) || ((unsigned int)len >= sizeof (filename)))
				continue;

			if ((fh = fopen (filename, "r")) == NULL)
			{
				char errbuf[1024];
				ERROR ("Cannot open `%s': %s", filename,
						sstrerror (errno, errbuf,
							sizeof (errbuf)));
				continue;
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
					valptr = NULL;

				if ((strcmp (fields[0], "charging") == 0)
						&& (strcmp (fields[1], "state:") == 0))
				{
					if (strcmp (fields[2], "charging") == 0)
						charging = 1;
					else
						charging = 0;
				}

				if (valptr != NULL)
				{
					char *endptr;

					endptr = NULL;
					errno  = 0;

					*valptr = strtod (fields[2], &endptr) / 1000.0;

					if ((fields[2] == endptr) || (errno != 0))
						*valptr = INVALID_VALUE;
				}
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
		}

		closedir (dh);
	}
#endif /* KERNEL_LINUX */

	return (0);
}