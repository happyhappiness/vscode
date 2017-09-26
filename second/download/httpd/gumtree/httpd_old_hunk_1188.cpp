     * delayed interlinking from SSL back to request_rec
     */
    ssl = sslconn->ssl;
    if (!ssl) {
        return DECLINED;
    }
    SSL_set_app_data2(ssl, r);

    /*
     * Log information about incoming HTTPS requests
     */
    if (r->server->loglevel >= APLOG_INFO && ap_is_initial_req(r)) {
