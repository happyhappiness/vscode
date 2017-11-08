apr_status_t mpm_service_started(void)
{
    set_service_description();
    if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        ReportStatusToSCMgr(SERVICE_RUNNING,    // service state
                            NO_ERROR,           // exit code
                            0);                 // wait hint
    }
    return APR_SUCCESS;
}