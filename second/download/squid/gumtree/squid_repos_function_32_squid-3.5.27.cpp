int
main(int argc, char *argv[])
{
    char *s;
    cachemgr_request *req;

    now = time(NULL);
#if _SQUID_WINDOWS_

    Win32SockInit();
    atexit(Win32SockCleanup);
    _setmode( _fileno( stdin ), _O_BINARY );
    _setmode( _fileno( stdout ), _O_BINARY );
    _fmode = _O_BINARY;

    if ((s = strrchr(argv[0], '\\')))
#else

    if ((s = strrchr(argv[0], '/')))
#endif

        progname = xstrdup(s + 1);
    else
        progname = xstrdup(argv[0]);

    if ((s = getenv("SCRIPT_NAME")) != NULL)
        script_name = xstrdup(s);

    char **args = argv;
    while (argc > 1 && args[1][0] == '-') {
//        const char *value = "";
        char option = args[1][1];
        switch (option) {
        case 'd':
            debug_enabled = 1;
            break;
        default:
#if 0 // unused for now.
            if (strlen(args[1]) > 2) {
                value = args[1] + 2;
            } else if (argc > 2) {
                value = args[2];
                ++args;
                --argc;
            } else
                value = "";
#endif
            break;
        }
        ++args;
        --argc;
    }

    req = read_request();

    return process_request(req);
}