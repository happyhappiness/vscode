static int dispatch_block (oconfig_item_t *ci)
{
	if (strcasecmp (ci->key, "Plugin") == 0)
		return (dispatch_block_plugin (ci));

	return (0);
}