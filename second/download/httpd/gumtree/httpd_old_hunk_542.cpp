{
    apr_pool_destroy(process->pool); /* and destroy all descendent pools */
    apr_terminate();
    exit(process_exit_value);
}

static process_rec *create_process(int argc, const char * const *argv)
{
    process_rec *process;
    apr_pool_t *cntx;
    apr_status_t stat;

    stat = apr_pool_create(&cntx, NULL);
    if (stat != APR_SUCCESS) {
        /* XXX From the time that we took away the NULL pool->malloc mapping
         *     we have been unable to log here without segfaulting.
         */
        ap_log_error(APLOG_MARK, APLOG_ERR, stat, NULL,
                     "apr_pool_create() failed to create "
                     "initial context");
        apr_terminate();
        exit(1);
    }

    apr_pool_tag(cntx, "process");
    ap_open_stderr_log(cntx);

    process = apr_palloc(cntx, sizeof(process_rec));
    process->pool = cntx;

    apr_pool_create(&process->pconf, process->pool);
    apr_pool_tag(process->pconf, "pconf");
    process->argc = argc;
    process->argv = argv;
    process->short_name = apr_filename_of_pathname(argv[0]);
    return process;
}

static void usage(process_rec *process)
{
    const char *bin = process->argv[0];
