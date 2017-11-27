static void sigrok_feed_callback(const struct sr_dev_inst *sdi,
		const struct sr_datafeed_packet *packet, void *cb_data)
{
	const struct sr_datafeed_analog *analog;
	struct config_device *cfdev;
	GSList *l;
	value_t value;
	value_list_t vl = VALUE_LIST_INIT;

	/* Find this device's configuration. */
	cfdev = NULL;
	for (l = config_devices; l; l = l->next) {
		cfdev = l->data;
		if (cfdev->sdi == sdi) {
			/* Found it. */
			break;
		}
		cfdev = NULL;
	}

	if (!cfdev) {
		ERROR("sigrok plugin: Received data from driver \"%s\" but "
				"can't find a configuration / device matching "
				"it.", sdi->driver->name);
		return;
	}

	if (packet->type == SR_DF_END) {
		/* TODO: try to restart acquisition after a delay? */
		WARNING("sigrok plugin: acquisition for \"%s\" ended.",
				cfdev->name);
		return;
	}

	if (packet->type != SR_DF_ANALOG)
		return;

	if ((cfdev->min_dispatch_interval != 0)
			&& ((cdtime() - cfdev->last_dispatch)
				< cfdev->min_dispatch_interval))
		return;

	/* Ignore all but the first sample on the first probe. */
	analog = packet->payload;
	value.gauge = analog->data[0];
	vl.values = &value;
	vl.values_len = 1;
	sstrncpy(vl.host, hostname_g, sizeof(vl.host));
	sstrncpy(vl.plugin, "sigrok", sizeof(vl.plugin));
	ssnprintf(vl.plugin_instance, sizeof(vl.plugin_instance),
			"%s", cfdev->name);
	sstrncpy(vl.type, sigrok_value_type(analog), sizeof(vl.type));

	plugin_dispatch_values(&vl);
	cfdev->last_dispatch = cdtime();
}