        worker->s->error_time = 0;
        worker->s->retries = 0;
    }
    return connected ? OK : DECLINED;
}

PROXY_DECLARE(int) ap_proxy_connection_create(const char *proxy_function,
                                              proxy_conn_rec *conn,
                                              conn_rec *c,
                                              server_rec *s)
{
    apr_sockaddr_t *backend_addr = conn->addr;
