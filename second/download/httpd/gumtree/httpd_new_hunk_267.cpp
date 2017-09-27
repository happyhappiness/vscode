    if (temp_error_log) {
        ap_replace_stderr_log(process->pool, temp_error_log);
    }
    server_conf = ap_read_config(process, ptemp, confname, &ap_conftree);
    if (ap_run_pre_config(pconf, plog, ptemp) != OK) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR, 0,
                     NULL, "Pre-configuration failed");
        destroy_and_exit_process(process, 1);
    }

    ap_process_config_tree(server_conf, ap_conftree, process->pconf, ptemp);
    ap_fixup_virtual_hosts(pconf, server_conf);
    ap_fini_vhost_config(pconf, server_conf);
