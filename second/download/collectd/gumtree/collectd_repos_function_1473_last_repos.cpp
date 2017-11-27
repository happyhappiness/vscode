static int tt_shutdown(void) {
  sfree(config_host);
  sfree(config_port);

  if (rdb != NULL) {
    if (!tcrdbclose(rdb)) {
      printerr();
      tcrdbdel(rdb);
      return 1;
    }
    tcrdbdel(rdb);
    rdb = NULL;
  }

  return 0;
}