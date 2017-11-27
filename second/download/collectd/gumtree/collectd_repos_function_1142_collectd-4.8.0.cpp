static int mysql_config_set_int (int *ret_int, /* {{{ */
				 oconfig_item_t *ci)
{
	if ((ci->values_num != 1)
	    || (ci->values[0].type != OCONFIG_TYPE_NUMBER))
	{
		WARNING ("mysql plugin: The `%s' config option "
			 "needs exactly one string argument.", ci->key);
		return (-1);
	}

	*ret_int = ci->values[0].value.number;

	return (0);
}