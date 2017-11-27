				datadir = NULL;
			}
		}
	}
	else if (strcasecmp ("StepSize", key) == 0)
	{
		int tmp = atoi (value);
		if (tmp <= 0)
		{
			fprintf (stderr, "rrdtool: `StepSize' must "
					"be greater than 0.\n");
			return (1);
		}
		stepsize = tmp;
	}
	else if (strcasecmp ("HeartBeat", key) == 0)
	{
		int tmp = atoi (value);
		if (tmp <= 0)
		{
			fprintf (stderr, "rrdtool: `HeartBeat' must "
					"be greater than 0.\n");
			return (1);
		}
		heartbeat = tmp;
	}
	else if (strcasecmp ("RRARows", key) == 0)
	{
		int tmp = atoi (value);
		if (tmp <= 0)
		{
