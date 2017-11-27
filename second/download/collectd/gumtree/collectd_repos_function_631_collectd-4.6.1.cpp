static int do_check_con_percentage (size_t values_num,
		double *values, char **values_names)
{
	size_t i;
	double sum = 0.0;
	double percentage;

	const char *status_str  = "UNKNOWN";
	int         status_code = RET_UNKNOWN;

	if ((values_num < 1) || (isnan (values[0])))
	{
		printf ("WARNING: The first value is not defined\n");
		return (RET_WARNING);
	}

	for (i = 0; i < values_num; i++)
		if (!isnan (values[i]))
			sum += values[i];

	if (sum == 0.0)
	{
		printf ("WARNING: Values sum up to zero\n");
		return (RET_WARNING);
	}

	percentage = 100.0 * values[0] / sum;

	if (match_range (&range_critical_g, percentage) != 0)
	{
		status_str  = "CRITICAL";
		status_code = RET_CRITICAL;
	}
	else if (match_range (&range_warning_g, percentage) != 0)
	{
		status_str  = "WARNING";
		status_code = RET_WARNING;
	}
	else
	{
		status_str  = "OKAY";
		status_code = RET_OKAY;
	}

	printf ("%s: %lf percent |", status_str, percentage);
	for (i = 0; i < values_num; i++)
		printf (" %s=%lf;;;;", values_names[i], values[i]);
	return (status_code);
}