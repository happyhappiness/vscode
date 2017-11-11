static int open_log(server_rec *s, apr_pool_t *p)
{
    fcfg *cfg = ap_get_module_config(s->module_config, &log_forensic_module);

    if (!cfg->logname || cfg->fd)
        return 1;

    if (*cfg->logname == '|') {
        piped_log *pl;
        const char *pname = ap_server_root_relative(p, cfg->logname + 1);

        pl = ap_open_piped_log(p, pname);
        if (pl == NULL) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                         "couldn't spawn forensic log pipe %s", cfg->logname);
            return 0;
        }
        cfg->fd = ap_piped_log_write_fd(pl);
    }
    else {
        const char *fname = ap_server_root_relative(p, cfg->logname);
        apr_status_t rv;

        if ((rv = apr_file_open(&cfg->fd, fname,
                                APR_WRITE | APR_APPEND | APR_CREATE,
                                APR_OS_DEFAULT, p)) != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "could not open forensic log file %s.", fname);
            return 0;
        }
    }

    return 1;
}