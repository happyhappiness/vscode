int cf_util_get_port_number (const oconfig_item_t *ci) /* {{{ */
{
	if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING))
	{
		ERROR ("cf_util_get_port_number: The %s option requires "
				"exactly one string argument.", ci->key);
		return (-1);
	}

	return (service_name_to_port_number (ci->values[0].value.string));
}