			fprintf (stderr, "rrdtool: `XFF' must "
					"be in the range 0 to 1 (exclusive).");
			ERROR ("rrdtool: `XFF' must "
					"be in the range 0 to 1 (exclusive).");
			return (1);
		}
		rrdcreate_config.xff = tmp;
	}
	else if (strcasecmp ("WritesPerSecond", key) == 0)
	{
		double wps = atof (value);

		if (wps < 0.0)
