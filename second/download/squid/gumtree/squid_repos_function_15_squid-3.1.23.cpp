int
main(int argc, char *argv[])
{
    char *s;
    cachemgr_request *req;

    now = time(NULL);
#ifdef _SQUID_MSWIN_

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

    req = read_request();

    return process_request(req);
}