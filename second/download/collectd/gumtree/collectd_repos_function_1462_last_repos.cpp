static int ovs_events_plugin_init(void) {
  ovs_db_t *ovs_db = NULL;
  ovs_db_callback_t cb = {.post_conn_init = ovs_events_conn_initialize,
                          .post_conn_terminate = ovs_events_conn_terminate};

  DEBUG(OVS_EVENTS_PLUGIN ": OVS DB address=%s, service=%s, unix=%s",
        ovs_events_ctx.config.ovs_db_node, ovs_events_ctx.config.ovs_db_serv,
        ovs_events_ctx.config.ovs_db_unix);

  /* generate OVS DB select condition based on list on configured interfaces */
  ovs_events_ctx.ovs_db_select_params = ovs_events_get_select_params();
  if (ovs_events_ctx.ovs_db_select_params == NULL) {
    ERROR(OVS_EVENTS_PLUGIN ": fail to get OVS DB select condition");
    goto ovs_events_failure;
  }

  /* initialize OVS DB */
  ovs_db = ovs_db_init(ovs_events_ctx.config.ovs_db_node,
                       ovs_events_ctx.config.ovs_db_serv,
                       ovs_events_ctx.config.ovs_db_unix, &cb);
  if (ovs_db == NULL) {
    ERROR(OVS_EVENTS_PLUGIN ": fail to connect to OVS DB server");
    goto ovs_events_failure;
  }

  /* store OVS DB handler */
  OVS_EVENTS_CTX_LOCK { ovs_events_ctx.ovs_db = ovs_db; }

  DEBUG(OVS_EVENTS_PLUGIN ": plugin has been initialized");
  return 0;

ovs_events_failure:
  ERROR(OVS_EVENTS_PLUGIN ": plugin initialize failed");
  /* release allocated memory */
  ovs_events_config_free();
  return -1;
}