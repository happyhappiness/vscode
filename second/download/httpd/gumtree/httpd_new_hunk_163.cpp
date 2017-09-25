        rv = apr_file_open(&fd, fname, xfer_flags, xfer_perms, p);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                            "could not open transfer log file %s.", fname);
            return NULL;
        }
        return fd;
    }
}
static void *ap_buffered_log_writer_init(apr_pool_t *p, server_rec *s, 
                                        const char* name)
{
