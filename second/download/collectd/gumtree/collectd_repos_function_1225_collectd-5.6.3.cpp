static int chrony_set_timeout(void) {
  /* Set the socket's  timeout to g_chrony_timeout; a value of 0 signals
   * infinite timeout */
  /* Returns 0 on success, !0 on error (check errno) */

  struct timeval tv;
  tv.tv_sec = g_chrony_timeout;
  tv.tv_usec = 0;

  assert(g_chrony_socket >= 0);
  if (setsockopt(g_chrony_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,
                 sizeof(struct timeval)) < 0) {
    return CHRONY_RC_FAIL;
  }
  return CHRONY_RC_OK;
}