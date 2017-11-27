static Msg *riemann_notification_to_protobuf(struct riemann_host *host, /* {{{ */
		notification_t const *n)
{
	Msg *msg;
	Event *event;
	char service_buffer[6 * DATA_MAX_NAME_LEN];
	char const *severity;
	notification_meta_t *meta;
	int i;

	msg = malloc (sizeof (*msg));
	if (msg == NULL)
	{
		ERROR ("write_riemann plugin: malloc failed.");
		return (NULL);
	}
	memset (msg, 0, sizeof (*msg));
	msg__init (msg);

	msg->events = malloc (sizeof (*msg->events));
	if (msg->events == NULL)
	{
		ERROR ("write_riemann plugin: malloc failed.");
		sfree (msg);
		return (NULL);
	}

	event = malloc (sizeof (*event));
	if (event == NULL)
	{
		ERROR ("write_riemann plugin: malloc failed.");
		sfree (msg->events);
		sfree (msg);
		return (NULL);
	}
	memset (event, 0, sizeof (*event));
	event__init (event);

	msg->events[0] = event;
	msg->n_events = 1;

	event->host = strdup (n->host);
	event->time = CDTIME_T_TO_TIME_T (n->time);
	event->has_time = 1;

	switch (n->severity)
	{
		case NOTIF_OKAY:	severity = "ok"; break;
		case NOTIF_WARNING:	severity = "warning"; break;
		case NOTIF_FAILURE:	severity = "critical"; break;
		default:		severity = "unknown";
	}
	event->state = strdup (severity);

	riemann_event_add_tag (event, "notification");
	if (n->host[0] != 0)
		riemann_event_add_attribute (event, "host", n->host);
	if (n->plugin[0] != 0)
		riemann_event_add_attribute (event, "plugin", n->plugin);
	if (n->plugin_instance[0] != 0)
		riemann_event_add_attribute (event, "plugin_instance",
				n->plugin_instance);

	if (n->type[0] != 0)
		riemann_event_add_attribute (event, "type", n->type);
	if (n->type_instance[0] != 0)
		riemann_event_add_attribute (event, "type_instance",
				n->type_instance);

	for (i = 0; i < riemann_attrs_num; i += 2)
		riemann_event_add_attribute(event,
					    riemann_attrs[i],
					    riemann_attrs[i +1]);

	for (i = 0; i < riemann_tags_num; i++)
		riemann_event_add_tag (event, riemann_tags[i]);

	format_name (service_buffer, sizeof (service_buffer),
			/* host = */ "", n->plugin, n->plugin_instance,
			n->type, n->type_instance);
	event->service = strdup (&service_buffer[1]);

	if (n->message[0] != 0)
		riemann_event_add_attribute (event, "description", n->message);

	/* Pull in values from threshold and add extra attributes */
	for (meta = n->meta; meta != NULL; meta = meta->next)
	{
		if (strcasecmp ("CurrentValue", meta->name) == 0 && meta->type == NM_TYPE_DOUBLE)
		{
			event->metric_d = meta->nm_value.nm_double;
			event->has_metric_d = 1;
			continue;
		}

		if (meta->type == NM_TYPE_STRING) {
			riemann_event_add_attribute (event, meta->name, meta->nm_value.nm_string);
			continue;
		}
	}

	DEBUG ("write_riemann plugin: Successfully created protobuf for notification: "
			"host = \"%s\", service = \"%s\", state = \"%s\"",
			event->host, event->service, event->state);
	return (msg);
}