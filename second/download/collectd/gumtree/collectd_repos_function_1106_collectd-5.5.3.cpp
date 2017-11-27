static int drbd_submit_fields (long int resource,
		char **fields, size_t fields_num)
{
	char plugin_instance[DATA_MAX_NAME_LEN];
	value_t values[fields_num];
	value_list_t vl = VALUE_LIST_INIT;
	size_t i;

	if (resource < 0)
	{
		WARNING ("drbd plugin: Unable to parse resource");
		return (EINVAL);
	}

	if (fields_num != drbd_names_num)
	{
		WARNING ("drbd plugin: Wrong number of fields for "
				 "r%ld statistics. Expected %zu, got %zu.",
				 resource, drbd_names_num, fields_num);
		return (EINVAL);
	}

	ssnprintf (plugin_instance, sizeof (plugin_instance), "r%ld",
			resource);

	for (i = 0; i < drbd_names_num; i++)
	{
		char *data;
		/* skip non numeric wo */
		if (strncmp(fields[i], "wo", 2) == 0)
			continue;
		data = strchr(fields[i], ':');
		if (data == NULL)
			return (EINVAL);
		(void) parse_value (++data, &values[i], DS_TYPE_DERIVE);
	}

	vl.values_len = 1;
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "drbd", sizeof (vl.plugin));
	sstrncpy (vl.plugin_instance, plugin_instance,
			sizeof (vl.plugin_instance));
	sstrncpy (vl.type, "drbd_resource", sizeof (vl.type));

	for (i = 0; i < fields_num; i++)
	{
		if (drbd_names[i] == NULL)
			continue;
		vl.values = values + i;
		sstrncpy (vl.type_instance, drbd_names[i],
				sizeof (vl.type_instance));
		plugin_dispatch_values (&vl);
	}

	return (0);
}