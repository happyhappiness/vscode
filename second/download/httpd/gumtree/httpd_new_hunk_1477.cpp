                || endstr == lenp || *endstr || ctx->remaining < 0) {

                ctx->remaining = 0;
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
                              "Invalid Content-Length");

                return bail_out_on_error(ctx, f, HTTP_BAD_REQUEST);
            }

            /* If we have a limit in effect and we know the C-L ahead of
             * time, stop it here if it is invalid.
             */
            if (ctx->limit && ctx->limit < ctx->remaining) {
