void service_stopped(void)
{
    /* Still have a thread & window to clean up, so signal now */
    if (globdat.service_thread)
    {
        if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
        {
            /* Stop logging to the event log */
            mpm_nt_eventlog_stderr_flush();

            /* Cause the service_nt_main_fn to complete */
            ReleaseMutex(globdat.service_term);

            ReportStatusToSCMgr(SERVICE_STOPPED, // service state
                                NO_ERROR,        // exit code
                                0);              // wait hint
        }
        else /* osver.dwPlatformId != VER_PLATFORM_WIN32_NT */
        {
            RegisterServiceProcess(0, 0);
            PostThreadMessage(globdat.service_thread_id, WM_CLOSE, 0, 0);
        }

        WaitForSingleObject(globdat.service_thread, 5000);
        CloseHandle(globdat.service_thread);
    }
}