                else {
                    do_sleep = 1;
                }

                apr_brigade_length(bb, 1, &len);

                rv = apr_brigade_partition(bb, ctx->chunk_size, &stop_point);
                if (rv != APR_SUCCESS && rv != APR_INCOMPLETE) {
                    ctx->state = RATE_ERROR;
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, APLOGNO(01456)
                                  "rl: partition failed.");
                    break;
                }
