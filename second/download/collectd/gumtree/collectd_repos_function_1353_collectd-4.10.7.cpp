static int mysql_config_set_boolean (int *ret_boolean, /* {{{ */
				oconfig_item_t *ci)
{
	int status = 0;

	if (ci->values_num != 1)
		status = -1;

	if (status == 0)
	{
		if (ci->values[0].type == OCONFIG_TYPE_BOOLEAN)
			*ret_boolean = ci->values[0].value.boolean;
		else if (ci->values[0].type == OCONFIG_TYPE_STRING)
		{
			if (IS_TRUE (ci->values[0].value.string))
				*ret_boolean = 1;
			else if (IS_FALSE (ci->values[0].value.string))
				*ret_boolean = 0;
			else
				status = -1;
		}
		else
			status = -1;
	}

	if (status != 0)
	{
		WARNING ("mysql plugin: The `%s' config option "
			"needs exactly one boolean argument.", ci->key);
		return (-1);
	}
	return (0);
}