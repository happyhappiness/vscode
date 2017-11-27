			"  percentage:    Apply the ranges to the ratio (in percent) of the first value\n"
			"                 and the sum of all values."
			"\n", name);
	exit (1);
} /* void usage */

static int do_check_con_none (size_t values_num,
		double *values, char **values_names)
{
	int num_critical = 0;
	int num_warning  = 0;
	int num_okay = 0;
