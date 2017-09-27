
    if ((rv = apr_socket_create(&c->aprsock, destsa->family,
                SOCK_STREAM, 0, c->ctx)) != APR_SUCCESS) {
    apr_err("socket", rv);
    }

    if ((rv = apr_socket_bind(c->aprsock, mysa)) != APR_SUCCESS) {
        apr_err("bind", rv);
    }

    c->pollfd.desc_type = APR_POLL_SOCKET;
    c->pollfd.desc.s = c->aprsock;
    c->pollfd.reqevents = 0;
    c->pollfd.client_data = c;
