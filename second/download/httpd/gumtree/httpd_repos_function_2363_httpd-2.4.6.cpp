static apr_status_t handle_set(include_ctx_t *ctx, ap_filter_t *f,
                               apr_bucket_brigade *bb)
{
    const char *encoding = "none", *decoding = "none";
    char *var = NULL;
    request_rec *r = f->r;
    request_rec *sub = r->main;
    apr_pool_t *p = r->pool;
    int error = 0;

    if (ctx->argc < 2) {
        ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r,
                      APLOGNO(01362) "missing argument for set element in %s",
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

        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, SSI_VALUE_RAW);

        if (!tag || !tag_val) {
            break;
        }

        if (!strcmp(tag, "var")) {
            decodehtml(tag_val);
            var = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
                                      SSI_EXPAND_DROP_NAME);
        }
        else if (!strcmp(tag, "decoding")) {
            decoding = tag_val;
        }
        else if (!strcmp(tag, "encoding")) {
            encoding = tag_val;
        }
        else if (!strcmp(tag, "value")) {
            char *parsed_string;

            if (!var) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01363) "variable must "
                              "precede value in set directive in %s",
                              r->filename);
                SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
                break;
            }

            parsed_string = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
                                                SSI_EXPAND_DROP_NAME);

            if (parsed_string) {
                char *last = NULL;
                char *e, *d, *token;

                d = apr_pstrdup(ctx->pool, decoding);
                token = apr_strtok(d, ", \t", &last);

                while(token) {
                    if (!strcasecmp(token, "none")) {
                        /* do nothing */
                    }
                    else if (!strcasecmp(token, "url")) {
                        char *buf = apr_pstrdup(ctx->pool, parsed_string);
                        ap_unescape_url(buf);
                        parsed_string = buf;
                    }
                    else if (!strcasecmp(token, "urlencoded")) {
                        char *buf = apr_pstrdup(ctx->pool, parsed_string);
                        ap_unescape_urlencoded(buf);
                        parsed_string = buf;
                    }
                    else if (!strcasecmp(token, "entity")) {
                        char *buf = apr_pstrdup(ctx->pool, parsed_string);
                        decodehtml(buf);
                        parsed_string = buf;
                    }
                    else if (!strcasecmp(token, "base64")) {
                        parsed_string = ap_pbase64decode(ctx->dpool, parsed_string);
                    }
                    else {
                        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01364) "unknown value "
                                      "\"%s\" to parameter \"decoding\" of tag set in "
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
                        parsed_string = ap_escape_uri(ctx->dpool, parsed_string);
                    }
                    else if (!strcasecmp(token, "urlencoded")) {
                        parsed_string = ap_escape_urlencoded(ctx->dpool, parsed_string);
                    }
                    else if (!strcasecmp(token, "entity")) {
                        parsed_string = ap_escape_html2(ctx->dpool, parsed_string, 0);
                    }
                    else if (!strcasecmp(token, "base64")) {
                        char *buf;
                        buf = ap_pbase64encode(ctx->dpool, (char *)parsed_string);
                        parsed_string = buf;
                    }
                    else {
                        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01365) "unknown value "
                                      "\"%s\" to parameter \"encoding\" of tag set in "
                                      "%s", token, r->filename);
                        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
                        error = 1;
                        break;
                    }
                    token = apr_strtok(NULL, ", \t", &last);
                }

            }

            if (error) {
                break;
            }

            apr_table_setn(r->subprocess_env, apr_pstrdup(p, var),
                           apr_pstrdup(p, parsed_string));
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01366) "Invalid tag for set "
                          "directive in %s", r->filename);
            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
            break;
        }
    }

    return APR_SUCCESS;
}