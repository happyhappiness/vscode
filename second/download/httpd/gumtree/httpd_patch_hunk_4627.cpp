             ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02547)
                          "SSL_CONF_CTX_finish() failed");
             SSL_CONF_CTX_free(cctx);
             ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
             return ssl_die(s);
     }
-    SSL_CONF_CTX_free(cctx);
 #endif
 
     if (SSL_CTX_check_private_key(sc->server->ssl_ctx) != 1) {
         ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02572)
                      "Failed to configure at least one certificate and key "
                      "for %s", sc->vhost_id);
