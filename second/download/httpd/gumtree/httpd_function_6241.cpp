int main(int argc, const char * const argv[])
{
    char c;
    int showcompile = 0, showdirectives = 0;
    const char *confname = SERVER_CONFIG_FILE;
    const char *def_server_root = HTTPD_ROOT;
    const char *temp_error_log = NULL;
    const char *error;
    process_rec *process;
    apr_pool_t *pconf;
    apr_pool_t *plog; /* Pool of log streams, reset _after_ each read of conf */
    apr_pool_t *ptemp; /* Pool for temporary config stuff, reset often */
    apr_pool_t *pcommands; /* Pool for -D, -C and -c switches */
    apr_getopt_t *opt;
    apr_status_t rv;
    module **mod;
    const char *opt_arg;
    APR_OPTIONAL_FN_TYPE(ap_signal_server) *signal_server;
    int rc = OK;

    AP_MONCONTROL(0); /* turn off profiling of startup */

    process = init_process(&argc, &argv);
    ap_pglobal = process->pool;
    pconf = process->pconf;
    ap_server_argv0 = process->short_name;
    ap_init_rng(ap_pglobal);

    /* Set up the OOM callback in the global pool, so all pools should
     * by default inherit it. */
    apr_pool_abort_set(abort_on_oom, apr_pool_parent_get(process->pool));

#if APR_CHARSET_EBCDIC
    if (ap_init_ebcdic(ap_pglobal) != APR_SUCCESS) {
        destroy_and_exit_process(process, 1);
    }
#endif

    apr_pool_create(&pcommands, ap_pglobal);
    apr_pool_tag(pcommands, "pcommands");
    ap_server_pre_read_config  = apr_array_make(pcommands, 1, sizeof(char *));
    ap_server_post_read_config = apr_array_make(pcommands, 1, sizeof(char *));
    ap_server_config_defines   = apr_array_make(pcommands, 1, sizeof(char *));

    error = ap_setup_prelinked_modules(process);
    if (error) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_EMERG, 0, NULL, APLOGNO(00012)
                     "%s: %s", ap_server_argv0, error);
        destroy_and_exit_process(process, 1);
    }

    ap_run_rewrite_args(process);

    /* Maintain AP_SERVER_BASEARGS list in http_main.h to allow the MPM
     * to safely pass on our args from its rewrite_args() handler.
     */
    apr_getopt_init(&opt, pcommands, process->argc, process->argv);

    while ((rv = apr_getopt(opt, AP_SERVER_BASEARGS, &c, &opt_arg))
            == APR_SUCCESS) {
        char **new;

        switch (c) {
        case 'c':
            new = (char **)apr_array_push(ap_server_post_read_config);
            *new = apr_pstrdup(pcommands, opt_arg);
            break;

        case 'C':
            new = (char **)apr_array_push(ap_server_pre_read_config);
            *new = apr_pstrdup(pcommands, opt_arg);
            break;

        case 'd':
            def_server_root = opt_arg;
            break;

        case 'D':
            new = (char **)apr_array_push(ap_server_config_defines);
            *new = apr_pstrdup(pcommands, opt_arg);
            /* Setting -D DUMP_VHOSTS should work like setting -S */
            if (strcmp(opt_arg, "DUMP_VHOSTS") == 0)
                ap_run_mode = AP_SQ_RM_CONFIG_DUMP;
            /* Setting -D DUMP_RUN_CFG should work like setting -S */
            else if (strcmp(opt_arg, "DUMP_RUN_CFG") == 0)
                ap_run_mode = AP_SQ_RM_CONFIG_DUMP;
            /* Setting -D DUMP_MODULES is equivalent to setting -M */
            else if (strcmp(opt_arg, "DUMP_MODULES") == 0)
                ap_run_mode = AP_SQ_RM_CONFIG_DUMP;
            break;

        case 'e':
            if (ap_parse_log_level(opt_arg, &ap_default_loglevel) != NULL)
                usage(process);
            break;

        case 'E':
            temp_error_log = apr_pstrdup(process->pool, opt_arg);
            break;

        case 'X':
            new = (char **)apr_array_push(ap_server_config_defines);
            *new = "DEBUG";
            break;

        case 'f':
            confname = opt_arg;
            break;

        case 'v':
            printf("Server version: %s\n", ap_get_server_description());
            printf("Server built:   %s\n", ap_get_server_built());
            destroy_and_exit_process(process, 0);

        case 'l':
            ap_show_modules();
            destroy_and_exit_process(process, 0);

        case 'L':
            ap_run_mode = AP_SQ_RM_CONFIG_DUMP;
            showdirectives = 1;
            break;

        case 't':
            if (ap_run_mode == AP_SQ_RM_UNKNOWN)
                ap_run_mode = AP_SQ_RM_CONFIG_TEST;
            break;

       case 'T':
           ap_document_root_check = 0;
           break;

        case 'S':
            ap_run_mode = AP_SQ_RM_CONFIG_DUMP;
            new = (char **)apr_array_push(ap_server_config_defines);
            *new = "DUMP_VHOSTS";
            new = (char **)apr_array_push(ap_server_config_defines);
            *new = "DUMP_RUN_CFG";
            break;

        case 'M':
            ap_run_mode = AP_SQ_RM_CONFIG_DUMP;
            new = (char **)apr_array_push(ap_server_config_defines);
            *new = "DUMP_MODULES";
            break;

        case 'V':
            if (strcmp(ap_show_mpm(), "")) { /* MPM built-in? */
                show_compile_settings();
                destroy_and_exit_process(process, 0);
            }
            else {
                showcompile = 1;
                ap_run_mode = AP_SQ_RM_CONFIG_DUMP;
            }
            break;

        case 'h':
        case '?':
            usage(process);
        }
    }

    if (ap_run_mode == AP_SQ_RM_UNKNOWN)
        ap_run_mode = AP_SQ_RM_NORMAL;

    /* bad cmdline option?  then we die */
    if (rv != APR_EOF || opt->ind < opt->argc) {
        usage(process);
    }

    ap_main_state = AP_SQ_MS_CREATE_PRE_CONFIG;
    apr_pool_create(&plog, ap_pglobal);
    apr_pool_tag(plog, "plog");
    apr_pool_create(&ptemp, pconf);
    apr_pool_tag(ptemp, "ptemp");

    /* Note that we preflight the config file once
     * before reading it _again_ in the main loop.
     * This allows things, log files configuration
     * for example, to settle down.
     */

    ap_server_root = def_server_root;
    if (temp_error_log) {
        ap_replace_stderr_log(process->pool, temp_error_log);
    }
    ap_server_conf = ap_read_config(process, ptemp, confname, &ap_conftree);
    if (!ap_server_conf) {
        destroy_and_exit_process(process, 1);
    }
    apr_pool_cleanup_register(pconf, &ap_server_conf, ap_pool_cleanup_set_null,
                              apr_pool_cleanup_null);
    /* sort hooks here to make sure pre_config hooks are sorted properly */
    apr_hook_sort_all();

    if (ap_run_pre_config(pconf, plog, ptemp) != OK) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR, 0,
                     NULL, APLOGNO(00013) "Pre-configuration failed");
        destroy_and_exit_process(process, 1);
    }

    rv = ap_process_config_tree(ap_server_conf, ap_conftree,
                                process->pconf, ptemp);
    if (rv == OK) {
        ap_fixup_virtual_hosts(pconf, ap_server_conf);
        ap_fini_vhost_config(pconf, ap_server_conf);
        /*
         * Sort hooks again because ap_process_config_tree may have add modules
         * and hence hooks. This happens with mod_perl and modules written in
         * perl.
         */
        apr_hook_sort_all();

        if (ap_run_check_config(pconf, plog, ptemp, ap_server_conf) != OK) {
            ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR, 0,
                         NULL, APLOGNO(00014) "Configuration check failed");
            destroy_and_exit_process(process, 1);
        }

        if (ap_run_mode != AP_SQ_RM_NORMAL) {
            if (showcompile) { /* deferred due to dynamically loaded MPM */
                show_compile_settings();
            }
            else if (showdirectives) { /* deferred in case of DSOs */
                ap_show_directives();
                destroy_and_exit_process(process, 0);
            }
            else {
                ap_run_test_config(pconf, ap_server_conf);
                if (ap_run_mode == AP_SQ_RM_CONFIG_TEST)
                    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, "Syntax OK");
            }
            destroy_and_exit_process(process, 0);
        }
    }

    /* If our config failed, deal with that here. */
    if (rv != OK) {
        destroy_and_exit_process(process, 1);
    }

    signal_server = APR_RETRIEVE_OPTIONAL_FN(ap_signal_server);
    if (signal_server) {
        int exit_status;

        if (signal_server(&exit_status, pconf) != 0) {
            destroy_and_exit_process(process, exit_status);
        }
    }

    apr_pool_clear(plog);

    if ( ap_run_open_logs(pconf, plog, ptemp, ap_server_conf) != OK) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR,
                     0, NULL, APLOGNO(00015) "Unable to open logs");
        destroy_and_exit_process(process, 1);
    }

    if ( ap_run_post_config(pconf, plog, ptemp, ap_server_conf) != OK) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR, 0,
                     NULL, APLOGNO(00016) "Configuration Failed");
        destroy_and_exit_process(process, 1);
    }

    apr_pool_destroy(ptemp);

    do {
        ap_main_state = AP_SQ_MS_DESTROY_CONFIG;
        apr_hook_deregister_all();
        apr_pool_clear(pconf);
        ap_clear_auth_internal();

        ap_main_state = AP_SQ_MS_CREATE_CONFIG;
        ap_config_generation++;
        for (mod = ap_prelinked_modules; *mod != NULL; mod++) {
            ap_register_hooks(*mod, pconf);
        }

        /* This is a hack until we finish the code so that it only reads
         * the config file once and just operates on the tree already in
         * memory.  rbb
         */
        ap_conftree = NULL;
        apr_pool_create(&ptemp, pconf);
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
        rc = ap_run_mpm(pconf, plog, ap_server_conf);

        apr_pool_lock(pconf, 0);

    } while (rc == OK);

    if (rc == DONE) {
        rc = OK;
    }
    else if (rc != OK) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, NULL, APLOGNO(02818)
                     "MPM run failed, exiting");
    }
    destroy_and_exit_process(process, rc);

    /* NOTREACHED */
    return !OK;
}