static int cna_config_volume_performance (host_config_t *host, /* {{{ */
		const oconfig_item_t *ci)
{
	cfg_volume_perf_t *cfg_volume_perf;
	int i;

	if ((host == NULL) || (ci == NULL))
		return (EINVAL);

	if (host->cfg_volume_perf == NULL)
	{
		cfg_volume_perf = malloc (sizeof (*cfg_volume_perf));
		if (cfg_volume_perf == NULL)
			return (ENOMEM);
		memset (cfg_volume_perf, 0, sizeof (*cfg_volume_perf));

		/* Set default flags */
		cfg_volume_perf->query = NULL;
		cfg_volume_perf->volumes = NULL;

		cfg_volume_perf->il_octets = ignorelist_create (/* invert = */ 1);
		if (cfg_volume_perf->il_octets == NULL)
		{
			sfree (cfg_volume_perf);
			return (ENOMEM);
		}

		cfg_volume_perf->il_operations = ignorelist_create (/* invert = */ 1);
		if (cfg_volume_perf->il_operations == NULL)
		{
			ignorelist_free (cfg_volume_perf->il_octets);
			sfree (cfg_volume_perf);
			return (ENOMEM);
		}

		cfg_volume_perf->il_latency = ignorelist_create (/* invert = */ 1);
		if (cfg_volume_perf->il_latency == NULL)
		{
			ignorelist_free (cfg_volume_perf->il_octets);
			ignorelist_free (cfg_volume_perf->il_operations);
			sfree (cfg_volume_perf);
			return (ENOMEM);
		}

		host->cfg_volume_perf = cfg_volume_perf;
	}
	cfg_volume_perf = host->cfg_volume_perf;
	
	for (i = 0; i < ci->children_num; ++i) {
		oconfig_item_t *item = ci->children + i;
		
		/* if (!item || !item->key || !*item->key) continue; */
		if (strcasecmp(item->key, "Interval") == 0)
			cna_config_get_interval (item, &cfg_volume_perf->interval);
		else if (!strcasecmp(item->key, "GetIO"))
			cna_config_volume_perf_option (cfg_volume_perf, item);
		else if (!strcasecmp(item->key, "GetOps"))
			cna_config_volume_perf_option (cfg_volume_perf, item);
		else if (!strcasecmp(item->key, "GetLatency"))
			cna_config_volume_perf_option (cfg_volume_perf, item);
		else if (!strcasecmp(item->key, "IgnoreSelectedIO"))
			cna_config_volume_perf_default (cfg_volume_perf, item);
		else if (!strcasecmp(item->key, "IgnoreSelectedOps"))
			cna_config_volume_perf_default (cfg_volume_perf, item);
		else if (!strcasecmp(item->key, "IgnoreSelectedLatency"))
			cna_config_volume_perf_default (cfg_volume_perf, item);
		else
			WARNING ("netapp plugin: The option %s is not allowed within "
					"`VolumePerf' blocks.", item->key);
	}

	return (0);
}