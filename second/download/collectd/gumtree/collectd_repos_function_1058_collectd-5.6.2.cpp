static int cgps_init(void) {
  int status;

  if (cgps_thread_running == CGPS_TRUE) {
    DEBUG("gps plugin: error gps thread already running ... ");
    return 0;
  }

  DEBUG("gps plugin: config{host: \"%s\", port: \"%s\", timeout: %.6f sec., "
        "pause connect: %.3f sec.}",
        cgps_config_data.host, cgps_config_data.port,
        CDTIME_T_TO_DOUBLE(cgps_config_data.timeout),
        CDTIME_T_TO_DOUBLE(cgps_config_data.pause_connect));

  status = plugin_thread_create(&cgps_thread_id, NULL, cgps_thread, NULL);
  if (status != 0) {
    ERROR("gps plugin: pthread_create() failed.");
    return (-1);
  }

  return (0);
}