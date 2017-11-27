static void ovs_events_conn_initialize(ovs_db_t *pdb) {
  const char tb_name[] = "Interface";
  const char *columns[] = {"_uuid", "external_ids", "name", "link_state", NULL};

  /* register update link status event if needed */
  if (ovs_events_ctx.config.send_notification) {
    int ret = ovs_db_table_cb_register(pdb, tb_name, columns,
                                       ovs_events_table_update_cb, NULL,
                                       OVS_DB_TABLE_CB_FLAG_MODIFY);
    if (ret < 0) {
      ERROR(OVS_EVENTS_PLUGIN ": register OVS DB update callback failed");
      return;
    }
  }
  OVS_EVENTS_CTX_LOCK { ovs_events_ctx.is_db_available = 1; }
  DEBUG(OVS_EVENTS_PLUGIN ": OVS DB connection has been initialized");
}