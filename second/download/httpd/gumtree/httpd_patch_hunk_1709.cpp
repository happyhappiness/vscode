             uri_addr = src_uri_addr;
             while (uri_addr) {
                 char *conf_ip;
                 char *uri_ip;
                 apr_sockaddr_ip_get(&conf_ip, conf_addr);
                 apr_sockaddr_ip_get(&uri_ip, uri_addr);
-                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
+                ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, r->server,
                              "proxy: ProxyBlock comparing %s and %s", conf_ip, uri_ip);
                 if (!apr_strnatcasecmp(conf_ip, uri_ip)) {
                     ap_log_error(APLOG_MARK, APLOG_WARNING, 0, r->server,
                                  "proxy: connect to remote machine %s blocked: IP %s matched", uri_addr->hostname, conf_ip);
                     return HTTP_FORBIDDEN;
                 }
