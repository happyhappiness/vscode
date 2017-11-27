static int cna_config (oconfig_item_t *ci) { /* {{{ */
	int i;
	oconfig_item_t *item;

	for (i = 0; i < ci->children_num; ++i) {
		item = ci->children + i;

		if (strcasecmp(item->key, "Host") == 0)
		{
			host_config_t *host;

			host = cna_alloc_host ();
			if (host == NULL) {
				ERROR ("netapp plugin: Failed to allocate host object.");
				continue;
			}

			if (cna_config_host (host, item) != 0) {
				free_host_config (host);
				continue;
			}

			cna_register_host (host);
		}
		else /* if (item->key != "Host") */
		{
			WARNING("netapp plugin: Ignoring unknown config option \"%s\".", item->key);
		}
	}
	return 0;
}