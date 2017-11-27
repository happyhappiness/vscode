static int dispatch_value_plugindir (const oconfig_item_t *ci)
{
	assert (strcasecmp (ci->key, "PluginDir") == 0);
	
	if (ci->values_num != 1)
		return (-1);
	if (ci->values[0].type != OCONFIG_TYPE_STRING)
		return (-1);

	plugin_set_dir (ci->values[0].value.string);
	return (0);
}