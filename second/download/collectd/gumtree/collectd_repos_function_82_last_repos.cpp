static int lv_connect(void) {
  if (conn == NULL) {
/* `conn_string == NULL' is acceptable */
#ifdef HAVE_FS_INFO
    /* virDomainGetFSInfo requires full read-write access connection */
    if (extra_stats & ex_stats_fs_info)
      conn = virConnectOpen(conn_string);
    else
#endif
      conn = virConnectOpenReadOnly(conn_string);
    if (conn == NULL) {
      c_complain(LOG_ERR, &conn_complain,
                 PLUGIN_NAME " plugin: Unable to connect: "
                             "virConnectOpen failed.");
      return -1;
    }
    int status = virNodeGetInfo(conn, &nodeinfo);
    if (status != 0) {
      ERROR(PLUGIN_NAME ": virNodeGetInfo failed");
      return -1;
    }
  }
  c_release(LOG_NOTICE, &conn_complain,
            PLUGIN_NAME " plugin: Connection established.");
  return 0;
}