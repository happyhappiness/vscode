static riemann_event_t *
wrr_value_to_event(struct riemann_host const *host, /* {{{ */
                   data_set_t const *ds, value_list_t const *vl, size_t index,
                   gauge_t const *rates, int status) {
  riemann_event_t *event;
  char name_buffer[5 * DATA_MAX_NAME_LEN];
  char service_buffer[6 * DATA_MAX_NAME_LEN];
  size_t i;

  event = riemann_event_new();
  if (event == NULL) {
    ERROR("write_riemann plugin: riemann_event_new() failed.");
    return NULL;
  }

  format_name(name_buffer, sizeof(name_buffer),
              /* host = */ "", vl->plugin, vl->plugin_instance, vl->type,
              vl->type_instance);
  if (host->always_append_ds || (ds->ds_num > 1)) {
    if (host->event_service_prefix == NULL)
      snprintf(service_buffer, sizeof(service_buffer), "%s/%s", &name_buffer[1],
               ds->ds[index].name);
    else
      snprintf(service_buffer, sizeof(service_buffer), "%s%s/%s",
               host->event_service_prefix, &name_buffer[1], ds->ds[index].name);
  } else {
    if (host->event_service_prefix == NULL)
      sstrncpy(service_buffer, &name_buffer[1], sizeof(service_buffer));
    else
      snprintf(service_buffer, sizeof(service_buffer), "%s%s",
               host->event_service_prefix, &name_buffer[1]);
  }

  riemann_event_set(
      event, RIEMANN_EVENT_FIELD_HOST, vl->host, RIEMANN_EVENT_FIELD_TIME,
      (int64_t)CDTIME_T_TO_TIME_T(vl->time), RIEMANN_EVENT_FIELD_TTL,
      (float)CDTIME_T_TO_DOUBLE(vl->interval) * host->ttl_factor,
      RIEMANN_EVENT_FIELD_STRING_ATTRIBUTES, "plugin", vl->plugin, "type",
      vl->type, "ds_name", ds->ds[index].name, NULL,
      RIEMANN_EVENT_FIELD_SERVICE, service_buffer, RIEMANN_EVENT_FIELD_NONE);

#if RCC_VERSION_NUMBER >= 0x010A00
  riemann_event_set(event, RIEMANN_EVENT_FIELD_TIME_MICROS,
                    (int64_t)CDTIME_T_TO_US(vl->time));
#endif

  if (host->check_thresholds) {
    const char *state = NULL;

    switch (status) {
    case STATE_OKAY:
      state = "ok";
      break;
    case STATE_ERROR:
      state = "critical";
      break;
    case STATE_WARNING:
      state = "warning";
      break;
    case STATE_MISSING:
      state = "unknown";
      break;
    }
    if (state)
      riemann_event_set(event, RIEMANN_EVENT_FIELD_STATE, state,
                        RIEMANN_EVENT_FIELD_NONE);
  }

  if (vl->plugin_instance[0] != 0)
    riemann_event_string_attribute_add(event, "plugin_instance",
                                       vl->plugin_instance);
  if (vl->type_instance[0] != 0)
    riemann_event_string_attribute_add(event, "type_instance",
                                       vl->type_instance);

  if ((ds->ds[index].type != DS_TYPE_GAUGE) && (rates != NULL)) {
    char ds_type[DATA_MAX_NAME_LEN];

    snprintf(ds_type, sizeof(ds_type), "%s:rate",
             DS_TYPE_TO_STRING(ds->ds[index].type));
    riemann_event_string_attribute_add(event, "ds_type", ds_type);
  } else {
    riemann_event_string_attribute_add(event, "ds_type",
                                       DS_TYPE_TO_STRING(ds->ds[index].type));
  }

  {
    char ds_index[DATA_MAX_NAME_LEN];

    snprintf(ds_index, sizeof(ds_index), "%zu", index);
    riemann_event_string_attribute_add(event, "ds_index", ds_index);
  }

  for (i = 0; i < riemann_attrs_num; i += 2)
    riemann_event_string_attribute_add(event, riemann_attrs[i],
                                       riemann_attrs[i + 1]);

  for (i = 0; i < riemann_tags_num; i++)
    riemann_event_tag_add(event, riemann_tags[i]);

  if (ds->ds[index].type == DS_TYPE_GAUGE) {
    riemann_event_set(event, RIEMANN_EVENT_FIELD_METRIC_D,
                      (double)vl->values[index].gauge,
                      RIEMANN_EVENT_FIELD_NONE);
  } else if (rates != NULL) {
    riemann_event_set(event, RIEMANN_EVENT_FIELD_METRIC_D, (double)rates[index],
                      RIEMANN_EVENT_FIELD_NONE);
  } else {
    int64_t metric;

    if (ds->ds[index].type == DS_TYPE_DERIVE)
      metric = (int64_t)vl->values[index].derive;
    else if (ds->ds[index].type == DS_TYPE_ABSOLUTE)
      metric = (int64_t)vl->values[index].absolute;
    else
      metric = (int64_t)vl->values[index].counter;

    riemann_event_set(event, RIEMANN_EVENT_FIELD_METRIC_S64, (int64_t)metric,
                      RIEMANN_EVENT_FIELD_NONE);
  }

  DEBUG("write_riemann plugin: Successfully created message for metric: "
        "host = \"%s\", service = \"%s\"",
        event->host, event->service);
  return event;
}