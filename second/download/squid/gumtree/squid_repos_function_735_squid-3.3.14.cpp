int main(int argc, char **argv)
{
    SERVICE_TABLE_ENTRY DispatchTable[] = {
        {NULL, SquidWinSvcMain},
        {NULL, NULL}
    };
    char *c;
    char stderr_path[256];

    if ((argc == 2) && strstr(argv[1], _WIN_SQUID_SERVICE_OPTION)) {
        strcpy(stderr_path, argv[0]);
        strcat(stderr_path,".log");
        freopen(stderr_path, "w", stderr);
        setmode(fileno(stderr), O_TEXT);
        WIN32_run_mode = _WIN_SQUID_RUN_MODE_SERVICE;

        if (!(c=strchr(argv[1],':'))) {
            fprintf(stderr, "Bad Service Parameter: %s\n", argv[1]);
            return 1;
        }

        WIN32_Service_name = xstrdup(c+1);
        DispatchTable[0].lpServiceName=WIN32_Service_name;
        strcat(REGKEY, WIN32_Service_name);
        keys[4] = WIN32_Service_name;

        if (!StartServiceCtrlDispatcher(DispatchTable)) {
            fprintf(stderr, "StartServiceCtrlDispatcher error = %ld\n",
                    GetLastError());
            return 1;
        }
    } else {
        WIN32_run_mode = _WIN_SQUID_RUN_MODE_INTERACTIVE;
        opt_no_daemon = 1;

        return SquidMain(argc, argv);
    }

    return 0;
}