         return OK;
     }
     else {
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, 
                      "Determining if request should be passed. "
                      "Child Num: %d, SD: %d, sd from table: %d, hostname from server: %s", child_num, 
-                     sconf->sd, child_info_table[child_num].sd, 
+                     sconf->input, child_info_table[child_num].input, 
                      r->server->server_hostname);
         /* sconf is the server config for this vhost, so if our socket
          * is not the same that was set in the config, then the request
          * needs to be passed to another child. */
-        if (sconf->sd != child_info_table[child_num].sd) {
+        if (sconf->input != child_info_table[child_num].input) {
             ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, 
                          "Passing request.");
             if (pass_request(r) == -1) {
                 ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                              ap_server_conf, "Could not pass request to proper "
                              "child, request will not be honored.");
