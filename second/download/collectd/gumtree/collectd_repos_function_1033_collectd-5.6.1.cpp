static int do_check_con_none (size_t values_num,
		double *values, char **values_names)
{
	int num_critical = 0;
	int num_warning  = 0;
	int num_okay = 0;
	const char *status_str = "UNKNOWN";
	int status_code = RET_UNKNOWN;

	for (size_t i = 0; i < values_num; i++)
	{
		if (isnan (values[i]))
		{
			if (nan_is_error_g)
				num_critical++;
			else
				num_warning++;
		}
		else if (match_range (&range_critical_g, values[i]) != 0)
			num_critical++;
		else if (match_range (&range_warning_g, values[i]) != 0)
			num_warning++;
		else
			num_okay++;
	}

	if ((num_critical == 0) && (num_warning == 0) && (num_okay == 0))
	{
		printf ("WARNING: No defined values found\n");
		return (RET_WARNING);
	}
	else if ((num_critical == 0) && (num_warning == 0))
	{
		status_str = "OKAY";
		status_code = RET_OKAY;
	}
	else if (num_critical == 0)
	{
		status_str = "WARNING";
		status_code = RET_WARNING;
	}
	else
	{
		status_str = "CRITICAL";
		status_code = RET_CRITICAL;
	}

	printf ("%s: %i critical, %i warning, %i okay", status_str,
			num_critical, num_warning, num_okay);
	if (values_num > 0)
	{
		printf (" |");
		for (size_t i = 0; i < values_num; i++)
			printf (" %s=%f;;;;", values_names[i], values[i]);
	}
	printf ("\n");

	return (status_code);
}