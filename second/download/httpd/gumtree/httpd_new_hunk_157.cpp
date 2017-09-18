            if (!strcasecmp(tenc, "chunked")) {
                ctx->state = BODY_CHUNK;
            }
        }
        else if (lenp) {
            const char *pos = lenp;
            int conversion_error = 0;

            /* This ensures that the number can not be negative. */
            while (apr_isdigit(*pos) || apr_isspace(*pos)) {
                ++pos;
            }

            if (*pos == '\0') {
                char *endstr;

                errno = 0;
                ctx->state = BODY_LENGTH;
                ctx->remaining = strtol(lenp, &endstr, 10);

                if (errno || (endstr && *endstr)) {
                    conversion_error = 1; 
                }
            }

            if (*pos != '\0' || conversion_error) {
                apr_bucket_brigade *bb;

                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
                              "Invalid Content-Length");

                bb = apr_brigade_create(f->r->pool, f->c->bucket_alloc);
                e = ap_bucket_error_create(HTTP_REQUEST_ENTITY_TOO_LARGE, NULL,
                                           f->r->pool, f->c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(bb, e);
                e = apr_bucket_eos_create(f->c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(bb, e);
                ctx->eos_sent = 1;
                return ap_pass_brigade(f->r->output_filters, bb);
            }
            
            /* If we have a limit in effect and we know the C-L ahead of
             * time, stop it here if it is invalid. 
             */ 
            if (ctx->limit && ctx->limit < ctx->remaining) {
                apr_bucket_brigade *bb;
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
                          "Requested content-length of %" APR_OFF_T_FMT 
                          " is larger than the configured limit"
                          " of %" APR_OFF_T_FMT, ctx->remaining, ctx->limit);
                bb = apr_brigade_create(f->r->pool, f->c->bucket_alloc);
                e = ap_bucket_error_create(HTTP_REQUEST_ENTITY_TOO_LARGE, NULL,
                                           f->r->pool, f->c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(bb, e);
                e = apr_bucket_eos_create(f->c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(bb, e);
                ctx->eos_sent = 1;
                return ap_pass_brigade(f->r->output_filters, bb);
            }
        }

        /* If we don't have a request entity indicated by the headers, EOS.
         * (BODY_NONE is a valid intermediate state due to trailers,
         *  but it isn't a valid starting state.)
         *
         * RFC 2616 Section 4.4 note 5 states that connection-close
         * is invalid for a request entity - request bodies must be
         * denoted by C-L or T-E: chunked.
         *
         * Note that since the proxy uses this filter to handle the
         * proxied *response*, proxy responses MUST be exempt.
         */
        if (ctx->state == BODY_NONE && f->r->proxyreq != PROXYREQ_RESPONSE) {
            e = apr_bucket_eos_create(f->c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(b, e);
            ctx->eos_sent = 1;
            return APR_SUCCESS;
        }

        /* Since we're about to read data, send 100-Continue if needed.
         * Only valid on chunked and C-L bodies where the C-L is > 0. */
        if ((ctx->state == BODY_CHUNK || 
            (ctx->state == BODY_LENGTH && ctx->remaining > 0)) &&
            f->r->expecting_100 && f->r->proto_num >= HTTP_VERSION(1,1)) {
            char *tmp;
