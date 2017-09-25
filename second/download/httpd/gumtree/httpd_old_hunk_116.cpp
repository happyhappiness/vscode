        destroy_and_exit_process(process, 1);
    }

    ap_process_config_tree(server_conf, ap_conftree, process->pconf, ptemp);
    ap_fixup_virtual_hosts(pconf, server_conf);
    ap_fini_vhost_config(pconf, server_conf);
    apr_sort_hooks();
    if (configtestonly) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, "Syntax OK");
        destroy_and_exit_process(process, 0);
    }

    signal_server = APR_RETRIEVE_OPTIONAL_FN(ap_signal_server);
