static int snmp_agent_shutdown(void) {
  int ret = 0;

  DEBUG(PLUGIN_NAME ": snmp_agent_shutdown");

  if (g_agent == NULL) {
    ERROR(PLUGIN_NAME ": snmp_agent_shutdown: plugin not initialized");
    return -EINVAL;
  }

  if (pthread_cancel(g_agent->thread) != 0)
    ERROR(PLUGIN_NAME ": snmp_agent_shutdown: failed to cancel the thread");

  if (pthread_join(g_agent->thread, NULL) != 0)
    ERROR(PLUGIN_NAME ": snmp_agent_shutdown: failed to join the thread");

  snmp_agent_free_config();

  snmp_shutdown(PLUGIN_NAME);

  pthread_mutex_destroy(&g_agent->lock);
  pthread_mutex_destroy(&g_agent->agentx_lock);

  sfree(g_agent);

  return ret;
}