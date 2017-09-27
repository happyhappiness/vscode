        apr_pool_tag(ptemp, "ptemp");
        ap_server_root = def_server_root;
        server_conf = ap_read_config(process, ptemp, confname, &ap_conftree);
        if (!server_conf) {
            destroy_and_exit_process(process, 1);
        }

        if (ap_run_pre_config(pconf, plog, ptemp) != OK) {
            ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR,
                         0, NULL, "Pre-configuration failed");
            destroy_and_exit_process(process, 1);
        }
