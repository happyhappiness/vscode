int
Log::TcpLogger::Open(Logfile * lf, const char *path, size_t bufsz, int fatalFlag)
{
    assert(!StillLogging(lf));
    debugs(5, 3, "Tcp Open called");

    Ip::Address addr;

    if (strncmp(path, "//", 2) == 0)
        path += 2;
    char *strAddr = xstrdup(path);
    if (!GetHostWithPort(strAddr, &addr)) {
        if (lf->flags.fatal) {
            fatalf("Invalid TCP logging address '%s'\n", lf->path);
        } else {
            debugs(50, DBG_IMPORTANT, "Invalid TCP logging address '" << lf->path << "'");
            safe_free(strAddr);
            return FALSE;
        }
    }
    safe_free(strAddr);

    TcpLogger *logger = new TcpLogger(bufsz, fatalFlag, addr);
    lf->data = new Pointer(logger);
    lf->f_close = &Close;
    lf->f_linewrite = &WriteLine;
    lf->f_linestart = &StartLine;
    lf->f_lineend = &EndLine;
    lf->f_flush = &Flush;
    lf->f_rotate = &Rotate;
    AsyncJob::Start(logger);

    return 1;
}