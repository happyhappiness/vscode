static apr_status_t connection_cleanup(void *theconn)
{
    proxy_conn_rec *conn = (proxy_conn_rec *)theconn;
    proxy_worker *worker = conn->worker;

    /*
     * If the connection pool is NULL the worker
     * cleanup has been run. Just return.
     */
    if (!worker->cp->pool) {
        return APR_SUCCESS;
    }

    if (conn->r) {
        apr_pool_destroy(conn->r->pool);
        conn->r = NULL;
    }

    /* Sanity check: Did we already return the pooled connection? */
    if (conn->inreslist) {
        ap_log_perror(APLOG_MARK, APLOG_ERR, 0, conn->pool, APLOGNO(00923)
                      "Pooled connection 0x%pp for worker %s has been"
                      " already returned to the connection pool.", conn,
                      ap_proxy_worker_name(conn->pool, worker));
        return APR_SUCCESS;
    }

    /* determine if the connection need to be closed */
    if (!worker->s->is_address_reusable || worker->s->disablereuse) {
        apr_pool_t *p = conn->pool;
        apr_pool_clear(p);
        conn = apr_pcalloc(p, sizeof(proxy_conn_rec));
        conn->pool = p;
        conn->worker = worker;
        apr_pool_create(&(conn->scpool), p);
        apr_pool_tag(conn->scpool, "proxy_conn_scpool");
    }
    else if (conn->close
                || (conn->connection
                    && conn->connection->keepalive == AP_CONN_CLOSE)) {
        socket_cleanup(conn);
        conn->close = 0;
    }

    if (worker->s->hmax && worker->cp->res) {
        conn->inreslist = 1;
        apr_reslist_release(worker->cp->res, (void *)conn);
    }
    else
    {
        worker->cp->conn = conn;
    }

    /* Always return the SUCCESS */
    return APR_SUCCESS;
}