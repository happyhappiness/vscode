int cf_util_get_double (const oconfig_item_t *ci, double *ret_value) /* {{{ */
{
	if ((ci == NULL) || (ret_value == NULL))
		return (EINVAL);

	if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_NUMBER))
	{
		ERROR ("cf_util_get_double: The %s option requires "
				"exactly one numeric argument.", ci->key);
		return (-1);
	}

	*ret_value = ci->values[0].value.number;

	return (0);
}