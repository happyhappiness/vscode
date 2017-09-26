
    rv = ap_process_config_tree(server_conf, ap_conftree,
                                process->pconf, ptemp);
    if (rv == OK) {
        ap_fixup_virtual_hosts(pconf, server_conf);
        ap_fini_vhost_config(pconf, server_conf);

        if (configtestonly) {
            ap_run_test_config(pconf, server_conf);
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, "Syntax OK");
            destroy_and_exit_process(process, 0);
        }
