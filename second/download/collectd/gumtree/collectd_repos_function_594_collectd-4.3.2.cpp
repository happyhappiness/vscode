static int dispatch_value_typesdb (const oconfig_item_t *ci)
{
	int i = 0;

	assert (strcasecmp (ci->key, "TypesDB") == 0);

	cf_default_typesdb = 0;

	if (ci->values_num < 1)
		return (-1);

	for (i = 0; i < ci->values_num; ++i)
	{
		if (OCONFIG_TYPE_STRING != ci->values[i].type)
			continue;

		read_types_list (ci->values[i].value.string);
	}
	return (0);
}