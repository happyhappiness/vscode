static void ovs_events_config_free() {
  ovs_events_iface_list_t *del_iface = NULL;
  sfree(ovs_events_ctx.ovs_db_select_params);
  while (ovs_events_ctx.config.ifaces) {
    del_iface = ovs_events_ctx.config.ifaces;
    ovs_events_ctx.config.ifaces = ovs_events_ctx.config.ifaces->next;
    sfree(del_iface);
  }
}