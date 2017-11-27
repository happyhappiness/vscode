static int sensor_threshold_event_handler(
    ipmi_sensor_t *sensor, enum ipmi_event_dir_e dir,
    enum ipmi_thresh_e threshold, enum ipmi_event_value_dir_e high_low,
    enum ipmi_value_present_e value_present, unsigned int raw_value,
    double value, void *cb_data, ipmi_event_t *event) {

  c_ipmi_instance_t *st = cb_data;

  /* From the IPMI specification Chapter 2: Events.
   * If a callback handles the event, then all future callbacks called due to
   * the event will receive a NULL for the event. So be ready to handle a NULL
   * event in all your event handlers. A NULL may also be passed to an event
   * handler if the callback was not due to an event. */
  if (event == NULL)
    return IPMI_EVENT_NOT_HANDLED;

  notification_t n = c_ipmi_notification_init(st, NOTIF_OKAY);
  /* offset is a table index and it's represented as enum of strings that are
     organized in the way - high and low for each threshold severity level */
  unsigned int offset = (2 * threshold) + high_low;
  unsigned int event_type = ipmi_sensor_get_event_reading_type(sensor);
  unsigned int sensor_type = ipmi_sensor_get_sensor_type(sensor);
  const char *event_state =
      ipmi_get_reading_name(event_type, sensor_type, offset);
  sensor_get_name(sensor, n.type_instance, sizeof(n.type_instance));
  if (value_present != IPMI_NO_VALUES_PRESENT)
    snprintf(n.message, sizeof(n.message),
             "sensor %s received event: %s, value is %f", n.type_instance,
             event_state, value);
  else
    snprintf(n.message, sizeof(n.message),
             "sensor %s received event: %s, value not provided",
             n.type_instance, event_state);

  DEBUG("Threshold event received for sensor %s", n.type_instance);

  sstrncpy(n.type, ipmi_sensor_get_sensor_type_string(sensor), sizeof(n.type));
  n.severity = sensor_convert_threshold_severity(threshold);
  n.time = NS_TO_CDTIME_T(ipmi_event_get_timestamp(event));

  plugin_notification_meta_add_string(&n, "severity",
                                      ipmi_get_threshold_string(threshold));
  plugin_notification_meta_add_string(&n, "direction",
                                      ipmi_get_value_dir_string(high_low));

  switch (value_present) {
  case IPMI_BOTH_VALUES_PRESENT:
    plugin_notification_meta_add_double(&n, "val", value);
  /* both values present, so fall-through to add raw value too */
  case IPMI_RAW_VALUE_PRESENT: {
    char buf[DATA_MAX_NAME_LEN] = {0};
    snprintf(buf, sizeof(buf), "0x%2.2x", raw_value);
    plugin_notification_meta_add_string(&n, "raw", buf);
  } break;
  default:
    break;
  } /* switch (value_present) */

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