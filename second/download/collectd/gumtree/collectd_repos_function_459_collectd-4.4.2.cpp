int do_check_con_sum (int values_num, double *values, char **values_names)
{
	int i;
	double total;
	int total_num;

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
		printf ("CRITICAL: Sum = %lf\n", total);
		return (RET_CRITICAL);
	}
	else if (match_range (&range_warning_g, total) != 0)
	{
		printf ("WARNING: Sum = %lf\n", total);
		return (RET_WARNING);
	}
	else
	{
		printf ("OKAY: Sum = %lf\n", total);
		return (RET_OKAY);
	}

	return (RET_UNKNOWN);
}