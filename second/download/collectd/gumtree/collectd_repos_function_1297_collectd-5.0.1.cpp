int cf_util_get_flag (const oconfig_item_t *ci, /* {{{ */
		unsigned int *ret_value, unsigned int flag)
{
	int status;
	_Bool b;

	if (ret_value == NULL)
		return (EINVAL);

	b = 0;
	status = cf_util_get_boolean (ci, &b);
	if (status != 0)
		return (status);

	if (b)
	{
		*ret_value |= flag;
	}
	else
	{
		*ret_value &= ~flag;
	}

	return (0);
}