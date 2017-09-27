    apr_status_t rv;

    fprintf(stderr,"Starting the %s service\n", mpm_display_name);

    if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        char **start_argv;
        SC_HANDLE   schService;
        SC_HANDLE   schSCManager;

        schSCManager = OpenSCManager(NULL, NULL, /* local, default database */
                                     SC_MANAGER_CONNECT);
        if (!schSCManager) {
