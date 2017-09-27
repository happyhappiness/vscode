    else {
        const char *fname = ap_server_root_relative(p, name);
        apr_file_t *fd;
        apr_status_t rv;

        if (!fname) {
            ap_log_error(APLOG_MARK, APLOG_ERR, APR_EBADPATH, s, APLOGNO(00648)
                            "invalid transfer log path %s.", name);
            return NULL;
        }
        rv = apr_file_open(&fd, fname, xfer_flags, xfer_perms, p);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(00649)
                            "could not open transfer log file %s.", fname);
            return NULL;
        }
        return fd;
    }
}
