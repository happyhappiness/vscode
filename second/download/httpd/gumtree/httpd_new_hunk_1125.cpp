                        continue;
                    }
                    else if (rv == APR_EOF) {
                        break;
                    }
                    else if (rv != APR_SUCCESS) {
                        /* In this case, we are in real trouble because
                         * our backend bailed on us. Pass along a 502 error
                         * error bucket
                         */
                        ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c,
                                      "proxy: error reading response");
                        ap_proxy_backend_broke(r, bb);
                        ap_pass_brigade(r->output_filters, bb);
                        backend_broke = 1;
                        backend->close = 1;
                        break;
                    }
                    /* next time try a non-blocking read */
                    mode = APR_NONBLOCK_READ;

                    apr_brigade_length(bb, 0, &readbytes);
