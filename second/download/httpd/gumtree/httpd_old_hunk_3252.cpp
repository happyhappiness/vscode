     * compute this config file name afterwards.
     */
    confname = ap_server_root_relative(p, filename);

    if (!confname) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT,
                     APR_EBADPATH, NULL, "Invalid config file path %s",
                     filename);
        return NULL;
    }

    error = ap_process_resource_config(s, confname, conftree, p, ptemp);
    if (error) {
