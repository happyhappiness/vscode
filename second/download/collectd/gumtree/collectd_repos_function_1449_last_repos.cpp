static int ovs_events_config_iface_exists(const char *ifname) {
  if (ovs_events_ctx.config.ifaces == NULL)
    return -1;

  /* check if given interface exists */
  for (ovs_events_iface_list_t *iface = ovs_events_ctx.config.ifaces; iface;
       iface = iface->next)
    if (strcmp(ifname, iface->name) == 0)
      return 1;

  return 0;
}