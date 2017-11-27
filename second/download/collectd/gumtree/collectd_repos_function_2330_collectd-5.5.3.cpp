static int dispatch_block (oconfig_item_t *ci)
{
	if (strcasecmp (ci->key, "LoadPlugin") == 0)
		return (dispatch_loadplugin (ci));
	else if (strcasecmp (ci->key, "Plugin") == 0)
		return (dispatch_block_plugin (ci));
	else if (strcasecmp (ci->key, "Chain") == 0)
		return (fc_configure (ci));

	return (0);
}