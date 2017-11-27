int plugin_dispatch_values(value_list_t const *vl) {
  int status;
  static pthread_mutex_t statistics_lock = PTHREAD_MUTEX_INITIALIZER;

  if (check_drop_value()) {
    if (record_statistics) {
      pthread_mutex_lock(&statistics_lock);
      stats_values_dropped++;
      pthread_mutex_unlock(&statistics_lock);
    }
    return 0;
  }

  status = plugin_write_enqueue(vl);
  if (status != 0) {
    char errbuf[1024];
    ERROR("plugin_dispatch_values: plugin_write_enqueue failed "
          "with status %i (%s).",
          status, sstrerror(status, errbuf, sizeof(errbuf)));
    return status;
  }

  return 0;
}