static int sensors_read (void)
{
	featurelist_t *fl;

	if (sensors_load_conf () != 0)
		return (-1);

#if SENSORS_API_VERSION < 0x400
	for (fl = first_feature; fl != NULL; fl = fl->next)
	{
		double value;
		int status;
		char plugin_instance[DATA_MAX_NAME_LEN];
		char type_instance[DATA_MAX_NAME_LEN];

		status = sensors_get_feature (*fl->chip,
				fl->data->number, &value);
		if (status < 0)
			continue;

		status = sensors_snprintf_chip_name (plugin_instance,
				sizeof (plugin_instance), fl->chip);
		if (status < 0)
			continue;
		plugin_instance[sizeof (plugin_instance) - 1] = '\0';

		strncpy (type_instance, fl->data->name,
				sizeof (type_instance));
		type_instance[sizeof (type_instance) - 1] = '\0';

		sensors_submit (plugin_instance,
				sensor_type_name_map[fl->type],
				type_instance,
				value);
	} /* for fl = first_feature .. NULL */
/* #endif SENSORS_API_VERSION < 0x400 */

#elif (SENSORS_API_VERSION >= 0x400) && (SENSORS_API_VERSION < 0x500)
	for (fl = first_feature; fl != NULL; fl = fl->next)
	{
		double value;
		int status;
		char plugin_instance[DATA_MAX_NAME_LEN];
		char type_instance[DATA_MAX_NAME_LEN];
		const char *type;

		status = sensors_get_value (fl->chip,
				fl->subfeature->number, &value);
		if (status < 0)
			continue;

		status = sensors_snprintf_chip_name (plugin_instance,
				sizeof (plugin_instance), fl->chip);
		if (status < 0)
			continue;
		plugin_instance[sizeof (plugin_instance) - 1] = '\0';

		strncpy (type_instance, fl->feature->name,
				sizeof (type_instance));
		type_instance[sizeof (type_instance) - 1] = '\0';

		if (fl->feature->type == SENSORS_FEATURE_IN)
			type = "voltage";
		else if (fl->feature->type
				== SENSORS_FEATURE_FAN)
			type = "fanspeed";
		else if (fl->feature->type
				== SENSORS_FEATURE_TEMP)
			type = "temperature";
		else
			continue;

		sensors_submit (plugin_instance, type, type_instance, value);
	} /* for fl = first_feature .. NULL */
#endif /* (SENSORS_API_VERSION >= 0x400) && (SENSORS_API_VERSION < 0x500) */

	return (0);
}