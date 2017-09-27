          */
         val = opt_ssl_var_lookup(pool, s, c, NULL, (char*)"SSL_PROTOCOL");
         if (val && *val) {
             if (strncmp("TLS", val, 3) 
                 || !strcmp("TLSv1", val) 
                 || !strcmp("TLSv1.1", val)) {
-            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(03050)
-                          "h2_h2(%ld): tls protocol not suitable: %s", 
-                          (long)c->id, val);
+                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(03050)
+                              "h2_h2(%ld): tls protocol not suitable: %s", 
+                              (long)c->id, val);
                 return 0;
             }
         }
         else if (require_all) {
             ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(03051)
                           "h2_h2(%ld): tls protocol is indetermined", (long)c->id);
