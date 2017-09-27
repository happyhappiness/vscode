                                               proxy_conn_rec *conn,
                                               server_rec *s)
{
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "proxy: %s: has released connection for (%s)",
                 proxy_function, conn->worker->hostname);
    /* If there is a connection kill it's cleanup */
    if (conn->connection) {
        apr_pool_cleanup_kill(conn->connection->pool, conn, connection_cleanup);
        conn->connection = NULL;
    }
    connection_cleanup(conn);

    return OK;
}

PROXY_DECLARE(int)
