            if (APR_STATUS_IS_EAGAIN(rv)) {
#if APR_FILES_AS_SOCKETS
                int num_events;
                
                rv = apr_poll(ctx->pollset,
                              &num_events,
                              f->r->server->timeout * APR_USEC_PER_SEC);
                if (rv || dc->debug >= DBGLVL_GORY) {
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG,
                                  rv, f->r, "apr_poll()");
                }
                if (rv != APR_SUCCESS && !APR_STATUS_IS_EINTR(rv)) { 
                    /* some error such as APR_TIMEUP */
