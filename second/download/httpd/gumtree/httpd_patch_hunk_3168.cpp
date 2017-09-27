 #ifdef SSL_OP_CIPHER_SERVER_PREFERENCE
             if (sc->cipher_server_pref == TRUE) {
                 SSL_set_options(ssl, SSL_OP_CIPHER_SERVER_PREFERENCE);
             }
 #endif
             /* tracing */
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02220)
                          "Reconfigured cipher suite will force renegotiation");
         }
     }
 
     /*
      * override of SSLVerifyDepth
