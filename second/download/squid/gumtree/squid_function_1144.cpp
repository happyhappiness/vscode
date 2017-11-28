void
WIN32_sendSignal(int WIN32_signal)
{
    SERVICE_STATUS ssStatus;
    DWORD fdwAccess, fdwControl;
    SC_HANDLE schService;
    SC_HANDLE schSCManager;

    if (!WIN32_Service_name)
        WIN32_Service_name = xstrdup(_WIN_SQUID_DEFAULT_SERVICE_NAME);

    schSCManager = OpenSCManager(NULL,	/* machine (NULL == local)    */
                                 NULL,			/* database (NULL == default) */
                                 SC_MANAGER_ALL_ACCESS	/* access required            */
                                );

    if (!schSCManager) {
        fprintf(stderr, "OpenSCManager failed\n");
        exit(1);
    }

    /* The required service object access depends on the control. */
    switch (WIN32_signal) {

    case 0:			/* SIGNULL */
        fdwAccess = SERVICE_INTERROGATE;
        fdwControl = _WIN_SQUID_SERVICE_CONTROL_INTERROGATE;
        break;

    case SIGUSR1:
        fdwAccess = SERVICE_USER_DEFINED_CONTROL;
        fdwControl = _WIN_SQUID_SERVICE_CONTROL_ROTATE;
        break;

    case SIGUSR2:
        fdwAccess = SERVICE_USER_DEFINED_CONTROL;
        fdwControl = _WIN_SQUID_SERVICE_CONTROL_DEBUG;
        break;

    case SIGHUP:
        fdwAccess = SERVICE_USER_DEFINED_CONTROL;
        fdwControl = _WIN_SQUID_SERVICE_CONTROL_RECONFIGURE;
        break;

    case SIGTERM:
        fdwAccess = SERVICE_STOP;
        fdwControl = _WIN_SQUID_SERVICE_CONTROL_STOP;
        break;

    case SIGINT:

    case SIGKILL:
        fdwAccess = SERVICE_USER_DEFINED_CONTROL;
        fdwControl = _WIN_SQUID_SERVICE_CONTROL_INTERRUPT;
        break;

    default:
        exit(1);
    }

    /* Open a handle to the service. */
    schService = OpenService(schSCManager,	/* SCManager database */
                             WIN32_Service_name,	/* name of service    */
                             fdwAccess);		/* specify access     */

    if (schService == NULL) {
        fprintf(stderr, "%s: ERROR: Could not open Service %s\n", APP_SHORTNAME,
                WIN32_Service_name);
        exit(1);
    } else {
        /* Send a control value to the service. */

        if (!ControlService(schService,	/* handle of service      */
                            fdwControl,	/* control value to send  */
                            &ssStatus)) {	/* address of status info */
            fprintf(stderr, "%s: ERROR: Could not Control Service %s\n",
                    APP_SHORTNAME, WIN32_Service_name);
            exit(1);
        } else {
            /* Print the service status. */
            printf("\nStatus of %s Service:\n", WIN32_Service_name);
            printf("  Service Type: 0x%lx\n", ssStatus.dwServiceType);
            printf("  Current State: 0x%lx\n", ssStatus.dwCurrentState);
            printf("  Controls Accepted: 0x%lx\n", ssStatus.dwControlsAccepted);
            printf("  Exit Code: %ld\n", ssStatus.dwWin32ExitCode);
            printf("  Service Specific Exit Code: %ld\n",
                   ssStatus.dwServiceSpecificExitCode);
            printf("  Check Point: %ld\n", ssStatus.dwCheckPoint);
            printf("  Wait Hint: %ld\n", ssStatus.dwWaitHint);
        }

        CloseServiceHandle(schService);
    }

    CloseServiceHandle(schSCManager);
}