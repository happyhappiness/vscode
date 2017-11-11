static apr_status_t handle_fsize(include_ctx_t *ctx, ap_filter_t *f,
                                 apr_bucket_brigade *bb)
{
    request_rec *r = f->r;

    if (!ctx->argc) {
        ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r, "missing argument for fsize element in %s",
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
        apr_finfo_t finfo;
        char *parsed_string;

        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, SSI_VALUE_DECODED);
        if (!tag || !tag_val) {
            break;
        }

        parsed_string = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
                                            SSI_EXPAND_DROP_NAME);

        if (!find_file(r, "fsize", tag, parsed_string, &finfo)) {
            char *buf;
            apr_size_t len;

            if (!(ctx->flags & SSI_FLAG_SIZE_IN_BYTES)) {
                buf = apr_strfsize(finfo.size, apr_palloc(ctx->pool, 5));
                len = 4; /* omit the \0 terminator */
            }
            else {
                apr_size_t l, x, pos;
                char *tmp;

                tmp = apr_psprintf(ctx->dpool, "%" APR_OFF_T_FMT, finfo.size);
                len = l = strlen(tmp);

                for (x = 0; x < l; ++x) {
                    if (x && !((l - x) % 3)) {
                        ++len;
                    }
                }

                if (len == l) {
                    buf = apr_pstrmemdup(ctx->pool, tmp, len);
                }
                else {
                    buf = apr_palloc(ctx->pool, len);

                    for (pos = x = 0; x < l; ++x) {
                        if (x && !((l - x) % 3)) {
                            buf[pos++] = ',';
                        }
                        buf[pos++] = tmp[x];
                    }
                }
            }

            APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pool_create(buf, len,
                                    ctx->pool, f->c->bucket_alloc));
        }
        else {
            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
            break;
        }
    }

    return APR_SUCCESS;
}