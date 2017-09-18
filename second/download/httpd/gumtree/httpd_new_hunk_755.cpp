    apr_pool_create(&c->ctx, cntxt);

    if ((rv = apr_socket_create(&c->aprsock, destsa->family,
				SOCK_STREAM, c->ctx)) != APR_SUCCESS) {
	apr_err("socket", rv);
    }
    if ((rv = apr_socket_opt_set(c->aprsock, APR_SO_NONBLOCK, 1))
         != APR_SUCCESS) {
        apr_err("socket nonblock", rv);
    }
    c->start = apr_time_now();
    if ((rv = apr_connect(c->aprsock, destsa)) != APR_SUCCESS) {
	if (APR_STATUS_IS_EINPROGRESS(rv)) {
