static int srrd_create (char *filename, unsigned long pdp_step, time_t last_up,
		int argc, char **argv)
{
	int status;

	optind = 0; /* bug in librrd? */
	rrd_clear_error ();

	status = rrd_create_r (filename, pdp_step, last_up, argc, argv);

	if (status != 0)
	{
		WARNING ("rrdtool plugin: rrd_create_r (%s) failed: %s",
				filename, rrd_get_error ());
	}

	return (status);
}