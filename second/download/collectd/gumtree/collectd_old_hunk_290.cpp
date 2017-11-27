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
} /* int do_check_con_sum */

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
	free (values_names); /* FIXME? */

	return (RET_UNKNOWN);
}

int main (int argc, char **argv)
{
	range_critical_g.min = NAN;
	range_critical_g.max = NAN;
	range_critical_g.invert = 0;
