                }

                /* Detect chunksize error (such as overflow) */
                if (rv != APR_SUCCESS || ctx->remaining < 0) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, "Error reading chunk %s ", 
                                  (ctx->remaining < 0) ? "(overflow)" : "");
                    if (APR_STATUS_IS_TIMEUP(rv) || ctx->remaining > 0) {
                        http_error = HTTP_REQUEST_TIME_OUT;
                    }
                    ctx->remaining = 0; /* Reset it in case we have to
                                         * come back here later */
                    return bail_out_on_error(ctx, f, http_error);
                }

                if (!ctx->remaining) {
                    return read_chunked_trailers(ctx, f, b,
                            conf->merge_trailers == AP_MERGE_TRAILERS_ENABLE);
                }
            }
            break;
        }
    }

