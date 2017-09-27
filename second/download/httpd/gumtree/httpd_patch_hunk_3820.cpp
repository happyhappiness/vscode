             }
         }
         if ((sc->proxy_ssl_check_peer_name != SSL_ENABLED_FALSE) &&
             hostname_note) {
             apr_table_unset(c->notes, "proxy-request-hostname");
             if (!cert
-                || SSL_X509_match_name(c->pool, cert, hostname_note,
-                                       TRUE, server) == FALSE) {
+                || modssl_X509_match_name(c->pool, cert, hostname_note,
+                                          TRUE, server) == FALSE) {
                 proxy_ssl_check_peer_ok = FALSE;
                 ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c, APLOGNO(02411)
                               "SSL Proxy: Peer certificate does not match "
                               "for hostname %s", hostname_note);
             }
         }
