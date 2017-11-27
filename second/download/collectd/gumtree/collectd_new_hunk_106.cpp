	int status_code = RET_UNKNOWN;

	total = 0.0;
	total_num = 0;
	for (i = 0; i < values_num; i++)
	{
		if (isnan (values[i]))
		{
			if (!nan_is_error_g)
				continue;

			printf ("CRITICAL: Data source \"%s\" is NaN\n",
					values_names[i]);
			return (RET_CRITICAL);
		}

		total += values[i];
		total_num++;
	}

	if (total_num == 0)
	{
		printf ("WARNING: No defined values found\n");
		return (RET_WARNING);
