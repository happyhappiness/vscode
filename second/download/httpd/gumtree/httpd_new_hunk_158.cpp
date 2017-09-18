    if (ctx->limit) {
        /* FIXME: Note that we might get slightly confused on chunked inputs
         * as we'd need to compensate for the chunk lengths which may not
         * really count.  This seems to be up for interpretation.  */
        ctx->limit_used += totalread;
        if (ctx->limit < ctx->limit_used) {
            apr_bucket_brigade *bb;
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
                          "Read content-length of %" APR_OFF_T_FMT 
                          " is larger than the configured limit"
                          " of %" APR_OFF_T_FMT, ctx->limit_used, ctx->limit);
            bb = apr_brigade_create(f->r->pool, f->c->bucket_alloc);
            e = ap_bucket_error_create(HTTP_REQUEST_ENTITY_TOO_LARGE, NULL,
                                       f->r->pool,
                                       f->c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, e);
            e = apr_bucket_eos_create(f->c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, e);
            ctx->eos_sent = 1;
            return ap_pass_brigade(f->r->output_filters, bb);
        }
    }

    return APR_SUCCESS;
}

