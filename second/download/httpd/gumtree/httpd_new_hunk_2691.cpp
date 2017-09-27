
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
                        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01345) "unknown value "
                                      "\"%s\" to parameter \"encoding\" of tag echo in "
                                      "%s", token, r->filename);
                        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
                        error = 1;
                        break;
                    }
                    token = apr_strtok(NULL, ", \t", &last);
                }

                e_len = strlen(echo_text);
            }
            else {
                echo_text = ctx->intern->undefined_echo;
                e_len = ctx->intern->undefined_echo_len;
            }

            if (error) {
                break;
            }

            APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pool_create(
                                    apr_pmemdup(ctx->pool, echo_text, e_len),
                                    e_len, ctx->pool, f->c->bucket_alloc));
        }
        else if (!strcmp(tag, "decoding")) {
            decoding = tag_val;
        }
        else if (!strcmp(tag, "encoding")) {
            encoding = tag_val;
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01346) "unknown parameter "
                          "\"%s\" in tag echo of %s", tag, r->filename);
            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
            break;
        }
    }

