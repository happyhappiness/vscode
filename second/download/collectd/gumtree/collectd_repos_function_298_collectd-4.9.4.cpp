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
	static c_complain_t acpi_dir_complaint = C_COMPLAIN_INIT_STATIC;

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

		len = ssnprintf (filename, sizeof (filename), battery_pmu_file, i);
		if ((len < 0) || ((unsigned int)len >= sizeof (filename)))
			continue;

		len = ssnprintf (batnum_str, sizeof (batnum_str), "%i", i);
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

	if (0 == access (battery_acpi_dir, R_OK))
		walk_directory (battery_acpi_dir, battery_read_acpi,
				/* user_data = */ NULL);
	else
	{
		char errbuf[1024];
		c_complain_once (LOG_WARNING, &acpi_dir_complaint,
				"battery plugin: Failed to access `%s': %s",
				battery_acpi_dir,
				sstrerror (errno, errbuf, sizeof (errbuf)));
	}

#endif /* KERNEL_LINUX */

	return (0);
}