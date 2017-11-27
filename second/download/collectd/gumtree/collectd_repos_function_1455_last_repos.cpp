static void
ovs_events_link_status_submit(const ovs_events_iface_info_t *ifinfo) {
  value_list_t vl = VALUE_LIST_INIT;
  meta_data_t *meta = NULL;

  /* add interface metadata to the submit value */
  if ((meta = meta_data_create()) != NULL) {
    if (meta_data_add_string(meta, "uuid", ifinfo->uuid) < 0)
      ERROR(OVS_EVENTS_PLUGIN ": add interface uuid meta data failed");

    if (strlen(ifinfo->ext_vm_uuid) > 0)
      if (meta_data_add_string(meta, "vm-uuid", ifinfo->ext_vm_uuid) < 0)
        ERROR(OVS_EVENTS_PLUGIN ": add interface vm-uuid meta data failed");

    if (strlen(ifinfo->ext_iface_id) > 0)
      if (meta_data_add_string(meta, "iface-id", ifinfo->ext_iface_id) < 0)
        ERROR(OVS_EVENTS_PLUGIN ": add interface iface-id meta data failed");
    vl.meta = meta;
  } else
    ERROR(OVS_EVENTS_PLUGIN ": create metadata failed");

  vl.time = cdtime();
  vl.values = &(value_t){.gauge = (gauge_t)ifinfo->link_status};
  vl.values_len = 1;
  sstrncpy(vl.plugin, OVS_EVENTS_PLUGIN, sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, ifinfo->name, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, "gauge", sizeof(vl.type));
  sstrncpy(vl.type_instance, "link_status", sizeof(vl.type_instance));
  plugin_dispatch_values(&vl);
  meta_data_destroy(meta);
}