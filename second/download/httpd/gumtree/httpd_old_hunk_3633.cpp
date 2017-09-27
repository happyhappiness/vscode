                        backend->close = 1;
                        break;
                    }
                    /* next time try a non-blocking read */
                    mode = APR_NONBLOCK_READ;

                    apr_brigade_length(bb, 0, &readbytes);
                    backend->worker->s->read += readbytes;
#if DEBUGGING
                    {
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01111)
                                  "readbytes: %#x", readbytes);
