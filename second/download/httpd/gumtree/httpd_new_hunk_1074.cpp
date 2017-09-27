     * If the connection pool is NULL the worker
     * cleanup has been run. Just return.
     */
    if (!worker->cp)
        return APR_SUCCESS;

#if APR_HAS_THREADS
    /* Sanity check: Did we already return the pooled connection? */
    if (conn->inreslist) {
        ap_log_perror(APLOG_MARK, APLOG_ERR, 0, conn->pool,
                      "proxy: Pooled connection 0x%pp for worker %s has been"
                      " already returned to the connection pool.", conn,
                      worker->name);
        return APR_SUCCESS;
    }
#endif

    /* determine if the connection need to be closed */
    if (conn->close_on_recycle || conn->close) {
        apr_pool_t *p = conn->pool;
        apr_pool_clear(conn->pool);
        memset(conn, 0, sizeof(proxy_conn_rec));
        conn->pool = p;
        conn->worker = worker;
    }
#if APR_HAS_THREADS
    if (worker->hmax && worker->cp->res) {
        conn->inreslist = 1;
        apr_reslist_release(worker->cp->res, (void *)conn);
    }
    else
#endif
    {
        worker->cp->conn = conn;
