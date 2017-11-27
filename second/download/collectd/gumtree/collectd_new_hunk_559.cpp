
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
} /* int do_check_con_none */

static int do_check_con_average (size_t values_num,
		double *values, char **values_names)
{
	double total;
	int total_num;
	double average;
	const char *status_str = "UNKNOWN";
	int status_code = RET_UNKNOWN;

	total = 0.0;
	total_num = 0;
	for (size_t i = 0; i < values_num; i++)
	{
		if (isnan (values[i]))
		{
			if (!nan_is_error_g)
				continue;

