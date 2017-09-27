            break;
    }

    if (f == NULL) {
        /* our filter hasn't been added yet */
        ctx = apr_pcalloc(r->pool, sizeof(*ctx));
        ap_add_output_filter("OLD_WRITE", ctx, r, r->connection);
        f = r->output_filters;
    }

    /* if the first filter is not our buffering filter, then we have to
     * deliver the content through the normal filter chain
     */
    if (f != r->output_filters) {
        apr_bucket_brigade *bb = apr_brigade_create(r->pool, c->bucket_alloc);
        apr_bucket *b = apr_bucket_transient_create(str, len, c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);

        return ap_pass_brigade(r->output_filters, bb);
    }

    /* grab the context from our filter */
    ctx = r->output_filters->ctx;

    if (ctx->bb == NULL) {
        ctx->bb = apr_brigade_create(r->pool, c->bucket_alloc);
    }

    return ap_fwrite(f->next, ctx->bb, str, len);
}
