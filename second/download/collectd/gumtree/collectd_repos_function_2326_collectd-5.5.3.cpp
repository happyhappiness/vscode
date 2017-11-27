static int dispatch_loadplugin (oconfig_item_t *ci)
{
	int i;
	const char *name;
	unsigned int flags = 0;
	plugin_ctx_t ctx;
	plugin_ctx_t old_ctx;
	int ret_val;

	assert (strcasecmp (ci->key, "LoadPlugin") == 0);

	if (ci->values_num != 1)
		return (-1);
	if (ci->values[0].type != OCONFIG_TYPE_STRING)
		return (-1);

	name = ci->values[0].value.string;
	if (strcmp ("libvirt", name) == 0)
		name = "virt";

	/* default to the global interval set before loading this plugin */
	memset (&ctx, 0, sizeof (ctx));
	ctx.interval = cf_get_default_interval ();

	for (i = 0; i < ci->children_num; ++i) {
		if (strcasecmp("Globals", ci->children[i].key) == 0)
			cf_util_get_flag (ci->children + i, &flags, PLUGIN_FLAGS_GLOBAL);
		else if (strcasecmp ("Interval", ci->children[i].key) == 0) {
			if (cf_util_get_cdtime (ci->children + i, &ctx.interval) != 0) {
				/* cf_util_get_cdtime will log an error */
				continue;
			}
		}
		else {
			WARNING("Ignoring unknown LoadPlugin option \"%s\" "
					"for plugin \"%s\"",
					ci->children[i].key, ci->values[0].value.string);
		}
	}

	old_ctx = plugin_set_ctx (ctx);
	ret_val = plugin_load (name, (uint32_t) flags);
	/* reset to the "global" context */
	plugin_set_ctx (old_ctx);

	return (ret_val);
}