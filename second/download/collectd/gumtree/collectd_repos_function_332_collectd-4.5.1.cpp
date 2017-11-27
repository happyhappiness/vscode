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
		if (new_val == NULL)
			return (1);
		fields_num = strsplit (new_val, fields,
				STATIC_ARRAY_SIZE (fields));
		if (fields_num != 2)
		{
			sfree (new_val);
			return (1);
		}
		ps_list_register (fields[0], fields[1]);
		sfree (new_val);
	}
	else
	{
		return (-1);
	}

	return (0);
}