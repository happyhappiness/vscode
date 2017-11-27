static int do_check_con_average (size_t values_num,
		double *values, char **values_names)
{
	size_t i;
	double total;
	int total_num;
	double average;
	const char *status_str = "UNKNOWN";
	int status_code = RET_UNKNOWN;

	total = 0.0;
	total_num = 0;
	for (i = 0; i < values_num; i++)
	{
		if (isnan (values[i]))
		{
			if (!nan_is_error_g)
				continue;

			printf ("CRITICAL: Data source \"%s\" is NaN\n",
					values_names[i]);
			return (RET_CRITICAL);
		}

		total += values[i];
		total_num++;
	}

	if (total_num == 0)
	{
		printf ("WARNING: No defined values found\n");
		return (RET_WARNING);
	}

	average = total / total_num;

	if (match_range (&range_critical_g, average) != 0)
	{
		status_str = "CRITICAL";
		status_code = RET_CRITICAL;
	}
	else if (match_range (&range_warning_g, average) != 0)
	{
		status_str = "WARNING";
		status_code = RET_WARNING;
	}
	else
	{
		status_str = "OKAY";
		status_code = RET_OKAY;
	}

	printf ("%s: %g average |", status_str, average);
	for (i = 0; i < values_num; i++)
		printf (" %s=%f;;;;", values_names[i], values[i]);
	printf ("\n");

	return (status_code);
}