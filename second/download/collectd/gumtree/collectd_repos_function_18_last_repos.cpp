static int try_reconnect(void) {
  int status;

  rrdc_disconnect();

  rrd_clear_error();
  status = rrdc_connect(daemon_address);
  if (status != 0) {
    ERROR("rrdcached plugin: Failed to reconnect to RRDCacheD "
          "at %s: %s (status=%d)",
          daemon_address, rrd_get_error(), status);
    return -1;
  }

  INFO("rrdcached plugin: Successfully reconnected to RRDCacheD "
       "at %s",
       daemon_address);
  return 0;
}