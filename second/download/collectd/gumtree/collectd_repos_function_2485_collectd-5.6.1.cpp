static int dispatch_block_plugin (oconfig_item_t *ci)
{
	const char *name;

	if (strcasecmp (ci->key, "Plugin") != 0)
		return (-1);
	if (ci->values_num < 1)
		return (-1);
	if (ci->values[0].type != OCONFIG_TYPE_STRING)
		return (-1);

	name = ci->values[0].value.string;
	if (strcmp ("libvirt", name) == 0)
	{
		/* TODO(octo): Remove this legacy. */
		WARNING ("The \"libvirt\" plugin has been renamed to \"virt\" to avoid problems with the build system. "
				"Your configuration is still using the old name. "
				"Please change it to use \"virt\" as soon as possible. "
				"This compatibility code will go away eventually.");
		name = "virt";
	}

	if (IS_TRUE (global_option_get ("AutoLoadPlugin")))
	{
		plugin_ctx_t ctx = { 0 };
		plugin_ctx_t old_ctx;
		int status;

		/* default to the global interval set before loading this plugin */
		ctx.interval = cf_get_default_interval ();

		old_ctx = plugin_set_ctx (ctx);
		status = plugin_load (name, /* flags = */ 0);
		/* reset to the "global" context */
		plugin_set_ctx (old_ctx);

		if (status != 0)
		{
			ERROR ("Automatically loading plugin \"%s\" failed "
					"with status %i.", name, status);
			return (status);
		}
	}

	/* Check for a complex callback first */
	for (cf_complex_callback_t *cb = complex_callback_head; cb != NULL; cb = cb->next)
	{
		if (strcasecmp (name, cb->type) == 0)
		{
			plugin_ctx_t old_ctx;
			int ret_val;

			old_ctx = plugin_set_ctx (cb->ctx);
			ret_val = (cb->callback (ci));
			plugin_set_ctx (old_ctx);
			return (ret_val);
		}
	}

	/* Hm, no complex plugin found. Dispatch the values one by one */
	for (int i = 0; i < ci->children_num; i++)
	{
		if (ci->children[i].children == NULL)
			dispatch_value_plugin (name, ci->children + i);
		else
		{
			WARNING ("There is a `%s' block within the "
					"configuration for the %s plugin. "
					"The plugin either only expects "
					"\"simple\" configuration statements "
					"or wasn't loaded using `LoadPlugin'."
					" Please check your configuration.",
					ci->children[i].key, name);
		}
	}

	return (0);
}