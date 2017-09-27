     if (err) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01059)
                       "error parsing URL %s: %s", url, err);
         return HTTP_BAD_REQUEST;
     }
 
-    apr_snprintf(sport, sizeof(sport), ":%d", port);
+    if (port != def_port)
+        apr_snprintf(sport, sizeof(sport), ":%d", port);
+    else
+        sport[0] = '\0';
 
     if (ap_strchr_c(host, ':')) {
         /* if literal IPv6 address */
         host = apr_pstrcat(r->pool, "[", host, "]", NULL);
     }
 
