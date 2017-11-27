static void handle_attribute(SkDisk *d, const SkSmartAttributeParsedData *a,
                             void *userdata) {
  char const *name = userdata;

  if (!a->current_value_valid || !a->worst_value_valid)
    return;

  value_list_t vl = VALUE_LIST_INIT;
  value_t values[] = {
      {.gauge = a->current_value},
      {.gauge = a->worst_value},
      {.gauge = a->threshold_valid ? a->threshold : 0},
      {.gauge = a->pretty_value},
  };

  vl.values = values;
  vl.values_len = STATIC_ARRAY_SIZE(values);
  sstrncpy(vl.plugin, "smart", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, name, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, "smart_attribute", sizeof(vl.type));
  sstrncpy(vl.type_instance, a->name, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);

  if (a->threshold_valid && a->current_value <= a->threshold) {
    notification_t notif = {NOTIF_WARNING,     cdtime(), "",  "", "smart", "",
                            "smart_attribute", "",       NULL};
    sstrncpy(notif.host, hostname_g, sizeof(notif.host));
    sstrncpy(notif.plugin_instance, name, sizeof(notif.plugin_instance));
    sstrncpy(notif.type_instance, a->name, sizeof(notif.type_instance));
    snprintf(notif.message, sizeof(notif.message),
             "attribute %s is below allowed threshold (%d < %d)", a->name,
             a->current_value, a->threshold);
    plugin_dispatch_notification(&notif);
  }
}