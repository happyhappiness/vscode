static void __stdcall service_nt_main_fn_w(DWORD argc, LPWSTR *argv)
{
    const char *ignored;
    nt_service_ctx_t *ctx = &globdat;
    char *service_name;
    apr_size_t wslen = wcslen(argv[0]) + 1;
    apr_size_t slen = wslen * 3 - 2;

    service_name = malloc(slen);
    (void)apr_conv_ucs2_to_utf8(argv[0], &wslen, service_name, &slen);

    /* args and service names live in the same pool */
    mpm_service_set_name(mpm_new_argv->pool, &ignored, service_name);

    memset(&ctx->ssStatus, 0, sizeof(ctx->ssStatus));
    ctx->ssStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    ctx->ssStatus.dwCurrentState = SERVICE_START_PENDING;
    ctx->ssStatus.dwCheckPoint = 1;
    if (!(ctx->hServiceStatus = 
              RegisterServiceCtrlHandlerExW(argv[0], service_nt_ctrl, ctx)))
    {
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, 
                     apr_get_os_error(), NULL, 
                     APLOGNO(00365) "Failure registering service handler");
        return;
    }

    /* Report status, no errors, and buy 3 more seconds */
    ReportStatusToSCMgr(SERVICE_START_PENDING, 30000, ctx);

    /* We need to append all the command arguments passed via StartService()
     * to our running service... which just got here via the SCM...
     * but we have no interest in argv[0] for the mpm_new_argv list.
     */
    if (argc > 1)
    {
        char **cmb_data, **cmb;
        DWORD i;

        mpm_new_argv->nalloc = mpm_new_argv->nelts + argc - 1;
        cmb_data = malloc(mpm_new_argv->nalloc * sizeof(const char *));

        /* mpm_new_argv remains first (of lower significance) */
        memcpy (cmb_data, mpm_new_argv->elts,
                mpm_new_argv->elt_size * mpm_new_argv->nelts);

        /* Service args follow from StartService() invocation */
        memcpy (cmb_data + mpm_new_argv->nelts, argv + 1,
                mpm_new_argv->elt_size * (argc - 1));

        cmb = cmb_data + mpm_new_argv->nelts;

        for (i = 1; i < argc; ++i)
        {
            wslen = wcslen(argv[i]) + 1;
            slen = wslen * 3 - 2;
            service_name = malloc(slen);
            (void)apr_conv_ucs2_to_utf8(argv[i], &wslen, *(cmb++), &slen);
        }

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