      * they callback the SNI. We need to make sure that we know which vhost
      * we are dealing with so we respect the correct protocols.
      */
     init_vhost(c, ssl);
     
     proposed = ap_select_protocol(c, NULL, sslconn->server, client_protos);
-    *out = (const unsigned char *)(proposed? proposed : ap_get_protocol(c));
-    len = strlen((const char*)*out);
+    if (!proposed) {
+        proposed = ap_get_protocol(c);
+    }
+    
+    len = strlen(proposed);
     if (len > 255) {
         ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(02840)
                       "ALPN negotiated protocol name too long");
         return SSL_TLSEXT_ERR_ALERT_FATAL;
     }
+    *out = (const unsigned char *)proposed;
     *outlen = (unsigned char)len;
+        
+    if (strcmp(proposed, ap_get_protocol(c))) {
+        apr_status_t status;
+        
+        status = ap_switch_protocol(c, NULL, sslconn->server, proposed);
+        if (status != APR_SUCCESS) {
+            ap_log_cerror(APLOG_MARK, APLOG_ERR, status, c,
+                          APLOGNO(02908) "protocol switch to '%s' failed",
+                          proposed);
+            return SSL_TLSEXT_ERR_ALERT_FATAL;
+        }
+    }
 
     return SSL_TLSEXT_ERR_OK;
 }
 #endif /* HAVE_TLS_ALPN */
 
 #ifdef HAVE_SRP
