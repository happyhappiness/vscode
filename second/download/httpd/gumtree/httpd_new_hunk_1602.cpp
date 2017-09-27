        }

        tenc = apr_table_get(f->r->headers_in, "Transfer-Encoding");
        lenp = apr_table_get(f->r->headers_in, "Content-Length");

        if (tenc) {
            if (!strcasecmp(tenc, "chunked")) {
                ctx->state = BODY_CHUNK;
            }
            /* test lenp, because it gives another case we can handle */
            else if (!lenp) {
                /* Something that isn't in HTTP, unless some future
                 * edition defines new transfer ecodings, is unsupported.
                 */
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
                              "Unknown Transfer-Encoding: %s", tenc);
                return bail_out_on_error(ctx, f, HTTP_NOT_IMPLEMENTED);
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, f->r,
                  "Unknown Transfer-Encoding: %s; using Content-Length", tenc);
                tenc = NULL;
            }
        }
        if (lenp && !tenc) {
            char *endstr;

            ctx->state = BODY_LENGTH;

            /* Protects against over/underflow, non-digit chars in the
             * string (excluding leading space) (the endstr checks)
             * and a negative number. */
            if (apr_strtoff(&ctx->remaining, lenp, &endstr, 10)
                || endstr == lenp || *endstr || ctx->remaining < 0) {

                ctx->remaining = 0;
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r,
                              "Invalid Content-Length");

                return bail_out_on_error(ctx, f, HTTP_REQUEST_ENTITY_TOO_LARGE);
            }

            /* If we have a limit in effect and we know the C-L ahead of
             * time, stop it here if it is invalid.
             */
            if (ctx->limit && ctx->limit < ctx->remaining) {
