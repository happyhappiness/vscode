static int thermal_config (const char *key, const char *value)
{
	if (device_list == NULL)
		device_list = ignorelist_create (1);

	if (strcasecmp (key, "Device") == 0)
	{
		if (ignorelist_add (device_list, value))
		{
			ERROR ("thermal plugin: "
					"Cannot add value to ignorelist.");
			return 1;
		}
	}
	else if (strcasecmp (key, "IgnoreSelected") == 0)
	{
		ignorelist_set_invert (device_list, 1);
		if ((strcasecmp (value, "True") == 0)
				|| (strcasecmp (value, "Yes") == 0)
				|| (strcasecmp (value, "On") == 0))
			ignorelist_set_invert (device_list, 0);
	}
	else if (strcasecmp (key, "ForceUseProcfs") == 0)
	{
		force_procfs = 0;
		if ((strcasecmp (value, "True") == 0)
				|| (strcasecmp (value, "Yes") == 0)
				|| (strcasecmp (value, "On") == 0))
			force_procfs = 1;
	}
	else
	{
		return -1;
	}

	return 0;
}