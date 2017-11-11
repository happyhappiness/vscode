static apr_status_t bucketeer_out_filter(ap_filter_t *f,
                                         apr_bucket_brigade *bb)
{
    apr_bucket *e;
    request_rec *r = f->r;
    bucketeer_ctx_t *ctx = f->ctx;
    bucketeer_filter_config_t *c;

    c = ap_get_module_config(r->server->module_config, &bucketeer_module);

    /* If have a context, it means we've done this before successfully. */
    if (!ctx) {
        if (!r->content_type || strncmp(r->content_type, "text/", 5)) {
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }

        /* We're cool with filtering this. */
        ctx = f->ctx = apr_pcalloc(f->r->pool, sizeof(*ctx));
        ctx->bb = apr_brigade_create(f->r->pool, f->c->bucket_alloc);
        apr_table_unset(f->r->headers_out, "Content-Length");
    }

    for (e = APR_BRIGADE_FIRST(bb);
         e != APR_BRIGADE_SENTINEL(bb);
         e = APR_BUCKET_NEXT(e))
    {
        const char *data;
        apr_size_t len, i, lastpos;

        if (APR_BUCKET_IS_EOS(e)) {
            APR_BUCKET_REMOVE(e);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, e);

            /* Okay, we've seen the EOS.
             * Time to pass it along down the chain.
             */
            return ap_pass_brigade(f->next, ctx->bb);
        }

        if (APR_BUCKET_IS_FLUSH(e)) {
            /*
             * Ignore flush buckets for the moment..
             * we decide what to stream
             */
            continue;
        }

        if (APR_BUCKET_IS_METADATA(e)) {
            /* metadata bucket */
            apr_bucket *cpy;
            apr_bucket_copy(e, &cpy);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, cpy);
            continue;
        }

        /* read */
        apr_bucket_read(e, &data, &len, APR_BLOCK_READ);

        if (len > 0) {
            lastpos = 0;
            for (i = 0; i < len; i++) {
                if (data[i] == c->flushdelimiter ||
                    data[i] == c->bucketdelimiter ||
                    data[i] == c->passdelimiter) {
                    apr_bucket *p;
                    if (i - lastpos > 0) {
                        p = apr_bucket_pool_create(apr_pmemdup(f->r->pool,
                                                               &data[lastpos],
                                                               i - lastpos),
                                                    i - lastpos,
                                                    f->r->pool,
                                                    f->c->bucket_alloc);
                        APR_BRIGADE_INSERT_TAIL(ctx->bb, p);
                    }
                    lastpos = i + 1;
                    if (data[i] == c->flushdelimiter) {
                        p = apr_bucket_flush_create(f->c->bucket_alloc);
                        APR_BRIGADE_INSERT_TAIL(ctx->bb, p);
                    }
                    if (data[i] == c->passdelimiter) {
                        apr_status_t rv;

                        rv = ap_pass_brigade(f->next, ctx->bb);
                        if (rv) {
                            return rv;
                        }
                    }
                }
            }
            /* XXX: really should append this to the next 'real' bucket */
            if (lastpos < i) {
                apr_bucket *p;
                p = apr_bucket_pool_create(apr_pmemdup(f->r->pool,
                                                       &data[lastpos],
                                                       i - lastpos),
                                           i - lastpos,
                                           f->r->pool,
                                           f->c->bucket_alloc);
                lastpos = i;
                APR_BRIGADE_INSERT_TAIL(ctx->bb, p);
            }
        }
    }

    return APR_SUCCESS;
}