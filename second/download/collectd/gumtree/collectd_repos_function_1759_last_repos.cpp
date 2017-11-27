static riemann_message_t *
wrr_notification_to_message(struct riemann_host *host, /* {{{ */
                            notification_t const *n) {
  riemann_message_t *msg;
  riemann_event_t *event;
  char service_buffer[6 * DATA_MAX_NAME_LEN];
  char const *severity;

  switch (n->severity) {
  case NOTIF_OKAY:
    severity = "ok";
    break;
  case NOTIF_WARNING:
    severity = "warning";
    break;
  case NOTIF_FAILURE:
    severity = "critical";
    break;
  default:
    severity = "unknown";
  }

  format_name(service_buffer, sizeof(service_buffer),
              /* host = */ "", n->plugin, n->plugin_instance, n->type,
              n->type_instance);

  event = riemann_event_create(
      RIEMANN_EVENT_FIELD_HOST, n->host, RIEMANN_EVENT_FIELD_TIME,
      (int64_t)CDTIME_T_TO_TIME_T(n->time), RIEMANN_EVENT_FIELD_TAGS,
      "notification", NULL, RIEMANN_EVENT_FIELD_STATE, severity,
      RIEMANN_EVENT_FIELD_SERVICE, &service_buffer[1],
      RIEMANN_EVENT_FIELD_NONE);

#if RCC_VERSION_NUMBER >= 0x010A00
  riemann_event_set(event, RIEMANN_EVENT_FIELD_TIME_MICROS,
                    (int64_t)CDTIME_T_TO_US(n->time));
#endif

  if (n->host[0] != 0)
    riemann_event_string_attribute_add(event, "host", n->host);
  if (n->plugin[0] != 0)
    riemann_event_string_attribute_add(event, "plugin", n->plugin);
  if (n->plugin_instance[0] != 0)
    riemann_event_string_attribute_add(event, "plugin_instance",
                                       n->plugin_instance);

  if (n->type[0] != 0)
    riemann_event_string_attribute_add(event, "type", n->type);
  if (n->type_instance[0] != 0)
    riemann_event_string_attribute_add(event, "type_instance",
                                       n->type_instance);

  for (size_t i = 0; i < riemann_attrs_num; i += 2)
    riemann_event_string_attribute_add(event, riemann_attrs[i],
                                       riemann_attrs[i + 1]);

  for (size_t i = 0; i < riemann_tags_num; i++)
    riemann_event_tag_add(event, riemann_tags[i]);

  if (n->message[0] != 0)
    riemann_event_string_attribute_add(event, "description", n->message);

  /* Pull in values from threshold and add extra attributes */
  for (notification_meta_t *meta = n->meta; meta != NULL; meta = meta->next) {
    if (strcasecmp("CurrentValue", meta->name) == 0 &&
        meta->type == NM_TYPE_DOUBLE) {
      riemann_event_set(event, RIEMANN_EVENT_FIELD_METRIC_D,
                        (double)meta->nm_value.nm_double,
                        RIEMANN_EVENT_FIELD_NONE);
      continue;
    }

    if (meta->type == NM_TYPE_STRING) {
      riemann_event_string_attribute_add(event, meta->name,
                                         meta->nm_value.nm_string);
      continue;
    }
  }

  msg = riemann_message_create_with_events(event, NULL);
  if (msg == NULL) {
    ERROR("write_riemann plugin: riemann_message_create_with_events() failed.");
    riemann_event_free(event);
    return NULL;
  }

  DEBUG("write_riemann plugin: Successfully created message for notification: "
        "host = \"%s\", service = \"%s\", state = \"%s\"",
        event->host, event->service, event->state);
  return msg;
}