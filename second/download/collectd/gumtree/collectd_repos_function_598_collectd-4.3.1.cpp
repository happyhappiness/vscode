static int dispatch_block_plugin (oconfig_item_t *ci)
{
	int i;
	char *name;

	cf_complex_callback_t *cb;

	if (strcasecmp (ci->key, "Plugin") != 0)
		return (-1);
	if (ci->values_num < 1)
		return (-1);
	if (ci->values[0].type != OCONFIG_TYPE_STRING)
		return (-1);

	name = ci->values[0].value.string;

	/* Check for a complex callback first */
	for (cb = complex_callback_head; cb != NULL; cb = cb->next)
		if (strcasecmp (name, cb->type) == 0)
			return (cb->callback (ci));

	/* Hm, no complex plugin found. Dispatch the values one by one */
	for (i = 0; i < ci->children_num; i++)
	{
		if (ci->children[i].children == NULL)
			dispatch_value_plugin (name, ci->children + i);
		else
			{DEBUG ("No nested config blocks allow for this plugin.");}
	}

	return (0);
}