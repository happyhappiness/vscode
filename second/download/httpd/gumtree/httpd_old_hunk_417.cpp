    ap_server_root = def_server_root;
    if (temp_error_log) {
        ap_replace_stderr_log(process->pool, temp_error_log);
    }
    server_conf = ap_read_config(process, ptemp, confname, &ap_conftree);
    if (ap_run_pre_config(pconf, plog, ptemp) != OK) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR| APLOG_NOERRNO, 0,
                     NULL, "Pre-configuration failed\n");
        destroy_and_exit_process(process, 1);
    }

    ap_process_config_tree(server_conf, ap_conftree, process->pconf, ptemp);
    ap_fixup_virtual_hosts(pconf, server_conf);
    ap_fini_vhost_config(pconf, server_conf);
    apr_sort_hooks();
    if (configtestonly) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL,
                     "Syntax OK\n");
        destroy_and_exit_process(process, 0);
    }

    apr_pool_clear(plog);

    /* It is assumed that if you are going to fail the open_logs phase, then
     * you will print out your own message that explains what has gone wrong.
     * The server doesn't need to do that for you.
     */
    if ( ap_run_open_logs(pconf, plog, ptemp, server_conf) != OK) {
        destroy_and_exit_process(process, 1);
    }

    if ( ap_run_post_config(pconf, plog, ptemp, server_conf) != OK) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR| APLOG_NOERRNO, 0,
                     NULL, "Configuration Failed\n");
        destroy_and_exit_process(process, 1);
    }

    apr_pool_destroy(ptemp);

