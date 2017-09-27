                          "apr_file_read(child output), len %" APR_SIZE_T_FMT,
                          !rv ? len : -1);
        }
        if (rv != APR_SUCCESS) {
            return rv;
        }
        b = apr_bucket_heap_create(buf, len, NULL, c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        return APR_SUCCESS;
    }
    /* we should never get here; if we do, a bogus error message would be
     * the least of our problems
     */
    return APR_ANONYMOUS;
}

static apr_status_t pass_data_to_filter(ap_filter_t *f, const char *data,
                                        apr_size_t len, apr_bucket_brigade *bb)
{
    ef_ctx_t *ctx = f->ctx;
    ef_dir_t *dc = ctx->dc;
    apr_status_t rv;
    apr_size_t bytes_written = 0;
    apr_size_t tmplen;

    do {
        tmplen = len - bytes_written;
        rv = apr_file_write(ctx->proc->in,
                       (const char *)data + bytes_written,
                       &tmplen);
        bytes_written += tmplen;
