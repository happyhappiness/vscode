void
WIN32_IpAddrChangeMonitorExit()
{
    DWORD status = ERROR_SUCCESS;

    if (NotifyAddrChange_thread != INVALID_HANDLE_VALUE) {
        TerminateThread(NotifyAddrChange_thread, status);
        CloseHandle(NotifyAddrChange_thread);
    }
}