static int config_set_boolean (int *ret_boolean, /* {{{ */
				    oconfig_item_t *ci)
{
	if ((ci->values_num != 1)
			|| ((ci->values[0].type != OCONFIG_TYPE_BOOLEAN)
				&& (ci->values[0].type != OCONFIG_TYPE_STRING)))
	{
		WARNING ("apache plugin: The `%s' config option "
				"needs exactly one boolean argument.", ci->key);
		return (-1);
	}

	if (ci->values[0].type == OCONFIG_TYPE_BOOLEAN)
	{
		if (ci->values[0].value.boolean)
			*ret_boolean = 1;
		else
			*ret_boolean = 0;
	}
	else /* if (ci->values[0].type != OCONFIG_TYPE_STRING) */
	{
		char *string = ci->values[0].value.string;
		if (IS_TRUE (string))
			*ret_boolean = 1;
		else if (IS_FALSE (string))
			*ret_boolean = 0;
		else
		{
			ERROR ("apache plugin: Cannot parse string "
					"as boolean value: %s", string);
			return (-1);
		}
	}

	return (0);
}