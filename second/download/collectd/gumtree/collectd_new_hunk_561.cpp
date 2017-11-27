	{
		status_str = "OKAY";
		status_code = RET_OKAY;
	}

	printf ("%s: %g sum |", status_str, total);
	for (size_t i = 0; i < values_num; i++)
		printf (" %s=%f;;;;", values_names[i], values[i]);
	printf ("\n");

	return (status_code);
} /* int do_check_con_sum */

static int do_check_con_percentage (size_t values_num,
		double *values, char **values_names)
{
	double sum = 0.0;
	double percentage;

	const char *status_str  = "UNKNOWN";
	int         status_code = RET_UNKNOWN;

	if ((values_num < 1) || (isnan (values[0])))
	{
		printf ("WARNING: The first value is not defined\n");
		return (RET_WARNING);
	}

	for (size_t i = 0; i < values_num; i++)
	{
		if (isnan (values[i]))
		{
			if (!nan_is_error_g)
				continue;

