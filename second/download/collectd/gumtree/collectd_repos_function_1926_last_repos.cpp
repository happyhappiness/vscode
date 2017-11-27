static int wh_write_json(const data_set_t *ds, const value_list_t *vl, /* {{{ */
                         wh_callback_t *cb) {
  int status;

  pthread_mutex_lock(&cb->send_lock);
  if (wh_callback_init(cb) != 0) {
    ERROR("write_http plugin: wh_callback_init failed.");
    pthread_mutex_unlock(&cb->send_lock);
    return -1;
  }

  status =
      format_json_value_list(cb->send_buffer, &cb->send_buffer_fill,
                             &cb->send_buffer_free, ds, vl, cb->store_rates);
  if (status == -ENOMEM) {
    status = wh_flush_nolock(/* timeout = */ 0, cb);
    if (status != 0) {
      wh_reset_buffer(cb);
      pthread_mutex_unlock(&cb->send_lock);
      return status;
    }

    status =
        format_json_value_list(cb->send_buffer, &cb->send_buffer_fill,
                               &cb->send_buffer_free, ds, vl, cb->store_rates);
  }
  if (status != 0) {
    pthread_mutex_unlock(&cb->send_lock);
    return status;
  }

  DEBUG("write_http plugin: <%s> buffer %zu/%zu (%g%%)", cb->location,
        cb->send_buffer_fill, cb->send_buffer_size,
        100.0 * ((double)cb->send_buffer_fill) /
            ((double)cb->send_buffer_size));

  /* Check if we have enough space for this command. */
  pthread_mutex_unlock(&cb->send_lock);

  return 0;
}