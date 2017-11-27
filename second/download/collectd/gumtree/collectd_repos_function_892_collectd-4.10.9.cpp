static host_config_t *cna_config_host (const oconfig_item_t *ci) /* {{{ */
{
	oconfig_item_t *item;
	host_config_t *host;
	int status;
	int i;
	
	if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
		WARNING("netapp plugin: \"Host\" needs exactly one string argument. Ignoring host block.");
		return 0;
	}

	host = malloc(sizeof(*host));
	memset (host, 0, sizeof (*host));
	host->name = NULL;
	host->protocol = NA_SERVER_TRANSPORT_HTTPS;
	host->host = NULL;
	host->username = NULL;
	host->password = NULL;
	host->srv = NULL;
	host->cfg_wafl = NULL;
	host->cfg_disk = NULL;
	host->cfg_volume_perf = NULL;
	host->cfg_volume_usage = NULL;
	host->cfg_system = NULL;

	status = cf_util_get_string (ci, &host->name);
	if (status != 0)
	{
		sfree (host);
		return (NULL);
	}

	for (i = 0; i < ci->children_num; ++i) {
		item = ci->children + i;

		status = 0;

		if (!strcasecmp(item->key, "Address")) {
			status = cf_util_get_string (item, &host->host);
		} else if (!strcasecmp(item->key, "Port")) {
			int tmp;

			tmp = cf_util_get_port_number (item);
			if (tmp > 0)
				host->port = tmp;
		} else if (!strcasecmp(item->key, "Protocol")) {
			if ((item->values_num != 1) || (item->values[0].type != OCONFIG_TYPE_STRING) || (strcasecmp(item->values[0].value.string, "http") && strcasecmp(item->values[0].value.string, "https"))) {
				WARNING("netapp plugin: \"Protocol\" needs to be either \"http\" or \"https\". Ignoring host block \"%s\".", ci->values[0].value.string);
				return 0;
			}
			if (!strcasecmp(item->values[0].value.string, "http")) host->protocol = NA_SERVER_TRANSPORT_HTTP;
			else host->protocol = NA_SERVER_TRANSPORT_HTTPS;
		} else if (!strcasecmp(item->key, "User")) {
			status = cf_util_get_string (item, &host->username);
		} else if (!strcasecmp(item->key, "Password")) {
			status = cf_util_get_string (item, &host->password);
		} else if (!strcasecmp(item->key, "Interval")) {
			if (item->values_num != 1 || item->values[0].type != OCONFIG_TYPE_NUMBER || item->values[0].value.number != (int) item->values[0].value.number || item->values[0].value.number < 2) {
				WARNING("netapp plugin: \"Interval\" of host %s needs exactly one integer argument.", ci->values[0].value.string);
				continue;
			}
			host->interval = item->values[0].value.number;
		} else if (!strcasecmp(item->key, "WAFL")) {
			cna_config_wafl(host, item);
		} else if (!strcasecmp(item->key, "Disks")) {
			cna_config_disk(host, item);
		} else if (!strcasecmp(item->key, "VolumePerf")) {
			cna_config_volume_performance(host, item);
		} else if (!strcasecmp(item->key, "VolumeUsage")) {
			cna_config_volume_usage(host, item);
		} else if (!strcasecmp(item->key, "System")) {
			cna_config_system(host, item);
		} else {
			WARNING("netapp plugin: Ignoring unknown config option \"%s\" in host block \"%s\".",
					item->key, ci->values[0].value.string);
		}

		if (status != 0)
			break;
	}

	if (host->host == NULL)
		host->host = strdup (host->name);

	if (host->host == NULL)
		status = -1;

	if (host->port <= 0)
		host->port = (host->protocol == NA_SERVER_TRANSPORT_HTTP) ? 80 : 443;

	if ((host->username == NULL) || (host->password == NULL)) {
		WARNING("netapp plugin: Please supply login information for host \"%s\". "
				"Ignoring host block.", host->name);
		status = -1;
	}

	if (status != 0)
	{
		free_host_config (host);
		return (NULL);
	}

	return host;
}