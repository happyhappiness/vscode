static int do_check_con_sum (size_t values_num,
		double *values, char **values_names)
{
	size_t i;
	double total;
	int total_num;
	const char *status_str = "UNKNOWN";
	int status_code = RET_UNKNOWN;

	total = 0.0;
	total_num = 0;
	for (i = 0; i < values_num; i++)
	{
		if (!isnan (values[i]))
		{
			total += values[i];
			total_num++;
		}
	}

	if (total_num == 0)
	{
		printf ("WARNING: No defined values found\n");
		return (RET_WARNING);
	}

	if (match_range (&range_critical_g, total) != 0)
	{
		status_str = "CRITICAL";
		status_code = RET_CRITICAL;
	}
	else if (match_range (&range_warning_g, total) != 0)
	{
		status_str = "WARNING";
		status_code = RET_WARNING;
	}
	else
	{
		status_str = "OKAY";
		status_code = RET_OKAY;
	}

	printf ("%s: %g sum |", status_str, total);
	for (i = 0; i < values_num; i++)
		printf (" %s=%g;;;;", values_names[i], values[i]);
	printf ("\n");

	return (status_code);
}