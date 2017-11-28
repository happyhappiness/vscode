DWORD
WIN32_IpAddrChangeMonitorInit()
{
    DWORD status = ERROR_SUCCESS;
    DWORD threadID = 0, ThrdParam = 0;

    if ((WIN32_run_mode == _WIN_SQUID_RUN_MODE_SERVICE) && (Config.onoff.WIN32_IpAddrChangeMonitor)) {
        NotifyAddrChange_thread = CreateThread(NULL, 0, WIN32_IpAddrChangeMonitor,
                                               &ThrdParam, 0, &threadID);
        if (NotifyAddrChange_thread == NULL) {
            status = GetLastError();
            NotifyAddrChange_thread = INVALID_HANDLE_VALUE;
            debugs(1, DBG_IMPORTANT, "Failed to start IP monitor thread.");
        } else
            debugs(1, 2, "Starting IP monitor thread [" << threadID << "] ...");
    }
    return status;
}