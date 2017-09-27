
    /* Sanity check: Did we already return the pooled connection? */
    if (conn->inreslist) {
        ap_log_perror(APLOG_MARK, APLOG_ERR, 0, conn->pool, APLOGNO(00923)
                      "Pooled connection 0x%pp for worker %s has been"
                      " already returned to the connection pool.", conn,
                      ap_proxy_worker_name(conn->pool, worker));
        return APR_SUCCESS;
    }

    /* determine if the connection need to be closed */
    if (conn->close || !worker->s->is_address_reusable || worker->s->disablereuse) {
        apr_pool_t *p = conn->pool;
