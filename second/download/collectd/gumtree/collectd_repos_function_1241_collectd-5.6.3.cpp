static int chrony_shutdown(void) {
  /* Collectd shutdown callback: Free mem */
  if (g_chrony_is_connected != 0) {
    close(g_chrony_socket);
    g_chrony_is_connected = 0;
  }
  if (g_chrony_host != NULL)
    sfree(g_chrony_host);

  if (g_chrony_port != NULL)
    sfree(g_chrony_port);

  if (g_chrony_plugin_instance != NULL)
    sfree(g_chrony_plugin_instance);

  return CHRONY_RC_OK;
}