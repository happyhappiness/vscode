                        backend->close = 1;
                        break;
                    }
                    /* next time try a non-blocking read */
                    mode = APR_NONBLOCK_READ;

                    if (!apr_is_empty_table(rp->trailers_in)) {
                        apr_table_do(add_trailers, r->trailers_out,
                                rp->trailers_in, NULL);
                        apr_table_clear(rp->trailers_in);
                    }

                    apr_brigade_length(bb, 0, &readbytes);
                    backend->worker->s->read += readbytes;
#if DEBUGGING
                    {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                                 r->server, "proxy (PID %d): readbytes: %#x",
