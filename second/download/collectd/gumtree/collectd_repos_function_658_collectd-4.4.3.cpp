static int cf_dispatch (const char *type, const char *orig_key,
		const char *orig_value)
{
	cf_callback_t *cf_cb;
	char *key;
	char *value;
	int ret;
	int i;

	DEBUG ("type = %s, key = %s, value = %s",
			ESCAPE_NULL(type),
			ESCAPE_NULL(orig_key),
			ESCAPE_NULL(orig_value));

	if ((cf_cb = cf_search (type)) == NULL)
	{
		WARNING ("Found a configuration for the `%s' plugin, but "
				"the plugin isn't loaded or didn't register "
				"a configuration callback.", type);
		return (-1);
	}

	if ((key = strdup (orig_key)) == NULL)
		return (1);
	if ((value = strdup (orig_value)) == NULL)
	{
		free (key);
		return (2);
	}

	ret = -1;

	for (i = 0; i < cf_cb->keys_num; i++)
	{
		if (strcasecmp (cf_cb->keys[i], key) == 0)
		{
			ret = (*cf_cb->callback) (key, value);
			break;
		}
	}

	if (i >= cf_cb->keys_num)
		WARNING ("Plugin `%s' did not register for value `%s'.", type, key);

	free (key);
	free (value);

	DEBUG ("return (%i)", ret);

	return (ret);
}