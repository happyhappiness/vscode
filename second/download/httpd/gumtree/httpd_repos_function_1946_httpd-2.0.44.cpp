int main(int argc, const char * const argv[])
{
    char c;
    int configtestonly = 0;
    const char *confname = SERVER_CONFIG_FILE;
    const char *def_server_root = HTTPD_ROOT;
    const char *temp_error_log = NULL;
    process_rec *process;
    server_rec *server_conf;
    apr_pool_t *pglobal;
    apr_pool_t *pconf;
    apr_pool_t *plog; /* Pool of log streams, reset _after_ each read of conf */
    apr_pool_t *ptemp; /* Pool for temporary config stuff, reset often */
    apr_pool_t *pcommands; /* Pool for -D, -C and -c switches */
    apr_getopt_t *opt;
    apr_status_t rv;
    module **mod;
    const char *optarg;
    APR_OPTIONAL_FN_TYPE(ap_signal_server) *signal_server;

    AP_MONCONTROL(0); /* turn off profiling of startup */

    apr_app_initialize(&argc, &argv, NULL);

    process = create_process(argc, argv);
    pglobal = process->pool;
    pconf = process->pconf;
    ap_server_argv0 = process->short_name;

#if APR_CHARSET_EBCDIC
    if (ap_init_ebcdic(pglobal) != APR_SUCCESS) {
        destroy_and_exit_process(process, 1);
    }
#endif

    ap_setup_prelinked_modules(process);

    apr_pool_create(&pcommands, pglobal);
    apr_pool_tag(pcommands, "pcommands");
    ap_server_pre_read_config  = apr_array_make(pcommands, 1, sizeof(char *));
    ap_server_post_read_config = apr_array_make(pcommands, 1, sizeof(char *));
    ap_server_config_defines   = apr_array_make(pcommands, 1, sizeof(char *));

    ap_run_rewrite_args(process);

    /* Maintain AP_SERVER_BASEARGS list in http_main.h to allow the MPM
     * to safely pass on our args from its rewrite_args() handler.
     */
    apr_getopt_init(&opt, pcommands, process->argc, process->argv);

    while ((rv = apr_getopt(opt, AP_SERVER_BASEARGS, &c, &optarg))
            == APR_SUCCESS) {
        char **new;

        switch (c) {
        case 'c':
            new = (char **)apr_array_push(ap_server_post_read_config);
            *new = apr_pstrdup(pcommands, optarg);
            break;

        case 'C':
            new = (char **)apr_array_push(ap_server_pre_read_config);
            *new = apr_pstrdup(pcommands, optarg);
            break;

        case 'd':
            def_server_root = optarg;
            break;

        case 'D':
            new = (char **)apr_array_push(ap_server_config_defines);
            *new = apr_pstrdup(pcommands, optarg);
            break;

        case 'e':
            if (strcasecmp(optarg, "emerg") == 0) {
                ap_default_loglevel = APLOG_EMERG;
            }
            else if (strcasecmp(optarg, "alert") == 0) {
                ap_default_loglevel = APLOG_ALERT;
            }
            else if (strcasecmp(optarg, "crit") == 0) {
                ap_default_loglevel = APLOG_CRIT;
            }
            else if (strncasecmp(optarg, "err", 3) == 0) {
                ap_default_loglevel = APLOG_ERR;
            }
            else if (strncasecmp(optarg, "warn", 4) == 0) {
                ap_default_loglevel = APLOG_WARNING;
            }
            else if (strcasecmp(optarg, "notice") == 0) {
                ap_default_loglevel = APLOG_NOTICE;
            }
            else if (strcasecmp(optarg, "info") == 0) {
                ap_default_loglevel = APLOG_INFO;
            }
            else if (strcasecmp(optarg, "debug") == 0) {
                ap_default_loglevel = APLOG_DEBUG;
            }
            else {
                usage(process);
            }
            break;

        case 'E':
            temp_error_log = apr_pstrdup(process->pool, optarg);
            break;

        case 'X':
            new = (char **)apr_array_push(ap_server_config_defines);
            *new = "DEBUG";
            break;

        case 'f':
            confname = optarg;
            break;

        case 'v':
            printf("Server version: %s\n", ap_get_server_version());
            printf("Server built:   %s\n", ap_get_server_built());
            destroy_and_exit_process(process, 0);

        case 'V':
            show_compile_settings();
            destroy_and_exit_process(process, 0);

        case 'l':
            ap_show_modules();
            destroy_and_exit_process(process, 0);

        case 'L':
            ap_show_directives();
            destroy_and_exit_process(process, 0);

        case 't':
            configtestonly = 1;
            break;
        
        case 'S':
            configtestonly = 1;
            new = (char **)apr_array_push(ap_server_config_defines);
            *new = "DUMP_VHOSTS";
            break;
            
        case 'h':
        case '?':
            usage(process);
        }
    }

    /* bad cmdline option?  then we die */
    if (rv != APR_EOF || opt->ind < opt->argc) {
        usage(process);
    }

    apr_pool_create(&plog, pglobal);
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
    server_conf = ap_read_config(process, ptemp, confname, &ap_conftree);
    if (ap_run_pre_config(pconf, plog, ptemp) != OK) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR, 0,
                     NULL, "Pre-configuration failed\n");
        destroy_and_exit_process(process, 1);
    }

    ap_process_config_tree(server_conf, ap_conftree, process->pconf, ptemp);
    ap_fixup_virtual_hosts(pconf, server_conf);
    ap_fini_vhost_config(pconf, server_conf);
    apr_hook_sort_all();
    if (configtestonly) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, "Syntax OK");
        destroy_and_exit_process(process, 0);
    }

    signal_server = APR_RETRIEVE_OPTIONAL_FN(ap_signal_server);
    if (signal_server) {
        int exit_status;

        if (signal_server(&exit_status, pconf) != 0) {
            destroy_and_exit_process(process, exit_status);
        }
    }

    apr_pool_clear(plog);

    if ( ap_run_open_logs(pconf, plog, ptemp, server_conf) != OK) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR,
                     0, NULL, "Unable to open logs\n");
        destroy_and_exit_process(process, 1);
    }

    if ( ap_run_post_config(pconf, plog, ptemp, server_conf) != OK) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR, 0,
                     NULL, "Configuration Failed\n");
        destroy_and_exit_process(process, 1);
    }

    apr_pool_destroy(ptemp);

    for (;;) {
        apr_hook_deregister_all();
        apr_pool_clear(pconf);

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
        server_conf = ap_read_config(process, ptemp, confname, &ap_conftree);
        if (ap_run_pre_config(pconf, plog, ptemp) != OK) {
            ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR,
                         0, NULL, "Pre-configuration failed\n");
            destroy_and_exit_process(process, 1);
        }

        ap_process_config_tree(server_conf, ap_conftree, process->pconf, ptemp);
        ap_fixup_virtual_hosts(pconf, server_conf);
        ap_fini_vhost_config(pconf, server_conf);
        apr_hook_sort_all();
        apr_pool_clear(plog);
        if (ap_run_open_logs(pconf, plog, ptemp, server_conf) != OK) {
            ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR,
                         0, NULL, "Unable to open logs\n");
            destroy_and_exit_process(process, 1);
        }

        if (ap_run_post_config(pconf, plog, ptemp, server_conf) != OK) {
            ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR,
                         0, NULL, "Configuration Failed\n");
            destroy_and_exit_process(process, 1);
        }

        apr_pool_destroy(ptemp);
        apr_pool_lock(pconf, 1);

        ap_run_optional_fn_retrieve();

        if (ap_mpm_run(pconf, plog, server_conf))
            break;

        apr_pool_lock(pconf, 0);
    }

    apr_pool_lock(pconf, 0);
    destroy_and_exit_process(process, 0);

    return 0; /* Termination 'ok' */
}