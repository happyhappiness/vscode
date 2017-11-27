static void lv_disconnect(void) {
  if (conn != NULL)
    virConnectClose(conn);
  conn = NULL;
  WARNING(PLUGIN_NAME " plugin: closed connection to libvirt");
}