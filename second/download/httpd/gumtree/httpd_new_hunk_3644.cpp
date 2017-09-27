        worker->s->error_time = 0;
        worker->s->retries = 0;
    }
    return connected ? OK : DECLINED;
}

static apr_status_t connection_shutdown(void *theconn)
{
    proxy_conn_rec *conn = (proxy_conn_rec *)theconn;
    conn_rec *c = conn->connection;
    if (c) {
        if (!c->aborted) {
            apr_interval_time_t saved_timeout = 0;
            apr_socket_timeout_get(conn->sock, &saved_timeout);
            if (saved_timeout) {
                apr_socket_timeout_set(conn->sock, 0);
            }

            (void)ap_shutdown_conn(c, 0);
            c->aborted = 1;

            if (saved_timeout) {
                apr_socket_timeout_set(conn->sock, saved_timeout);
            }
        }

        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(02642)
                      "proxy: connection shutdown");
    }
    return APR_SUCCESS;
}


PROXY_DECLARE(int) ap_proxy_connection_create(const char *proxy_function,
                                              proxy_conn_rec *conn,
                                              conn_rec *c,
                                              server_rec *s)
{
    apr_sockaddr_t *backend_addr = conn->addr;
