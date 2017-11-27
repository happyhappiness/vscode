void module_register(void) {
  plugin_register_config("log_logstash", log_logstash_config, config_keys,
                         config_keys_num);
  plugin_register_log("log_logstash", log_logstash_log,
                      /* user_data = */ NULL);
  plugin_register_notification("log_logstash", log_logstash_notification,
                               /* user_data = */ NULL);
}