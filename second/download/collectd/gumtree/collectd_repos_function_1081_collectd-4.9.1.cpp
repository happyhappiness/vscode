static int hddtemp_read (void)
{
	char buf[1024];
	char *fields[128];
	char *ptr;
	char *saveptr;
	int num_fields;
	int num_disks;
	int i;

	/* get data from daemon */
	if (hddtemp_query_daemon (buf, sizeof (buf)) < 0)
		return (-1);

	/* NB: strtok_r will eat up "||" and leading "|"'s */
	num_fields = 0;
	ptr = buf;
	saveptr = NULL;
	while ((fields[num_fields] = strtok_r (ptr, "|", &saveptr)) != NULL)
	{
		ptr = NULL;
		num_fields++;

		if (num_fields >= 128)
			break;
	}

	num_disks = num_fields / 4;

	for (i = 0; i < num_disks; i++)
	{
		char *name, *major_minor;
		double temperature;
		char *mode;

		mode = fields[4*i + 3];
		name = basename (fields[4*i + 0]);

		/* Skip non-temperature information */
		if (mode[0] != 'C' && mode[0] != 'F')
			continue;

		temperature = atof (fields[4*i + 2]);

		/* Convert farenheit to celsius */
		if (mode[0] == 'F')
			temperature = (temperature - 32.0) * 5.0 / 9.0;

		if (translate_devicename
				&& (major_minor = hddtemp_get_major_minor (name)) != NULL)
		{
			hddtemp_submit (major_minor, temperature);
			free (major_minor);
		}
		else
		{
			hddtemp_submit (name, temperature);
		}
	}
	
	return (0);
}