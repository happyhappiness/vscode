
static void sigTermHandler (int signal)
{
	loop++;
}

static int init_global_variables (void)
{
	const char *str;

	str = global_option_get ("Hostname");
	if (str != NULL)
	{
		strncpy (hostname_g, str, sizeof (hostname_g));
	}
	else
	{
		if (gethostname (hostname_g, sizeof (hostname_g)) != 0)
		{
			fprintf (stderr, "`gethostname' failed and no "
					"hostname was configured.\n");
			return (-1);
		}
	}
	DEBUG ("hostname_g = %s;", hostname_g);

	str = global_option_get ("Interval");
	if (str == NULL)
		str = "10";
	interval_g = atoi (str);
	if (interval_g <= 0)
