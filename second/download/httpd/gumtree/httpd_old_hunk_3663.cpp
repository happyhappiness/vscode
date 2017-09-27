/* service_nt_main_fn is outside of the call stack and outside of the
 * primary server thread... so now we _really_ need a placeholder!
 * The winnt_rewrite_args has created and shared mpm_new_argv with us.
 */
extern apr_array_header_t *mpm_new_argv;

/* ###: utf-ize */
static void __stdcall service_nt_main_fn(DWORD argc, LPTSTR *argv)
{
    const char *ignored;
    nt_service_ctx_t *ctx = &globdat;

    /* args and service names live in the same pool */
    mpm_service_set_name(mpm_new_argv->pool, &ignored, argv[0]);

    memset(&ctx->ssStatus, 0, sizeof(ctx->ssStatus));
    ctx->ssStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    ctx->ssStatus.dwCurrentState = SERVICE_START_PENDING;
    ctx->ssStatus.dwCheckPoint = 1;

    /* ###: utf-ize */
    if (!(ctx->hServiceStatus = RegisterServiceCtrlHandlerEx(argv[0], service_nt_ctrl, ctx)))
    {
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(),
                     NULL, APLOGNO(00365) "Failure registering service handler");
        return;
    }

    /* Report status, no errors, and buy 3 more seconds */
    ReportStatusToSCMgr(SERVICE_START_PENDING, 30000, ctx);

    /* We need to append all the command arguments passed via StartService()
     * to our running service... which just got here via the SCM...
     * but we hvae no interest in argv[0] for the mpm_new_argv list.
     */
    if (argc > 1)
    {
        char **cmb_data;

        mpm_new_argv->nalloc = mpm_new_argv->nelts + argc - 1;
        cmb_data = malloc(mpm_new_argv->nalloc * sizeof(const char *));

        /* mpm_new_argv remains first (of lower significance) */
        memcpy (cmb_data, mpm_new_argv->elts,
                mpm_new_argv->elt_size * mpm_new_argv->nelts);

        /* Service args follow from StartService() invocation */
        memcpy (cmb_data + mpm_new_argv->nelts, argv + 1,
                mpm_new_argv->elt_size * (argc - 1));

        /* The replacement arg list is complete */
        mpm_new_argv->elts = (char *)cmb_data;
        mpm_new_argv->nelts = mpm_new_argv->nalloc;
    }

    /* Let the main thread continue now... but hang on to the
     * signal_monitor event so we can take further action
     */
    SetEvent(ctx->service_init);

    WaitForSingleObject(ctx->service_term, INFINITE);
}


static DWORD WINAPI service_nt_dispatch_thread(LPVOID nada)
{
    apr_status_t rv = APR_SUCCESS;

    SERVICE_TABLE_ENTRY dispatchTable[] =
    {
        { "", service_nt_main_fn },
        { NULL, NULL }
    };

    /* ###: utf-ize */
    if (!StartServiceCtrlDispatcher(dispatchTable))
    {
        /* This is a genuine failure of the SCM. */
        rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, APLOGNO(00366)
                     "Error starting service control dispatcher");
    }

    return (rv);
}


/* The service configuration's is stored under the following trees:
 *
