        ap_replace_stderr_log(process->pool, temp_error_log);
    }
    ap_server_conf = ap_read_config(process, ptemp, confname, &ap_conftree);
    if (!ap_server_conf) {
        destroy_and_exit_process(process, 1);
    }

    if (ap_run_pre_config(pconf, plog, ptemp) != OK) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR, 0,
                     NULL, "Pre-configuration failed");
        destroy_and_exit_process(process, 1);
    }

    rv = ap_process_config_tree(ap_server_conf, ap_conftree,
                                process->pconf, ptemp);
    if (rv == OK) {
        ap_fixup_virtual_hosts(pconf, ap_server_conf);
        ap_fini_vhost_config(pconf, ap_server_conf);
        apr_hook_sort_all();

        if (ap_run_check_config(pconf, plog, ptemp, ap_server_conf) != OK) {
            ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR, 0,
                         NULL, "Configuration check failed");
            destroy_and_exit_process(process, 1);
        }

        if (configtestonly) {
            ap_run_test_config(pconf, ap_server_conf);
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, "Syntax OK");
            destroy_and_exit_process(process, 0);
        }
        else if (showcompile) { /* deferred due to dynamically loaded MPM */
            show_compile_settings();
            destroy_and_exit_process(process, 0);
        }
    }

    signal_server = APR_RETRIEVE_OPTIONAL_FN(ap_signal_server);
    if (signal_server) {
