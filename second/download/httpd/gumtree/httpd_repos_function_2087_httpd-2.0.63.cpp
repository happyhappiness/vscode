void mpm_service_stopping(void)
{
    if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
        ReportStatusToSCMgr(SERVICE_STOP_PENDING, // service state
                            NO_ERROR,             // exit code
                            30000);               // wait hint
}