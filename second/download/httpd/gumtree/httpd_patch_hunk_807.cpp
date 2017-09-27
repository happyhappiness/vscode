 
         /* cleanup */
         if (cipher_list_old) {
             sk_SSL_CIPHER_free(cipher_list_old);
         }
 
+        /* tracing */
         if (renegotiate) {
-#ifdef SSL_OP_CIPHER_SERVER_PREFERENCE
-            if (sc->cipher_server_pref == TRUE) {
-                SSL_set_options(ssl, SSL_OP_CIPHER_SERVER_PREFERENCE);
-            }
-#endif
-            /* tracing */
             ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                          "Reconfigured cipher suite will force renegotiation");
         }
     }
 
     /*
