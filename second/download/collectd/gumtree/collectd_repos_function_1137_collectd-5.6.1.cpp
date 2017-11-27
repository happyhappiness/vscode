static int cna_config_snapvault (host_config_t *host, /* {{{ */
		const oconfig_item_t *ci)
{
	cfg_snapvault_t *cfg_snapvault;

	if ((host == NULL) || (ci == NULL))
		return EINVAL;

	if (host->cfg_snapvault == NULL)
	{
		cfg_snapvault = calloc (1, sizeof (*cfg_snapvault));
		if (cfg_snapvault == NULL)
			return ENOMEM;
		cfg_snapvault->query = NULL;

		host->cfg_snapvault = cfg_snapvault;
	}

	cfg_snapvault = host->cfg_snapvault;

	for (int i = 0; i < ci->children_num; ++i) {
		oconfig_item_t *item = ci->children + i;

		if (strcasecmp (item->key, "Interval") == 0)
			cna_config_get_interval (item, &cfg_snapvault->interval);
		else
			WARNING ("netapp plugin: The option %s is not allowed within "
					"`SnapVault' blocks.", item->key);
	}

	return 0;
}