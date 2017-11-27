static int varnish_config (oconfig_item_t *ci) /* {{{ */
{
	for (int i = 0; i < ci->children_num; i++)
	{
		oconfig_item_t *child = ci->children + i;

		if (strcasecmp ("Instance", child->key) == 0)
			varnish_config_instance (child);
		else
		{
			WARNING ("Varnish plugin: Ignoring unknown "
					"configuration option: \"%s\"",
					child->key);
		}
	}

	return (0);
}