                 proxy_function, worker->s->hostname);

    (*conn)->worker = worker;
    (*conn)->close  = 0;
    (*conn)->inreslist = 0;

    return OK;
}

PROXY_DECLARE(int) ap_proxy_release_connection(const char *proxy_function,
                                               proxy_conn_rec *conn,
                                               server_rec *s)
