	{
		status_str = "OKAY";
		status_code = RET_OKAY;
	}

	printf ("%s: %g average |", status_str, average);
	for (i = 0; i < values_num; i++)
		printf (" %s=%f;;;;", values_names[i], values[i]);
	printf ("\n");

	return (status_code);
} /* int do_check_con_average */

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
		if (isnan (values[i]))
		{
			if (!nan_is_error_g)
				continue;

