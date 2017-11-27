static int sigrok_config_device(oconfig_item_t *ci)
{
	struct config_device *cfdev;
	int i;

	if (!(cfdev = malloc(sizeof(struct config_device)))) {
		ERROR("sigrok plugin: malloc() failed.");
		return -1;
	}
	memset(cfdev, 0, sizeof(*cfdev));
	if (cf_util_get_string(ci, &cfdev->name)) {
		free(cfdev);
		WARNING("sigrok plugin: Invalid device name.");
		return -1;
	}
	cfdev->min_dispatch_interval = DEFAULT_MIN_DISPATCH_INTERVAL;

	for (i = 0; i < ci->children_num; i++) {
		oconfig_item_t *item = ci->children + i;
		if (!strcasecmp(item->key, "driver"))
			cf_util_get_string(item, &cfdev->driver);
		else if (!strcasecmp(item->key, "conn"))
			cf_util_get_string(item, &cfdev->conn);
		else if (!strcasecmp(item->key, "serialcomm"))
			cf_util_get_string(item, &cfdev->serialcomm);
		else if (!strcasecmp(item->key, "minimuminterval"))
			cf_util_get_cdtime(item, &cfdev->min_dispatch_interval);
		else
			WARNING("sigrok plugin: Invalid keyword \"%s\".",
					item->key);
	}

	config_devices = g_slist_append(config_devices, cfdev);

	return 0;
}