{
    apr_pool_destroy(process->pool); /* and destroy all descendent pools */
    apr_terminate();
    exit(process_exit_value);
}

static process_rec *init_process(int *argc, const char * const * *argv)
{
    process_rec *process;
    apr_pool_t *cntx;
    apr_status_t stat;
    const char *failed = "apr_app_initialize()";

    stat = apr_app_initialize(argc, argv, NULL);
    if (stat == APR_SUCCESS) {
        failed = "apr_pool_create()";
        stat = apr_pool_create(&cntx, NULL);
    }

    if (stat != APR_SUCCESS) {
        /* For all intents and purposes, this is impossibly unlikely,
         * but APR doesn't exist yet, we can't use it for reporting
         * these earliest two failures;
         */
        char ctimebuff[APR_CTIME_LEN];
        apr_ctime(ctimebuff, apr_time_now());
        fprintf(stderr, "[%s] [crit] (%d) %s: %s failed "
                        "to initial context, exiting\n", 
                        ctimebuff, stat, (*argv)[0], failed);
        apr_terminate();
        exit(1);
    }

    apr_pool_tag(cntx, "process");
    ap_open_stderr_log(cntx);

    /* Now we have initialized apr and our logger, no more
     * exceptional error reporting required for the lifetime
     * of this server process.
     */

    process = apr_palloc(cntx, sizeof(process_rec));
    process->pool = cntx;

    apr_pool_create(&process->pconf, process->pool);
    apr_pool_tag(process->pconf, "pconf");
    process->argc = *argc;
    process->argv = *argv;
    process->short_name = apr_filepath_name_get((*argv)[0]);
    return process;
}

static void usage(process_rec *process)
{
    const char *bin = process->argv[0];
