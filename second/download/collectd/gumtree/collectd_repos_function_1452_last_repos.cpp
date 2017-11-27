static int ovs_events_config_get_interfaces(const oconfig_item_t *ci) {
  for (int j = 0; j < ci->values_num; j++) {
    /* check interface name type */
    if (ci->values[j].type != OCONFIG_TYPE_STRING) {
      ERROR(OVS_EVENTS_PLUGIN ": given interface name is not a string [idx=%d]",
            j);
      return -1;
    }
    /* allocate memory for configured interface */
    ovs_events_iface_list_t *new_iface = calloc(1, sizeof(*new_iface));
    if (new_iface == NULL) {
      ERROR(OVS_EVENTS_PLUGIN ": calloc () copy interface name fail");
      return -1;
    } else {
      /* store interface name */
      sstrncpy(new_iface->name, ci->values[j].value.string,
               sizeof(new_iface->name));
      new_iface->next = ovs_events_ctx.config.ifaces;
      ovs_events_ctx.config.ifaces = new_iface;
      DEBUG(OVS_EVENTS_PLUGIN ": found monitored interface \"%s\"",
            new_iface->name);
    }
  }
  return 0;
}