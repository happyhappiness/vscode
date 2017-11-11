static apr_status_t buffer_in_filter(ap_filter_t *f, apr_bucket_brigade *bb,
        ap_input_mode_t mode, apr_read_type_e block, apr_off_t readbytes)
{
    apr_bucket *e, *after;
    apr_status_t rv;
    buffer_ctx *ctx = f->ctx;

    /* buffer on main requests only */
    if (!ap_is_initial_req(f->r)) {
        ap_remove_input_filter(f);
        return ap_get_brigade(f->next, bb, mode, block, readbytes);
    }

    /* first time in? create a context */
    if (!ctx) {
        ctx = f->ctx = apr_pcalloc(f->r->pool, sizeof(*ctx));
        ctx->bb = apr_brigade_create(f->r->pool, f->c->bucket_alloc);
        ctx->tmp = apr_brigade_create(f->r->pool, f->c->bucket_alloc);
        ctx->conf = ap_get_module_config(f->r->per_dir_config, &buffer_module);
    }

    /* just get out of the way of things we don't want. */
    if (mode != AP_MODE_READBYTES) {
        return ap_get_brigade(f->next, bb, mode, block, readbytes);
    }

    /* if our buffer is empty, read off the network until the buffer is full */
    if (APR_BRIGADE_EMPTY(ctx->bb)) {
        int seen_flush = 0;

        ctx->remaining = ctx->conf->size;

        while (!ctx->seen_eos && !seen_flush && ctx->remaining > 0) {
            const char *data;
            apr_size_t size = 0;

            if (APR_BRIGADE_EMPTY(ctx->tmp)) {
                rv = ap_get_brigade(f->next, ctx->tmp, mode, block,
                                    ctx->remaining);

                /* if an error was received, bail out now. If the error is
                 * EAGAIN and we have not yet seen an EOS, we will definitely
                 * be called again, at which point we will send our buffered
                 * data. Instead of sending EAGAIN, some filters return an
                 * empty brigade instead when data is not yet available. In
                 * this case, pass through the APR_SUCCESS and emulate the
                 * underlying filter.
                 */
                if (rv != APR_SUCCESS || APR_BRIGADE_EMPTY(ctx->tmp)) {
                    return rv;
                }
            }

            do {
                e = APR_BRIGADE_FIRST(ctx->tmp);

                /* if we see an EOS, we are done */
                if (APR_BUCKET_IS_EOS(e)) {
                    APR_BUCKET_REMOVE(e);
                    APR_BRIGADE_INSERT_TAIL(ctx->bb, e);
                    ctx->seen_eos = 1;
                    break;
                }

                /* flush buckets clear the buffer */
                if (APR_BUCKET_IS_FLUSH(e)) {
                    APR_BUCKET_REMOVE(e);
                    APR_BRIGADE_INSERT_TAIL(ctx->bb, e);
                    seen_flush = 1;
                    break;
                }

                /* pass metadata buckets through */
                if (APR_BUCKET_IS_METADATA(e)) {
                    APR_BUCKET_REMOVE(e);
                    APR_BRIGADE_INSERT_TAIL(ctx->bb, e);
                    continue;
                }

                /* read the bucket in, pack it into the buffer */
                if (APR_SUCCESS == (rv = apr_bucket_read(e, &data, &size,
                                                         APR_BLOCK_READ))) {
                    apr_brigade_write(ctx->bb, NULL, NULL, data, size);
                    ctx->remaining -= size;
                    apr_bucket_delete(e);
                } else {
                    return rv;
                }

            } while (!APR_BRIGADE_EMPTY(ctx->tmp));
        }
    }

    /* give the caller the data they asked for from the buffer */
    apr_brigade_partition(ctx->bb, readbytes, &after);
    e = APR_BRIGADE_FIRST(ctx->bb);
    while (e != after) {
        if (APR_BUCKET_IS_EOS(e)) {
            /* last bucket read, step out of the way */
            ap_remove_input_filter(f);
        }
        APR_BUCKET_REMOVE(e);
        APR_BRIGADE_INSERT_TAIL(bb, e);
        e = APR_BRIGADE_FIRST(ctx->bb);
    }

    return APR_SUCCESS;
}