static int sensors_config (const char *key, const char *value)
{
	if (sensor_list == NULL)
		sensor_list = ignorelist_create (1);

	if (strcasecmp (key, "Sensor") == 0)
	{
		if (ignorelist_add (sensor_list, value))
		{
			ERROR ("sensors plugin: "
					"Cannot add value to ignorelist.");
			return (1);
		}
	}
	else if (strcasecmp (key, "IgnoreSelected") == 0)
	{
		ignorelist_set_invert (sensor_list, 1);
		if ((strcasecmp (value, "True") == 0)
				|| (strcasecmp (value, "Yes") == 0)
				|| (strcasecmp (value, "On") == 0))
			ignorelist_set_invert (sensor_list, 0);
	}
	else
	{
		return (-1);
	}

	return (0);
}