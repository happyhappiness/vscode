static int dispatch_loadplugin (const oconfig_item_t *ci)
{
	int i;
	uint32_t flags = 0;
	assert (strcasecmp (ci->key, "LoadPlugin") == 0);

	if (ci->values_num != 1)
		return (-1);
	if (ci->values[0].type != OCONFIG_TYPE_STRING)
		return (-1);

	for (i = 0; i < ci->children_num; ++i) {
		if (ci->children[i].values_num != 1 ||
				ci->children[i].values[0].type != OCONFIG_TYPE_BOOLEAN) {
			WARNING("Ignoring unknown LoadPlugin option %s for plugin %s", ci->children[i].key, ci->values[0].value.string);
			continue;
		}
		if (strcasecmp(ci->children[i].key, "globals") == 0) {
			flags |= PLUGIN_FLAGS_GLOBAL;
		} else {
			WARNING("Ignoring unknown LoadPlugin option %s for plugin %s", ci->children[i].key, ci->values[0].value.string);
		}
	}
	return (plugin_load (ci->values[0].value.string, flags));
}