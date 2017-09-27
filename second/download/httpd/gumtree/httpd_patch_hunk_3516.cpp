                 server_hostname = apr_pstrdup(a, str);
             } else {
                 apr_sockaddr_ip_get(&hostname, sockaddr);
                 server_hostname = apr_pstrdup(a, hostname);
             }
         } else {
-            ap_log_perror(APLOG_MARK, APLOG_STARTUP | APLOG_WARNING, 0, a,
+            ap_log_perror(APLOG_MARK, APLOG_STARTUP | APLOG_WARNING, 0, a, APLOGNO(00557)
                          "%s: apr_sockaddr_info_get() failed for %s",
                          ap_server_argv0, str);
         }
     }
 
     if (!server_hostname)
         server_hostname = apr_pstrdup(a, "127.0.0.1");
 
-    ap_log_perror(APLOG_MARK, APLOG_ALERT|APLOG_STARTUP, 0, a,
+    ap_log_perror(APLOG_MARK, APLOG_ALERT|APLOG_STARTUP, 0, a, APLOGNO(00558)
                  "%s: Could not reliably determine the server's fully qualified "
-                 "domain name, using %s for ServerName",
+                 "domain name, using %s. Set the 'ServerName' directive globally "
+                 "to suppress this message",
                  ap_server_argv0, server_hostname);
 
     return server_hostname;
 }
 
 /* simple 'pool' alloc()ing glue to apr_base64.c
