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
		{
			total += values[i];
			total_num++;
		}
	}

	if (total_num == 0)
		average = NAN;
	else
		average = total / total_num;
	printf ("%lf average |", average);
	for (i = 0; i < values_num; i++)
		printf (" %s=%lf;;;;", values_names[i], values[i]);

	if (total_num == 0)
		return (RET_WARNING);

	if (isnan (average)
			|| match_range (&range_critical_g, average))
		return (RET_CRITICAL);
	else if (match_range (&range_warning_g, average) != 0)
		return (RET_WARNING);

	return (RET_OKAY);
}