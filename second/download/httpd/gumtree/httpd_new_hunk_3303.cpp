    destroy_and_exit_process(process, 1);
}

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
