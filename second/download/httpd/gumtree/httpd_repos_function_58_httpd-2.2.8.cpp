int main (int argc, const char * const argv[])
{
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
    apr_getopt_t *opt;
    apr_status_t rv;
    char c;
    const char *optarg;
    char *ptr = NULL;

    apr_app_initialize(&argc, &argv, NULL);
    atexit(apr_terminate);

    apr_pool_create(&pool, NULL);
    apr_getopt_init(&opt, pool, argc, argv);
    while ((rv = apr_getopt(opt, "l", &c, &optarg)) == APR_SUCCESS) {
        switch (c) {
        case 'l':
            use_localtime = 1;
            break;
        }
    }

    if (rv != APR_EOF) {
        usage(argv[0], NULL /* specific error message already issued */ );
    }

    if (opt->ind + 2 != argc && opt->ind + 3 != argc) {
        usage(argv[0], "Incorrect number of arguments");
    }

    szLogRoot = argv[opt->ind++];

    ptr = strchr(argv[opt->ind], 'M');
    if (ptr) { /* rotation based on file size */
        if (*(ptr+1) == '\0') {
            sRotation = atoi(argv[opt->ind]) * 1048576;
        }
        if (sRotation == 0) {
            usage(argv[0], "Invalid rotation size parameter");
        }
    }
    else { /* rotation based on elapsed time */
        tRotation = atoi(argv[opt->ind]);
        if (tRotation <= 0) {
            usage(argv[0], "Invalid rotation time parameter");
        }
    }
    opt->ind++;

    if (opt->ind < argc) { /* have UTC offset */
        if (use_localtime) {
            usage(argv[0], "UTC offset parameter is not valid with -l");
        }
        utc_offset = atoi(argv[opt->ind]) * 60;
    }

    use_strftime = (strchr(szLogRoot, '%') != NULL);
    if (apr_file_open_stdin(&f_stdin, pool) != APR_SUCCESS) {
        fprintf(stderr, "Unable to open stdin\n");
        exit(1);
    }

    for (;;) {
        nRead = sizeof(buf);
        if (apr_file_read(f_stdin, buf, &nRead) != APR_SUCCESS) {
            exit(3);
        }
        if (tRotation) {
            /*
             * Check for our UTC offset every time through the loop, since
             * it might change if there's a switch between standard and
             * daylight savings time.
             */
            if (use_localtime) {
                apr_time_exp_t lt;
                apr_time_exp_lt(&lt, apr_time_now());
                utc_offset = lt.tm_gmtoff;
            }
            now = (int)(apr_time_now() / APR_USEC_PER_SEC) + utc_offset;
            if (nLogFD != NULL && now >= tLogEnd) {
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

            if (current_size > sRotation) {
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
            apr_status_t rv;

            if (tRotation) {
                tLogStart = (now / tRotation) * tRotation;
            }
            else {
                if (use_localtime) {
                    /* Check for our UTC offset before using it, since it might
                     * change if there's a switch between standard and daylight
                     * savings time.
                     */
                    apr_time_exp_t lt;
                    apr_time_exp_lt(&lt, apr_time_now());
                    utc_offset = lt.tm_gmtoff;
                }
                tLogStart = (int)apr_time_sec(apr_time_now()) + utc_offset;
            }

            if (use_strftime) {
                apr_time_t tNow = apr_time_from_sec(tLogStart);
                apr_time_exp_t e;
                apr_size_t rs;

                apr_time_exp_gmt(&e, tNow);
                apr_strftime(buf2, &rs, sizeof(buf2), szLogRoot, &e);
            }
            else {
                sprintf(buf2, "%s.%010d", szLogRoot, tLogStart);
            }
            tLogEnd = tLogStart + tRotation;
            rv = apr_file_open(&nLogFD, buf2, APR_WRITE | APR_CREATE | APR_APPEND,
                               APR_OS_DEFAULT, pool);
            if (rv != APR_SUCCESS) {
                char error[120];

                apr_strerror(rv, error, sizeof error);

                /* Uh-oh. Failed to open the new log file. Try to clear
                 * the previous log file, note the lost log entries,
                 * and keep on truckin'. */
                if (nLogFDprev == NULL) {
                    fprintf(stderr, "Could not open log file '%s' (%s)\n", buf2, error);
                    exit(2);
                }
                else {
                    nLogFD = nLogFDprev;
                    /* Try to keep this error message constant length
                     * in case it occurs several times. */
                    apr_snprintf(errbuf, sizeof errbuf,
                                 "Resetting log file due to error opening "
                                 "new log file, %10d messages lost: %-25.25s\n",
                                 nMessCount, error);
                    nWrite = strlen(errbuf);
                    apr_file_trunc(nLogFD, 0);
                    if (apr_file_write(nLogFD, errbuf, &nWrite) != APR_SUCCESS) {
                        fprintf(stderr, "Error writing to the file %s\n", buf2);
                        exit(2);
                    }
                }
            }
            else if (nLogFDprev) {
                apr_file_close(nLogFDprev);
            }
            nMessCount = 0;
        }
        nWrite = nRead;
        apr_file_write(nLogFD, buf, &nWrite);
        if (nWrite != nRead) {
            nMessCount++;
            sprintf(errbuf,
                    "Error writing to log file. "
                    "%10d messages lost.\n",
                    nMessCount);
            nWrite = strlen(errbuf);
            apr_file_trunc(nLogFD, 0);
            if (apr_file_write(nLogFD, errbuf, &nWrite) != APR_SUCCESS) {
                fprintf(stderr, "Error writing to the file %s\n", buf2);
                exit(2);
            }
        }
        else {
            nMessCount++;
        }
    }
    /* Of course we never, but prevent compiler warnings */
    return 0;
}