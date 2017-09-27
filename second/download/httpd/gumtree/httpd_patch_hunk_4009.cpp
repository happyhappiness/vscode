          */
         val = opt_ssl_var_lookup(pool, s, c, NULL, (char*)"SSL_PROTOCOL");
         if (val && *val) {
             if (strncmp("TLS", val, 3) 
                 || !strcmp("TLSv1", val) 
                 || !strcmp("TLSv1.1", val)) {
-            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
+            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(03050)
                           "h2_h2(%ld): tls protocol not suitable: %s", 
                           (long)c->id, val);
                 return 0;
             }
         }
         else if (require_all) {
-            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
+            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(03051)
                           "h2_h2(%ld): tls protocol is indetermined", (long)c->id);
             return 0;
         }
 
         /* Check TLS cipher blacklist
          */
         val = opt_ssl_var_lookup(pool, s, c, NULL, (char*)"SSL_CIPHER");
         if (val && *val) {
             const char *source;
             if (cipher_is_blacklisted(val, &source)) {
-                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
+                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(03052)
                               "h2_h2(%ld): tls cipher %s blacklisted by %s", 
                               (long)c->id, val, source);
                 return 0;
             }
         }
         else if (require_all) {
-            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
+            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(03053)
                           "h2_h2(%ld): tls cipher is indetermined", (long)c->id);
             return 0;
         }
     }
     return 1;
 }
 
 int h2_allows_h2_direct(conn_rec *c)
 {
     const h2_config *cfg = h2_config_get(c);
+    int is_tls = h2_h2_is_tls(c);
+    const char *needed_protocol = is_tls? "h2" : "h2c";
     int h2_direct = h2_config_geti(cfg, H2_CONF_DIRECT);
     
     if (h2_direct < 0) {
-        if (h2_h2_is_tls(c)) {
-            /* disabled by default on TLS */
-            h2_direct = 0;
-        }
-        else {
-            /* enabled if "Protocols h2c" is configured */
-            h2_direct = ap_is_allowed_protocol(c, NULL, NULL, "h2c");
-        }
+        h2_direct = is_tls? 0 : 1;
     }
-    return !!h2_direct;
+    return (h2_direct 
+            && ap_is_allowed_protocol(c, NULL, NULL, needed_protocol));
 }
 
 int h2_allows_h2_upgrade(conn_rec *c)
 {
     const h2_config *cfg = h2_config_get(c);
     int h2_upgrade = h2_config_geti(cfg, H2_CONF_UPGRADE);
