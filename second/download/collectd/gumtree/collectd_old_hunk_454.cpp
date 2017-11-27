	freeaddrinfo (ai_list);
	return (0);
} /* int init_hostname */

static int init_global_variables (void)
{
	const char *str;

	str = global_option_get ("Interval");
	if (str == NULL)
	{
		interval_g = TIME_T_TO_CDTIME_T (10);
	}
	else
	{
		double tmp;

		tmp = atof (str);
		if (tmp <= 0.0)
		{
			fprintf (stderr, "Cannot set the interval to a "
					"correct value.\n"
					"Please check your settings.\n");
			return (-1);
		}

		interval_g = DOUBLE_TO_CDTIME_T (tmp);
	}
	DEBUG ("interval_g = %.3f;", CDTIME_T_TO_DOUBLE (interval_g));

	str = global_option_get ("Timeout");
	if (str == NULL)
		str = "2";
	timeout_g = atoi (str);
