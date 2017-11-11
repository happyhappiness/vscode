static VOID WINAPI service_nt_ctrl(DWORD dwCtrlCode)
{
    if (dwCtrlCode == SERVICE_CONTROL_STOP)
    {
        ap_signal_parent(SIGNAL_PARENT_SHUTDOWN);
        ReportStatusToSCMgr(SERVICE_STOP_PENDING, NO_ERROR, 30000);
        return;
    }
    if (dwCtrlCode == SERVICE_APACHE_RESTART)
    {
        ap_signal_parent(SIGNAL_PARENT_RESTART);
        ReportStatusToSCMgr(SERVICE_START_PENDING, NO_ERROR, 30000);
        return;
    }
    
    ReportStatusToSCMgr(globdat.ssStatus.dwCurrentState, NO_ERROR, 0);            
}