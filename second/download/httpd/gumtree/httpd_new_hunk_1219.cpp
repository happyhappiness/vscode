    char buf[BUFSIZE], buf2[MAX_PATH], errbuf[ERRMSGSZ];
    int tLogEnd = 0, tRotation = 0, utc_offset = 0;
    unsigned int sRotation = 0;
    int nMessCount = 0;
    apr_size_t nRead, nWrite;
    int use_strftime = 0;
    int use_localtime = 0;
    int now = 0;
    const char *szLogRoot;
    apr_file_t *f_stdin, *nLogFD = NULL, *nLogFDprev = NULL;
    apr_pool_t *pool;
    char *ptr = NULL;
    int argBase = 0;
    int argFile = 1;
    int argIntv = 2;
    int argOffset = 3;

    apr_app_initialize(&argc, &argv, NULL);
    atexit(apr_terminate);

    apr_pool_create(&pool, NULL);
    if ((argc > 2) && (strcmp(argv[1], "-l") == 0)) {
        argBase++;
        argFile += argBase;
        argIntv += argBase;
        argOffset += argBase;
        use_localtime = 1;
    }
    if (argc < (argBase + 3) || argc > (argBase + 4)) {
        fprintf(stderr,
                "Usage: %s [-l] <logfile> <rotation time in seconds> "
                "[offset minutes from UTC] or <rotation size in megabytes>\n\n",
                argv[0]);
#ifdef OS2
        fprintf(stderr,
                "Add this:\n\nTransferLog \"|%s.exe /some/where 86400\"\n\n",
                argv[0]);
