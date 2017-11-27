static int wrr_batch_flush_nolock(cdtime_t timeout, struct riemann_host *host) {
  cdtime_t now;
  int status = 0;

  now = cdtime();
  if (timeout > 0) {
    if ((host->batch_init + timeout) > now) {
      return status;
    }
  }
  wrr_send_nolock(host, host->batch_msg);
  riemann_message_free(host->batch_msg);

  host->batch_init = now;
  host->batch_msg = NULL;
  return status;
}