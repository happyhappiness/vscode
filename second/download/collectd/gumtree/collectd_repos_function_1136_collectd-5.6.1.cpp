static int cna_config_volume_usage(host_config_t *host, /* {{{ */
		const oconfig_item_t *ci)
{
	cfg_volume_usage_t *cfg_volume_usage;

	if ((host == NULL) || (ci == NULL))
		return (EINVAL);

	if (host->cfg_volume_usage == NULL)
	{
		cfg_volume_usage = calloc (1, sizeof (*cfg_volume_usage));
		if (cfg_volume_usage == NULL)
			return (ENOMEM);

		/* Set default flags */
		cfg_volume_usage->query = NULL;
		cfg_volume_usage->volumes = NULL;

		cfg_volume_usage->il_capacity = ignorelist_create (/* invert = */ 1);
		if (cfg_volume_usage->il_capacity == NULL)
		{
			sfree (cfg_volume_usage);
			return (ENOMEM);
		}

		cfg_volume_usage->il_snapshot = ignorelist_create (/* invert = */ 1);
		if (cfg_volume_usage->il_snapshot == NULL)
		{
			ignorelist_free (cfg_volume_usage->il_capacity);
			sfree (cfg_volume_usage);
			return (ENOMEM);
		}

		host->cfg_volume_usage = cfg_volume_usage;
	}
	cfg_volume_usage = host->cfg_volume_usage;

	for (int i = 0; i < ci->children_num; ++i) {
		oconfig_item_t *item = ci->children + i;

		/* if (!item || !item->key || !*item->key) continue; */
		if (strcasecmp(item->key, "Interval") == 0)
			cna_config_get_interval (item, &cfg_volume_usage->interval);
		else if (!strcasecmp(item->key, "GetCapacity"))
			cna_config_volume_usage_option (cfg_volume_usage, item);
		else if (!strcasecmp(item->key, "GetSnapshot"))
			cna_config_volume_usage_option (cfg_volume_usage, item);
		else if (!strcasecmp(item->key, "IgnoreSelectedCapacity"))
			cna_config_volume_usage_default (cfg_volume_usage, item);
		else if (!strcasecmp(item->key, "IgnoreSelectedSnapshot"))
			cna_config_volume_usage_default (cfg_volume_usage, item);
		else
			WARNING ("netapp plugin: The option %s is not allowed within "
					"`VolumeUsage' blocks.", item->key);
	}

	return (0);
}