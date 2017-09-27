          * configuring.
          */
 
         /*
          * Read the server certificate and key
          */
-        ssl_init_ConfigureServer(s, p, ptemp, sc);
+        if ((rv = ssl_init_ConfigureServer(s, p, ptemp, sc, pphrases))
+            != APR_SUCCESS) {
+            return rv;
+        }
+    }
+
+    if (pphrases->nelts > 0) {
+        memset(pphrases->elts, 0, pphrases->elt_size * pphrases->nelts);
+        pphrases->nelts = 0;
+        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(02560)
+                     "Init: Wiped out the queried pass phrases from memory");
     }
 
     /*
      * Configuration consistency checks
      */
-    ssl_init_CheckServers(base_server, ptemp);
+    if ((rv = ssl_init_CheckServers(base_server, ptemp)) != APR_SUCCESS) {
+        return rv;
+    }
 
     /*
      *  Announce mod_ssl and SSL library in HTTP Server field
      *  as ``mod_ssl/X.X.X OpenSSL/X.X.X''
      */
     ssl_add_version_components(p, base_server);
