static Event *riemann_value_to_protobuf(struct riemann_host const *host, /* {{{ */
		data_set_t const *ds,
		value_list_t const *vl, size_t index,
					 gauge_t const *rates,
					 int status)
{
	Event *event;
	char name_buffer[5 * DATA_MAX_NAME_LEN];
	char service_buffer[6 * DATA_MAX_NAME_LEN];
	double ttl;
	int i;

	event = malloc (sizeof (*event));
	if (event == NULL)
	{
		ERROR ("write_riemann plugin: malloc failed.");
		return (NULL);
	}
	memset (event, 0, sizeof (*event));
	event__init (event);

	event->host = strdup (vl->host);
	event->time = CDTIME_T_TO_TIME_T (vl->time);
	event->has_time = 1;

	if (host->check_thresholds) {
		switch (status) {
			case STATE_OKAY:
				event->state = strdup("ok");
				break;
			case STATE_ERROR:
				event->state = strdup("critical");
				break;
			case STATE_WARNING:
				event->state = strdup("warning");
				break;
			case STATE_MISSING:
				event->state = strdup("unknown");
				break;
		}
	}

	ttl = CDTIME_T_TO_DOUBLE (vl->interval) * host->ttl_factor;
	event->ttl = (float) ttl;
	event->has_ttl = 1;

	riemann_event_add_attribute (event, "plugin", vl->plugin);
	if (vl->plugin_instance[0] != 0)
		riemann_event_add_attribute (event, "plugin_instance",
				vl->plugin_instance);

	riemann_event_add_attribute (event, "type", vl->type);
	if (vl->type_instance[0] != 0)
		riemann_event_add_attribute (event, "type_instance",
				vl->type_instance);

	if ((ds->ds[index].type != DS_TYPE_GAUGE) && (rates != NULL))
	{
		char ds_type[DATA_MAX_NAME_LEN];

		ssnprintf (ds_type, sizeof (ds_type), "%s:rate",
				DS_TYPE_TO_STRING(ds->ds[index].type));
		riemann_event_add_attribute (event, "ds_type", ds_type);
	}
	else
	{
		riemann_event_add_attribute (event, "ds_type",
				DS_TYPE_TO_STRING(ds->ds[index].type));
	}
	riemann_event_add_attribute (event, "ds_name", ds->ds[index].name);
	{
		char ds_index[DATA_MAX_NAME_LEN];

		ssnprintf (ds_index, sizeof (ds_index), "%zu", index);
		riemann_event_add_attribute (event, "ds_index", ds_index);
	}

	for (i = 0; i < riemann_attrs_num; i += 2)
		riemann_event_add_attribute(event,
					    riemann_attrs[i],
					    riemann_attrs[i +1]);

	for (i = 0; i < riemann_tags_num; i++)
		riemann_event_add_tag (event, riemann_tags[i]);

	if (ds->ds[index].type == DS_TYPE_GAUGE)
	{
		event->has_metric_d = 1;
		event->metric_d = (double) vl->values[index].gauge;
	}
	else if (rates != NULL)
	{
		event->has_metric_d = 1;
		event->metric_d = (double) rates[index];
	}
	else
	{
		event->has_metric_sint64 = 1;
		if (ds->ds[index].type == DS_TYPE_DERIVE)
			event->metric_sint64 = (int64_t) vl->values[index].derive;
		else if (ds->ds[index].type == DS_TYPE_ABSOLUTE)
			event->metric_sint64 = (int64_t) vl->values[index].absolute;
		else
			event->metric_sint64 = (int64_t) vl->values[index].counter;
	}

	format_name (name_buffer, sizeof (name_buffer),
			/* host = */ "", vl->plugin, vl->plugin_instance,
			vl->type, vl->type_instance);
	if (host->always_append_ds || (ds->ds_num > 1))
	{
		if (host->event_service_prefix == NULL)
			ssnprintf (service_buffer, sizeof (service_buffer), "%s/%s",
					&name_buffer[1], ds->ds[index].name);
		else
			ssnprintf (service_buffer, sizeof (service_buffer), "%s%s/%s",
					host->event_service_prefix, &name_buffer[1], ds->ds[index].name);
	}
	else
	{
		if (host->event_service_prefix == NULL)
			sstrncpy (service_buffer, &name_buffer[1], sizeof (service_buffer));
		else
			ssnprintf (service_buffer, sizeof (service_buffer), "%s%s",
					host->event_service_prefix, &name_buffer[1]);
	}

	event->service = strdup (service_buffer);

	DEBUG ("write_riemann plugin: Successfully created protobuf for metric: "
			"host = \"%s\", service = \"%s\"",
			event->host, event->service);
	return (event);
}