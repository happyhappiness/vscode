static int init_global_variables (void)
{
	const char *str;

	str = global_option_get ("Interval");
	if (str == NULL)
		str = "10";
	interval_g = atoi (str);
	if (interval_g <= 0)
	{
		fprintf (stderr, "Cannot set the interval to a correct value.\n"
				"Please check your settings.\n");
		return (-1);
	}
	DEBUG ("interval_g = %i;", interval_g);

	str = global_option_get ("Timeout");
	if (str == NULL)
		str = "2";
	timeout_g = atoi (str);
	if (timeout_g <= 1)
