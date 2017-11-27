		}
		else
		{
			write_rate = 1.0 / wps;
		}
	}
	else if (strcasecmp ("RandomTimeout", key) == 0)
        {
		int tmp;

		tmp = atoi (value);
		if (tmp < 0)
		{
			fprintf (stderr, "rrdtool: `RandomTimeout' must "
					"be greater than or equal to zero.\n");
			ERROR ("rrdtool: `RandomTimeout' must "
					"be greater then or equal to zero.");
		}
		else
		{
			random_timeout = tmp;
		}
	}
	else
	{
		return (-1);
	}
	return (0);
} /* int rrd_config */
