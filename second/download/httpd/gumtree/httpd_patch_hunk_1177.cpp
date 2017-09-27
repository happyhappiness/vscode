 {
     cache_server_conf *conf;
     cache_request_rec *cache;
     char *port_str, *hn, *lcs;
     const char *hostname, *scheme;
     int i;
+    char *path, *querystring;
 
     cache = (cache_request_rec *) ap_get_module_config(r->request_config,
                                                        &cache_module);
     if (!cache) {
         /* This should never happen */
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
