static int sensors_read (void)
{
	featurelist_t *feature;
	double value;

	char plugin_instance[DATA_MAX_NAME_LEN];
	char type_instance[DATA_MAX_NAME_LEN];

	if (sensors_load_conf () != 0)
		return (-1);

	for (feature = first_feature; feature != NULL; feature = feature->next)
	{
		if (sensors_get_feature (*feature->chip, feature->data->number, &value) < 0)
			continue;

		/* full chip name logic borrowed from lm_sensors */
		if (feature->chip->bus == SENSORS_CHIP_NAME_BUS_ISA)
		{
			if (snprintf (plugin_instance, DATA_MAX_NAME_LEN, "%s-isa-%04x",
						feature->chip->prefix,
						feature->chip->addr)
					>= 512)
				continue;
		}
		else if (feature->chip->bus == SENSORS_CHIP_NAME_BUS_DUMMY)
		{
			if (snprintf (plugin_instance, 512, "%s-%s-%04x",
						feature->chip->prefix,
						feature->chip->busname,
						feature->chip->addr)
					>= 512)
				continue;
		}
		else
		{
			if (snprintf (plugin_instance, 512, "%s-i2c-%d-%02x",
						feature->chip->prefix,
						feature->chip->bus,
						feature->chip->addr)
					>= 512)
				continue;
		}

		strncpy (type_instance, feature->data->name, DATA_MAX_NAME_LEN);

		sensors_submit (plugin_instance,
				sensor_to_type[feature->type],
				type_instance,
				value);
	} /* for feature = first_feature .. NULL */

	return (0);
}