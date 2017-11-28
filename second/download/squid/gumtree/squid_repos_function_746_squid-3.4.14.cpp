void
WIN32_InstallService()
{
    SC_HANDLE schService;
    SC_HANDLE schSCManager;
    char ServicePath[512];
    char szPath[512];
    int lenpath;

    if (!WIN32_Service_name)
        WIN32_Service_name = xstrdup(_WIN_SQUID_DEFAULT_SERVICE_NAME);

    strcat(REGKEY, WIN32_Service_name);

    keys[4] = WIN32_Service_name;

    if ((lenpath = GetModuleFileName(NULL, ServicePath, 512)) == 0) {
        fprintf(stderr, "Can't get executable path\n");
        exit(1);
    }

    snprintf(szPath, sizeof(szPath), "%s %s:%s", ServicePath, _WIN_SQUID_SERVICE_OPTION, WIN32_Service_name);
    schSCManager = OpenSCManager(NULL,	/* machine (NULL == local)    */
                                 NULL,			/* database (NULL == default) */
                                 SC_MANAGER_ALL_ACCESS	/* access required            */
                                );

    if (!schSCManager) {
        fprintf(stderr, "OpenSCManager failed\n");
        exit(1);
    } else {
        schService = CreateService(schSCManager,    /* SCManager database     */
                                   WIN32_Service_name,			    /* name of service        */
                                   WIN32_Service_name,			    /* name to display        */
                                   SERVICE_ALL_ACCESS,			    /* desired access         */
                                   SERVICE_WIN32_OWN_PROCESS,		    /* service type           */
                                   SERVICE_AUTO_START,			    /* start type             */
                                   SERVICE_ERROR_NORMAL,		    /* error control type     */
                                   (const char *) szPath,		    /* service's binary       */
                                   NULL,				    /* no load ordering group */
                                   NULL,				    /* no tag identifier      */
                                   "Tcpip\0AFD\0",			    /* dependencies           */
                                   NULL,				    /* LocalSystem account    */
                                   NULL);				    /* no password            */

        if (schService) {
            if (WIN32_OS_version > _WIN_OS_WINNT) {
                HMODULE ADVAPI32Handle;
                PFChangeServiceConfig2 ChangeServiceConfig2;
                DWORD dwInfoLevel = SERVICE_CONFIG_DESCRIPTION;

                ADVAPI32Handle = GetModuleHandle("advapi32");
                ChangeServiceConfig2 = (PFChangeServiceConfig2) GetProcAddress(ADVAPI32Handle, CHANGESERVICECONFIG2);
                ChangeServiceConfig2(schService, dwInfoLevel, &Squid_ServiceDescription);
                dwInfoLevel = SERVICE_CONFIG_FAILURE_ACTIONS;
                ChangeServiceConfig2(schService, dwInfoLevel, &Squid_ServiceFailureActions);
            }

            CloseServiceHandle(schService);
            /* Now store the config file location in the registry */

            if (!ConfigFile)
                ConfigFile = xstrdup(DefaultConfigFile);

            WIN32_StoreKey(CONFIGFILE, REG_SZ, (unsigned char *) ConfigFile, strlen(ConfigFile) + 1);

            printf("Squid Cache version %s for %s\n", version_string,
                   CONFIG_HOST_TYPE);

            printf("installed successfully as %s Windows System Service.\n",
                   WIN32_Service_name);

            printf
            ("To run, start it from the Services Applet of Control Panel.\n");

            printf("Don't forget to edit squid.conf before starting it.\n\n");
        } else {
            fprintf(stderr, "CreateService failed\n");
            exit(1);
        }

        CloseServiceHandle(schSCManager);
    }
}