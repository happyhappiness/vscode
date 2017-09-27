        if (ap_process_config_tree(server_conf, ap_conftree, process->pconf,
                                   ptemp) != OK) {
            destroy_and_exit_process(process, 1);
        }
        ap_fixup_virtual_hosts(pconf, server_conf);
        ap_fini_vhost_config(pconf, server_conf);
        apr_pool_clear(plog);
        if (ap_run_open_logs(pconf, plog, ptemp, server_conf) != OK) {
            ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR,
                         0, NULL, "Unable to open logs");
            destroy_and_exit_process(process, 1);
        }
