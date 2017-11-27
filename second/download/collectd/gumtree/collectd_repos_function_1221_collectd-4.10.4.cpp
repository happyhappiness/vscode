int cf_util_get_int (const oconfig_item_t *ci, int *ret_value) /* {{{ */
{
	if ((ci == NULL) || (ret_value == NULL))
		return (EINVAL);

	if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_NUMBER))
	{
		ERROR ("cf_util_get_int: The %s option requires "
				"exactly one numeric argument.", ci->key);
		return (-1);
	}

	*ret_value = (int) ci->values[0].value.number;

	return (0);
}