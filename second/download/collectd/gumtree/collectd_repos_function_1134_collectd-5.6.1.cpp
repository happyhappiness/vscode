static int cna_config_disk(host_config_t *host, oconfig_item_t *ci) { /* {{{ */
	cfg_disk_t *cfg_disk;

	if ((host == NULL) || (ci == NULL))
		return (EINVAL);

	if (host->cfg_disk == NULL)
	{
		cfg_disk = calloc (1, sizeof (*cfg_disk));
		if (cfg_disk == NULL)
			return (ENOMEM);

		/* Set default flags */
		cfg_disk->flags = CFG_DISK_ALL;
		cfg_disk->query = NULL;
		cfg_disk->disks = NULL;

		host->cfg_disk = cfg_disk;
	}
	cfg_disk = host->cfg_disk;

	for (int i = 0; i < ci->children_num; ++i) {
		oconfig_item_t *item = ci->children + i;

		/* if (!item || !item->key || !*item->key) continue; */
		if (strcasecmp(item->key, "Interval") == 0)
			cna_config_get_interval (item, &cfg_disk->interval);
		else if (strcasecmp(item->key, "GetBusy") == 0)
			cna_config_bool_to_flag (item, &cfg_disk->flags, CFG_DISK_BUSIEST);
	}

	if ((cfg_disk->flags & CFG_DISK_ALL) == 0)
	{
		NOTICE ("netapp plugin: All disk related values have been disabled. "
				"Collection of per-disk data will be disabled entirely.");
		free_cfg_disk (host->cfg_disk);
		host->cfg_disk = NULL;
	}

	return (0);
}