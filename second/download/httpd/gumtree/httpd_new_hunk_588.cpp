        }
    }

    return status;
}

/* 128K maximum buffer size by default. */
#ifndef SSL_MAX_IO_BUFFER
#define SSL_MAX_IO_BUFFER (128 * 1024)
#endif

struct modssl_buffer_ctx {
    apr_bucket_brigade *bb;
    apr_pool_t *pool;
};

int ssl_io_buffer_fill(request_rec *r)
{
    conn_rec *c = r->connection;
    struct modssl_buffer_ctx *ctx;
    apr_bucket_brigade *tempb;
    apr_off_t total = 0; /* total length buffered */
    int eos = 0; /* non-zero once EOS is seen */
    
    /* Create the context which will be passed to the input filter;
     * containing a setaside pool and a brigade which constrain the
     * lifetime of the buffered data. */
    ctx = apr_palloc(r->pool, sizeof *ctx);
    apr_pool_create(&ctx->pool, r->pool);
    ctx->bb = apr_brigade_create(ctx->pool, c->bucket_alloc);

    /* ... and a temporary brigade. */
    tempb = apr_brigade_create(r->pool, c->bucket_alloc);

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "filling buffer");

    do {
        apr_status_t rv;
        apr_bucket *e, *next;

        /* The request body is read from the protocol-level input
         * filters; the buffering filter will reinject it from that
         * level, allowing content/resource filters to run later, if
         * necessary. */

        rv = ap_get_brigade(r->proto_input_filters, tempb, AP_MODE_READBYTES,
                            APR_BLOCK_READ, 8192);
        if (rv) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "could not read request body for SSL buffer");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        
        /* Iterate through the returned brigade: setaside each bucket
         * into the context's pool and move it into the brigade. */
        for (e = APR_BRIGADE_FIRST(tempb); 
             e != APR_BRIGADE_SENTINEL(tempb) && !eos; e = next) {
            const char *data;
            apr_size_t len;

            next = APR_BUCKET_NEXT(e);

            if (APR_BUCKET_IS_EOS(e)) {
                eos = 1;
            } else if (!APR_BUCKET_IS_METADATA(e)) {
                rv = apr_bucket_read(e, &data, &len, APR_BLOCK_READ);
                if (rv != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "could not read bucket for SSL buffer");
                    return HTTP_INTERNAL_SERVER_ERROR;
                }
                total += len;
            }
                
            rv = apr_bucket_setaside(e, ctx->pool);
            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                              "could not setaside bucket for SSL buffer");
                return HTTP_INTERNAL_SERVER_ERROR;
            }
            
            APR_BUCKET_REMOVE(e);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, e);
        }

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, 
                      "total of %" APR_OFF_T_FMT " bytes in buffer, eos=%d",
                      total, eos);

        /* Fail if this exceeds the maximum buffer size. */
        if (total > SSL_MAX_IO_BUFFER) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "request body exceeds maximum size for SSL buffer");
            return HTTP_REQUEST_ENTITY_TOO_LARGE;
        }

    } while (!eos);

    apr_brigade_destroy(tempb);

    /* Insert the filter which will supply the buffered data. */
    ap_add_input_filter(ssl_io_buffer, ctx, r, c);

    return 0;
}

/* This input filter supplies the buffered request body to the caller
 * from the brigade stored in f->ctx. */
static apr_status_t ssl_io_filter_buffer(ap_filter_t *f,
                                         apr_bucket_brigade *bb,
                                         ap_input_mode_t mode,
                                         apr_read_type_e block,
                                         apr_off_t bytes)
{
    struct modssl_buffer_ctx *ctx = f->ctx;
    apr_status_t rv;

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r,
                  "read from buffered SSL brigade, mode %d, "
                  "%" APR_OFF_T_FMT " bytes",
                  mode, bytes);

    if (mode != AP_MODE_READBYTES && mode != AP_MODE_GETLINE) {
        return APR_ENOTIMPL;
    }

    if (mode == AP_MODE_READBYTES) {
        apr_bucket *e;

        /* Partition the buffered brigade. */
        rv = apr_brigade_partition(ctx->bb, bytes, &e);
        if (rv && rv != APR_INCOMPLETE) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r,
                          "could not partition buffered SSL brigade");
            ap_remove_input_filter(f);
            return rv;
        }

        /* If the buffered brigade contains less then the requested
         * length, just pass it all back. */
        if (rv == APR_INCOMPLETE) {
            APR_BRIGADE_CONCAT(bb, ctx->bb);
        } else {
            apr_bucket *d = APR_BRIGADE_FIRST(ctx->bb);

            e = APR_BUCKET_PREV(e);
            
            /* Unsplice the partitioned segment and move it into the
             * passed-in brigade; no convenient way to do this with
             * the APR_BRIGADE_* macros. */
            APR_RING_UNSPLICE(d, e, link);
            APR_RING_SPLICE_HEAD(&bb->list, d, e, apr_bucket, link);

            APR_BRIGADE_CHECK_CONSISTENCY(bb);
            APR_BRIGADE_CHECK_CONSISTENCY(ctx->bb);
        }
    }
    else {
        /* Split a line into the passed-in brigade. */
        rv = apr_brigade_split_line(bb, ctx->bb, mode, bytes);

        if (rv) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r,
                          "could not split line from buffered SSL brigade");
            ap_remove_input_filter(f);
            return rv;
        }
    }

    if (APR_BRIGADE_EMPTY(ctx->bb)) {
        apr_bucket *e = APR_BRIGADE_LAST(bb);
        
        /* Ensure that the brigade is terminated by an EOS if the
         * buffered request body has been entirely consumed. */
        if (e == APR_BRIGADE_SENTINEL(bb) || !APR_BUCKET_IS_EOS(e)) {
            e = apr_bucket_eos_create(f->c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, e);
        }

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r,
                      "buffered SSL brigade now exhausted; removing filter");
        ap_remove_input_filter(f);
    }

    return APR_SUCCESS;
}

static void ssl_io_input_add_filter(ssl_filter_ctx_t *filter_ctx, conn_rec *c,
                                    SSL *ssl)
{
    bio_filter_in_ctx_t *inctx;

    inctx = apr_palloc(c->pool, sizeof(*inctx));
