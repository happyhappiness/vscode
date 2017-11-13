static int proxy_fdpass_handler(request_rec *r, proxy_worker *worker,
                              proxy_server_conf *conf,
                              char *url, const char *proxyname,
                              apr_port_t proxyport)
{
    apr_status_t rv;
    apr_socket_t *sock;
    apr_socket_t *clientsock;

    if (strncasecmp(url, "fd://", 5) == 0) {
        url += 5;
    }
    else {
        return DECLINED;
    }

    rv = get_socket_from_path(r->pool, url, &sock);

    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "proxy: FD: Failed to connect to '%s'",
                      url);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    {
        int status;
        const char *flush_method = worker->flusher ? worker->flusher : "flush";

        proxy_fdpass_flush *flush = ap_lookup_provider(PROXY_FDPASS_FLUSHER,
                                                       flush_method, "0");

        if (!flush) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "proxy: FD: Unable to find configured flush "
                          "provider '%s'", flush_method);
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        status = flush->flusher(r);
        if (status) {
            return status;
        }
    }

    /* XXXXX: THIS IS AN EVIL HACK */
    /* There should really be a (documented) public API for this ! */
    clientsock = ap_get_module_config(r->connection->conn_config, &core_module);

    rv = send_socket(r->pool, sock, clientsock);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "proxy: FD: send_socket failed:");
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    {
        apr_socket_t *dummy;
        /* Create a dummy unconnected socket, and set it as the one we were 
         * connected to, so that when the core closes it, it doesn't close 
         * the tcp connection to the client.
         */
        rv = apr_socket_create(&dummy, APR_INET, SOCK_STREAM, APR_PROTO_TCP,
                               r->connection->pool);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "proxy: FD: failed to create dummy socket");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        ap_set_module_config(r->connection->conn_config, &core_module, dummy);
    }
    
    
    return OK;
}