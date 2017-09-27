        }

        tenc = apr_table_get(f->r->headers_in, "Transfer-Encoding");
        lenp = apr_table_get(f->r->headers_in, "Content-Length");

        if (tenc) {
            if (strcasecmp(tenc, "chunked") == 0 /* fast path */
                    || ap_find_last_token(f->r->pool, tenc, "chunked")) {
                ctx->state = BODY_CHUNK;
            }
            else if (f->r->proxyreq == PROXYREQ_RESPONSE) {
                /* http://tools.ietf.org/html/draft-ietf-httpbis-p1-messaging-23
                 * Section 3.3.3.3: "If a Transfer-Encoding header field is
                 * present in a response and the chunked transfer coding is not
                 * the final encoding, the message body length is determined by
                 * reading the connection until it is closed by the server."
                 */
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, f->r,
                              "Unknown Transfer-Encoding: %s; "
                              "using read-until-close", tenc);
                tenc = NULL;
            }
            else {
                /* Something that isn't a HTTP request, unless some future
                 * edition defines new transfer encodings, is unsupported.
                 */
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, f->r,
                              "Unknown Transfer-Encoding: %s", tenc);
                return bail_out_on_error(ctx, f, HTTP_NOT_IMPLEMENTED);
            }
            lenp = NULL;
        }
        if (lenp) {
            char *endstr;

            ctx->state = BODY_LENGTH;
            errno = 0;

            /* Protects against over/underflow, non-digit chars in the
