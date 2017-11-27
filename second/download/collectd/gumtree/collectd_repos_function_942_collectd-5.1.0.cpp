static void cna_config_volume_perf_default (cfg_volume_perf_t *cvp, /* {{{ */
		const oconfig_item_t *ci)
{
	ignorelist_t *il;

	if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_BOOLEAN))
	{
		WARNING ("netapp plugin: The %s option requires exactly one string argument.",
				ci->key);
		return;
	}

	if (strcasecmp ("IgnoreSelectedIO", ci->key) == 0)
		il = cvp->il_octets;
	else if (strcasecmp ("IgnoreSelectedOps", ci->key) == 0)
		il = cvp->il_operations;
	else if (strcasecmp ("IgnoreSelectedLatency", ci->key) == 0)
		il = cvp->il_latency;
	else
		return;

	if (ci->values[0].value.boolean)
		ignorelist_set_invert (il, /* invert = */ 0);
	else
		ignorelist_set_invert (il, /* invert = */ 1);
}