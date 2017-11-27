         yajl_gen_status_ok)
       goto err;
     break;
   }
 
   log_logstash_print(g, LOG_INFO, (n->time != 0) ? n->time : cdtime());
-  return (0);
+  return 0;
 
 err:
   yajl_gen_free(g);
   fprintf(stderr, "Could not correctly generate JSON notification\n");
-  return (0);
+  return 0;
 } /* int log_logstash_notification */
 
 void module_register(void) {
   plugin_register_config("log_logstash", log_logstash_config, config_keys,
                          config_keys_num);
   plugin_register_log("log_logstash", log_logstash_log,
                       /* user_data = */ NULL);
   plugin_register_notification("log_logstash", log_logstash_notification,
                                /* user_data = */ NULL);
 } /* void module_register (void) */
-
-/* vim: set sw=4 ts=4 tw=78 noexpandtab : */
