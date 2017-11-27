static int sensors_load_conf (void)
{
	FILE *fh;
	featurelist_t *last_feature = NULL;
	
	const sensors_chip_name *chip;
	int chip_num;

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

#if SENSORS_API_VERSION < 0x400
	chip_num = 0;
	while ((chip = sensors_get_detected_chips (&chip_num)) != NULL)
	{
		int feature_num0 = 0;
		int feature_num1 = 0;

		while (42)
		{
			const sensors_feature_data *feature;
			int feature_type;
			featurelist_t *fl;

			feature = sensors_get_all_features (*chip,
					&feature_num0, &feature_num1);

			/* Check if all features have been read. */
			if (feature == NULL)
				break;

			/* "master features" only */
			if (feature->mapping != SENSORS_NO_MAPPING)
				continue;

			/* skip ignored in sensors.conf */
			if (sensors_get_ignored (*chip, feature->number) == 0)
				break;

			feature_type = sensors_feature_name_to_type (
					feature->name);
			if (feature_type == SENSOR_TYPE_UNKNOWN)
				continue;

			fl = (featurelist_t *) malloc (sizeof (featurelist_t));
			if (fl == NULL)
			{
				ERROR ("sensors plugin: malloc failed.");
				continue;
			}
			memset (fl, '\0', sizeof (featurelist_t));

			fl->chip = chip;
			fl->data = feature;
			fl->type = feature_type;

			if (first_feature == NULL)
				first_feature = fl;
			else
				last_feature->next = fl;
			last_feature = fl;
		} /* while sensors_get_all_features */
	} /* while sensors_get_detected_chips */
/* #endif SENSORS_API_VERSION < 0x400 */

#elif (SENSORS_API_VERSION >= 0x400) && (SENSORS_API_VERSION < 0x500)
	chip_num = 0;
	while ((chip = sensors_get_detected_chips (NULL, &chip_num)) != NULL)
	{
		const sensors_feature *feature;
		int feature_num = 0;

		while ((feature = sensors_get_features (chip, &feature_num)) != NULL)
		{
			const sensors_subfeature *subfeature;
			int subfeature_num = 0;

			/* Only handle voltage, fanspeeds and temperatures */
			if ((feature->type != SENSORS_FEATURE_IN)
					&& (feature->type != SENSORS_FEATURE_FAN)
					&& (feature->type != SENSORS_FEATURE_TEMP))
				continue;

			while ((subfeature = sensors_get_all_subfeatures (chip,
							feature, &subfeature_num)) != NULL)
			{
				featurelist_t *fl;

				if ((subfeature->type != SENSORS_SUBFEATURE_IN_INPUT)
						&& (subfeature->type != SENSORS_SUBFEATURE_FAN_INPUT)
						&& (subfeature->type != SENSORS_SUBFEATURE_TEMP_INPUT))
					continue;

				fl = (featurelist_t *) malloc (sizeof (featurelist_t));
				if (fl == NULL)
				{
					ERROR ("sensors plugin: malloc failed.");
					continue;
				}
				memset (fl, '\0', sizeof (featurelist_t));

				fl->chip = chip;
				fl->feature = feature;
				fl->subfeature = subfeature;

				if (first_feature == NULL)
					first_feature = fl;
				else
					last_feature->next = fl;
				last_feature  = fl;
			} /* while (subfeature) */
		} /* while (feature) */
	} /* while (chip) */
#endif /* (SENSORS_API_VERSION >= 0x400) && (SENSORS_API_VERSION < 0x500) */

	if (first_feature == NULL)
	{
		sensors_cleanup ();
		INFO ("sensors plugin: lm_sensors reports no "
				"features. Data will not be collected.");
		return (-1);
	}

	return (0);
}