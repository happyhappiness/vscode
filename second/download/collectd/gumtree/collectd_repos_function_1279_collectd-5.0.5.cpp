static int dispatch_global_option (const oconfig_item_t *ci)
{
	if (ci->values_num != 1)
		return (-1);
	if (ci->values[0].type == OCONFIG_TYPE_STRING)
		return (global_option_set (ci->key, ci->values[0].value.string));
	else if (ci->values[0].type == OCONFIG_TYPE_NUMBER)
	{
		char tmp[128];
		ssnprintf (tmp, sizeof (tmp), "%lf", ci->values[0].value.number);
		return (global_option_set (ci->key, tmp));
	}
	else if (ci->values[0].type == OCONFIG_TYPE_BOOLEAN)
	{
		if (ci->values[0].value.boolean)
			return (global_option_set (ci->key, "true"));
		else
			return (global_option_set (ci->key, "false"));
	}

	return (-1);
}