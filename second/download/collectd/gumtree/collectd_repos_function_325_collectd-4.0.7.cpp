int do_check (void)
{
	double  *values;
	char   **values_names;
	int      values_num;

	if (get_values (&values_num, &values, &values_names) != 0)
	{
		fputs ("ERROR: Cannot get values from daemon\n", stdout);
		return (RET_CRITICAL);
	}

	if (consolitation_g == CON_NONE)
		return (do_check_con_none (values_num, values, values_names));
	else if (consolitation_g == CON_AVERAGE)
		return (do_check_con_average (values_num, values, values_names));
	else if (consolitation_g == CON_SUM)
		return (do_check_con_sum (values_num, values, values_names));

	free (values);
	free (values_names);

	return (RET_UNKNOWN);
}