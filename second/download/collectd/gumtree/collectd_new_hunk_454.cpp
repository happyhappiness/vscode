	freeaddrinfo (ai_list);
	return (0);
} /* int init_hostname */

static int init_global_variables (void)
{
	char const *str;

	interval_g = cf_get_default_interval ();
	assert (interval_g > 0);
	DEBUG ("interval_g = %.3f;", CDTIME_T_TO_DOUBLE (interval_g));

	str = global_option_get ("Timeout");
	if (str == NULL)
		str = "2";
	timeout_g = atoi (str);
