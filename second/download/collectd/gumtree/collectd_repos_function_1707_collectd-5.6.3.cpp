static int wh_flush_nolock(cdtime_t timeout, wh_callback_t *cb) /* {{{ */
{
  int status;

  DEBUG("write_http plugin: wh_flush_nolock: timeout = %.3f; "
        "send_buffer_fill = %zu;",
        CDTIME_T_TO_DOUBLE(timeout), cb->send_buffer_fill);

  /* timeout == 0  => flush unconditionally */
  if (timeout > 0) {
    cdtime_t now;

    now = cdtime();
    if ((cb->send_buffer_init_time + timeout) > now)
      return (0);
  }

  if (cb->format == WH_FORMAT_COMMAND) {
    if (cb->send_buffer_fill == 0) {
      cb->send_buffer_init_time = cdtime();
      return (0);
    }

    status = wh_post_nolock(cb, cb->send_buffer);
    wh_reset_buffer(cb);
  } else if (cb->format == WH_FORMAT_JSON || cb->format == WH_FORMAT_KAIROSDB) {
    if (cb->send_buffer_fill <= 2) {
      cb->send_buffer_init_time = cdtime();
      return (0);
    }

    status = format_json_finalize(cb->send_buffer, &cb->send_buffer_fill,
                                  &cb->send_buffer_free);
    if (status != 0) {
      ERROR("write_http: wh_flush_nolock: "
            "format_json_finalize failed.");
      wh_reset_buffer(cb);
      return (status);
    }

    status = wh_post_nolock(cb, cb->send_buffer);
    wh_reset_buffer(cb);
  } else {
    ERROR("write_http: wh_flush_nolock: "
          "Unknown format: %i",
          cb->format);
    return (-1);
  }

  return (status);
}