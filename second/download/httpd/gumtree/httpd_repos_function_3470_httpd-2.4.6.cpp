static void service_stopped(void)
{
    /* Still have a thread & window to clean up, so signal now */
    if (globdat.service_thread)
    {
        /* Stop logging to the event log */
        mpm_nt_eventlog_stderr_flush();

        /* Cause the service_nt_main_fn to complete */
        ReleaseMutex(globdat.service_term);

        ReportStatusToSCMgr(SERVICE_STOPPED, 0, &globdat);

        WaitForSingleObject(globdat.service_thread, 5000);
        CloseHandle(globdat.service_thread);
    }
}