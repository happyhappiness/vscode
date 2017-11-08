static void spawn_server(apr_pool_t *p, apr_proc_t *out_proc)
{
    apr_proc_t proc = {0};
    apr_procattr_t *procattr;
    apr_status_t rv;
    const char *args[3];

    rv = apr_procattr_create(&procattr, p);
    if (rv != APR_SUCCESS) {
        aprerr("apr_procattr_create()", rv);
    }

    rv = apr_procattr_io_set(procattr, APR_CHILD_BLOCK, APR_CHILD_BLOCK,
                             APR_CHILD_BLOCK);
    if (rv != APR_SUCCESS) {
        aprerr("apr_procattr_io_set()", rv);
    }

    rv = apr_procattr_cmdtype_set(procattr, APR_PROGRAM_ENV);
    if (rv != APR_SUCCESS) {
        aprerr("apr_procattr_cmdtype_set()", rv);
    }

    rv = apr_procattr_error_check_set(procattr, 1);
    if (rv != APR_SUCCESS) {
        aprerr("apr_procattr_error_check_set()", rv);
    }

    args[0] = "sendfile" EXTENSION;
    args[1] = "server";
    args[2] = NULL;
    rv = apr_proc_create(&proc, TESTBINPATH "sendfile" EXTENSION, args, NULL, procattr, p);
    if (rv != APR_SUCCESS) {
        aprerr("apr_proc_create()", rv);
    }

    *out_proc = proc;
}