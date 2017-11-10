static int ef_unified_filter(ap_filter_t *f, apr_bucket_brigade *bb)
{
    request_rec *r = f->r;
    conn_rec *c = r->connection;
    ef_ctx_t *ctx = f->ctx;
    apr_bucket *b;
    apr_size_t len;
    const char *data;
    apr_status_t rv;
    char buf[4096];
    apr_bucket *eos = NULL;
    apr_bucket_brigade *bb_tmp;

    bb_tmp = apr_brigade_create(r->pool, c->bucket_alloc);

    for (b = APR_BRIGADE_FIRST(bb);
         b != APR_BRIGADE_SENTINEL(bb);
         b = APR_BUCKET_NEXT(b))
    {
        if (APR_BUCKET_IS_EOS(b)) {
            eos = b;
            break;
        }

        rv = apr_bucket_read(b, &data, &len, APR_BLOCK_READ);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01463) "apr_bucket_read()");
            return rv;
        }

        /* Good cast, we just tested len isn't negative */
        if (len > 0 &&
            (rv = pass_data_to_filter(f, data, (apr_size_t)len, bb_tmp))
                != APR_SUCCESS) {
            return rv;
        }
    }

    apr_brigade_cleanup(bb);
    APR_BRIGADE_CONCAT(bb, bb_tmp);
    apr_brigade_destroy(bb_tmp);

    if (eos) {
        /* close the child's stdin to signal that no more data is coming;
         * that will cause the child to finish generating output
         */
        if ((rv = apr_file_close(ctx->proc->in)) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01464)
                          "apr_file_close(child input)");
            return rv;
        }
        /* since we've seen eos and closed the child's stdin, set the proper pipe
         * timeout; we don't care if we don't return from apr_file_read() for a while...
         */
        rv = apr_file_pipe_timeout_set(ctx->proc->out,
                                       r->server->timeout);
        if (rv) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01465)
                          "apr_file_pipe_timeout_set(child output)");
            return rv;
        }
    }

    do {
        int lvl = APLOG_TRACE6;
        len = sizeof(buf);
        rv = apr_file_read(ctx->proc->out, buf, &len);
        if (rv && !APR_STATUS_IS_EOF(rv) && !APR_STATUS_IS_EAGAIN(rv))
            lvl = APLOG_ERR;
        ap_log_rerror(APLOG_MARK, lvl, rv, r, APLOGNO(01466)
                      "apr_file_read(child output), len %" APR_SIZE_T_FMT,
                      !rv ? len : -1);
        if (APR_STATUS_IS_EAGAIN(rv)) {
            if (eos) {
                /* should not occur, because we have an APR timeout in place */
                AP_DEBUG_ASSERT(1 != 1);
            }
            return APR_SUCCESS;
        }

        if (rv == APR_SUCCESS) {
            b = apr_bucket_heap_create(buf, len, NULL, c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, b);
        }
    } while (rv == APR_SUCCESS);

    if (!APR_STATUS_IS_EOF(rv)) {
        return rv;
    }

    if (eos) {
        b = apr_bucket_eos_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
    }

    return APR_SUCCESS;
}