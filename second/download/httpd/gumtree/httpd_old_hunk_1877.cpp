
    /* We should never get here, but this is (mostly) harmless */
    return FALSE;
}


static void stop_child_console_handler(void)
{
    SetConsoleCtrlHandler(child_control_handler, FALSE);
}


void mpm_start_child_console_handler(void)
{
    if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT) {
        FreeConsole();
    }
    else
    {
        SetConsoleCtrlHandler(child_control_handler, TRUE);
        atexit(stop_child_console_handler);
    }
}


/**********************************
  WinNT service control management
 **********************************/

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

/* Set the service description regardless of platform.
 * We revert to set_service_description on NT/9x, the
 * very long way so any Apache management program can grab the
 * description.  This would be bad on Win2000, since it wouldn't
 * notify the service control manager of the name change.
 */

/* borrowed from mpm_winnt.c */
extern apr_pool_t *pconf;

/* Windows 2000 alone supports ChangeServiceConfig2 in order to
 * register our server_version string... so we need some fixups
 * to avoid binding to that function if we are on WinNT/9x.
 */
static void set_service_description(void)
{
    const char *full_description;
    SC_HANDLE schSCManager;

    /* Nothing to do if we are a console
     */
    if (!mpm_service_name)
        return;

    /* Time to fix up the description, upon each successful restart
     */
    full_description = ap_get_server_description();

    if ((osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
          && (osver.dwMajorVersion > 4)
          && (ChangeServiceConfig2)
          && (schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT)))
    {
        SC_HANDLE schService;

#if APR_HAS_UNICODE_FS
        IF_WIN_OS_IS_UNICODE
        {
            schService = OpenServiceW(schSCManager, mpm_service_name_w,
                                      SERVICE_CHANGE_CONFIG);
        }
#endif /* APR_HAS_UNICODE_FS */
#if APR_HAS_ANSI_FS
        ELSE_WIN_OS_IS_ANSI
        {
            schService = OpenService(schSCManager, mpm_service_name,
                                     SERVICE_CHANGE_CONFIG);
        }
#endif
        if (schService) {
            /* Cast is necessary, ChangeServiceConfig2 handles multiple
             * object types, some volatile, some not.
             */
#if APR_HAS_UNICODE_FS
            IF_WIN_OS_IS_UNICODE
            {
                apr_size_t slen = strlen(full_description) + 1;
                apr_size_t wslen = slen;
                apr_wchar_t *full_description_w = apr_palloc(pconf, wslen * sizeof(apr_wchar_t));
                apr_status_t rv = apr_conv_utf8_to_ucs2(full_description, &slen,
                                                        full_description_w, &wslen);
                if ((rv != APR_SUCCESS) || slen
                        || ChangeServiceConfig2W(schService,
                                                 1 /* SERVICE_CONFIG_DESCRIPTION */,
                                                 (LPVOID) &full_description_w))
                    full_description = NULL;
            }
#endif /* APR_HAS_UNICODE_FS */
#if APR_HAS_ANSI_FS
            ELSE_WIN_OS_IS_ANSI
            {
                if (ChangeServiceConfig2(schService,
                                         1 /* SERVICE_CONFIG_DESCRIPTION */,
                                         (LPVOID) &full_description))
                    full_description = NULL;
            }
#endif
            CloseServiceHandle(schService);
        }
        CloseServiceHandle(schSCManager);
    }

    if (full_description)
    {
        char szPath[MAX_PATH];
        ap_regkey_t *svckey;
        apr_status_t rv;

        /* Find the Service key that Monitor Applications iterate */
        apr_snprintf(szPath, sizeof(szPath),
                     "SYSTEM\\CurrentControlSet\\Services\\%s",
                     mpm_service_name);
        rv = ap_regkey_open(&svckey, AP_REGKEY_LOCAL_MACHINE, szPath,
                            APR_READ | APR_WRITE, pconf);
        if (rv != APR_SUCCESS) {
            return;
        }
        /* Attempt to set the Description value for our service */
        ap_regkey_value_set(svckey, "Description", full_description, 0, pconf);
        ap_regkey_close(svckey);
    }
}

/* handle the SCM's ControlService() callbacks to our service */

static VOID WINAPI service_nt_ctrl(DWORD dwCtrlCode)
{
    if (dwCtrlCode == SERVICE_CONTROL_STOP)
    {
        ap_signal_parent(SIGNAL_PARENT_SHUTDOWN);
        ReportStatusToSCMgr(SERVICE_STOP_PENDING, NO_ERROR, 30000);
        return;
    }
    if (dwCtrlCode == SERVICE_APACHE_RESTART)
    {
        ap_signal_parent(SIGNAL_PARENT_RESTART);
        ReportStatusToSCMgr(SERVICE_START_PENDING, NO_ERROR, 30000);
        return;
    }

    ReportStatusToSCMgr(globdat.ssStatus.dwCurrentState, NO_ERROR, 0);
}


/* service_nt_main_fn is outside of the call stack and outside of the
 * primary server thread... so now we _really_ need a placeholder!
 * The winnt_rewrite_args has created and shared mpm_new_argv with us.
 */
extern apr_array_header_t *mpm_new_argv;

#if APR_HAS_UNICODE_FS
static void __stdcall service_nt_main_fn_w(DWORD argc, LPWSTR *argv)
{
    const char *ignored;
    char *service_name;
    apr_size_t wslen = wcslen(argv[0]) + 1;
    apr_size_t slen = wslen * 3 - 2;

    service_name = malloc(slen);
    (void)apr_conv_ucs2_to_utf8(argv[0], &wslen, service_name, &slen);

    /* args and service names live in the same pool */
    mpm_service_set_name(mpm_new_argv->pool, &ignored, service_name);

    memset(&globdat.ssStatus, 0, sizeof(globdat.ssStatus));
    globdat.ssStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    globdat.ssStatus.dwCurrentState = SERVICE_START_PENDING;
    globdat.ssStatus.dwCheckPoint = 1;

    if (!(globdat.hServiceStatus = RegisterServiceCtrlHandlerW(argv[0], service_nt_ctrl)))
    {
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(),
                     NULL, "Failure registering service handler");
        return;
    }

    /* Report status, no errors, and buy 3 more seconds */
    ReportStatusToSCMgr(SERVICE_START_PENDING, NO_ERROR, 30000);

    /* We need to append all the command arguments passed via StartService()
     * to our running service... which just got here via the SCM...
     * but we have no interest in argv[0] for the mpm_new_argv list.
     */
    if (argc > 1)
    {
        char **cmb_data, **cmb;
        DWORD i;

        mpm_new_argv->nalloc = mpm_new_argv->nelts + argc - 1;
        cmb_data = malloc(mpm_new_argv->nalloc * sizeof(const char *));

        /* mpm_new_argv remains first (of lower significance) */
        memcpy (cmb_data, mpm_new_argv->elts,
                mpm_new_argv->elt_size * mpm_new_argv->nelts);

        /* Service args follow from StartService() invocation */
        memcpy (cmb_data + mpm_new_argv->nelts, argv + 1,
                mpm_new_argv->elt_size * (argc - 1));

        cmb = cmb_data + mpm_new_argv->nelts;

        for (i = 1; i < argc; ++i)
        {
            wslen = wcslen(argv[i]) + 1;
            slen = wslen * 3 - 2;
            service_name = malloc(slen);
            (void)apr_conv_ucs2_to_utf8(argv[i], &wslen, *(cmb++), &slen);
        }

        /* The replacement arg list is complete */
        mpm_new_argv->elts = (char *)cmb_data;
        mpm_new_argv->nelts = mpm_new_argv->nalloc;
    }

    /* Let the main thread continue now... but hang on to the
     * signal_monitor event so we can take further action
     */
    SetEvent(globdat.service_init);

    WaitForSingleObject(globdat.service_term, INFINITE);
}
#endif /* APR_HAS_UNICODE_FS */


#if APR_HAS_ANSI_FS
static void __stdcall service_nt_main_fn(DWORD argc, LPSTR *argv)
{
    const char *ignored;

    /* args and service names live in the same pool */
    mpm_service_set_name(mpm_new_argv->pool, &ignored, argv[0]);

    memset(&globdat.ssStatus, 0, sizeof(globdat.ssStatus));
    globdat.ssStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    globdat.ssStatus.dwCurrentState = SERVICE_START_PENDING;
    globdat.ssStatus.dwCheckPoint = 1;

    if (!(globdat.hServiceStatus = RegisterServiceCtrlHandlerA(argv[0], service_nt_ctrl)))
    {
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(),
                     NULL, "Failure registering service handler");
        return;
    }

    /* Report status, no errors, and buy 3 more seconds */
    ReportStatusToSCMgr(SERVICE_START_PENDING, NO_ERROR, 30000);

    /* We need to append all the command arguments passed via StartService()
     * to our running service... which just got here via the SCM...
     * but we have no interest in argv[0] for the mpm_new_argv list.
     */
    if (argc > 1)
    {
        char **cmb_data;

        mpm_new_argv->nalloc = mpm_new_argv->nelts + argc - 1;
