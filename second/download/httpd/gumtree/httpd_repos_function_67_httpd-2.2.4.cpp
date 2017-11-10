int main(int argc, const char * const argv[])
{
    apr_off_t max;
    apr_time_t current, repeat, delay, previous;
    apr_status_t status;
    apr_pool_t *pool, *instance;
    apr_getopt_t *o;
    apr_finfo_t info;
    int retries, isdaemon, limit_found, intelligent, dowork;
    char opt;
    const char *arg;
    char *proxypath, *path;

    interrupted = 0;
    repeat = 0;
    isdaemon = 0;
    dryrun = 0;
    limit_found = 0;
    max = 0;
    verbose = 0;
    realclean = 0;
    benice = 0;
    deldirs = 0;
    intelligent = 0;
    previous = 0; /* avoid compiler warning */
    proxypath = NULL;

    if (apr_app_initialize(&argc, &argv, NULL) != APR_SUCCESS) {
        return 1;
    }
    atexit(apr_terminate);

    if (argc) {
        shortname = apr_filepath_name_get(argv[0]);
    }

    if (apr_pool_create(&pool, NULL) != APR_SUCCESS) {
        return 1;
    }
    apr_pool_abort_set(oom, pool);
    apr_file_open_stderr(&errfile, pool);
    apr_signal(SIGINT, setterm);
    apr_signal(SIGTERM, setterm);

    apr_getopt_init(&o, pool, argc, argv);

    while (1) {
        status = apr_getopt(o, "iDnvrtd:l:L:p:", &opt, &arg);
        if (status == APR_EOF) {
            break;
        }
        else if (status != APR_SUCCESS) {
            usage();
        }
        else {
            switch (opt) {
            case 'i':
                if (intelligent) {
                    usage();
                }
                intelligent = 1;
                break;

            case 'D':
                if (dryrun) {
                    usage();
                }
                dryrun = 1;
                break;

            case 'n':
                if (benice) {
                    usage();
                }
                benice = 1;
                break;

            case 't':
                if (deldirs) {
                    usage();
                }
                deldirs = 1;
                break;

            case 'v':
                if (verbose) {
                    usage();
                }
                verbose = 1;
                break;

            case 'r':
                if (realclean) {
                    usage();
                }
                realclean = 1;
                deldirs = 1;
                break;

            case 'd':
                if (isdaemon) {
                    usage();
                }
                isdaemon = 1;
                repeat = apr_atoi64(arg);
                repeat *= SECS_PER_MIN;
                repeat *= APR_USEC_PER_SEC;
                break;

            case 'l':
                if (limit_found) {
                    usage();
                }
                limit_found = 1;

                do {
                    apr_status_t rv;
                    char *end;

                    rv = apr_strtoff(&max, arg, &end, 10);
                    if (rv == APR_SUCCESS) {
                        if ((*end == 'K' || *end == 'k') && !end[1]) {
                            max *= KBYTE;
                        }
                        else if ((*end == 'M' || *end == 'm') && !end[1]) {
                            max *= MBYTE;
                        }
                        else if ((*end == 'G' || *end == 'g') && !end[1]) {
                            max *= GBYTE;
                        }
                        else if (*end &&        /* neither empty nor [Bb] */
                                 ((*end != 'B' && *end != 'b') || end[1])) {
                            rv = APR_EGENERAL;
                        }
                    }
                    if (rv != APR_SUCCESS) {
                        apr_file_printf(errfile, "Invalid limit: %s"
                                                 APR_EOL_STR APR_EOL_STR, arg);
                        usage();
                    }
                } while(0);
                break;

            case 'p':
                if (proxypath) {
                    usage();
                }
                proxypath = apr_pstrdup(pool, arg);
                if (apr_filepath_set(proxypath, pool) != APR_SUCCESS) {
                    usage();
                }
                break;
            } /* switch */
        } /* else */
    } /* while */

    if (o->ind != argc) {
         usage();
    }

    if (isdaemon && (repeat <= 0 || verbose || realclean || dryrun)) {
         usage();
    }

    if (!isdaemon && intelligent) {
         usage();
    }

    if (!proxypath || max <= 0) {
         usage();
    }

    if (apr_filepath_get(&path, 0, pool) != APR_SUCCESS) {
        usage();
    }
    baselen = strlen(path);

#ifndef DEBUG
    if (isdaemon) {
        apr_file_close(errfile);
        apr_proc_detach(APR_PROC_DETACH_DAEMONIZE);
    }
#endif

    do {
        apr_pool_create(&instance, pool);

        now = apr_time_now();
        APR_RING_INIT(&root, _entry, link);
        delcount = 0;
        unsolicited = 0;
        dowork = 0;

        switch (intelligent) {
        case 0:
            dowork = 1;
            break;

        case 1:
            retries = STAT_ATTEMPTS;
            status = APR_SUCCESS;

            do {
                if (status != APR_SUCCESS) {
                    apr_sleep(STAT_DELAY);
                }
                status = apr_stat(&info, path, APR_FINFO_MTIME, instance);
            } while (status != APR_SUCCESS && !interrupted && --retries);

            if (status == APR_SUCCESS) {
                previous = info.mtime;
                intelligent = 2;
            }
            dowork = 1;
            break;

        case 2:
            retries = STAT_ATTEMPTS;
            status = APR_SUCCESS;

            do {
                if (status != APR_SUCCESS) {
                    apr_sleep(STAT_DELAY);
                }
                status = apr_stat(&info, path, APR_FINFO_MTIME, instance);
            } while (status != APR_SUCCESS && !interrupted && --retries);

            if (status == APR_SUCCESS) {
                if (previous != info.mtime) {
                    dowork = 1;
                }
                previous = info.mtime;
                break;
            }
            intelligent = 1;
            dowork = 1;
            break;
        }

        if (dowork && !interrupted) {
            if (!process_dir(path, instance) && !interrupted) {
                purge(path, instance, max);
            }
            else if (!isdaemon && !interrupted) {
                apr_file_printf(errfile, "An error occurred, cache cleaning "
                                         "aborted." APR_EOL_STR);
                return 1;
            }

            if (intelligent && !interrupted) {
                retries = STAT_ATTEMPTS;
                status = APR_SUCCESS;
                do {
                    if (status != APR_SUCCESS) {
                        apr_sleep(STAT_DELAY);
                    }
                    status = apr_stat(&info, path, APR_FINFO_MTIME, instance);
                } while (status != APR_SUCCESS && !interrupted && --retries);

                if (status == APR_SUCCESS) {
                    previous = info.mtime;
                    intelligent = 2;
                }
                else {
                    intelligent = 1;
                }
            }
        }

        apr_pool_destroy(instance);

        current = apr_time_now();
        if (current < now) {
            delay = repeat;
        }
        else if (current - now >= repeat) {
            delay = repeat;
        }
        else {
            delay = now + repeat - current;
        }

        /* we can't sleep the whole delay time here apiece as this is racy
         * with respect to interrupt delivery - think about what happens
         * if we have tested for an interrupt, then get scheduled
         * before the apr_sleep() call and while waiting for the cpu
         * we do get an interrupt
         */
        if (isdaemon) {
            while (delay && !interrupted) {
                if (delay > APR_USEC_PER_SEC) {
                    apr_sleep(APR_USEC_PER_SEC);
                    delay -= APR_USEC_PER_SEC;
                }
                else {
                    apr_sleep(delay);
   