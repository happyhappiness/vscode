static int cna_config_host (host_config_t *host, /* {{{ */
		const oconfig_item_t *ci)
{
	oconfig_item_t *item;
	_Bool is_vfiler = 0;
	int status;

	if (! strcasecmp (ci->key, "VFiler"))
		is_vfiler = 1;

	if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
		WARNING ("netapp plugin: \"%s\" needs exactly one string argument. Ignoring host block.", ci->key);
		return (1);
	}

	status = cf_util_get_string (ci, &host->name);
	if (status != 0)
		return (1);

	for (int i = 0; i < ci->children_num; ++i) {
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
				return (1);
			}
			if (!strcasecmp(item->values[0].value.string, "http")) host->protocol = NA_SERVER_TRANSPORT_HTTP;
			else host->protocol = NA_SERVER_TRANSPORT_HTTPS;
		} else if (!strcasecmp(item->key, "User")) {
			status = cf_util_get_string (item, &host->username);
		} else if (!strcasecmp(item->key, "Password")) {
			status = cf_util_get_string (item, &host->password);
		} else if (!strcasecmp(item->key, "Interval")) {
			status = cf_util_get_cdtime (item, &host->interval);
		} else if (!strcasecmp(item->key, "WAFL")) {
			cna_config_wafl(host, item);
		} else if (!strcasecmp(item->key, "Disks")) {
			cna_config_disk(host, item);
		} else if (!strcasecmp(item->key, "VolumePerf")) {
			cna_config_volume_performance(host, item);
		} else if (!strcasecmp(item->key, "VolumeUsage")) {
			cna_config_volume_usage(host, item);
		} else if (!strcasecmp(item->key, "Quota")) {
			cna_config_quota(host, item);
		} else if (!strcasecmp(item->key, "SnapVault")) {
			cna_config_snapvault(host, item);
		} else if (!strcasecmp(item->key, "System")) {
			cna_config_system(host, item);
		} else if ((!strcasecmp(item->key, "VFiler")) && (! is_vfiler)) {
			host_config_t *vfiler;

			vfiler = cna_shallow_clone_host (host);
			if (! vfiler) {
				ERROR ("netapp plugin: Failed to allocate host object for vfiler.");
				continue;
			}

			if (cna_config_host (vfiler, item)) {
				free_host_config (vfiler);
				continue;
			}

			cna_register_host (vfiler);
		} else if ((!strcasecmp(item->key, "VFilerName")) && is_vfiler) {
			status = cf_util_get_string (item, &host->vfiler);
		} else {
			WARNING ("netapp plugin: Ignoring unknown config option \"%s\" in %s block \"%s\".",
					item->key, is_vfiler ? "vfiler" : "host", ci->values[0].value.string);
		}

		if (status != 0)
			break;
	}

	if (host->host == NULL)
		host->host = strdup (host->name);

	if (is_vfiler && (! host->vfiler))
		host->vfiler = strdup (host->name);

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
		return status;

	return (0);
}