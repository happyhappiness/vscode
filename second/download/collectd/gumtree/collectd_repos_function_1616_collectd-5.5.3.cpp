static int memory_config (oconfig_item_t *ci) /* {{{ */
{
	int i;

	for (i = 0; i < ci->children_num; i++)
	{
		oconfig_item_t *child = ci->children + i;
		if (strcasecmp ("ValuesAbsolute", child->key) == 0)
			cf_util_get_boolean (child, &values_absolute);
		else if (strcasecmp ("ValuesPercentage", child->key) == 0)
			cf_util_get_boolean (child, &values_percentage);
		else
			ERROR ("memory plugin: Invalid configuration option: "
					"\"%s\".", child->key);
	}

	return (0);
}