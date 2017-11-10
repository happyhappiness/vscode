static DWORD WINAPI service_nt_ctrl(DWORD dwCtrlCode, DWORD dwEventType,
                                   LPVOID lpEventData, LPVOID lpContext)
{
    nt_service_ctx_t *ctx = lpContext;

    /* SHUTDOWN is offered before STOP, accept the first opportunity */
    if ((dwCtrlCode == SERVICE_CONTROL_STOP)
         || (dwCtrlCode == SERVICE_CONTROL_SHUTDOWN))
    {
        ap_signal_parent(SIGNAL_PARENT_SHUTDOWN);
        ReportStatusToSCMgr(SERVICE_STOP_PENDING, 30000, ctx);
        return (NO_ERROR);
    }
    if (dwCtrlCode == SERVICE_APACHE_RESTART)
    {
        ap_signal_parent(SIGNAL_PARENT_RESTART);
        ReportStatusToSCMgr(SERVICE_START_PENDING, 30000, ctx);
        return (NO_ERROR);
    }
    if (dwCtrlCode == SERVICE_CONTROL_INTERROGATE) {
        ReportStatusToSCMgr(globdat.ssStatus.dwCurrentState, 0, ctx);
        return (NO_ERROR);
    }

    return (ERROR_CALL_NOT_IMPLEMENTED);
}