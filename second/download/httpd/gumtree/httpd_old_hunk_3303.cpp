    destroy_and_exit_process(process, 1);
}

int main(int argc, const char * const argv[])
{
    char c;
    int configtestonly = 0, showcompile = 0;
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
    const char *optarg;
    APR_OPTIONAL_FN_TYPE(ap_signal_server) *signal_server;

    AP_MONCONTROL(0); /* turn off profiling of startup */

    process = init_process(&argc, &argv);
    ap_pglobal = process->pool;
    pconf = process->pconf;
    ap_server_argv0 = process->short_name;

    /* Set up the OOM callback in the global pool, so all pools should
     * by default inherit it. */
    apr_pool_abort_set(abort_on_oom, apr_pool_parent_get(process->pool));

#if APR_CHARSET_EBCDIC
    if (ap_init_ebcdic(ap_pglobal) != APR_SUCCESS) {
        destroy_and_exit_process(process, 1);
    }
#endif
    if (ap_expr_init(ap_pglobal) != APR_SUCCESS) {
        destroy_and_exit_process(process, 1);
    }

    apr_pool_create(&pcommands, ap_pglobal);
    apr_pool_tag(pcommands, "pcommands");
    ap_server_pre_read_config  = apr_array_make(pcommands, 1, sizeof(char *));
    ap_server_post_read_config = apr_array_make(pcommands, 1, sizeof(char *));
    ap_server_config_defines   = apr_array_make(pcommands, 1, sizeof(char *));

    error = ap_setup_prelinked_modules(process);
    if (error) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_EMERG, 0, NULL, "%s: %s",
                     ap_server_argv0, error);
        destroy_and_exit_process(process, 1);
    }

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
            /* Setting -D DUMP_VHOSTS is equivalent to setting -S */
            if (strcmp(optarg, "DUMP_VHOSTS") == 0)
                configtestonly = 1;
            /* Setting -D DUMP_MODULES is equivalent to setting -M */
            if (strcmp(optarg, "DUMP_MODULES") == 0)
                configtestonly = 1;
            break;

        case 'e':
            if (ap_parse_log_level(optarg, &ap_default_loglevel) != NULL)
                usage(process);
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
            printf("Server version: %s\n", ap_get_server_description());
            printf("Server built:   %s\n", ap_get_server_built());
            destroy_and_exit_process(process, 0);

        case 'V':
            if (strcmp(ap_show_mpm(), "")) { /* MPM built-in? */
                show_compile_settings();
                destroy_and_exit_process(process, 0);
            }
            else {
                showcompile = 1;
            }
            break;

        case 'l':
            ap_show_modules();
            destroy_and_exit_process(process, 0);

        case 'L':
            ap_show_directives();
            destroy_and_exit_process(process, 0);

        case 't':
            configtestonly = 1;
            break;

       case 'T':
           ap_document_root_check = 0;
           break;

        case 'S':
            configtestonly = 1;
            new = (char **)apr_array_push(ap_server_config_defines);
            *new = "DUMP_VHOSTS";
            break;

        case 'M':
            configtestonly = 1;
            new = (char **)apr_array_push(ap_server_config_defines);
            *new = "DUMP_MODULES";
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

    apr_pool_create(&plog, ap_pglobal);
    apr_pool_tag(plog, "plog");
    apr_pool_create(&ptemp, pconf);
    apr_pool_tag(ptemp, "ptemp");

    /* Note that we preflight the config file once
