int WIN32_Subsystem_Init(int * argc, char *** argv)
{
#if defined(_MSC_VER) /* Microsoft C Compiler ONLY */
    _invalid_parameter_handler oldHandler, newHandler;
#endif

    WIN32_OS_version = GetOSVersion();

    if ((WIN32_OS_version == _WIN_OS_UNKNOWN) || (WIN32_OS_version == _WIN_OS_WIN32S))
        return 1;

    if (atexit(WIN32_Exit) != 0)
        return 1;

#if defined(_MSC_VER) /* Microsoft C Compiler ONLY */

    newHandler = Squid_Win32InvalidParameterHandler;

    oldHandler = _set_invalid_parameter_handler(newHandler);

    _CrtSetReportMode(_CRT_ASSERT, 0);

#endif
#if USE_WIN32_SERVICE

    if (WIN32_run_mode == _WIN_SQUID_RUN_MODE_SERVICE) {
        char path[512];
        HKEY hndKey;

        if (signal(SIGABRT, WIN32_Abort) == SIG_ERR)
            return 1;

        /* Register the service Handler function */
        svcHandle = RegisterServiceCtrlHandler(WIN32_Service_name, WIN32_svcHandler);

        if (svcHandle == 0)
            return 1;

        /* Set Process work dir to directory cointaining squid.exe */
        GetModuleFileName(NULL, path, 512);

        WIN32_module_name=xstrdup(path);

        path[strlen(path) - 10] = '\0';

        if (SetCurrentDirectory(path) == 0)
            return 1;

        safe_free(ConfigFile);

        /* get config file from Windows Registry */
        if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, REGKEY, 0, KEY_QUERY_VALUE, &hndKey) == ERROR_SUCCESS) {
            DWORD Type = 0;
            DWORD Size = 0;
            LONG Result;
            Result = RegQueryValueEx(hndKey, CONFIGFILE, NULL, &Type, NULL, &Size);

            if (Result == ERROR_SUCCESS && Size) {
                ConfigFile = static_cast<char *>(xmalloc(Size));
                RegQueryValueEx(hndKey, CONFIGFILE, NULL, &Type, (unsigned char *)ConfigFile, &Size);
            } else
                ConfigFile = xstrdup(DefaultConfigFile);

            Size = 0;

            Type = 0;

            Result = RegQueryValueEx(hndKey, COMMANDLINE, NULL, &Type, NULL, &Size);

            if (Result == ERROR_SUCCESS && Size) {
                WIN32_Service_Command_Line = static_cast<char *>(xmalloc(Size));
                RegQueryValueEx(hndKey, COMMANDLINE, NULL, &Type, (unsigned char *)WIN32_Service_Command_Line, &Size);
            } else
                WIN32_Service_Command_Line = xstrdup("");

            RegCloseKey(hndKey);
        } else {
            ConfigFile = xstrdup(DefaultConfigFile);
            WIN32_Service_Command_Line = xstrdup("");
        }

        WIN32_build_argv(WIN32_Service_Command_Line);
        *argc = WIN32_argc;
        *argv = WIN32_argv;
        /* Set Service Status to SERVICE_START_PENDING */
        svcStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
        svcStatus.dwCurrentState = SERVICE_START_PENDING;
        svcStatus.dwControlsAccepted =
            SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
        svcStatus.dwWin32ExitCode = 0;
        svcStatus.dwServiceSpecificExitCode = 0;
        svcStatus.dwCheckPoint = 0;
        svcStatus.dwWaitHint = 10000;
        SetServiceStatus(svcHandle, &svcStatus);

        _setmaxstdio(Squid_MaxFD);

    }

#endif /* USE_WIN32_SERVICE */
    if (Win32SockInit() < 0)
        return 1;

    return 0;
}