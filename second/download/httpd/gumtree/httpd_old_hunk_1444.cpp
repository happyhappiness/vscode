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
            errno = 0;

            /* Protects against over/underflow, non-digit chars in the
