static apr_status_t handle_flastmod(include_ctx_t *ctx, ap_filter_t *f,
                                    apr_bucket_brigade *bb)
{
    request_rec *r = f->r;

    if (!ctx->argc) {
        ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r, "missing argument for flastmod element in %s",
                      r->filename);
    }

    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
        return APR_SUCCESS;
    }

    if (!ctx->argc) {
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    while (1) {
        char *tag     = NULL;
        char *tag_val = NULL;
        apr_finfo_t  finfo;
        char *parsed_string;

        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, SSI_VALUE_DECODED);
        if (!tag || !tag_val) {
            break;
        }

        parsed_string = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
                                            SSI_EXPAND_DROP_NAME);

        if (!find_file(r, "flastmod", tag, parsed_string, &finfo)) {
            char *t_val;
            apr_size_t t_len;

            t_val = ap_ht_time(ctx->pool, finfo.mtime, ctx->time_str, 0);
            t_len = strlen(t_val);

            APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pool_create(t_val, t_len,
                                    ctx->pool, f->c->bucket_alloc));
        }
        else {
            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
            break;
        }
    }

    return APR_SUCCESS;
}