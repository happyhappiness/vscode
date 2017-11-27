static int cna_config_wafl(host_config_t *host, oconfig_item_t *ci) /* {{{ */
{
	cfg_wafl_t *cfg_wafl;
	int i;

	if ((host == NULL) || (ci == NULL))
		return (EINVAL);

	if (host->cfg_wafl == NULL)
	{
		cfg_wafl = malloc (sizeof (*cfg_wafl));
		if (cfg_wafl == NULL)
			return (ENOMEM);
		memset (cfg_wafl, 0, sizeof (*cfg_wafl));

		/* Set default flags */
		cfg_wafl->flags = CFG_WAFL_ALL;

		host->cfg_wafl = cfg_wafl;
	}
	cfg_wafl = host->cfg_wafl;

	for (i = 0; i < ci->children_num; ++i) {
		oconfig_item_t *item = ci->children + i;
		
		if (strcasecmp(item->key, "Interval") == 0)
			cna_config_get_interval (item, &cfg_wafl->interval);
		else if (!strcasecmp(item->key, "GetNameCache"))
			cna_config_bool_to_flag (item, &cfg_wafl->flags, CFG_WAFL_NAME_CACHE);
		else if (!strcasecmp(item->key, "GetDirCache"))
			cna_config_bool_to_flag (item, &cfg_wafl->flags, CFG_WAFL_DIR_CACHE);
		else if (!strcasecmp(item->key, "GetBufferCache"))
			cna_config_bool_to_flag (item, &cfg_wafl->flags, CFG_WAFL_BUF_CACHE);
		else if (!strcasecmp(item->key, "GetInodeCache"))
			cna_config_bool_to_flag (item, &cfg_wafl->flags, CFG_WAFL_INODE_CACHE);
		else
			WARNING ("netapp plugin: The %s config option is not allowed within "
					"`WAFL' blocks.", item->key);
	}

	if ((cfg_wafl->flags & CFG_WAFL_ALL) == 0)
	{
		NOTICE ("netapp plugin: All WAFL related values have been disabled. "
				"Collection of WAFL data will be disabled entirely.");
		free_cfg_wafl (host->cfg_wafl);
		host->cfg_wafl = NULL;
	}

	return (0);
}