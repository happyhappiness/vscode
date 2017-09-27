             * string (excluding leading space) (the endstr checks)
             * and a negative number. */
            if (apr_strtoff(&ctx->remaining, lenp, &endstr, 10)
                || endstr == lenp || *endstr || ctx->remaining < 0) {

                ctx->remaining = 0;
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, f->r, APLOGNO(01587)
                              "Invalid Content-Length");

                return bail_out_on_error(ctx, f, HTTP_REQUEST_ENTITY_TOO_LARGE);
            }

            /* If we have a limit in effect and we know the C-L ahead of
             * time, stop it here if it is invalid.
             */
            if (ctx->limit && ctx->limit < ctx->remaining) {
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, f->r, APLOGNO(01588)
                          "Requested content-length of %" APR_OFF_T_FMT
                          " is larger than the configured limit"
                          " of %" APR_OFF_T_FMT, ctx->remaining, ctx->limit);
                return bail_out_on_error(ctx, f, HTTP_REQUEST_ENTITY_TOO_LARGE);
            }
        }
