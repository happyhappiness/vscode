void
WIN32_Exit()
{
#ifdef _SQUID_MSWIN_
    Win32SockCleanup();
#endif
#if USE_WIN32_SERVICE

    if (WIN32_run_mode == _WIN_SQUID_RUN_MODE_SERVICE) {
        if (!Squid_Aborting) {
            svcStatus.dwCurrentState = SERVICE_STOPPED;
            SetServiceStatus(svcHandle, &svcStatus);
        }
    }

#endif
#ifdef _SQUID_MSWIN_
    if (dbg_mutex)
        DeleteCriticalSection(dbg_mutex);

    WIN32_ExceptionHandlerCleanup();
    WIN32_IpAddrChangeMonitorExit();

#endif

    _exit(0);
}