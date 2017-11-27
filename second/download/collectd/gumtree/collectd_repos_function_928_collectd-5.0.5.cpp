static int cna_config_bool_to_flag (const oconfig_item_t *ci, /* {{{ */
		uint32_t *flags, uint32_t flag)
{
	if ((ci == NULL) || (flags == NULL))
		return (EINVAL);

	if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_BOOLEAN))
	{
		WARNING ("netapp plugin: The %s option needs exactly one boolean argument.",
				ci->key);
		return (-1);
	}

	if (ci->values[0].value.boolean)
		*flags |= flag;
	else
		*flags &= ~flag;

	return (0);
}