            if (!strcasecmp(tenc, "chunked")) {
                ctx->state = BODY_CHUNK;
            }
        }
        else if (lenp) {
            const char *pos = lenp;

            while (apr_isdigit(*pos) || apr_isspace(*pos)) {
                ++pos;
            }

            if (*pos == '\0') {
                ctx->state = BODY_LENGTH;
                ctx->remaining = atol(lenp);
            }
            
            /* If we have a limit in effect and we know the C-L ahead of
             * time, stop it here if it is invalid. 
             */ 
            if (ctx->limit && ctx->limit < ctx->remaining) {
                ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, f->r,
                          "Requested content-length of %" APR_OFF_T_FMT 
                          " is larger than the configured limit"
                          " of %" APR_OFF_T_FMT, ctx->remaining, ctx->limit);
                ap_die(HTTP_REQUEST_ENTITY_TOO_LARGE, f->r);
                return APR_EGENERAL;
            }
        }

        /* Since we're about to read data, send 100-Continue if needed.
         * Only valid on chunked and C-L bodies where the C-L is > 0. */
        if ((ctx->state == BODY_CHUNK || 
            (ctx->state == BODY_LENGTH && ctx->remaining > 0)) &&
            f->r->expecting_100 && f->r->proto_num >= HTTP_VERSION(1,1)) {
            char *tmp;
