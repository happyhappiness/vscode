static int ps_config (const char *key, const char *value)
{
	if (strcasecmp (key, "Process") == 0)
	{
		ps_list_register (value, NULL);
	}
	else if (strcasecmp (key, "ProcessMatch") == 0)
	{
		char *new_val;
		char *fields[3];
		int fields_num;

		new_val = strdup (value);
		if (new_val == NULL) {
			ERROR ("processes plugin: strdup failed when processing "
					"`ProcessMatch %s'.", value);
			return (1);
		}

		fields_num = strsplit (new_val, fields,
				STATIC_ARRAY_SIZE (fields));
		if (fields_num != 2)
		{
			ERROR ("processes plugin: `ProcessMatch' needs exactly "
					"two string arguments.");
			sfree (new_val);
			return (1);
		}
		ps_list_register (fields[0], fields[1]);
		sfree (new_val);
	}
	else
	{
		ERROR ("processes plugin: The `%s' configuration option is not "
				"understood and will be ignored.", key);
		return (-1);
	}

	return (0);
}