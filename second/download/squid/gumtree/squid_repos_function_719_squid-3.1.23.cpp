void
WIN32_svcstatusupdate(DWORD svcstate, DWORD WaitHint)
{
    if (WIN32_run_mode == _WIN_SQUID_RUN_MODE_SERVICE) {
        svcStatus.dwCheckPoint++;
        svcStatus.dwWaitHint = WaitHint;
        svcStatus.dwCurrentState = svcstate;
        SetServiceStatus(svcHandle, &svcStatus);
    }
}