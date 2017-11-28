void
WIN32_Abort(int sig)
{
    svcStatus.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
    svcStatus.dwServiceSpecificExitCode = 1;
    Squid_Aborting = 1;
    WIN32_Exit();
}