static void *ap_default_log_writer_init(apr_pool_t *p, server_rec *s,
                                        const char* name)
{
    if (*name == '|') {
        piped_log *pl;

        pl = ap_open_piped_log(p, name + 1);
        if (pl == NULL) {
           return NULL;;
        }
        return ap_piped_log_write_fd(pl);
    }
    else {
        const char *fname = ap_server_root_relative(p, name);
        apr_file_t *fd;
        apr_status_t rv;

        if (!fname) {
            ap_log_error(APLOG_MARK, APLOG_ERR, APR_EBADPATH, s,
                            "invalid transfer log path %s.", name);
            return NULL;
        }
        rv = apr_file_open(&fd, fname, xfer_flags, xfer_perms, p);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                            "could not open transfer log file %s.", fname);
            return NULL;
        }
        return fd;
    }
}