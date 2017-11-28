void
WIN32_Exit()
{
    Win32SockCleanup();
#if USE_WIN32_SERVICE

    if (WIN32_run_mode == _WIN_SQUID_RUN_MODE_SERVICE) {
        if (!Squid_Aborting) {
            svcStatus.dwCurrentState = SERVICE_STOPPED;
            SetServiceStatus(svcHandle, &svcStatus);
        }
    }

#endif
    if (dbg_mutex)
        DeleteCriticalSection(dbg_mutex);

    WIN32_ExceptionHandlerCleanup();
    WIN32_IpAddrChangeMonitorExit();
    _exit(0);
}