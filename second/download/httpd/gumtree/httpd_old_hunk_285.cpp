    int n, err;
    long verify_result;

    if (!SSL_is_init_finished(filter->pssl)) {
        if (sslconn->is_proxy) {
            if ((n = SSL_connect(filter->pssl)) <= 0) {
                ssl_log(c->base_server,
                        SSL_LOG_ERROR|SSL_ADD_SSLERR|SSL_ADD_ERRNO,
                        "SSL Proxy connect failed");
                return ssl_abort(filter, c);
            }

            return APR_SUCCESS;
        }

