

AP_DECLARE(server_rec*) ap_read_config(process_rec *process, apr_pool_t *ptemp,
                                       const char *filename,
                                       ap_directive_t **conftree)
{
    const char *confname;
    apr_pool_t *p = process->pconf;
    server_rec *s = init_server_config(process, p);

    init_config_globals(p);

    /* All server-wide config files now have the SAME syntax... */
    process_command_config(s, ap_server_pre_read_config, conftree,
                           p, ptemp);

    /* process_command_config may change the ServerRoot so
     * compute this config file name afterwards.
     */
    confname = ap_server_root_relative(p, filename);

    if (!confname) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT,
                     APR_EBADPATH, NULL, "Invalid config file path %s",
                     filename);
        exit(1);
    }

    ap_process_resource_config(s, confname, conftree, p, ptemp);

    process_command_config(s, ap_server_post_read_config, conftree,
                           p, ptemp);

    return s;
}

AP_DECLARE(void) ap_single_module_configure(apr_pool_t *p, server_rec *s,
                                            module *m)
