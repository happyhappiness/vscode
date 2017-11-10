static apr_status_t handle_echo(include_ctx_t *ctx, ap_filter_t *f,
                                apr_bucket_brigade *bb)
{
    const char *encoding = "entity", *decoding = "none";
    request_rec *r = f->r;
    int error = 0;

    if (!ctx->argc) {
        ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r, APLOGNO(01343)
                      "missing argument for echo element in %s",
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
                char *last = NULL;
                char *e, *d, *token;

                echo_text = val;

                d = apr_pstrdup(ctx->pool, decoding);
                token = apr_strtok(d, ", \t", &last);

                while(token) {
                    if (!strcasecmp(token, "none")) {
                        /* do nothing */
                    }
                    else if (!strcasecmp(token, "url")) {
                        char *buf = apr_pstrdup(ctx->pool, echo_text);
                        ap_unescape_url(buf);
                        echo_text = buf;
                    }
                    else if (!strcasecmp(token, "urlencoded")) {
                        char *buf = apr_pstrdup(ctx->pool, echo_text);
                        ap_unescape_urlencoded(buf);
                        echo_text = buf;
                    }
                    else if (!strcasecmp(token, "entity")) {
                        char *buf = apr_pstrdup(ctx->pool, echo_text);
                        decodehtml(buf);
                        echo_text = buf;
                    }
                    else if (!strcasecmp(token, "base64")) {
                        echo_text = ap_pbase64decode(ctx->dpool, echo_text);
                    }
                    else {
                        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01344) "unknown value "
                                      "\"%s\" to parameter \"decoding\" of tag echo in "
                                      "%s", token, r->filename);
                        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
                        error = 1;
                        break;
                    }
                    token = apr_strtok(NULL, ", \t", &last);
                }

                e = apr_pstrdup(ctx->pool, encoding);
                token = apr_strtok(e, ", \t", &last);

                while(token) {
                    if (!strcasecmp(token, "none")) {
                        /* do nothing */
                    }
                    else if (!strcasecmp(token, "url")) {
                        echo_text = ap_escape_uri(ctx->dpool, echo_text);
                    }
                    else if (!strcasecmp(token, "urlencoded")) {
                        echo_text = ap_escape_urlencoded(ctx->dpool, echo_text);
                    }
                    else if (!strcasecmp(token, "entity")) {
                        echo_text = ap_escape_html2(ctx->dpool, echo_text, 0);
                    }
                    else if (!strcasecmp(token, "base64")) {
                        char *buf;
                        buf = ap_pbase64encode(ctx->dpool, (char *)echo_text);
                        echo_text = buf;
                    }
                    else {
                        ap_log_rerror(