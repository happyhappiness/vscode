static int camqp_subscribe_init(camqp_config_t *conf) /* {{{ */
{
  int status;
  pthread_t *tmp;

  tmp = realloc(subscriber_threads,
                sizeof(*subscriber_threads) * (subscriber_threads_num + 1));
  if (tmp == NULL) {
    ERROR("amqp plugin: realloc failed.");
    sfree(subscriber_threads);
    return ENOMEM;
  }
  subscriber_threads = tmp;
  tmp = subscriber_threads + subscriber_threads_num;
  memset(tmp, 0, sizeof(*tmp));

  status = plugin_thread_create(tmp, /* attr = */ NULL, camqp_subscribe_thread,
                                conf, "amqp subscribe");
  if (status != 0) {
    char errbuf[1024];
    ERROR("amqp plugin: pthread_create failed: %s",
          sstrerror(status, errbuf, sizeof(errbuf)));
    return status;
  }

  subscriber_threads_num++;

  return 0;
}