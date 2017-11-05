static apr_status_t pass_data_to_filter(ap_filter_t *f, const char *data, 
                                        apr_size_t len)
{
    ef_ctx_t *ctx = f->ctx;
    ef_dir_t *dc = ctx->dc;
    apr_status_t rv;
    apr_size_t bytes_written = 0;
    apr_size_t tmplen;
    
    do {
        tmplen = len - bytes_written;
        rv = apr_file_write(ctx->proc->in,
                       (const char *)data + bytes_written,
                       &tmplen);
        bytes_written += tmplen;
        if (rv != APR_SUCCESS && !APR_STATUS_IS_EAGAIN(rv)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r,
                          "apr_file_write(child input), len %" APR_SIZE_T_FMT,
                          tmplen);
            return rv;
        }
        if (APR_STATUS_IS_EAGAIN(rv)) {
            /* XXX handle blocking conditions here...  if we block, we need 
             * to read data from the child process and pass it down to the
             * next filter!
             */
            rv = drain_available_output(f);
            if (APR_STATUS_IS_EAGAIN(rv)) {
#if APR_FILES_AS_SOCKETS
                int num_events;
                
                rv = apr_poll(ctx->pollset, 2,
                              &num_events, f->r->server->timeout);
                if (rv || dc->debug >= DBGLVL_GORY) {
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG,
                                  rv, f->r, "apr_poll()");
                }
                if (rv != APR_SUCCESS && !APR_STATUS_IS_EINTR(rv)) { 
                    /* some error such as APR_TIMEUP */
                    return rv;
                }
#else /* APR_FILES_AS_SOCKETS */
                /* Yuck... I'd really like to wait until I can read
                 * or write, but instead I have to sleep and try again 
                 */
                apr_sleep(100000); /* 100 milliseconds */
                if (dc->debug >= DBGLVL_GORY) {
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 
                                  0, f->r, "apr_sleep()");
                }
#endif /* APR_FILES_AS_SOCKETS */
            }
            else if (rv != APR_SUCCESS) {
                return rv;
            }
        }
    } while (bytes_written < len);
    return rv;
}