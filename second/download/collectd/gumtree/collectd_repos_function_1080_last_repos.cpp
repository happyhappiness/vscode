static int mcelog_init(void) {
  if (mcelog_apply_defaults) {
    INFO(MCELOG_PLUGIN
         ": No configuration selected defaulting to memory errors.");
    memset(g_mcelog_config.logfile, 0, sizeof(g_mcelog_config.logfile));
  }
  g_mcelog_config.dimms_list = llist_create();
  int err = pthread_mutex_init(&g_mcelog_config.dimms_lock, NULL);
  if (err < 0) {
    ERROR(MCELOG_PLUGIN ": plugin: failed to initialize cache lock");
    return -1;
  }

  if (socket_adapter.reinit(&socket_adapter) != 0) {
    ERROR(MCELOG_PLUGIN ": Cannot connect to client socket");
    return -1;
  }

  if (strlen(socket_adapter.unix_sock.sun_path)) {
    if (plugin_thread_create(&g_mcelog_config.tid, NULL, poll_worker, NULL,
                             NULL) != 0) {
      ERROR(MCELOG_PLUGIN ": Error creating poll thread.");
      return -1;
    }
  }
  return 0;
}