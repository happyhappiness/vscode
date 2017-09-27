                    }
                    apr_brigade_cleanup(bb);
                }

                /* Detect chunksize error (such as overflow) */
                if (rv != APR_SUCCESS || ctx->remaining < 0) {
                    ctx->remaining = 0; /* Reset it in case we have to
                                         * come back here later */
                    bail_out_on_error(ctx, f, http_error);
                    return rv;
                }

                if (!ctx->remaining) {
                    /* Handle trailers by calling ap_get_mime_headers again! */
                    ctx->state = BODY_NONE;
                    ap_get_mime_headers(f->r);
