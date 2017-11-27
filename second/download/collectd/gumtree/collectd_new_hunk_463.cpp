	else if (strcasecmp ("HeartBeat", key) == 0)
	{
		int temp = atoi (value);
		if (temp > 0)
			rrdcreate_config.heartbeat = temp;
	}
	else if (strcasecmp ("CreateFilesAsync", key) == 0)
	{
		if (IS_TRUE (value))
			rrdcreate_config.async = 1;
		else
			rrdcreate_config.async = 0;
	}
	else if (strcasecmp ("RRARows", key) == 0)
	{
		int tmp = atoi (value);
		if (tmp <= 0)
		{
			fprintf (stderr, "rrdtool: `RRARows' must "
