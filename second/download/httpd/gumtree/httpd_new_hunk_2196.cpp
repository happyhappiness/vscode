    }

    /* Always return the SUCCESS */
    return APR_SUCCESS;
}

static void socket_cleanup(proxy_conn_rec *conn)
{
    conn->sock = NULL;
    conn->connection = NULL;
    apr_pool_clear(conn->scpool);
}

PROXY_DECLARE(apr_status_t) ap_proxy_ssl_connection_cleanup(proxy_conn_rec *conn,
                                                            request_rec *r)
{
    apr_bucket_brigade *bb;
    apr_status_t rv;

    /*
     * If we have an existing SSL connection it might be possible that the
     * server sent some SSL message we have not read so far (e.g. a SSL
     * shutdown message if the server closed the keepalive connection while
     * the connection was held unused in our pool).
     * So ensure that if present (=> APR_NONBLOCK_READ) it is read and
     * processed. We don't expect any data to be in the returned brigade.
     */
    if (conn->sock && conn->connection) {
        bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
        rv = ap_get_brigade(conn->connection->input_filters, bb,
                            AP_MODE_READBYTES, APR_NONBLOCK_READ,
                            HUGE_STRING_LEN);
        if ((rv != APR_SUCCESS) && !APR_STATUS_IS_EAGAIN(rv)) {
            socket_cleanup(conn);
        }
        if (!APR_BRIGADE_EMPTY(bb)) {
            apr_off_t len;

            rv = apr_brigade_length(bb, 0, &len);
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
                          "proxy: SSL cleanup brigade contained %"
                          APR_OFF_T_FMT " bytes of data.", len);
        }
        apr_brigade_destroy(bb);
    }
    return APR_SUCCESS;
}

/* reslist constructor */
static apr_status_t connection_constructor(void **resource, void *params,
                                           apr_pool_t *pool)
{
    apr_pool_t *ctx;
    apr_pool_t *scpool;
    proxy_conn_rec *conn;
    proxy_worker *worker = (proxy_worker *)params;

    /*
     * Create the subpool for each connection
     * This keeps the memory consumption constant
     * when disconnecting from backend.
     */
    apr_pool_create(&ctx, pool);
    apr_pool_tag(ctx, "proxy_conn_pool");
    /*
     * Create another subpool that manages the data for the
     * socket and the connection member of the proxy_conn_rec struct as we
     * destroy this data more frequently than other data in the proxy_conn_rec
     * struct like hostname and addr (at least in the case where we have
     * keepalive connections that timed out).
     */
    apr_pool_create(&scpool, ctx);
    apr_pool_tag(scpool, "proxy_conn_scpool");
    conn = apr_pcalloc(ctx, sizeof(proxy_conn_rec));

    conn->pool   = ctx;
    conn->scpool = scpool;
    conn->worker = worker;
#if APR_HAS_THREADS
    conn->inreslist = 1;
#endif
    *resource = conn;

