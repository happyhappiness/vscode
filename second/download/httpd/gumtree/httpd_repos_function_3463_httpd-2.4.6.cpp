static int ReportStatusToSCMgr(int currentState, int waitHint,
                               nt_service_ctx_t *ctx)
{
    int rv = APR_SUCCESS;

    if (ctx->hServiceStatus)
    {
        if (currentState == SERVICE_RUNNING) {
            ctx->ssStatus.dwWaitHint = 0;
            ctx->ssStatus.dwCheckPoint = 0;
            ctx->ssStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP
                                             | SERVICE_ACCEPT_SHUTDOWN;
        }
        else if (currentState == SERVICE_STOPPED) {
            ctx->ssStatus.dwWaitHint = 0;
            ctx->ssStatus.dwCheckPoint = 0;
            /* An unexpected exit?  Better to error! */
            if (ctx->ssStatus.dwCurrentState != SERVICE_STOP_PENDING
                    && !ctx->ssStatus.dwServiceSpecificExitCode)
                ctx->ssStatus.dwServiceSpecificExitCode = 1;
            if (ctx->ssStatus.dwServiceSpecificExitCode)
                ctx->ssStatus.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
        }
        else {
            ++ctx->ssStatus.dwCheckPoint;
            ctx->ssStatus.dwControlsAccepted = 0;
            if(waitHint)
                ctx->ssStatus.dwWaitHint = waitHint;
        }

        ctx->ssStatus.dwCurrentState = currentState;

        rv = SetServiceStatus(ctx->hServiceStatus, &ctx->ssStatus);
    }
    return(rv);
}