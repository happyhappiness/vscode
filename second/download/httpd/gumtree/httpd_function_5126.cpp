ULONG APIENTRY thread_exception_handler(EXCEPTIONREPORTRECORD *pReportRec,
                                        EXCEPTIONREGISTRATIONRECORD *pRegRec,
                                        CONTEXTRECORD *pContext,
                                        PVOID p)
{
    int c;

    if (pReportRec->fHandlerFlags & EH_NESTED_CALL) {
        return XCPT_CONTINUE_SEARCH;
    }

    if (pReportRec->ExceptionNum == XCPT_ACCESS_VIOLATION ||
        pReportRec->ExceptionNum == XCPT_INTEGER_DIVIDE_BY_ZERO) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf,
                     "caught exception in worker thread, initiating child shutdown pid=%d", getpid());
        for (c=0; c<HARD_THREAD_LIMIT; c++) {
            if (ap_scoreboard_image->servers[child_slot][c].tid == _gettid()) {
                ap_scoreboard_image->servers[child_slot][c].status = SERVER_DEAD;
                break;
            }
        }

        /* Shut down process ASAP, it could be quite unhealthy & leaking resources */
        shutdown_pending = 1;
        ap_scoreboard_image->parent[child_slot].quiescing = 1;
        kill(getpid(), SIGHUP);
        DosUnwindException(UNWIND_ALL, 0, 0);
    }

    return XCPT_CONTINUE_SEARCH;
}