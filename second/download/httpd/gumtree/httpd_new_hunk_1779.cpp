                                               proxy_conn_rec *conn,
                                               server_rec *s)
{
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "proxy: %s: has released connection for (%s)",
                 proxy_function, conn->worker->hostname);
    connection_cleanup(conn);

    return OK;
}

PROXY_DECLARE(int)
