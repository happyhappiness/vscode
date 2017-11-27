static int sigrok_config(oconfig_item_t *ci)
{
	for (int i = 0; i < ci->children_num; i++) {
		oconfig_item_t *item = ci->children + i;
		if (strcasecmp("LogLevel", item->key) == 0) {
			int status;
			int tmp = -1;

			status = cf_util_get_int (item, &tmp);
			if (status != 0)
				continue;
			else if ((tmp < 0) || (tmp > 5)) {
				ERROR ("sigrok plugin: The \"LogLevel\" "
						"configuration option expects "
						"an integer between 0 and 5 "
						"(inclusive); you provided %i.",
						tmp);
				continue;
			}
			loglevel = tmp;
		} else if (!strcasecmp(item->key, "Device"))
			sigrok_config_device(item);
		else
			WARNING("sigrok plugin: Invalid keyword \"%s\".",
					item->key);
	}

	return 0;
}