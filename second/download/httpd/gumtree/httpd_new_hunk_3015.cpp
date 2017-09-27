        return DECLINED;
    }

    rv = get_socket_from_path(r->pool, url, &sock);

    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01152)
                      "Failed to connect to '%s'", url);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    {
        int status;
        const char *flush_method = worker->s->flusher ? worker->s->flusher : "flush";

        proxy_fdpass_flush *flush = ap_lookup_provider(PROXY_FDPASS_FLUSHER,
                                                       flush_method, "0");

        if (!flush) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01153)
                          "Unable to find configured flush provider '%s'",
                          flush_method);
            return HTTP_INTERNAL_SERVER_ERROR;
        }

        status = flush->flusher(r);
        if (status) {
            return status;
        }
    }

    clientsock = ap_get_conn_socket(r->connection);

    rv = send_socket(r->pool, sock, clientsock);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01154) "send_socket failed:");
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
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01155)
                          "failed to create dummy socket");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        ap_set_core_module_config(r->connection->conn_config, dummy);
    }


    return OK;
}

static int standard_flush(request_rec *r)
{
    int status;
