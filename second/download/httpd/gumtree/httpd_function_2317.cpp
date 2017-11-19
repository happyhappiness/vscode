static void __stdcall service_nt_main_fn(DWORD argc, LPSTR *argv)
{
    const char *ignored;

    /* args and service names live in the same pool */
    mpm_service_set_name(mpm_new_argv->pool, &ignored, argv[0]);

    memset(&globdat.ssStatus, 0, sizeof(globdat.ssStatus));
    globdat.ssStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    globdat.ssStatus.dwCurrentState = SERVICE_START_PENDING;
    globdat.ssStatus.dwCheckPoint = 1;

    if (!(globdat.hServiceStatus = RegisterServiceCtrlHandlerA(argv[0], service_nt_ctrl)))
    {
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(),
                     NULL, "Failure registering service handler");
        return;
    }

    /* Report status, no errors, and buy 3 more seconds */
    ReportStatusToSCMgr(SERVICE_START_PENDING, NO_ERROR, 30000);

    /* We need to append all the command arguments passed via StartService()
     * to our running service... which just got here via the SCM...
     * but we have no interest in argv[0] for the mpm_new_argv list.
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
    SetEvent(globdat.service_init);

    WaitForSingleObject(globdat.service_term, INFINITE);
}