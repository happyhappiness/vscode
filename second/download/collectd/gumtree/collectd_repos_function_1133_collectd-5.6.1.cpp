static int cna_config_quota (host_config_t *host, oconfig_item_t *ci) /* {{{ */
{
	cfg_quota_t *cfg_quota;

	if ((host == NULL) || (ci == NULL))
		return (EINVAL);

	if (host->cfg_quota == NULL)
	{
		cfg_quota = calloc (1, sizeof (*cfg_quota));
		if (cfg_quota == NULL)
			return (ENOMEM);
		cfg_quota->query = NULL;

		host->cfg_quota = cfg_quota;
	}
	cfg_quota = host->cfg_quota;

	for (int i = 0; i < ci->children_num; ++i) {
		oconfig_item_t *item = ci->children + i;

		if (strcasecmp (item->key, "Interval") == 0)
			cna_config_get_interval (item, &cfg_quota->interval);
		else
			WARNING ("netapp plugin: The option %s is not allowed within "
					"`Quota' blocks.", item->key);
	}

	return (0);
}