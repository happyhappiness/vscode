static void add_event_common_data(notification_t *n, ipmi_sensor_t *sensor,
                                  enum ipmi_event_dir_e dir,
                                  ipmi_event_t *event) {
  ipmi_entity_t *ent = ipmi_sensor_get_entity(sensor);

  plugin_notification_meta_add_string(n, "entity_name",
                                      ipmi_entity_get_entity_id_string(ent));
  plugin_notification_meta_add_signed_int(n, "entity_id",
                                          ipmi_entity_get_entity_id(ent));
  plugin_notification_meta_add_signed_int(n, "entity_instance",
                                          ipmi_entity_get_entity_instance(ent));
  plugin_notification_meta_add_boolean(n, "assert", dir == IPMI_ASSERTION);

  if (event)
    plugin_notification_meta_add_signed_int(n, "event_type",
                                            ipmi_event_get_type(event));
}