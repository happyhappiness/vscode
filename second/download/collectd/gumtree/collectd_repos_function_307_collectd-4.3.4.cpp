int format_name (char *ret, int ret_len,
		const char *hostname,
		const char *plugin, const char *plugin_instance,
		const char *type, const char *type_instance)
{
	int  status;

	assert (plugin != NULL);
	assert (type != NULL);

	if ((plugin_instance == NULL) || (strlen (plugin_instance) == 0))
	{
		if ((type_instance == NULL) || (strlen (type_instance) == 0))
			status = snprintf (ret, ret_len, "%s/%s/%s",
					hostname, plugin, type);
		else
			status = snprintf (ret, ret_len, "%s/%s/%s-%s",
					hostname, plugin, type,
					type_instance);
	}
	else
	{
		if ((type_instance == NULL) || (strlen (type_instance) == 0))
			status = snprintf (ret, ret_len, "%s/%s-%s/%s",
					hostname, plugin, plugin_instance,
					type);
		else
			status = snprintf (ret, ret_len, "%s/%s-%s/%s-%s",
					hostname, plugin, plugin_instance,
					type, type_instance);
	}

	if ((status < 1) || (status >= ret_len))
		return (-1);
	return (0);
}