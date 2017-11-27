static int wrr_send(struct riemann_host *host, riemann_message_t *msg) {
  int status = 0;

  pthread_mutex_lock(&host->lock);
  status = wrr_send_nolock(host, msg);
  pthread_mutex_unlock(&host->lock);
  return status;
}