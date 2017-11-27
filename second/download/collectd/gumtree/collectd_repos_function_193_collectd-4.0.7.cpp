static int wireless_read (void)
{
#ifdef KERNEL_LINUX
	FILE *fh;
	char buffer[1024];

	char   *device;
	double  quality;
	double  power;
	double  noise;
	
	char *fields[8];
	int   numfields;

	int devices_found;
	int len;

	/* there are a variety of names for the wireless device */
	if ((fh = fopen (WIRELESS_PROC_FILE, "r")) == NULL)
	{
		char errbuf[1024];
		WARNING ("wireless: fopen: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	devices_found = 0;
	while (fgets (buffer, sizeof (buffer), fh) != NULL)
	{
		numfields = strsplit (buffer, fields, 8);

		if (numfields < 5)
			continue;

		len = strlen (fields[0]) - 1;
		if (len < 1)
			continue;
		if (fields[0][len] != ':')
			continue;
		fields[0][len] = '\0';

		device  = fields[0];
		quality = atof (fields[2]);
		power   = atof (fields[3]);
		noise   = atof (fields[4]);

		/* Fill in invalid values when conversion failed.. */
		if (quality == 0.0)
			quality = -1.0; /* quality >= 0 */

		if (power == 0.0)
			power = 1.0; /* power <= 0 */

		if (noise == 0.0)
			noise = 1.0; /* noise <= 0 */

		wireless_submit (device, "signal_quality", quality);
		wireless_submit (device, "signal_power", power);
		wireless_submit (device, "signal_noise", noise);

		devices_found++;
	}

	fclose (fh);

	/* If no wireless devices are present return an error, so the plugin
	 * code delays our read function. */
	if (devices_found == 0)
		return (-1);
#endif /* KERNEL_LINUX */

	return (0);
}