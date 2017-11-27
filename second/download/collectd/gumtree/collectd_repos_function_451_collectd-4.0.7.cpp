static int dispatch_block_plugin (oconfig_item_t *ci)
{
	int i;
	char *name;

	if (strcasecmp (ci->key, "Plugin") != 0)
		return (-1);
	if (ci->values_num != 1)
		return (-1);
	if (ci->values[0].type != OCONFIG_TYPE_STRING)
		return (-1);

	name = ci->values[0].value.string;

	for (i = 0; i < ci->children_num; i++)
	{
		if (ci->children[i].children == NULL)
			dispatch_value_plugin (name, ci->children + i);
		else
			{DEBUG ("No nested config blocks allow for plugins. Yet.");}
	}

	return (0);
}