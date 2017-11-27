static int dispatch_value_loadplugin (const oconfig_item_t *ci)
{
	assert (strcasecmp (ci->key, "LoadPlugin") == 0);

	if (ci->values_num != 1)
		return (-1);
	if (ci->values[0].type != OCONFIG_TYPE_STRING)
		return (-1);

	return (plugin_load (ci->values[0].value.string));
}