#define MAX_PATH        1024
#endif

int main (int argc, const char * const argv[])
{
    char buf[BUFSIZE], buf2[MAX_PATH], errbuf[ERRMSGSZ];
    int tLogEnd = 0, tRotation = 0, utc_offset = 0;
    unsigned int sRotation = 0;
    int nMessCount = 0;
    apr_size_t nRead, nWrite;
    int use_strftime = 0;
    int now = 0;
    const char *szLogRoot;
    apr_file_t *f_stdin, *nLogFD = NULL, *nLogFDprev = NULL;
    apr_pool_t *pool;
    char *ptr = NULL;

    apr_app_initialize(&argc, &argv, NULL);
    atexit(apr_terminate);

    apr_pool_create(&pool, NULL);
    if (argc < 3 || argc > 4) {
        fprintf(stderr,
                "Usage: %s <logfile> <rotation time in seconds> "
                "[offset minutes from UTC] or <rotation size in megabytes>\n\n",
                argv[0]);
#ifdef OS2
        fprintf(stderr,
                "Add this:\n\nTransferLog \"|%s.exe /some/where 86400\"\n\n",
                argv[0]);
#else
        fprintf(stderr,
                "Add this:\n\nTransferLog \"|%s /some/where 86400\"\n\n",
                argv[0]);
        fprintf(stderr,
                "or \n\nTransferLog \"|%s /some/where 5M\"\n\n", argv[0]);
#endif
        fprintf(stderr,
                "to httpd.conf. The generated name will be /some/where.nnnn "
                "where nnnn is the\nsystem time at which the log nominally "
                "starts (N.B. if using a rotation time,\nthe time will always "
                "be a multiple of the rotation time, so you can synchronize\n"
                "cron scripts with it). At the end of each rotation time or "
                "when the file size\nis reached a new log is started.\n");
        exit(1);
    }

    szLogRoot = argv[1];

    ptr = strchr (argv[2], 'M');
    if (ptr) {
        if (*(ptr+1) == '\0') {
            sRotation = atoi(argv[2]) * 1048576;
        }
        if (sRotation == 0) {
            fprintf(stderr, "Invalid rotation size parameter\n");
            exit(1);
        }
    }
    else {
        if (argc >= 4) {
            utc_offset = atoi(argv[3]) * 60;
        }
        tRotation = atoi(argv[2]);
        if (tRotation <= 0) {
            fprintf(stderr, "Rotation time must be > 0\n");
            exit(6);
        }
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
        if (nRead == 0)
            exit(3);
        if (tRotation) {
            now = (int)(apr_time_now() / APR_USEC_PER_SEC) + utc_offset;
            if (nLogFD != NULL && (now >= tLogEnd || nRead < 0)) {
                nLogFDprev = nLogFD;
                nLogFD = NULL;
            }
        }
        else if (sRotation) {
            apr_finfo_t finfo;
            apr_off_t current_size = -1;

            if ((nLogFD != NULL) && 
                (apr_file_info_get(&finfo, APR_FINFO_SIZE, nLogFD) == APR_SUCCESS)) {
                current_size = finfo.size;
            }

            if (current_size > sRotation || nRead < 0) {
                nLogFDprev = nLogFD;
                nLogFD = NULL;
            }
        }
        else {
            fprintf(stderr, "No rotation time or size specified\n");
            exit(2);
        }

        if (nLogFD == NULL) {
            int tLogStart;
                
            if (tRotation)
                tLogStart = (now / tRotation) * tRotation;
            else
                tLogStart = (int)apr_time_sec(apr_time_now());

            if (use_strftime) {
                apr_time_t tNow = apr_time_from_sec(tLogStart);
                apr_time_exp_t e;
                apr_size_t rs;

                apr_time_exp_gmt(&e, tNow);
                apr_strftime(buf2, &rs, sizeof(buf2), szLogRoot, &e);
            }
