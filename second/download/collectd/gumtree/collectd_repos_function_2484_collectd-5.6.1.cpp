static int dispatch_value (oconfig_item_t *ci)
{
	int ret = 0;

	for (int i = 0; i < cf_value_map_num; i++)
		if (strcasecmp (cf_value_map[i].key, ci->key) == 0)
		{
			ret = cf_value_map[i].func (ci);
			break;
		}

	for (int i = 0; i < cf_global_options_num; i++)
		if (strcasecmp (cf_global_options[i].key, ci->key) == 0)
		{
			ret = dispatch_global_option (ci);
			break;
		}

	return (ret);
}