static apr_status_t handle_echo(include_ctx_t *ctx, ap_filter_t *f,
                                apr_bucket_brigade *bb)
{
    enum {E_NONE, E_URL, E_ENTITY} encode;
    request_rec *r = f->r;

    if (!ctx->argc) {
        ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r, "missing argument for echo element in %s",
                      r->filename);
    }

    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
        return APR_SUCCESS;
    }

    if (!ctx->argc) {
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    encode = E_ENTITY;

    while (1) {
        char *tag = NULL;
        char *tag_val = NULL;

        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, SSI_VALUE_DECODED);
        if (!tag || !tag_val) {
            break;
        }

        if (!strcmp(tag, "var")) {
            const char *val;
            const char *echo_text = NULL;
            apr_size_t e_len;

            val = get_include_var(ap_ssi_parse_string(ctx, tag_val, NULL,
                                                      0, SSI_EXPAND_DROP_NAME),
                                  ctx);

            if (val) {
                switch(encode) {
                case E_NONE:
                    echo_text = val;
                    break;
                case E_URL:
                    echo_text = ap_escape_uri(ctx->dpool, val);
                    break;
                case E_ENTITY:
                    /* PR#25202: escape anything non-ascii here */
                    echo_text = ap_escape_html2(ctx->dpool, val, 1);
                    break;
                }

                e_len = strlen(echo_text);
            }
            else {
                echo_text = ctx->intern->undefined_echo;
                e_len = ctx->intern->undefined_echo_len;
            }

            APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pool_create(
                                    apr_pmemdup(ctx->pool, echo_text, e_len),
                                    e_len, ctx->pool, f->c->bucket_alloc));
        }
        else if (!strcmp(tag, "encoding")) {
            if (!strcasecmp(tag_val, "none")) {
                encode = E_NONE;
            }
            else if (!strcasecmp(tag_val, "url")) {
                encode = E_URL;
            }
            else if (!strcasecmp(tag_val, "entity")) {
                encode = E_ENTITY;
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown value "
                              "\"%s\" to parameter \"encoding\" of tag echo in "
                              "%s", tag_val, r->filename);
                SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
                break;
            }
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown parameter "
                          "\"%s\" in tag echo of %s", tag, r->filename);
            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
            break;
        }
    }

    return APR_SUCCESS;
}