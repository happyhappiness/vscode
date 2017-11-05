static apr_status_t handle_set(include_ctx_t *ctx, ap_filter_t *f,
                               apr_bucket_brigade *bb)
{
    char *var = NULL;
    request_rec *r = f->r;
    request_rec *sub = r->main;
    apr_pool_t *p = r->pool;

    if (ctx->argc < 2) {
        ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r, "missing argument for set element in %s",
                      r->filename);
    }

    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
        return APR_SUCCESS;
    }

    if (ctx->argc < 2) {
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    /* we need to use the 'main' request pool to set notes as that is
     * a notes lifetime
     */
    while (sub) {
        p = sub->pool;
        sub = sub->main;
    }

    while (1) {
        char *tag = NULL;
        char *tag_val = NULL;

        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, SSI_VALUE_DECODED);

        if (!tag || !tag_val) {
            break;
        }

        if (!strcmp(tag, "var")) {
            var = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
                                      SSI_EXPAND_DROP_NAME);
        }
        else if (!strcmp(tag, "value")) {
            char *parsed_string;

            if (!var) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "variable must "
                              "precede value in set directive in %s",
                              r->filename);
                SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
                break;
            }

            parsed_string = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
                                                SSI_EXPAND_DROP_NAME);
            apr_table_setn(r->subprocess_env, apr_pstrdup(p, var),
                           apr_pstrdup(p, parsed_string));
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "Invalid tag for set "
                          "directive in %s", r->filename);
            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
            break;
        }
    }

    return APR_SUCCESS;
}