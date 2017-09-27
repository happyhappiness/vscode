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

