             || npent[j].name[0] == '*') {
             ap_log_error(APLOG_MARK, APLOG_WARNING, 0, r->server,
                          "proxy: connect to remote machine %s blocked: name %s matched", uri_addr->hostname, npent[j].name);
             return HTTP_FORBIDDEN;
         }
         while (conf_addr) {
+            uri_addr = src_uri_addr;
             while (uri_addr) {
                 char *conf_ip;
                 char *uri_ip;
                 apr_sockaddr_ip_get(&conf_ip, conf_addr);
                 apr_sockaddr_ip_get(&uri_ip, uri_addr);
                 ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
