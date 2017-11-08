apr_status_t mpm_service_started(void)
{
    set_service_description();
    ReportStatusToSCMgr(SERVICE_RUNNING, 0, &globdat);
    return APR_SUCCESS;
}