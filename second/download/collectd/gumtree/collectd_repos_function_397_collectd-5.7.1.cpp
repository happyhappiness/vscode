static void *camqp_subscribe_thread(void *user_data) /* {{{ */
{
  camqp_config_t *conf = user_data;
  int status;

  cdtime_t interval = plugin_get_interval();

  while (subscriber_threads_running) {
    amqp_frame_t frame;

    status = camqp_connect(conf);
    if (status != 0) {
      ERROR("amqp plugin: camqp_connect failed. "
            "Will sleep for %.3f seconds.",
            CDTIME_T_TO_DOUBLE(interval));
      nanosleep(&CDTIME_T_TO_TIMESPEC(interval), /* remaining = */ NULL);
      continue;
    }

    status = amqp_simple_wait_frame(conf->connection, &frame);
    if (status < 0) {
      ERROR("amqp plugin: amqp_simple_wait_frame failed. "
            "Will sleep for %.3f seconds.",
            CDTIME_T_TO_DOUBLE(interval));
      camqp_close_connection(conf);
      nanosleep(&CDTIME_T_TO_TIMESPEC(interval), /* remaining = */ NULL);
      continue;
    }

    if (frame.frame_type != AMQP_FRAME_METHOD) {
      DEBUG("amqp plugin: Unexpected frame type: %#" PRIx8, frame.frame_type);
      continue;
    }

    if (frame.payload.method.id != AMQP_BASIC_DELIVER_METHOD) {
      DEBUG("amqp plugin: Unexpected method id: %#" PRIx32,
            frame.payload.method.id);
      continue;
    }

    camqp_read_header(conf);

    amqp_maybe_release_buffers(conf->connection);
  } /* while (subscriber_threads_running) */

  camqp_config_free(conf);
  pthread_exit(NULL);
  return (NULL);
}