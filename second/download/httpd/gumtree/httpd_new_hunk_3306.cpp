        apr_pool_tag(ptemp, "ptemp");
        ap_server_root = def_server_root;
        ap_server_conf = ap_read_config(process, ptemp, confname, &ap_conftree);
        if (!ap_server_conf) {
            destroy_and_exit_process(process, 1);
        }
        apr_pool_cleanup_register(pconf, &ap_server_conf,
                                  ap_pool_cleanup_set_null, apr_pool_cleanup_null);
        /* sort hooks here to make sure pre_config hooks are sorted properly */
        apr_hook_sort_all();

        if (ap_run_pre_config(pconf, plog, ptemp) != OK) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, NULL,
                         APLOGNO(00017) "Pre-configuration failed, exiting");
            destroy_and_exit_process(process, 1);
        }

        if (ap_process_config_tree(ap_server_conf, ap_conftree, process->pconf,
                                   ptemp) != OK) {
            destroy_and_exit_process(process, 1);
        }
        ap_fixup_virtual_hosts(pconf, ap_server_conf);
        ap_fini_vhost_config(pconf, ap_server_conf);
        /*
         * Sort hooks again because ap_process_config_tree may have add modules
         * and hence hooks. This happens with mod_perl and modules written in
         * perl.
         */
        apr_hook_sort_all();

        if (ap_run_check_config(pconf, plog, ptemp, ap_server_conf) != OK) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, NULL,
                         APLOGNO(00018) "Configuration check failed, exiting");
            destroy_and_exit_process(process, 1);
        }

        apr_pool_clear(plog);
        if (ap_run_open_logs(pconf, plog, ptemp, ap_server_conf) != OK) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, NULL,
                         APLOGNO(00019) "Unable to open logs, exiting");
            destroy_and_exit_process(process, 1);
        }

        if (ap_run_post_config(pconf, plog, ptemp, ap_server_conf) != OK) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, NULL,
                         APLOGNO(00020) "Configuration Failed, exiting");
            destroy_and_exit_process(process, 1);
        }

        apr_pool_destroy(ptemp);
        apr_pool_lock(pconf, 1);

        ap_run_optional_fn_retrieve();

        ap_main_state = AP_SQ_MS_RUN_MPM;
        if (ap_run_mpm(pconf, plog, ap_server_conf) != OK)
            break;

        apr_pool_lock(pconf, 0);
    }

