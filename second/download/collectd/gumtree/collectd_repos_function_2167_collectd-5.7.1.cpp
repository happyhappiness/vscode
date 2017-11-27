static void wg_force_reconnect_check(struct wg_callback *cb) {
  cdtime_t now;

  if (cb->reconnect_interval == 0)
    return;

  /* check if address changes if addr_timeout */
  now = cdtime();
  if ((now - cb->last_reconnect_time) < cb->reconnect_interval)
    return;

  /* here we should close connection on next */
  close(cb->sock_fd);
  cb->sock_fd = -1;
  cb->last_reconnect_time = now;
  cb->reconnect_interval_reached = 1;

  INFO("write_graphite plugin: Connection closed after %.3f seconds.",
       CDTIME_T_TO_DOUBLE(now - cb->last_reconnect_time));
}