static int add_to_buffer (char *buffer, int buffer_size,
		value_list_t *vl_def, char *type_def,
		const data_set_t *ds, const value_list_t *vl)
{
	char *buffer_orig = buffer;

	if (strcmp (vl_def->host, vl->host) != 0)
	{
		if (write_part_string (&buffer, &buffer_size, TYPE_HOST,
					vl->host, strlen (vl->host)) != 0)
			return (-1);
		strcpy (vl_def->host, vl->host);
		DEBUG ("network plugin: add_to_buffer: host = %s", vl->host);
	}

	if (vl_def->time != vl->time)
	{
		if (write_part_number (&buffer, &buffer_size, TYPE_TIME,
					(uint64_t) vl->time))
			return (-1);
		vl_def->time = vl->time;
		DEBUG ("network plugin: add_to_buffer: time = %u",
				(unsigned int) vl->time);
	}

	if (strcmp (vl_def->plugin, vl->plugin) != 0)
	{
		if (write_part_string (&buffer, &buffer_size, TYPE_PLUGIN,
					vl->plugin, strlen (vl->plugin)) != 0)
			return (-1);
		strcpy (vl_def->plugin, vl->plugin);
		DEBUG ("network plugin: add_to_buffer: plugin = %s",
				vl->plugin);
	}

	if (strcmp (vl_def->plugin_instance, vl->plugin_instance) != 0)
	{
		if (write_part_string (&buffer, &buffer_size, TYPE_PLUGIN_INSTANCE,
					vl->plugin_instance,
					strlen (vl->plugin_instance)) != 0)
			return (-1);
		strcpy (vl_def->plugin_instance, vl->plugin_instance);
		DEBUG ("network plugin: add_to_buffer: plugin_instance = %s",
				vl->plugin_instance);
	}

	if (strcmp (type_def, ds->type) != 0)
	{
		if (write_part_string (&buffer, &buffer_size, TYPE_TYPE,
					ds->type, strlen (ds->type)) != 0)
			return (-1);
		strcpy (type_def, ds->type);
		DEBUG ("network plugin: add_to_buffer: type = %s", ds->type);
	}

	if (strcmp (vl_def->type_instance, vl->type_instance) != 0)
	{
		if (write_part_string (&buffer, &buffer_size, TYPE_TYPE_INSTANCE,
					vl->type_instance,
					strlen (vl->type_instance)) != 0)
			return (-1);
		strcpy (vl_def->type_instance, vl->type_instance);
		DEBUG ("network plugin: add_to_buffer: type_instance = %s",
				vl->type_instance);
	}
	
	if (write_part_values (&buffer, &buffer_size, ds, vl) != 0)
		return (-1);

	return (buffer - buffer_orig);
}