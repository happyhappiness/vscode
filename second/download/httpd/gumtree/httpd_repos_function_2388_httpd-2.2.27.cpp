static int ReportStatusToSCMgr(int currentState, int exitCode, int waitHint)
{
    static int checkPoint = 1;
    int rv = APR_SUCCESS;

    if (globdat.hServiceStatus)
    {
        if (currentState == SERVICE_RUNNING) {
            globdat.ssStatus.dwWaitHint = 0;
            globdat.ssStatus.dwCheckPoint = 0;
            globdat.ssStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
        }
        else if (currentState == SERVICE_STOPPED) {
            globdat.ssStatus.dwWaitHint = 0;
            globdat.ssStatus.dwCheckPoint = 0;
            if (!exitCode && globdat.ssStatus.dwCurrentState
                                           != SERVICE_STOP_PENDING) {
                /* An unexpected exit?  Better to error! */
                exitCode = 1;
            }
            if (exitCode) {
                globdat.ssStatus.dwWin32ExitCode =ERROR_SERVICE_SPECIFIC_ERROR;
                globdat.ssStatus.dwServiceSpecificExitCode = exitCode;
            }
        }
        else {
            globdat.ssStatus.dwCheckPoint = ++checkPoint;
            globdat.ssStatus.dwControlsAccepted = 0;
            if(waitHint)
                globdat.ssStatus.dwWaitHint = waitHint;
        }

        globdat.ssStatus.dwCurrentState = currentState;

        rv = SetServiceStatus(globdat.hServiceStatus, &globdat.ssStatus);
    }
    return(rv);
}