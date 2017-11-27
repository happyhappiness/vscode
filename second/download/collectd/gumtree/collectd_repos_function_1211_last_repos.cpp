static int publish(mqtt_client_conf_t *conf, char const *topic,
                   void const *payload, size_t payload_len) {
  int status;

  pthread_mutex_lock(&conf->lock);

  status = mqtt_connect(conf);
  if (status != 0) {
    pthread_mutex_unlock(&conf->lock);
    ERROR("mqtt plugin: unable to reconnect to broker");
    return status;
  }

  status = mosquitto_publish(conf->mosq, /* message_id */ NULL, topic,
#if LIBMOSQUITTO_MAJOR == 0
                             (uint32_t)payload_len, payload,
#else
                             (int)payload_len, payload,
#endif
                             conf->qos, conf->retain);
  if (status != MOSQ_ERR_SUCCESS) {
    char errbuf[1024];
    c_complain(LOG_ERR, &conf->complaint_cantpublish,
               "mqtt plugin: mosquitto_publish failed: %s",
               (status == MOSQ_ERR_ERRNO)
                   ? sstrerror(errno, errbuf, sizeof(errbuf))
                   : mosquitto_strerror(status));
    /* Mark our connection "down" regardless of the error as a safety
     * measure; we will try to reconnect the next time we have to publish a
     * message */
    conf->connected = 0;
    mosquitto_disconnect(conf->mosq);

    pthread_mutex_unlock(&conf->lock);
    return -1;
  }

  pthread_mutex_unlock(&conf->lock);
  return 0;
}