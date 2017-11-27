static int cna_config_snapvault (host_config_t *host, /* {{{ */
		const oconfig_item_t *ci)
{
	cfg_snapvault_t *cfg_snapvault;
	int i;

	if ((host == NULL) || (ci == NULL))
		return EINVAL;

	if (host->cfg_snapvault == NULL)
	{
		cfg_snapvault = malloc (sizeof (*cfg_snapvault));
		if (cfg_snapvault == NULL)
			return ENOMEM;
		memset (cfg_snapvault, 0, sizeof (*cfg_snapvault));
		cfg_snapvault->query = NULL;

		host->cfg_snapvault = cfg_snapvault;
	}

	cfg_snapvault = host->cfg_snapvault;

	for (i = 0; i < ci->children_num; ++i) {
		oconfig_item_t *item = ci->children + i;

		if (strcasecmp (item->key, "Interval") == 0)
			cna_config_get_interval (item, &cfg_snapvault->interval);
		else
			WARNING ("netapp plugin: The option %s is not allowed within "
					"`SnapVault' blocks.", item->key);
	}

	return 0;
}