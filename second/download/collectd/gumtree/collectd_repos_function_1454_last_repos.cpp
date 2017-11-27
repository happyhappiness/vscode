static void
ovs_events_dispatch_notification(const ovs_events_iface_info_t *ifinfo) {
  const char *msg_link_status = NULL;
  notification_t n = {
      NOTIF_FAILURE, cdtime(), "", "", OVS_EVENTS_PLUGIN, "", "", "", NULL};

  /* convert link status to message string */
  switch (ifinfo->link_status) {
  case UP:
    msg_link_status = "UP";
    n.severity = NOTIF_OKAY;
    break;
  case DOWN:
    msg_link_status = "DOWN";
    n.severity = NOTIF_WARNING;
    break;
  default:
    ERROR(OVS_EVENTS_PLUGIN ": unknown interface link status");
    return;
  }

  /* add interface metadata to the notification */
  if (plugin_notification_meta_add_string(&n, "uuid", ifinfo->uuid) < 0) {
    ERROR(OVS_EVENTS_PLUGIN ": add interface uuid meta data failed");
    return;
  }

  if (strlen(ifinfo->ext_vm_uuid) > 0) {
    if (plugin_notification_meta_add_string(&n, "vm-uuid",
                                            ifinfo->ext_vm_uuid) < 0) {
      ERROR(OVS_EVENTS_PLUGIN ": add interface vm-uuid meta data failed");
      return;
    }
  }

  if (strlen(ifinfo->ext_iface_id) > 0) {
    if (plugin_notification_meta_add_string(&n, "iface-id",
                                            ifinfo->ext_iface_id) < 0) {
      ERROR(OVS_EVENTS_PLUGIN ": add interface iface-id meta data failed");
      return;
    }
  }

  /* fill the notification data */
  snprintf(n.message, sizeof(n.message),
           "link state of \"%s\" interface has been changed to \"%s\"",
           ifinfo->name, msg_link_status);
  sstrncpy(n.host, hostname_g, sizeof(n.host));
  sstrncpy(n.plugin_instance, ifinfo->name, sizeof(n.plugin_instance));
  sstrncpy(n.type, "gauge", sizeof(n.type));
  sstrncpy(n.type_instance, "link_status", sizeof(n.type_instance));
  plugin_dispatch_notification(&n);
}