static int mqtt_init(void) {
  mosquitto_lib_init();

  for (size_t i = 0; i < subscribers_num; i++) {
    int status;

    if (subscribers[i]->loop)
      continue;

    status = plugin_thread_create(&subscribers[i]->thread,
                                  /* attrs = */ NULL,
                                  /* func  = */ subscribers_thread,
                                  /* args  = */ subscribers[i],
                                  /* name  = */ "mqtt");
    if (status != 0) {
      char errbuf[1024];
      ERROR("mqtt plugin: pthread_create failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      continue;
    }
  }

  return (0);
}