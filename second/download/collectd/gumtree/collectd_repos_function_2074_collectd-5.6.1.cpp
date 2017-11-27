curl_stats_t *curl_stats_from_config (oconfig_item_t *ci)
{
	curl_stats_t *s;

	if (ci == NULL)
		return NULL;

	s = calloc (1, sizeof (*s));
	if (s == NULL)
		return NULL;

	for (int i = 0; i < ci->children_num; ++i)
	{
		oconfig_item_t *c = ci->children + i;
		size_t field;

		_Bool enabled = 0;

		for (field = 0; field < STATIC_ARRAY_SIZE (field_specs); ++field) {
			if (! strcasecmp (c->key, field_specs[field].config_key))
				break;
			if (! strcasecmp (c->key, field_specs[field].name))
				break;
		}
		if (field >= STATIC_ARRAY_SIZE (field_specs))
		{
			ERROR ("curl stats: Unknown field name %s", c->key);
			free (s);
			return NULL;
		}


		if (cf_util_get_boolean (c, &enabled) != 0) {
			free (s);
			return NULL;
		}
		if (enabled)
			enable_field (s, field_specs[field].offset);
	}

	return s;
}