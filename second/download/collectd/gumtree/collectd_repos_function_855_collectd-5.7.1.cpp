static int email_init(void) {
  if (plugin_thread_create(&connector, NULL, open_connection, NULL,
                           "email listener") != 0) {
    char errbuf[1024];
    disabled = 1;
    log_err("plugin_thread_create() failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
    return (-1);
  }

  return (0);
}