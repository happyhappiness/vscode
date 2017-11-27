	{
		printf ("WARNING: The first value is not defined\n");
		return (RET_WARNING);
	}

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

		sum += values[i];
	}

	if (sum == 0.0)
	{
		printf ("WARNING: Values sum up to zero\n");
		return (RET_WARNING);
	}
