{
    SERVICE_STATUS ssStatus;
    DWORD fdwAccess, fdwControl;
    SC_HANDLE schService;
    SC_HANDLE schSCManager;

    if (service_name.isEmpty())
        service_name = SBuf(APP_SHORTNAME);

    schSCManager = OpenSCManager(NULL,	/* machine (NULL == local)    */
                                 NULL,          /* database (NULL == default) */
                                 SC_MANAGER_ALL_ACCESS	/* access required            */
                                );

    if (!schSCManager) {
        fprintf(stderr, "OpenSCManager failed\n");
        exit(1);
    }

    /* The required service object access depends on the control. */
    switch (WIN32_signal) {

    case 0:         /* SIGNULL */
        fdwAccess = SERVICE_INTERROGATE;
        fdwControl = _WIN_SQUID_SERVICE_CONTROL_INTERROGATE;
        break;

    case SIGUSR1:
        fdwAccess = SERVICE_USER_DEFINED_CONTROL;
