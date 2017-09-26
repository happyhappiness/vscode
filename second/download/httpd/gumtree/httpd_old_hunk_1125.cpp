                        continue;
                    }
                    else if (rv == APR_EOF) {
                        break;
                    }
                    else if (rv != APR_SUCCESS) {
                        ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c,
                                      "proxy: error reading response");
                        break;
                    }
                    /* next time try a non-blocking read */
                    mode = APR_NONBLOCK_READ;

                    apr_brigade_length(bb, 0, &readbytes);
