		else if (match_range (&range_warning_g, values[i]) != 0)
			num_warning++;
		else
			num_okay++;
	}

	printf ("%i critical, %i warning, %i okay",
			num_critical, num_warning, num_okay);
	if (values_num > 0)
	{
		printf (" |");
		for (i = 0; i < values_num; i++)
			printf (" %s=%lf;;;;", values_names[i], values[i]);
	}
	printf ("\n");

	if ((num_critical != 0) || (values_num == 0))
		return (RET_CRITICAL);
	else if (num_warning != 0)
		return (RET_WARNING);

	return (RET_OKAY);
} /* int do_check_con_none */

int do_check_con_average (int values_num, double *values, char **values_names)
{
	int i;
	double total;
	int total_num;
	double average;

	total = 0.0;
	total_num = 0;
	for (i = 0; i < values_num; i++)
	{
		if (!isnan (values[i]))
