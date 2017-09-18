#define MAX_PATH        1024
#endif

int main (int argc, const char * const argv[])
{
    char buf[BUFSIZE], buf2[MAX_PATH], errbuf[ERRMSGSZ];
    int tLogEnd = 0, tRotation, utc_offset = 0;
    int nMessCount = 0;
    apr_size_t nRead, nWrite;
    int use_strftime = 0;
    int now;
    const char *szLogRoot;
    apr_file_t *f_stdin, *nLogFD = NULL, *nLogFDprev = NULL;
    apr_pool_t *pool;

    apr_app_initialize(&argc, &argv, NULL);
    atexit(apr_terminate);

    apr_pool_create(&pool, NULL);
    if (argc < 3 || argc > 4) {
        fprintf(stderr,
                "Usage: %s <logfile> <rotation time in seconds> "
                "[offset minutes from UTC]\n\n",
                argv[0]);
#ifdef OS2
        fprintf(stderr,
                "Add this:\n\nTransferLog \"|%s.exe /some/where 86400\"\n\n",
                argv[0]);
#else
        fprintf(stderr,
                "Add this:\n\nTransferLog \"|%s /some/where 86400\"\n\n",
                argv[0]);
#endif
        fprintf(stderr,
                "to httpd.conf. The generated name will be /some/where.nnnn "
                "where nnnn is the\nsystem time at which the log nominally "
                "starts (N.B. this time will always be a\nmultiple of the "
                "rotation time, so you can synchronize cron scripts with it).\n"
                "At the end of each rotation time a new log is started.\n");
        exit(1);
    }

    szLogRoot = argv[1];
    if (argc >= 4) {
        utc_offset = atoi(argv[3]) * 60;
    }
    tRotation = atoi(argv[2]);
    if (tRotation <= 0) {
        fprintf(stderr, "Rotation time must be > 0\n");
        exit(6);
    }

    use_strftime = (strchr(szLogRoot, '%') != NULL);
    if (apr_file_open_stdin(&f_stdin, pool) != APR_SUCCESS) {
        fprintf(stderr, "Unable to open stdin\n");
        exit(1);
    }

    for (;;) {
        nRead = sizeof(buf);
        if (apr_file_read(f_stdin, buf, &nRead) != APR_SUCCESS)
            exit(3);
        now = (int)(apr_time_now() / APR_USEC_PER_SEC) + utc_offset;
        if (nRead == 0)
            exit(3);
        if (nLogFD != NULL && (now >= tLogEnd || nRead < 0)) {
            nLogFDprev = nLogFD;
            nLogFD = NULL;
        }
        if (nLogFD == NULL) {
            int tLogStart = (now / tRotation) * tRotation;
            if (use_strftime) {
		apr_time_t tNow = tLogStart * APR_USEC_PER_SEC;
                apr_time_exp_t e;
                apr_size_t rs;

                apr_time_exp_gmt(&e, tNow);
                apr_strftime(buf2, &rs, sizeof(buf2), szLogRoot, &e);
            }
