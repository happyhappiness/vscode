static int wrr_batch_add_value_list(struct riemann_host *host, /* {{{ */
                                    data_set_t const *ds,
                                    value_list_t const *vl, int *statuses) {
  riemann_message_t *msg;
  size_t len;
  int ret;
  cdtime_t timeout;

  msg = wrr_value_list_to_message(host, ds, vl, statuses);
  if (msg == NULL)
    return -1;

  pthread_mutex_lock(&host->lock);

  if (host->batch_msg == NULL) {
    host->batch_msg = msg;
  } else {
    int status;

    status = riemann_message_append_events_n(host->batch_msg, msg->n_events,
                                             msg->events);
    msg->n_events = 0;
    msg->events = NULL;

    riemann_message_free(msg);

    if (status != 0) {
      pthread_mutex_unlock(&host->lock);
      ERROR("write_riemann plugin: out of memory");
      return -1;
    }
  }

  len = riemann_message_get_packed_size(host->batch_msg);
  ret = 0;
  if ((host->batch_max < 0) || (((size_t)host->batch_max) <= len)) {
    ret = wrr_batch_flush_nolock(0, host);
  } else {
    if (host->batch_timeout > 0) {
      timeout = TIME_T_TO_CDTIME_T((time_t)host->batch_timeout);
      ret = wrr_batch_flush_nolock(timeout, host);
    }
  }

  pthread_mutex_unlock(&host->lock);
  return ret;
}