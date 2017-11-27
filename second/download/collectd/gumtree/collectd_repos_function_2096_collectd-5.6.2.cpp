static int wt_send_message(const char *key, const char *value, cdtime_t time,
                           struct wt_callback *cb, const char *host,
                           meta_data_t *md) {
  int status;
  size_t message_len;
  char *temp = NULL;
  const char *tags = "";
  char message[1024];
  const char *host_tags = cb->host_tags ? cb->host_tags : "";
  const char *meta_tsdb = "tsdb_tags";

  /* skip if value is NaN */
  if (value[0] == 'n')
    return 0;

  if (md) {
    status = meta_data_get_string(md, meta_tsdb, &temp);
    if (status == -ENOENT) {
      /* defaults to empty string */
    } else if (status < 0) {
      ERROR("write_tsdb plugin: tags metadata get failure");
      sfree(temp);
      pthread_mutex_unlock(&cb->send_lock);
      return status;
    } else {
      tags = temp;
    }
  }

  status =
      ssnprintf(message, sizeof(message), "put %s %.0f %s fqdn=%s %s %s\r\n",
                key, CDTIME_T_TO_DOUBLE(time), value, host, tags, host_tags);
  sfree(temp);
  if (status < 0)
    return -1;
  message_len = (size_t)status;

  if (message_len >= sizeof(message)) {
    ERROR("write_tsdb plugin: message buffer too small: "
          "Need %zu bytes.",
          message_len + 1);
    return -1;
  }

  pthread_mutex_lock(&cb->send_lock);

  if (cb->sock_fd < 0) {
    status = wt_callback_init(cb);
    if (status != 0) {
      ERROR("write_tsdb plugin: wt_callback_init failed.");
      pthread_mutex_unlock(&cb->send_lock);
      return -1;
    }
  }

  if (message_len >= cb->send_buf_free) {
    status = wt_flush_nolock(0, cb);
    if (status != 0) {
      pthread_mutex_unlock(&cb->send_lock);
      return status;
    }
  }

  /* Assert that we have enough space for this message. */
  assert(message_len < cb->send_buf_free);

  /* `message_len + 1' because `message_len' does not include the
   * trailing null byte. Neither does `send_buffer_fill'. */
  memcpy(cb->send_buf + cb->send_buf_fill, message, message_len + 1);
  cb->send_buf_fill += message_len;
  cb->send_buf_free -= message_len;

  DEBUG("write_tsdb plugin: [%s]:%s buf %zu/%zu (%.1f %%) \"%s\"", cb->node,
        cb->service, cb->send_buf_fill, sizeof(cb->send_buf),
        100.0 * ((double)cb->send_buf_fill) / ((double)sizeof(cb->send_buf)),
        message);

  pthread_mutex_unlock(&cb->send_lock);

  return 0;
}