static int sensu_notification(const notification_t *n,
                              user_data_t *ud) /* {{{ */
{
  int status;
  struct sensu_host *host = ud->data;
  char *msg;

  pthread_mutex_lock(&host->lock);

  msg = sensu_notification_to_json(host, n);
  if (msg == NULL) {
    pthread_mutex_unlock(&host->lock);
    return -1;
  }

  status = sensu_send(host, msg);
  free(msg);
  if (status != 0)
    ERROR("write_sensu plugin: sensu_send failed with status %i", status);
  pthread_mutex_unlock(&host->lock);

  return status;
}