                                              const void *parsed_require_line)
 {
     const char *t, *w;
     const char *remotehost = NULL;
     int remotehost_is_ip;
 
-    remotehost = ap_get_remote_host(r->connection,
-                                    r->per_dir_config,
-                                    REMOTE_DOUBLE_REV,
-                                    &remotehost_is_ip);
+    remotehost = ap_get_useragent_host(r, REMOTE_DOUBLE_REV, &remotehost_is_ip);
 
     if ((remotehost == NULL) || remotehost_is_ip) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01753)
                       "access check of '%s' to %s failed, reason: unable to get the "
                       "remote host name", require_line, r->uri);
     }
