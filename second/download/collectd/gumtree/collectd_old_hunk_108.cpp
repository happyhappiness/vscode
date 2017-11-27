	{
		printf ("WARNING: The first value is not defined\n");
		return (RET_WARNING);
	}

	for (i = 0; i < values_num; i++)
		if (!isnan (values[i]))
			sum += values[i];

	if (sum == 0.0)
	{
		printf ("WARNING: Values sum up to zero\n");
		return (RET_WARNING);
	}
