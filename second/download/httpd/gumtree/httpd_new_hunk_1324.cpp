
    rv = ap_process_config_tree(server_conf, ap_conftree,
                                process->pconf, ptemp);
    if (rv == OK) {
        ap_fixup_virtual_hosts(pconf, server_conf);
        ap_fini_vhost_config(pconf, server_conf);
        /*
         * Sort hooks again because ap_process_config_tree may have added
         * modules and hence hooks. This happens with mod_perl and modules
         * written in perl.
         */
        apr_hook_sort_all();

        if (configtestonly) {
            ap_run_test_config(pconf, server_conf);
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, "Syntax OK");
            destroy_and_exit_process(process, 0);
        }
