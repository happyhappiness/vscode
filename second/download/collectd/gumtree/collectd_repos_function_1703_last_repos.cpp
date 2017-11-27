static int snmp_agent_init(void) {
  int ret;

  if (g_agent == NULL || ((llist_head(g_agent->scalars) == NULL) &&
                          (llist_head(g_agent->tables) == NULL))) {
    ERROR(PLUGIN_NAME ": snmp_agent_init: plugin not configured");
    return -EINVAL;
  }

  plugin_register_shutdown(PLUGIN_NAME, snmp_agent_shutdown);

  ret = snmp_agent_register_scalar_oids();
  if (ret != 0)
    return ret;

  ret = snmp_agent_register_table_oids();
  if (ret != 0)
    return ret;

  ret = pthread_mutex_init(&g_agent->lock, NULL);
  if (ret != 0) {
    ERROR(PLUGIN_NAME ": Failed to initialize mutex, err %u", ret);
    return ret;
  }

  ret = pthread_mutex_init(&g_agent->agentx_lock, NULL);
  if (ret != 0) {
    ERROR(PLUGIN_NAME ": Failed to initialize AgentX mutex, err %u", ret);
    return ret;
  }

  /* create a second thread to listen for requests from AgentX*/
  ret = pthread_create(&g_agent->thread, NULL, &snmp_agent_thread_run, NULL);
  if (ret != 0) {
    ERROR(PLUGIN_NAME ": Failed to create a separate thread, err %u", ret);
    return ret;
  }

  if (llist_head(g_agent->tables) != NULL) {
    plugin_register_write(PLUGIN_NAME, snmp_agent_collect, NULL);
    plugin_register_missing(PLUGIN_NAME, snmp_agent_clear_missing, NULL);
  }

  return 0;
}