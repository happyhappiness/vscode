static int sensor_discrete_event_handler(ipmi_sensor_t *sensor,
                                         enum ipmi_event_dir_e dir, int offset,
                                         int severity, int prev_severity,
                                         void *cb_data, ipmi_event_t *event) {

  c_ipmi_instance_t *st = cb_data;

  /* From the IPMI specification Chapter 2: Events.
   * If a callback handles the event, then all future callbacks called due to
   * the event will receive a NULL for the event. So be ready to handle a NULL
   * event in all your event handlers. A NULL may also be passed to an event
   * handler if the callback was not due to an event. */
  if (event == NULL)
    return IPMI_EVENT_NOT_HANDLED;

  notification_t n = c_ipmi_notification_init(st, NOTIF_OKAY);
  unsigned int event_type = ipmi_sensor_get_event_reading_type(sensor);
  unsigned int sensor_type = ipmi_sensor_get_sensor_type(sensor);
  const char *event_state =
      ipmi_get_reading_name(event_type, sensor_type, offset);
  sensor_get_name(sensor, n.type_instance, sizeof(n.type_instance));
  snprintf(n.message, sizeof(n.message), "sensor %s received event: %s",
           n.type_instance, event_state);

  DEBUG("Discrete event received for sensor %s", n.type_instance);

  sstrncpy(n.type, ipmi_sensor_get_sensor_type_string(sensor), sizeof(n.type));
  n.time = NS_TO_CDTIME_T(ipmi_event_get_timestamp(event));

  plugin_notification_meta_add_signed_int(&n, "offset", offset);

  if (severity != -1)
    plugin_notification_meta_add_signed_int(&n, "severity", severity);

  if (prev_severity != -1)
    plugin_notification_meta_add_signed_int(&n, "prevseverity", prev_severity);

  add_event_common_data(&n, sensor, dir, event);

  plugin_dispatch_notification(&n);
  plugin_notification_meta_free(n.meta);

  /* Delete handled ipmi event from the list */
  if (st->sel_clear_event) {
    ipmi_event_delete(event, NULL, NULL);
    return IPMI_EVENT_HANDLED;
  }

  return IPMI_EVENT_NOT_HANDLED;
}