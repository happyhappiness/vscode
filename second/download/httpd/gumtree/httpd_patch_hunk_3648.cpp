 
         apr_sockaddr_ip_get(&addr, s->addrs->host_addr);
         key = apr_psprintf(p, "%s:%u", addr, s->addrs->host_port);
         klen = strlen(key);
 
         if ((ps = (server_rec *)apr_hash_get(table, key, klen))) {
-            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, base_server,
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, base_server, APLOGNO(02662)
                          "Init: SSL server IP/port conflict: "
                          "%s (%s:%d) vs. %s (%s:%d)",
                          ssl_util_vhostid(p, s),
                          (s->defn_name ? s->defn_name : "unknown"),
                          s->defn_line_number,
                          ssl_util_vhostid(p, ps),
