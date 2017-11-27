static int rrd_create_file (char *filename, const data_set_t *ds, const value_list_t *vl)
{
	char **argv;
	int argc;
	char **rra_def;
	int rra_num;
	char **ds_def;
	int ds_num;
	int status = 0;

	if (check_create_dir (filename))
		return (-1);

	if ((rra_num = rra_get (&rra_def, vl)) < 1)
	{
		ERROR ("rrd_create_file failed: Could not calculate RRAs");
		return (-1);
	}

	if ((ds_num = ds_get (&ds_def, ds, vl)) < 1)
	{
		ERROR ("rrd_create_file failed: Could not calculate DSes");
		return (-1);
	}

	argc = ds_num + rra_num;

	if ((argv = (char **) malloc (sizeof (char *) * (argc + 1))) == NULL)
	{
		char errbuf[1024];
		ERROR ("rrd_create failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	memcpy (argv, ds_def, ds_num * sizeof (char *));
	memcpy (argv + ds_num, rra_def, rra_num * sizeof (char *));
	argv[ds_num + rra_num] = NULL;

	assert (vl->time > 10);
	status = srrd_create (filename,
			(stepsize > 0) ? stepsize : vl->interval,
			vl->time - 10,
			argc, argv);

	free (argv);
	ds_free (ds_num, ds_def);
	rra_free (rra_num, rra_def);

	return (status);
}