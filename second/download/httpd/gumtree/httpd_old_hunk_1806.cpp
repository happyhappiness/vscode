    c->bread = 0;
    c->keepalive = 0;
    c->cbx = 0;
    c->gotheader = 0;
    c->rwrite = 0;
    if (c->ctx)
        apr_pool_destroy(c->ctx);
    apr_pool_create(&c->ctx, cntxt);

    if ((rv = apr_socket_create(&c->aprsock, destsa->family,
                SOCK_STREAM, 0, c->ctx)) != APR_SUCCESS) {
    apr_err("socket", rv);
    }
    if ((rv = apr_socket_opt_set(c->aprsock, APR_SO_NONBLOCK, 1))
         != APR_SUCCESS) {
        apr_err("socket nonblock", rv);
    }
    c->start = apr_time_now();
#ifdef USE_SSL
    if (is_ssl) {
        BIO *bio;
        apr_os_sock_t fd;

        if ((c->ssl = SSL_new(ssl_ctx)) == NULL) {
