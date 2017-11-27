static int cna_config_system (host_config_t *host, /* {{{ */
		oconfig_item_t *ci)
{
	cfg_system_t *cfg_system;

	if ((host == NULL) || (ci == NULL))
		return (EINVAL);

	if (host->cfg_system == NULL)
	{
		cfg_system = calloc (1, sizeof (*cfg_system));
		if (cfg_system == NULL)
			return (ENOMEM);

		/* Set default flags */
		cfg_system->flags = CFG_SYSTEM_ALL;
		cfg_system->query = NULL;

		host->cfg_system = cfg_system;
	}
	cfg_system = host->cfg_system;

	for (int i = 0; i < ci->children_num; ++i) {
		oconfig_item_t *item = ci->children + i;

		if (strcasecmp(item->key, "Interval") == 0) {
			cna_config_get_interval (item, &cfg_system->interval);
		} else if (!strcasecmp(item->key, "GetCPULoad")) {
			cna_config_bool_to_flag (item, &cfg_system->flags, CFG_SYSTEM_CPU);
		} else if (!strcasecmp(item->key, "GetInterfaces")) {
			cna_config_bool_to_flag (item, &cfg_system->flags, CFG_SYSTEM_NET);
		} else if (!strcasecmp(item->key, "GetDiskOps")) {
			cna_config_bool_to_flag (item, &cfg_system->flags, CFG_SYSTEM_OPS);
		} else if (!strcasecmp(item->key, "GetDiskIO")) {
			cna_config_bool_to_flag (item, &cfg_system->flags, CFG_SYSTEM_DISK);
		} else {
			WARNING ("netapp plugin: The %s config option is not allowed within "
					"`System' blocks.", item->key);
		}
	}

	if ((cfg_system->flags & CFG_SYSTEM_ALL) == 0)
	{
		NOTICE ("netapp plugin: All system related values have been disabled. "
				"Collection of system data will be disabled entirely.");
		free_cfg_system (host->cfg_system);
		host->cfg_system = NULL;
	}

	return (0);
}