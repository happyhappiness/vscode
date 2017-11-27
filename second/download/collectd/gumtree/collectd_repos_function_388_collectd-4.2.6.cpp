int do_check_con_none (int values_num, double *values, char **values_names)
{
	int i;

	int num_critical = 0;
	int num_warning  = 0;
	int num_okay = 0;

	for (i = 0; i < values_num; i++)
	{
		if (isnan (values[i]))
			num_warning++;
		else if (match_range (&range_critical_g, values[i]) != 0)
			num_critical++;
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
}