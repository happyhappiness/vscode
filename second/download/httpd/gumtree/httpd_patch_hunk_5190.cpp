                 ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, APLOGNO(01884)
                              "Operating in SSL FIPS mode");
             }
             else {
                 ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01885) "FIPS mode failed");
                 ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
-                ssl_die(s);
+                return ssl_die(s);
             }
         }
     }
     else {
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01886)
                      "SSL FIPS mode disabled");
     }
 #endif
 
     /*
-     * read server private keys/public certs into memory.
-     * decrypting any encrypted keys via configured SSLPassPhraseDialogs
-     * anything that needs to live longer than ptemp needs to also survive
-     * restarts, in which case they'll live inside s->process->pool.
-     */
-    ssl_pphrase_Handle(base_server, ptemp);
-
-    /*
      * initialize the mutex handling
      */
     if (!ssl_mutex_init(base_server, p)) {
         return HTTP_INTERNAL_SERVER_ERROR;
     }
 #ifdef HAVE_OCSP_STAPLING
     ssl_stapling_ex_init();
 #endif
 
     /*
      * initialize session caching
      */
-    ssl_scache_init(base_server, p);
+    if ((rv = ssl_scache_init(base_server, p)) != APR_SUCCESS) {
+        return rv;
+    }
+
+    pphrases = apr_array_make(ptemp, 2, sizeof(char *));
 
     /*
      *  initialize servers
      */
     ap_log_error(APLOG_MARK, APLOG_INFO, 0, base_server, APLOGNO(01887)
                  "Init: Initializing (virtual) servers for SSL");
