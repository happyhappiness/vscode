static int dispatch_loadplugin (const oconfig_item_t *ci)
{
	int i;
	const char *name;
	unsigned int flags = 0;
	assert (strcasecmp (ci->key, "LoadPlugin") == 0);

	if (ci->values_num != 1)
		return (-1);
	if (ci->values[0].type != OCONFIG_TYPE_STRING)
		return (-1);

	name = ci->values[0].value.string;

	/*
	 * XXX: Magic at work:
	 *
	 * Some of the language bindings, for example the Python and Perl
	 * plugins, need to be able to export symbols to the scripts they run.
	 * For this to happen, the "Globals" flag needs to be set.
	 * Unfortunately, this technical detail is hard to explain to the
	 * average user and she shouldn't have to worry about this, ideally.
	 * So in order to save everyone's sanity use a different default for a
	 * handful of special plugins. --octo
	 */
	if ((strcasecmp ("Perl", name) == 0)
			|| (strcasecmp ("Python", name) == 0))
		flags |= PLUGIN_FLAGS_GLOBAL;

	for (i = 0; i < ci->children_num; ++i) {
		if (strcasecmp("Globals", ci->children[i].key) == 0)
			cf_util_get_flag (ci->children + i, &flags, PLUGIN_FLAGS_GLOBAL);
		else {
			WARNING("Ignoring unknown LoadPlugin option \"%s\" "
					"for plugin \"%s\"",
					ci->children[i].key, ci->values[0].value.string);
		}
	}

	return (plugin_load (name, (uint32_t) flags));
}