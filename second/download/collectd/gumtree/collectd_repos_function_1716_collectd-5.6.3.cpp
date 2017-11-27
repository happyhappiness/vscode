static int wh_config_node(oconfig_item_t *ci) /* {{{ */
{
  wh_callback_t *cb;
  int buffer_size = 0;
  char callback_name[DATA_MAX_NAME_LEN];
  int status = 0;

  cb = calloc(1, sizeof(*cb));
  if (cb == NULL) {
    ERROR("write_http plugin: calloc failed.");
    return (-1);
  }
  cb->verify_peer = 1;
  cb->verify_host = 1;
  cb->format = WH_FORMAT_COMMAND;
  cb->sslversion = CURL_SSLVERSION_DEFAULT;
  cb->low_speed_limit = 0;
  cb->timeout = 0;
  cb->log_http_error = 0;
  cb->headers = NULL;
  cb->send_metrics = 1;
  cb->send_notifications = 0;

  pthread_mutex_init(&cb->send_lock, /* attr = */ NULL);

  cf_util_get_string(ci, &cb->name);

  /* FIXME: Remove this legacy mode in version 6. */
  if (strcasecmp("URL", ci->key) == 0)
    cf_util_get_string(ci, &cb->location);

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("URL", child->key) == 0)
      status = cf_util_get_string(child, &cb->location);
    else if (strcasecmp("User", child->key) == 0)
      status = cf_util_get_string(child, &cb->user);
    else if (strcasecmp("Password", child->key) == 0)
      status = cf_util_get_string(child, &cb->pass);
    else if (strcasecmp("VerifyPeer", child->key) == 0)
      status = cf_util_get_boolean(child, &cb->verify_peer);
    else if (strcasecmp("VerifyHost", child->key) == 0)
      status = cf_util_get_boolean(child, &cb->verify_host);
    else if (strcasecmp("CACert", child->key) == 0)
      status = cf_util_get_string(child, &cb->cacert);
    else if (strcasecmp("CAPath", child->key) == 0)
      status = cf_util_get_string(child, &cb->capath);
    else if (strcasecmp("ClientKey", child->key) == 0)
      status = cf_util_get_string(child, &cb->clientkey);
    else if (strcasecmp("ClientCert", child->key) == 0)
      status = cf_util_get_string(child, &cb->clientcert);
    else if (strcasecmp("ClientKeyPass", child->key) == 0)
      status = cf_util_get_string(child, &cb->clientkeypass);
    else if (strcasecmp("SSLVersion", child->key) == 0) {
      char *value = NULL;

      status = cf_util_get_string(child, &value);
      if (status != 0)
        break;

      if (value == NULL || strcasecmp("default", value) == 0)
        cb->sslversion = CURL_SSLVERSION_DEFAULT;
      else if (strcasecmp("SSLv2", value) == 0)
        cb->sslversion = CURL_SSLVERSION_SSLv2;
      else if (strcasecmp("SSLv3", value) == 0)
        cb->sslversion = CURL_SSLVERSION_SSLv3;
      else if (strcasecmp("TLSv1", value) == 0)
        cb->sslversion = CURL_SSLVERSION_TLSv1;
#if (LIBCURL_VERSION_MAJOR > 7) ||                                             \
    (LIBCURL_VERSION_MAJOR == 7 && LIBCURL_VERSION_MINOR >= 34)
      else if (strcasecmp("TLSv1_0", value) == 0)
        cb->sslversion = CURL_SSLVERSION_TLSv1_0;
      else if (strcasecmp("TLSv1_1", value) == 0)
        cb->sslversion = CURL_SSLVERSION_TLSv1_1;
      else if (strcasecmp("TLSv1_2", value) == 0)
        cb->sslversion = CURL_SSLVERSION_TLSv1_2;
#endif
      else {
        ERROR("write_http plugin: Invalid SSLVersion "
              "option: %s.",
              value);
        status = EINVAL;
      }

      sfree(value);
    } else if (strcasecmp("Format", child->key) == 0)
      status = config_set_format(cb, child);
    else if (strcasecmp("Metrics", child->key) == 0)
      cf_util_get_boolean(child, &cb->send_metrics);
    else if (strcasecmp("Notifications", child->key) == 0)
      cf_util_get_boolean(child, &cb->send_notifications);
    else if (strcasecmp("StoreRates", child->key) == 0)
      status = cf_util_get_boolean(child, &cb->store_rates);
    else if (strcasecmp("BufferSize", child->key) == 0)
      status = cf_util_get_int(child, &buffer_size);
    else if (strcasecmp("LowSpeedLimit", child->key) == 0)
      status = cf_util_get_int(child, &cb->low_speed_limit);
    else if (strcasecmp("Timeout", child->key) == 0)
      status = cf_util_get_int(child, &cb->timeout);
    else if (strcasecmp("LogHttpError", child->key) == 0)
      status = cf_util_get_boolean(child, &cb->log_http_error);
    else if (strcasecmp("Header", child->key) == 0)
      status = wh_config_append_string("Header", &cb->headers, child);
    else {
      ERROR("write_http plugin: Invalid configuration "
            "option: %s.",
            child->key);
      status = EINVAL;
    }

    if (status != 0)
      break;
  }

  if (status != 0) {
    wh_callback_free(cb);
    return (status);
  }

  if (cb->location == NULL) {
    ERROR("write_http plugin: no URL defined for instance '%s'", cb->name);
    wh_callback_free(cb);
    return (-1);
  }

  if (!cb->send_metrics && !cb->send_notifications) {
    ERROR("write_http plugin: Neither metrics nor notifications "
          "are enabled for \"%s\".",
          cb->name);
    wh_callback_free(cb);
    return (-1);
  }

  if (cb->low_speed_limit > 0)
    cb->low_speed_time = CDTIME_T_TO_TIME_T(plugin_get_interval());

  /* Determine send_buffer_size. */
  cb->send_buffer_size = WRITE_HTTP_DEFAULT_BUFFER_SIZE;
  if (buffer_size >= 1024)
    cb->send_buffer_size = (size_t)buffer_size;
  else if (buffer_size != 0)
    ERROR("write_http plugin: Ignoring invalid BufferSize setting (%d).",
          buffer_size);

  /* Allocate the buffer. */
  cb->send_buffer = malloc(cb->send_buffer_size);
  if (cb->send_buffer == NULL) {
    ERROR("write_http plugin: malloc(%zu) failed.", cb->send_buffer_size);
    wh_callback_free(cb);
    return (-1);
  }
  /* Nulls the buffer and sets ..._free and ..._fill. */
  wh_reset_buffer(cb);

  ssnprintf(callback_name, sizeof(callback_name), "write_http/%s", cb->name);
  DEBUG("write_http: Registering write callback '%s' with URL '%s'",
        callback_name, cb->location);

  user_data_t user_data = {
      .data = cb, .free_func = wh_callback_free,
  };

  if (cb->send_metrics) {
    plugin_register_write(callback_name, wh_write, &user_data);
    user_data.free_func = NULL;

    plugin_register_flush(callback_name, wh_flush, &user_data);
  }

  if (cb->send_notifications) {
    plugin_register_notification(callback_name, wh_notify, &user_data);
    user_data.free_func = NULL;
  }

  return (0);
}