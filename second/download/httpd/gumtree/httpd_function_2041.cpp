void ssl_init_ticket_key(server_rec *s,
                                apr_pool_t *p,
                                apr_pool_t *ptemp,
                                modssl_ctx_t *mctx)
{
    apr_status_t rv;
    apr_file_t *fp;
    apr_size_t len;
    char buf[TLSEXT_TICKET_KEY_LEN];
    char *path;
    modssl_ticket_key_t *ticket_key = mctx->ticket_key;

    if (!ticket_key->file_path) {
        return;
    }

    path = ap_server_root_relative(p, ticket_key->file_path);

    rv = apr_file_open(&fp, path, APR_READ|APR_BINARY,
                       APR_OS_DEFAULT, ptemp);

    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s,
                     "Failed to open ticket key file %s: (%d) %pm",
                     path, rv, &rv);
        ssl_die();
    }

    rv = apr_file_read_full(fp, &buf[0], TLSEXT_TICKET_KEY_LEN, &len);

    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s,
                     "Failed to read %d bytes from %s: (%d) %pm",
                     TLSEXT_TICKET_KEY_LEN, path, rv, &rv);
        ssl_die();
    }

    memcpy(ticket_key->key_name, buf, 16);
    memcpy(ticket_key->hmac_secret, buf + 16, 16);
    memcpy(ticket_key->aes_key, buf + 32, 16);

    if (!SSL_CTX_set_tlsext_ticket_key_cb(mctx->ssl_ctx,
                                          ssl_callback_SessionTicket)) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s,
                     "Unable to initialize TLS session ticket key callback "
                     "(incompatible OpenSSL version?)");
        ssl_log_ssl_error(APLOG_MARK, APLOG_EMERG, s);
        ssl_die();
    }

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                 "TLS session ticket key for %s successfully loaded from %s",
                 (mySrvConfig(s))->vhost_id, path);
}