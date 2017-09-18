                                      APR_BLOCK_READ, 
                                      conf->io_buffer_size) == APR_SUCCESS) {
#if DEBUGGING
                    {
                    apr_off_t readbytes;
                    apr_brigade_length(bb, 0, &readbytes);
                    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0,
                                 r->server, "proxy (PID %d): readbytes: %#x",
                                 getpid(), readbytes);
                    }
#endif
                    /* sanity check */
                    if (APR_BRIGADE_EMPTY(bb)) {
