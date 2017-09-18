    int n, err;
    long verify_result;

    if (!SSL_is_init_finished(filter->pssl)) {
        if (sslconn->is_proxy) {
            if ((n = SSL_connect(filter->pssl)) <= 0) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                             c->base_server,
                             "SSL Proxy connect failed");
                ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, c->base_server);
                return ssl_abort(filter, c);
            }

            return APR_SUCCESS;
        }

