static int ts_config_set_double (double *ret, oconfig_item_t *ci) /* {{{ */
{
	if ((ci->values_num != 1)
			|| (ci->values[0].type != OCONFIG_TYPE_NUMBER))
	{
		WARNING ("scale target: The `%s' config option needs "
				"exactly one numeric argument.", ci->key);
		return (-1);
	}

	*ret = ci->values[0].value.number;
	DEBUG ("ts_config_set_double: *ret = %g", *ret);

	return (0);
}