static int cna_config_get_interval (const oconfig_item_t *ci, /* {{{ */
		cna_interval_t *out_interval)
{
	time_t tmp;

	if ((ci == NULL) || (out_interval == NULL))
		return (EINVAL);

	if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_NUMBER))
	{
		WARNING ("netapp plugin: The `Interval' option needs exactly one numeric argument.");
		return (-1);
	}

	tmp = (time_t) (ci->values[0].value.number + .5);
	if (tmp < 1)
	{
		WARNING ("netapp plugin: The `Interval' option needs a positive integer argument.");
		return (-1);
	}

	out_interval->interval = tmp;
	out_interval->last_read = 0;

	return (0);
}