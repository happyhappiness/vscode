static int rrd_create_file (char *filename, const data_set_t *ds)
{
	char **argv;
	int argc;
	char **rra_def;
	int rra_num;
	char **ds_def;
	int ds_num;
	int i, j;
	char stepsize_str[16];
	int status = 0;

	if (check_create_dir (filename))
		return (-1);

	if ((rra_num = rra_get (&rra_def)) < 1)
	{
		ERROR ("rrd_create_file failed: Could not calculate RRAs");
		return (-1);
	}

	if ((ds_num = ds_get (&ds_def, ds)) < 1)
	{
		ERROR ("rrd_create_file failed: Could not calculate DSes");
		return (-1);
	}

	argc = ds_num + rra_num + 4;

	if ((argv = (char **) malloc (sizeof (char *) * (argc + 1))) == NULL)
	{
		char errbuf[1024];
		ERROR ("rrd_create failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	status = snprintf (stepsize_str, sizeof (stepsize_str),
			"%i", stepsize);
	if ((status < 1) || (status >= sizeof (stepsize_str)))
	{
		ERROR ("rrdtool plugin: snprintf failed.");
		return (-1);
	}

	argv[0] = "create";
	argv[1] = filename;
	argv[2] = "-s";
	argv[3] = stepsize_str;

	j = 4;
	for (i = 0; i < ds_num; i++)
		argv[j++] = ds_def[i];
	for (i = 0; i < rra_num; i++)
		argv[j++] = rra_def[i];
	argv[j] = NULL;

	optind = 0; /* bug in librrd? */
	rrd_clear_error ();
	if (rrd_create (argc, argv) == -1)
	{
		ERROR ("rrd_create failed: %s: %s", filename, rrd_get_error ());
		status = -1;
	}

	free (argv);
	ds_free (ds_num, ds_def);

	return (status);
}