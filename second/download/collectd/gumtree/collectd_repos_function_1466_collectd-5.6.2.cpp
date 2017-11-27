static void smart_handle_disk_attribute(SkDisk *d,
                                        const SkSmartAttributeParsedData *a,
                                        void *userdata) {
  const char *dev = userdata;
  value_t values[4];
  value_list_t vl = VALUE_LIST_INIT;

  if (!a->current_value_valid || !a->worst_value_valid)
    return;
  values[0].gauge = a->current_value;
  values[1].gauge = a->worst_value;
  values[2].gauge = a->threshold_valid ? a->threshold : 0;
  values[3].gauge = a->pretty_value;

  vl.values = values;
  vl.values_len = 4;
  sstrncpy(vl.host, hostname_g, sizeof(vl.host));
  sstrncpy(vl.plugin, "smart", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, dev, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, "smart_attribute", sizeof(vl.type));
  sstrncpy(vl.type_instance, a->name, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);

  if (a->threshold_valid && a->current_value <= a->threshold) {
    notification_t notif = {NOTIF_WARNING,     cdtime(), "",  "", "smart", "",
                            "smart_attribute", "",       NULL};
    sstrncpy(notif.host, hostname_g, sizeof(notif.host));
    sstrncpy(notif.plugin_instance, dev, sizeof(notif.plugin_instance));
    sstrncpy(notif.type_instance, a->name, sizeof(notif.type_instance));
    ssnprintf(notif.message, sizeof(notif.message),
              "attribute %s is below allowed threshold (%d < %d)", a->name,
              a->current_value, a->threshold);
    plugin_dispatch_notification(&notif);
  }
}