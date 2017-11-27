static int sensors_load_conf (void)
{
	FILE *fh;
	featurelist_t *last_feature = NULL;
	featurelist_t *new_feature = NULL;
	
	const sensors_chip_name *chip;
	int chip_num;

	const sensors_feature_data *data;
	int data_num0, data_num1;

	struct stat statbuf;
	int status;
	
	status = stat (conffile, &statbuf);
	if (status != 0)
	{
		char errbuf[1024];
		ERROR ("sensors plugin: stat (%s) failed: %s", conffile,
				sstrerror (errno, errbuf, sizeof (errbuf)));
		sensors_config_mtime = 0;
	}

	if ((sensors_config_mtime != 0)
			&& (sensors_config_mtime == statbuf.st_mtime))
		return (0);

	if (sensors_config_mtime != 0)
	{
		NOTICE ("sensors plugin: Reloading config from %s",
				conffile);
		sensors_free_features ();
		sensors_config_mtime = 0;
	}

	fh = fopen (conffile, "r");
	if (fh == NULL)
	{
		char errbuf[1024];
		ERROR ("sensors plugin: fopen(%s) failed: %s", conffile,
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	status = sensors_init (fh);
	fclose (fh);
	if (status != 0)
	{
		ERROR ("sensors plugin: Cannot initialize sensors. "
				"Data will not be collected.");
		return (-1);
	}

	sensors_config_mtime = statbuf.st_mtime;

	chip_num = 0;
	while ((chip = sensors_get_detected_chips (&chip_num)) != NULL)
	{
		data = NULL;
		data_num0 = data_num1 = 0;

		while ((data = sensors_get_all_features (*chip, &data_num0, &data_num1))
				!= NULL)
		{
			int i;

			/* "master features" only */
			if (data->mapping != SENSORS_NO_MAPPING)
				continue;

			/* Only known features */
			for (i = 0; i < known_features_num; i++)
			{
				if (strcmp (data->name, known_features[i].label) != 0)
					continue;

				/* skip ignored in sensors.conf */
				if (sensors_get_ignored (*chip, data->number) == 0)
					break;

				DEBUG ("Adding feature: %s-%s-%s",
						chip->prefix,
						sensor_to_type[known_features[i].type],
						data->name);

				if ((new_feature = (featurelist_t *) malloc (sizeof (featurelist_t))) == NULL)
				{
					char errbuf[1024];
					ERROR ("sensors plugin: malloc: %s",
							sstrerror (errno, errbuf, sizeof (errbuf)));
					break;
				}

				new_feature->chip = chip;
				new_feature->data = data;
				new_feature->type = known_features[i].type;
				new_feature->next = NULL;

				if (first_feature == NULL)
				{
					first_feature = new_feature;
					last_feature  = new_feature;
				}
				else
				{
					last_feature->next = new_feature;
					last_feature = new_feature;
				}

				/* stop searching known features at first found */
				break;
			} /* for i */
		} /* while sensors_get_all_features */
	} /* while sensors_get_detected_chips */

	if (first_feature == NULL)
	{
		sensors_cleanup ();
		INFO ("sensors plugin: lm_sensors reports no "
				"features. Data will not be collected.");
		return (-1);
	}

	return (0);
}