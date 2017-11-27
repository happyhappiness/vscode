static int rrd_write_cache_entry (const char *filename, rrd_cache_t *rc)
{
	char **argv;
	int    argc;

	char *fn;
	int status;

	int i;

	if (rc->values_num < 1)
		return (0);

	argc = rc->values_num + 2;
	argv = (char **) malloc ((argc + 1) * sizeof (char *));
	if (argv == NULL)
		return (-1);

	fn = strdup (filename);
	if (fn == NULL)
	{
		free (argv);
		return (-1);
	}

	argv[0] = "update";
	argv[1] = fn;
	memcpy (argv + 2, rc->values, rc->values_num * sizeof (char *));
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

	free (argv);
	free (fn);
	/* Free the value list of `rc' */
	for (i = 0; i < rc->values_num; i++)
		free (rc->values[i]);
	free (rc->values);
	rc->values = NULL;
	rc->values_num = 0;

	return (status);
}