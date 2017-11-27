static void kafka_config_topic(rd_kafka_conf_t *conf,
                               oconfig_item_t *ci) /* {{{ */
{
  int status;
  struct kafka_topic_context *tctx;
  char *key = NULL;
  char *val;
  char callback_name[DATA_MAX_NAME_LEN];
  char errbuf[1024];
  oconfig_item_t *child;
  rd_kafka_conf_res_t ret;

  if ((tctx = calloc(1, sizeof(*tctx))) == NULL) {
    ERROR("write_kafka plugin: calloc failed.");
    return;
  }

  tctx->escape_char = '.';
  tctx->store_rates = 1;
  tctx->format = KAFKA_FORMAT_JSON;
  tctx->key = NULL;

  if ((tctx->kafka_conf = rd_kafka_conf_dup(conf)) == NULL) {
    sfree(tctx);
    ERROR("write_kafka plugin: cannot allocate memory for kafka config");
    return;
  }

#ifdef HAVE_LIBRDKAFKA_LOG_CB
  rd_kafka_conf_set_log_cb(tctx->kafka_conf, kafka_log);
#endif

  if ((tctx->conf = rd_kafka_topic_conf_new()) == NULL) {
    rd_kafka_conf_destroy(tctx->kafka_conf);
    sfree(tctx);
    ERROR("write_kafka plugin: cannot create topic configuration.");
    return;
  }

  if (ci->values_num != 1) {
    WARNING("kafka topic name needed.");
    goto errout;
  }

  if (ci->values[0].type != OCONFIG_TYPE_STRING) {
    WARNING("kafka topic needs a string argument.");
    goto errout;
  }

  if ((tctx->topic_name = strdup(ci->values[0].value.string)) == NULL) {
    ERROR("write_kafka plugin: cannot copy topic name.");
    goto errout;
  }

  for (int i = 0; i < ci->children_num; i++) {
    /*
     * The code here could be simplified but makes room
     * for easy adding of new options later on.
     */
    child = &ci->children[i];
    status = 0;

    if (strcasecmp("Property", child->key) == 0) {
      if (child->values_num != 2) {
        WARNING("kafka properties need both a key and a value.");
        goto errout;
      }
      if (child->values[0].type != OCONFIG_TYPE_STRING ||
          child->values[1].type != OCONFIG_TYPE_STRING) {
        WARNING("kafka properties needs string arguments.");
        goto errout;
      }
      key = child->values[0].value.string;
      val = child->values[1].value.string;
      ret =
          rd_kafka_topic_conf_set(tctx->conf, key, val, errbuf, sizeof(errbuf));
      if (ret != RD_KAFKA_CONF_OK) {
        WARNING("cannot set kafka topic property %s to %s: %s.", key, val,
                errbuf);
        goto errout;
      }

    } else if (strcasecmp("Key", child->key) == 0) {
      if (cf_util_get_string(child, &tctx->key) != 0)
        continue;
      if (strcasecmp("Random", tctx->key) == 0) {
        sfree(tctx->key);
        tctx->key = strdup(kafka_random_key(KAFKA_RANDOM_KEY_BUFFER));
      }
    } else if (strcasecmp("Format", child->key) == 0) {
      status = cf_util_get_string(child, &key);
      if (status != 0)
        goto errout;

      assert(key != NULL);

      if (strcasecmp(key, "Command") == 0) {
        tctx->format = KAFKA_FORMAT_COMMAND;

      } else if (strcasecmp(key, "Graphite") == 0) {
        tctx->format = KAFKA_FORMAT_GRAPHITE;

      } else if (strcasecmp(key, "Json") == 0) {
        tctx->format = KAFKA_FORMAT_JSON;

      } else {
        WARNING("write_kafka plugin: Invalid format string: %s", key);
      }

      sfree(key);

    } else if (strcasecmp("StoreRates", child->key) == 0) {
      status = cf_util_get_boolean(child, &tctx->store_rates);
      (void)cf_util_get_flag(child, &tctx->graphite_flags,
                             GRAPHITE_STORE_RATES);

    } else if (strcasecmp("GraphiteSeparateInstances", child->key) == 0) {
      status = cf_util_get_flag(child, &tctx->graphite_flags,
                                GRAPHITE_SEPARATE_INSTANCES);

    } else if (strcasecmp("GraphiteAlwaysAppendDS", child->key) == 0) {
      status = cf_util_get_flag(child, &tctx->graphite_flags,
                                GRAPHITE_ALWAYS_APPEND_DS);

    } else if (strcasecmp("GraphitePrefix", child->key) == 0) {
      status = cf_util_get_string(child, &tctx->prefix);
    } else if (strcasecmp("GraphitePostfix", child->key) == 0) {
      status = cf_util_get_string(child, &tctx->postfix);
    } else if (strcasecmp("GraphiteEscapeChar", child->key) == 0) {
      char *tmp_buff = NULL;
      status = cf_util_get_string(child, &tmp_buff);
      if (strlen(tmp_buff) > 1)
        WARNING("write_kafka plugin: The option \"GraphiteEscapeChar\" handles "
                "only one character. Others will be ignored.");
      tctx->escape_char = tmp_buff[0];
      sfree(tmp_buff);
    } else {
      WARNING("write_kafka plugin: Invalid directive: %s.", child->key);
    }

    if (status != 0)
      break;
  }

  rd_kafka_topic_conf_set_partitioner_cb(tctx->conf, kafka_partition);
  rd_kafka_topic_conf_set_opaque(tctx->conf, tctx);

  ssnprintf(callback_name, sizeof(callback_name), "write_kafka/%s",
            tctx->topic_name);

  user_data_t ud = {.data = tctx, .free_func = kafka_topic_context_free};

  status = plugin_register_write(callback_name, kafka_write, &ud);
  if (status != 0) {
    WARNING("write_kafka plugin: plugin_register_write (\"%s\") "
            "failed with status %i.",
            callback_name, status);
    goto errout;
  }

  pthread_mutex_init(&tctx->lock, /* attr = */ NULL);

  return;
errout:
  if (tctx->topic_name != NULL)
    free(tctx->topic_name);
  if (tctx->conf != NULL)
    rd_kafka_topic_conf_destroy(tctx->conf);
  if (tctx->kafka_conf != NULL)
    rd_kafka_conf_destroy(tctx->kafka_conf);
  sfree(tctx);
}