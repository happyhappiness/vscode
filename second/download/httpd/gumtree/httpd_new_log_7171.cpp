(SSL_CTX_check_private_key(sc->server->ssl_ctx) != 1) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02572)
                     "Failed to configure at least one certificate and key "
                     "for %s", sc->vhost_id);;