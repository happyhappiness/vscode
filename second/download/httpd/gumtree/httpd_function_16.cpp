static config_log_state *open_config_log(server_rec *s, apr_pool_t *p,
                                         config_log_state *cls,
                                         apr_array_header_t *default_format)
{
    apr_status_t status;
    void *data;
    const char *userdata_key = "open_config_log";

    /* Skip opening the log the first time through. It's really
     * good to avoid starting the piped log process during preflight.
     */
    apr_pool_userdata_get(&data, userdata_key, s->process->pool);
    if (!data) {
        apr_pool_userdata_set((const void *)1, userdata_key,
                              NULL, s->process->pool);
        /* If logging for the first time after a restart, keep going. */
        if (!ap_my_generation) {
            return cls;
        }
    }

    if (cls->log_fd != NULL) {
        return cls;             /* virtual config shared w/main server */
    }

    if (cls->fname == NULL) {
        return cls;             /* Leave it NULL to decline.  */
    }

    if (*cls->fname == '|') {
        piped_log *pl;

        pl = ap_open_piped_log(p, cls->fname + 1);
        if (pl == NULL) {
            exit(1);
        }
        cls->log_fd = ap_piped_log_write_fd(pl);
    }
    else {
        const char *fname = ap_server_root_relative(p, cls->fname);
        if (!fname) {
            ap_log_error(APLOG_MARK, APLOG_ERR, APR_EBADPATH, s,
                         "invalid transfer log path %s.", cls->fname);
            exit(1);
        }
        if ((status = apr_file_open(&cls->log_fd, fname, xfer_flags,
                                    xfer_perms, p)) != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, status, s,
                         "could not open transfer log file %s.", fname);
            exit(1);
        }
        apr_file_inherit_set(cls->log_fd);
    }
#ifdef BUFFERED_LOGS
    cls->outcnt = 0;
#endif

    return cls;
}