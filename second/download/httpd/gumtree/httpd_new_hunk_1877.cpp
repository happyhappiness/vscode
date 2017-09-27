
    /* We should never get here, but this is (mostly) harmless */
    return FALSE;
}


void mpm_start_child_console_handler(void)
{
    FreeConsole();
}


/**********************************
  WinNT service control management
 **********************************/

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

/* Note this works on Win2000 and later due to ChangeServiceConfig2
 * Continue to test it's existence, but at least drop the feature
 * of revising service description tags prior to Win2000.
 */

/* borrowed from mpm_winnt.c */
extern apr_pool_t *pconf;

static void set_service_description(void)
{
    const char *full_description;
    SC_HANDLE schSCManager;
    BOOL ret = 0;

    /* Nothing to do if we are a console
     */
    if (!mpm_service_name)
        return;

    /* Time to fix up the description, upon each successful restart
     */
    full_description = ap_get_server_description();

    if ((ChangeServiceConfig2) &&
        (schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT)))
    {
        SC_HANDLE schService = OpenService(schSCManager, mpm_service_name,
                                           SERVICE_CHANGE_CONFIG);
        if (schService) {
            /* Cast is necessary, ChangeServiceConfig2 handles multiple
             * object types, some volatile, some not.
             */
            /* ###: utf-ize */
            ChangeServiceConfig2(schService,
                                 1 /* SERVICE_CONFIG_DESCRIPTION */,
                                 (LPVOID) &full_description);
            CloseServiceHandle(schService);
        }
        CloseServiceHandle(schSCManager);
    }
}

/* handle the SCM's ControlService() callbacks to our service */

static DWORD WINAPI service_nt_ctrl(DWORD dwCtrlCode, DWORD dwEventType, 
                                   LPVOID lpEventData, LPVOID lpContext)
{
    nt_service_ctx_t *ctx = lpContext;

    /* SHUTDOWN is offered before STOP, accept the first opportunity */
    if ((dwCtrlCode == SERVICE_CONTROL_STOP)
         || (dwCtrlCode == SERVICE_CONTROL_SHUTDOWN))
    {
        ap_signal_parent(SIGNAL_PARENT_SHUTDOWN);
        ReportStatusToSCMgr(SERVICE_STOP_PENDING, 30000, ctx);
        return (NO_ERROR);
    }
    if (dwCtrlCode == SERVICE_APACHE_RESTART)
    {
        ap_signal_parent(SIGNAL_PARENT_RESTART);
        ReportStatusToSCMgr(SERVICE_START_PENDING, 30000, ctx);
        return (NO_ERROR);
    }
    if (dwCtrlCode == SERVICE_CONTROL_INTERROGATE) {
        ReportStatusToSCMgr(globdat.ssStatus.dwCurrentState, 0, ctx);
        return (NO_ERROR);
    }

    return (ERROR_CALL_NOT_IMPLEMENTED);
}


/* service_nt_main_fn is outside of the call stack and outside of the
 * primary server thread... so now we _really_ need a placeholder!
 * The winnt_rewrite_args has created and shared mpm_new_argv with us.
 */
extern apr_array_header_t *mpm_new_argv;

/* ###: utf-ize */
static void __stdcall service_nt_main_fn(DWORD argc, LPTSTR *argv)
{
    const char *ignored;
    nt_service_ctx_t *ctx = &globdat;

    /* args and service names live in the same pool */
    mpm_service_set_name(mpm_new_argv->pool, &ignored, argv[0]);

    memset(&ctx->ssStatus, 0, sizeof(ctx->ssStatus));
    ctx->ssStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    ctx->ssStatus.dwCurrentState = SERVICE_START_PENDING;
    ctx->ssStatus.dwCheckPoint = 1;

    /* ###: utf-ize */
    if (!(ctx->hServiceStatus = RegisterServiceCtrlHandlerEx(argv[0], service_nt_ctrl, ctx)))
    {
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(),
                     NULL, "Failure registering service handler");
        return;
    }

    /* Report status, no errors, and buy 3 more seconds */
    ReportStatusToSCMgr(SERVICE_START_PENDING, 30000, ctx);

    /* We need to append all the command arguments passed via StartService()
     * to our running service... which just got here via the SCM...
     * but we hvae no interest in argv[0] for the mpm_new_argv list.
     */
    if (argc > 1)
    {
        char **cmb_data;

        mpm_new_argv->nalloc = mpm_new_argv->nelts + argc - 1;
