			total += values[i];
			total_num++;
		}
	}

	if (total_num == 0)
	{
		printf ("WARNING: No defined values found\n");
		return (RET_WARNING);
	}

	if (match_range (&range_critical_g, total / total_num) != 0)
	{
		printf ("CRITICAL: Average = %lf\n",
				(double) (total / total_num));
		return (RET_CRITICAL);
	}
	else if (match_range (&range_warning_g, total / total_num) != 0)
	{
		printf ("WARNING: Average = %lf\n",
				(double) (total / total_num));
		return (RET_WARNING);
	}
	else
	{
		printf ("OKAY: Average = %lf\n",
				(double) (total / total_num));
		return (RET_OKAY);
	}

	return (RET_UNKNOWN);
} /* int do_check_con_average */

int do_check_con_sum (int values_num, double *values, char **values_names)
{
	int i;
	double total;
