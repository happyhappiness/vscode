void
WIN32_Abort(int sig)
{
#if USE_WIN32_SERVICE
    svcStatus.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
    svcStatus.dwServiceSpecificExitCode = 1;
#endif

    Squid_Aborting = 1;
    WIN32_Exit();
}