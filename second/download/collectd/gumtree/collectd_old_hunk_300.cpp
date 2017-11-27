
		dummy = value_copy;
		while ((ptr = strtok_r (dummy, ", \t", &saveptr)) != NULL)
		{
			dummy = NULL;
			
			tmp_alloc = realloc (rra_timespans_custom,
					sizeof (int) * (rra_timespans_custom_num + 1));
			if (tmp_alloc == NULL)
			{
				fprintf (stderr, "rrdtool: realloc failed.\n");
				ERROR ("rrdtool: realloc failed.\n");
				free (value_copy);
				return (1);
			}
			rra_timespans_custom = tmp_alloc;
			rra_timespans_custom[rra_timespans_custom_num] = atoi (ptr);
			if (rra_timespans_custom[rra_timespans_custom_num] != 0)
				rra_timespans_custom_num++;
		} /* while (strtok_r) */

		qsort (/* base = */ rra_timespans_custom,
				/* nmemb  = */ rra_timespans_custom_num,
				/* size   = */ sizeof (rra_timespans_custom[0]),
				/* compar = */ rrd_compare_numeric);

		free (value_copy);
	}
	else if (strcasecmp ("XFF", key) == 0)
	{
