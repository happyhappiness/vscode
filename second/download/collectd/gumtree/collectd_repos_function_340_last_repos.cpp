static int us_init(void) {
  static int have_init = 0;

  int status;

  /* Initialize only once. */
  if (have_init != 0)
    return 0;
  have_init = 1;

  loop = 1;

  status = plugin_thread_create(&listen_thread, NULL, us_server_thread, NULL,
                                "unixsock listen");
  if (status != 0) {
    char errbuf[1024];
    ERROR("unixsock plugin: pthread_create failed: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  return 0;
}