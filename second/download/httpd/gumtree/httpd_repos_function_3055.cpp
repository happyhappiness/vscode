void mpm_service_stopping(void)
{
    ReportStatusToSCMgr(SERVICE_STOP_PENDING, 30000, &globdat);
}