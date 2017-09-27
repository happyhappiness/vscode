                     ((peercert = SSL_get_peer_certificate(ssl)) != NULL))
                 {
                     renegotiate_quick = TRUE;
                     X509_free(peercert);
                 }
 
-                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02255)
                               "Changed client verification type will force "
                               "%srenegotiation",
                               renegotiate_quick ? "quick " : "");
              }
         }
         /* If we're handling a request for a vhost other than the default one,
