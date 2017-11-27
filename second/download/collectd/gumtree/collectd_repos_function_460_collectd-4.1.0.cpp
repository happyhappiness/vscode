static int rrd_write_to_file (char *filename, char **values, int values_num)
{
	char **argv;
	int argc;
	int status;

	if (values_num < 1)
		return (0);

	argc = values_num + 2;
	argv = (char **) malloc ((argc + 1) * sizeof (char *));
	if (argv == NULL)
		return (-1);

	argv[0] = "update";
	argv[1] = filename;
	memcpy (argv + 2, values, values_num * sizeof (char *));
	argv[argc] = NULL;

	DEBUG ("rrd_update (argc = %i, argv = %p)", argc, (void *) argv);

	optind = 0; /* bug in librrd? */
	rrd_clear_error ();
	status = rrd_update (argc, argv);
	if (status != 0)
	{
		WARNING ("rrd_update failed: %s: %s",
				filename, rrd_get_error ());
		status = -1;
	}

	sfree (argv);

	return (status);
}