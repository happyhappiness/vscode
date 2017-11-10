void netware_rewrite_args(process_rec *process)
{
    char *def_server_root;
    char optbuf[3];
    const char *opt_arg;
    apr_getopt_t *opt;
    apr_array_header_t *mpm_new_argv;


    atexit (mpm_term);
    InstallConsoleHandler();

    /* Make sure to hold the Apache screen open if exit() is called */
    hold_screen_on_exit = 1;

    /* Rewrite process->argv[];
     *
     * add default -d serverroot from the path of this executable
     *
     * The end result will look like:
     *     The -d serverroot default from the running executable
     */
    if (process->argc > 0) {
        char *s = apr_pstrdup (process->pconf, process->argv[0]);
        if (s) {
            int i, len = strlen(s);

            for (i=len; i; i--) {
                if (s[i] == '\\' || s[i] == '/') {
                    s[i] = '\0';
                    apr_filepath_merge(&def_server_root, NULL, s,
                        APR_FILEPATH_TRUENAME, process->pool);
                    break;
                }
            }
            /* Use process->pool so that the rewritten argv
            * lasts for the lifetime of the server process,
            * because pconf will be destroyed after the
            * initial pre-flight of the config parser.
            */
            mpm_new_argv = apr_array_make(process->pool, process->argc + 2,
                                  sizeof(const char *));
            *(const char **)apr_array_push(mpm_new_argv) = process->argv[0];
            *(const char **)apr_array_push(mpm_new_argv) = "-d";
            *(const char **)apr_array_push(mpm_new_argv) = def_server_root;

            optbuf[0] = '-';
            optbuf[2] = '\0';
            apr_getopt_init(&opt, process->pool, process->argc, (char**) process->argv);
            while (apr_getopt(opt, AP_SERVER_BASEARGS"n:", optbuf + 1, &opt_arg) == APR_SUCCESS) {
                switch (optbuf[1]) {
                case 'n':
                    if (opt_arg) {
                        renamescreen(opt_arg);
                    }
                    break;
                case 'E':
                    /* Don't need to hold the screen open if the output is going to a file */
                    hold_screen_on_exit = -1;
                default:
                    *(const char **)apr_array_push(mpm_new_argv) =
                        apr_pstrdup(process->pool, optbuf);

                    if (opt_arg) {
                        *(const char **)apr_array_push(mpm_new_argv) = opt_arg;
                    }
                    break;
                }
            }
            process->argc = mpm_new_argv->nelts;
            process->argv = (const char * const *) mpm_new_argv->elts;
        }
    }
}