     fprintf(stderr,
             "to httpd.conf. The generated name will be /some/where.nnnn "
             "where nnnn is the\nsystem time at which the log nominally "
             "starts (N.B. if using a rotation time,\nthe time will always "
             "be a multiple of the rotation time, so you can synchronize\n"
             "cron scripts with it). At the end of each rotation time or "
-            "when the file size\nis reached a new log is started.\n");
+            "when the file size\nis reached a new log is started. If the "
+            "-t option is specified, the specified\nfile will be truncated "
+            "instead of rotated, and is useful where tail is used to\n"
+            "process logs in real time.  If the -L option is specified, "
+            "a hard link will be\nmade from the current log file to the "
+            "specified filename.\n");
     exit(1);
 }
 
-static int get_now(int use_localtime, int utc_offset)
+/*
+ * Get the unix time with timezone corrections
+ * given in the config struct.
+ */
+static int get_now(rotate_config_t *config)
 {
     apr_time_t tNow = apr_time_now();
-    if (use_localtime) {
+    int utc_offset = config->utc_offset;
+    if (config->use_localtime) {
         /* Check for our UTC offset before using it, since it might
          * change if there's a switch between standard and daylight
          * savings time.
          */
         apr_time_exp_t lt;
         apr_time_exp_lt(&lt, tNow);
         utc_offset = lt.tm_gmtoff;
     }
     return (int)apr_time_sec(tNow) + utc_offset;
 }
 
+/*
+ * Close a file and destroy the associated pool.
+ */
+static void closeFile(rotate_config_t *config, apr_pool_t *pool, apr_file_t *file)
+{
+    if (file != NULL) {
+        if (config->verbose) {
+            apr_finfo_t finfo;
+            apr_int32_t wanted = APR_FINFO_NAME;
+            if (apr_file_info_get(&finfo, wanted, file) == APR_SUCCESS) {
+                fprintf(stderr, "Closing file %s (%s)\n", finfo.name, finfo.fname);
+            }
+        }
+        apr_file_close(file);
+        if (pool) {
+            apr_pool_destroy(pool);
+        }
+    }
+}
+
+/*
+ * Dump the configuration parsing result to STDERR.
+ */
+static void dumpConfig (rotate_config_t *config)
+{
+    fprintf(stderr, "Rotation time interval:      %12d\n", config->tRotation);
+    fprintf(stderr, "Rotation size interval:      %12d\n", config->sRotation);
+    fprintf(stderr, "Rotation time UTC offset:    %12d\n", config->utc_offset);
+    fprintf(stderr, "Rotation based on localtime: %12s\n", config->use_localtime ? "yes" : "no");
+    fprintf(stderr, "Rotation file date pattern:  %12s\n", config->use_strftime ? "yes" : "no");
+    fprintf(stderr, "Rotation file forced open:   %12s\n", config->force_open ? "yes" : "no");
+    fprintf(stderr, "Rotation verbose:            %12s\n", config->verbose ? "yes" : "no");
+    fprintf(stderr, "Rotation file name: %21s\n", config->szLogRoot);
+}
+
+/*
+ * Check whether we need to rotate.
+ * Possible reasons are:
+ * - No log file open (ROTATE_NEW)
+ * - User forces us to rotate (ROTATE_FORCE)
+ * - Our log file size is already bigger than the
+ *   allowed maximum (ROTATE_SIZE)
+ * - The next log time interval expired (ROTATE_TIME)
+ *
+ * When size and time constraints are both given,
+ * it suffices that one of them is fulfilled.
+ */
+static void checkRotate(rotate_config_t *config, rotate_status_t *status)
+{
+
+    if (status->nLogFD == NULL) {
+        status->rotateReason = ROTATE_NEW;
+    }
+    else if (config->sRotation) {
+        apr_finfo_t finfo;
+        apr_off_t current_size = -1;
+
+        if (apr_file_info_get(&finfo, APR_FINFO_SIZE, status->nLogFD) == APR_SUCCESS) {
+            current_size = finfo.size;
+        }
+
+        if (current_size > config->sRotation) {
+            status->rotateReason = ROTATE_SIZE;
+        }
+        else if (config->tRotation) {
+            if (get_now(config) >= status->tLogEnd) {
+                status->rotateReason = ROTATE_TIME;
+            }
+        }
+    }
+    else if (config->tRotation) {
+        if (get_now(config) >= status->tLogEnd) {
+            status->rotateReason = ROTATE_TIME;
+        }
+    }
+    else {
+        fprintf(stderr, "No rotation time or size specified\n");
+        exit(2);
+    }
+
+    if (status->rotateReason != ROTATE_NONE && config->verbose) {
+        fprintf(stderr, "File rotation needed, reason: %s\n", ROTATE_REASONS[status->rotateReason]);
+    }
+
+    return;
+}
+
+/*
+ * Open a new log file, and if successful
+ * also close the old one.
+ *
+ * The timestamp for the calculation of the file
+ * name of the new log file will be the actual millisecond
+ * timestamp, except when a regular rotation based on a time
+ * interval is configured and the previous interval
+ * is over. Then the timestamp is the starting time
+ * of the actual interval.
+ */
+static void doRotate(rotate_config_t *config, rotate_status_t *status)
+{
+
+    int now = get_now(config);
+    int tLogStart;
+    apr_status_t rv;
+
+    status->rotateReason = ROTATE_NONE;
+    status->nLogFDprev = status->nLogFD;
+    status->nLogFD = NULL;
+    status->pfile_prev = status->pfile;
+
+    if (config->tRotation) {
+        int tLogEnd;
+        tLogStart = (now / config->tRotation) * config->tRotation;
+        tLogEnd = tLogStart + config->tRotation;
+        /*
+         * Check if rotation was forced and the last rotation
+         * interval is not yet over. Use the value of now instead
+         * of the time interval boundary for the file name then.
+         */
+        if (tLogStart < status->tLogEnd) {
+            tLogStart = now;
+        }
+        status->tLogEnd = tLogEnd;
+    }
+    else {
+        tLogStart = now;
+    }
+
+    if (config->use_strftime) {
+        apr_time_t tNow = apr_time_from_sec(tLogStart);
+        apr_time_exp_t e;
+        apr_size_t rs;
+
+        apr_time_exp_gmt(&e, tNow);
+        apr_strftime(status->filename, &rs, sizeof(status->filename), config->szLogRoot, &e);
+    }
+    else {
+        if (config->truncate) {
+            apr_snprintf(status->filename, sizeof(status->filename), "%s", config->szLogRoot);
+        }
+        else {
+            apr_snprintf(status->filename, sizeof(status->filename), "%s.%010d", config->szLogRoot,
+                    tLogStart);
+        }
+    }
+    apr_pool_create(&status->pfile, status->pool);
+    if (config->verbose) {
+        fprintf(stderr, "Opening file %s\n", status->filename);
+    }
+    rv = apr_file_open(&status->nLogFD, status->filename, APR_WRITE | APR_CREATE | APR_APPEND
+                       | (config->truncate ? APR_TRUNCATE : 0), APR_OS_DEFAULT, status->pfile);
+    if (rv != APR_SUCCESS) {
+        char error[120];
+
+        apr_strerror(rv, error, sizeof error);
+
+        /* Uh-oh. Failed to open the new log file. Try to clear
+         * the previous log file, note the lost log entries,
+         * and keep on truckin'. */
+        if (status->nLogFDprev == NULL) {
+            fprintf(stderr, "Could not open log file '%s' (%s)\n", status->filename, error);
+            exit(2);
+        }
+        else {
+            apr_size_t nWrite;
+            status->nLogFD = status->nLogFDprev;
+            apr_pool_destroy(status->pfile);
+            status->pfile = status->pfile_prev;
+            /* Try to keep this error message constant length
+             * in case it occurs several times. */
+            apr_snprintf(status->errbuf, sizeof status->errbuf,
+                         "Resetting log file due to error opening "
+                         "new log file, %10d messages lost: %-25.25s\n",
+                         status->nMessCount, error);
+            nWrite = strlen(status->errbuf);
+            apr_file_trunc(status->nLogFD, 0);
+            if (apr_file_write(status->nLogFD, status->errbuf, &nWrite) != APR_SUCCESS) {
+                fprintf(stderr, "Error writing to the file %s\n", status->filename);
+                exit(2);
+            }
+        }
+    }
+    else {
+        closeFile(config, status->pfile_prev, status->nLogFDprev);
+        status->nLogFDprev = NULL;
+        status->pfile_prev = NULL;
+    }
+    status->nMessCount = 0;
+    if (config->linkfile) {
+        apr_file_remove(config->linkfile, status->pfile);
+        if (config->verbose) {
+            fprintf(stderr,"Linking %s to %s\n", status->filename, config->linkfile);
+        }
+        rv = apr_file_link(status->filename, config->linkfile);
+        if (rv != APR_SUCCESS) {
+            char error[120];
+            apr_strerror(rv, error, sizeof error);
+            fprintf(stderr, "Error linking file %s to %s (%s)\n",
+                    status->filename, config->linkfile, error);
+            exit(2);
+        }
+    }
+}
+
+/*
+ * Get a size or time param from a string.
+ * Parameter 'last' indicates, whether the
+ * argument is the last commadnline argument.
+ * UTC offset is only allowed as a last argument
+ * in order to make is distinguishable from the
+ * rotation interval time.
+ */
+static const char *get_time_or_size(rotate_config_t *config,
+                                    const char *arg, int last) {
+    char *ptr = NULL;
+    /* Byte multiplier */
+    unsigned int mult = 1;
+    if ((ptr = strchr(arg, 'B')) != NULL) { /* Found KB size */
+        mult = 1;
+    }
+    else if ((ptr = strchr(arg, 'K')) != NULL) { /* Found KB size */
+        mult = 1024;
+    }
+    else if ((ptr = strchr(arg, 'M')) != NULL) { /* Found MB size */
+        mult = 1024 * 1024;
+    }
+    else if ((ptr = strchr(arg, 'G')) != NULL) { /* Found GB size */
+        mult = 1024 * 1024 * 1024;
+    }
+    if (ptr) { /* rotation based on file size */
+        if (config->sRotation > 0) {
+            return "Rotation size parameter allowed only once";
+        }
+        if (*(ptr+1) == '\0') {
+            config->sRotation = atoi(arg) * mult;
+        }
+        if (config->sRotation == 0) {
+            return "Invalid rotation size parameter";
+        }
+    }
+    else if ((config->sRotation > 0 || config->tRotation > 0) && last) {
+        /* rotation based on elapsed time */
+        if (config->use_localtime) {
+            return "UTC offset parameter is not valid with -l";
+        }
+        config->utc_offset = atoi(arg) * 60;
+    }
+    else { /* rotation based on elapsed time */
+        if (config->tRotation > 0) {
+            return "Rotation time parameter allowed only once";
+        }
+        config->tRotation = atoi(arg);
+        if (config->tRotation <= 0) {
+            return "Invalid rotation time parameter";
+        }
+    }
+    return NULL;
+}
+
 int main (int argc, const char * const argv[])
 {
-    char buf[BUFSIZE], buf2[MAX_PATH], errbuf[ERRMSGSZ];
-    int tLogEnd = 0, tRotation = 0, utc_offset = 0;
-    unsigned int sRotation = 0;
-    int nMessCount = 0;
+    char buf[BUFSIZE];
     apr_size_t nRead, nWrite;
-    int use_strftime = 0;
-    int use_localtime = 0;
-    int bypass_io = 0;
-    int now = 0;
-    const char *szLogRoot;
-    apr_file_t *f_stdin, *nLogFD = NULL, *nLogFDprev = NULL;
-    apr_pool_t *pool;
-    apr_pool_t *pfile = NULL;
-    apr_pool_t *pfile_prev = NULL;
+    apr_file_t *f_stdin;
     apr_getopt_t *opt;
     apr_status_t rv;
     char c;
     const char *optarg;
-    char *ptr = NULL;
+    const char *err = NULL;
 
     apr_app_initialize(&argc, &argv, NULL);
     atexit(apr_terminate);
 
-    apr_pool_create(&pool, NULL);
-    apr_getopt_init(&opt, pool, argc, argv);
-    while ((rv = apr_getopt(opt, "lf", &c, &optarg)) == APR_SUCCESS) {
+    config.sRotation = 0;
+    config.tRotation = 0;
+    config.utc_offset = 0;
+    config.use_localtime = 0;
+    config.use_strftime = 0;
+    config.force_open = 0;
+    config.verbose = 0;
+    status.pool = NULL;
+    status.pfile = NULL;
+    status.pfile_prev = NULL;
+    status.nLogFD = NULL;
+    status.nLogFDprev = NULL;
+    status.tLogEnd = 0;
+    status.rotateReason = ROTATE_NONE;
+    status.nMessCount = 0;
+
+    apr_pool_create(&status.pool, NULL);
+    apr_getopt_init(&opt, status.pool, argc, argv);
+    while ((rv = apr_getopt(opt, "lL:ftv", &c, &optarg)) == APR_SUCCESS) {
         switch (c) {
         case 'l':
-            use_localtime = 1;
+            config.use_localtime = 1;
+            break;
+        case 'L':
+            config.linkfile = optarg;
             break;
         case 'f':
-            bypass_io = 1;
+            config.force_open = 1;
+            break;
+        case 't':
+            config.truncate = 1;
+            break;
+        case 'v':
+            config.verbose = 1;
             break;
         }
     }
 
     if (rv != APR_EOF) {
         usage(argv[0], NULL /* specific error message already issued */ );
     }
 
-    if (opt->ind + 2 != argc && opt->ind + 3 != argc) {
+    /*
+     * After the initial flags we need 2 to 4 arguments,
+     * the file name, either the rotation interval time or size
+     * or both of them, and optionally the UTC offset.
+     */
+    if ((argc - opt->ind < 2) || (argc - opt->ind > 4) ) {
         usage(argv[0], "Incorrect number of arguments");
     }
 
-    szLogRoot = argv[opt->ind++];
+    config.szLogRoot = argv[opt->ind++];
 
-    ptr = strchr(argv[opt->ind], 'M');
-    if (ptr) { /* rotation based on file size */
-        if (*(ptr+1) == '\0') {
-            sRotation = atoi(argv[opt->ind]) * 1048576;
-        }
-        if (sRotation == 0) {
-            usage(argv[0], "Invalid rotation size parameter");
+    /* Read in the remaining flags, namely time, size and UTC offset. */
+    for(; opt->ind < argc; opt->ind++) {
+        if ((err = get_time_or_size(&config, argv[opt->ind],
+                                    opt->ind < argc - 1 ? 0 : 1)) != NULL) {
+            usage(argv[0], err);
         }
     }
-    else { /* rotation based on elapsed time */
-        tRotation = atoi(argv[opt->ind]);
-        if (tRotation <= 0) {
-            usage(argv[0], "Invalid rotation time parameter");
-        }
-    }
-    opt->ind++;
 
-    if (opt->ind < argc) { /* have UTC offset */
-        if (use_localtime) {
-            usage(argv[0], "UTC offset parameter is not valid with -l");
-        }
-        utc_offset = atoi(argv[opt->ind]) * 60;
-    }
+    config.use_strftime = (strchr(config.szLogRoot, '%') != NULL);
 
-    use_strftime = (strchr(szLogRoot, '%') != NULL);
-    if (apr_file_open_stdin(&f_stdin, pool) != APR_SUCCESS) {
+    if (apr_file_open_stdin(&f_stdin, status.pool) != APR_SUCCESS) {
         fprintf(stderr, "Unable to open stdin\n");
         exit(1);
     }
 
-    for (;;) {
-        nRead = sizeof(buf);
-        /*
-         * Bypass reading stdin if we are forcing the logfile
-         * to be opened as soon as we start. Since we won't be
-         * writing anything, we just want to open the file.
-         * First time through is the only time we do this
-         * since we reset bypass_io after the 1st loop
-         */
-        if (!bypass_io) {
-            if (apr_file_read(f_stdin, buf, &nRead) != APR_SUCCESS) {
-                exit(3);
-            }
-        }
-        if (tRotation) {
-            now = get_now(use_localtime, utc_offset);
-            if (nLogFD != NULL && now >= tLogEnd) {
-                nLogFDprev = nLogFD;
-                nLogFD = NULL;
-            }
-        }
-        else if (sRotation) {
-            apr_finfo_t finfo;
-            apr_off_t current_size = -1;
-
-            if ((nLogFD != NULL) &&
-                (apr_file_info_get(&finfo, APR_FINFO_SIZE, nLogFD) == APR_SUCCESS)) {
-                current_size = finfo.size;
-            }
-
-            if (current_size > sRotation) {
-                nLogFDprev = nLogFD;
-                nLogFD = NULL;
-            }
-        }
-        else {
-            fprintf(stderr, "No rotation time or size specified\n");
-            exit(2);
-        }
-
-        if (nLogFD == NULL) {
-            int tLogStart;
-            apr_status_t rv;
+    /*
+     * Write out result of config parsing if verbose is set.
+     */
+    if (config.verbose) {
+        dumpConfig(&config);
+    }
 
-            if (tRotation) {
-                tLogStart = (now / tRotation) * tRotation;
-            }
-            else {
-                tLogStart = get_now(use_localtime, utc_offset);
-            }
+    /*
+     * Immediately open the logfile as we start, if we were forced
+     * to do so via '-f'.
+     */
+    if (config.force_open) {
+        doRotate(&config, &status);
+    }
 
-            if (use_strftime) {
-                apr_time_t tNow = apr_time_from_sec(tLogStart);
-                apr_time_exp_t e;
-                apr_size_t rs;
+    for (;;) {
+        nRead = sizeof(buf);
+        rv = apr_file_read(f_stdin, buf, &nRead);
+        if (rv != APR_SUCCESS) {
+            exit(3);
+        }
+        checkRotate(&config, &status);
+        if (status.rotateReason != ROTATE_NONE) {
+            doRotate(&config, &status);
+        }
+
+        nWrite = nRead;
+        rv = apr_file_write(status.nLogFD, buf, &nWrite);
+        if (rv == APR_SUCCESS && nWrite != nRead) {
+            /* buffer partially written, which for rotatelogs means we encountered
+             * an error such as out of space or quota or some other limit reached;
+             * try to write the rest so we get the real error code
+             */
+            apr_size_t nWritten = nWrite;
 
-                apr_time_exp_gmt(&e, tNow);
-                apr_strftime(buf2, &rs, sizeof(buf2), szLogRoot, &e);
-            }
-            else {
-                apr_snprintf(buf2, sizeof(buf2), "%s.%010d", szLogRoot, tLogStart);
-            }
-            tLogEnd = tLogStart + tRotation;
-            pfile_prev = pfile;
-            apr_pool_create(&pfile, pool);
-            rv = apr_file_open(&nLogFD, buf2, APR_WRITE | APR_CREATE | APR_APPEND,
-                               APR_OS_DEFAULT, pfile);
-            if (rv != APR_SUCCESS) {
-                char error[120];
-
-                apr_strerror(rv, error, sizeof error);
-
-                /* Uh-oh. Failed to open the new log file. Try to clear
-                 * the previous log file, note the lost log entries,
-                 * and keep on truckin'. */
-                if (nLogFDprev == NULL) {
-                    fprintf(stderr, "Could not open log file '%s' (%s)\n", buf2, error);
-                    exit(2);
-                }
-                else {
-                    nLogFD = nLogFDprev;
-                    apr_pool_destroy(pfile);
-                    pfile = pfile_prev;
-                    /* Try to keep this error message constant length
-                     * in case it occurs several times. */
-                    apr_snprintf(errbuf, sizeof errbuf,
-                                 "Resetting log file due to error opening "
-                                 "new log file, %10d messages lost: %-25.25s\n",
-                                 nMessCount, error);
-                    nWrite = strlen(errbuf);
-                    apr_file_trunc(nLogFD, 0);
-                    if (apr_file_write(nLogFD, errbuf, &nWrite) != APR_SUCCESS) {
-                        fprintf(stderr, "Error writing to the file %s\n", buf2);
-                        exit(2);
-                    }
-                }
-            }
-            else if (nLogFDprev) {
-                apr_file_close(nLogFDprev);
-                if (pfile_prev) {
-                    apr_pool_destroy(pfile_prev);
-                }
-            }
-            nMessCount = 0;
-        }
-        /*
-         * If we just bypassed reading stdin, due to bypass_io,
-         * then we have nothing to write, so skip this.
-         */
-        if (!bypass_io) {
+            nRead  = nRead - nWritten;
             nWrite = nRead;
-            rv = apr_file_write(nLogFD, buf, &nWrite);
-            if (rv == APR_SUCCESS && nWrite != nRead) {
-                /* buffer partially written, which for rotatelogs means we encountered
-                 * an error such as out of space or quota or some other limit reached;
-                 * try to write the rest so we get the real error code
-                 */
-                apr_size_t nWritten = nWrite;
-
-                nRead  = nRead - nWritten;
-                nWrite = nRead;
-                rv = apr_file_write(nLogFD, buf + nWritten, &nWrite);
-            }
-            if (nWrite != nRead) {
-                char strerrbuf[120];
-                apr_off_t cur_offset;
-                
-                cur_offset = 0;
-                if (apr_file_seek(nLogFD, APR_CUR, &cur_offset) != APR_SUCCESS) {
-                    cur_offset = -1;
-                }
-                apr_strerror(rv, strerrbuf, sizeof strerrbuf);
-                nMessCount++;
-                apr_snprintf(errbuf, sizeof errbuf,
-                             "Error %d writing to log file at offset %" APR_OFF_T_FMT ". "
-                             "%10d messages lost (%s)\n",
-                             rv, cur_offset, nMessCount, strerrbuf);
-                nWrite = strlen(errbuf);
-                apr_file_trunc(nLogFD, 0);
-                if (apr_file_write(nLogFD, errbuf, &nWrite) != APR_SUCCESS) {
-                    fprintf(stderr, "Error writing to the file %s\n", buf2);
+            rv = apr_file_write(status.nLogFD, buf + nWritten, &nWrite);
+        }
+        if (nWrite != nRead) {
+            char strerrbuf[120];
+            apr_off_t cur_offset;
+
+            cur_offset = 0;
+            if (apr_file_seek(status.nLogFD, APR_CUR, &cur_offset) != APR_SUCCESS) {
+                cur_offset = -1;
+            }
+            apr_strerror(rv, strerrbuf, sizeof strerrbuf);
+            status.nMessCount++;
+            apr_snprintf(status.errbuf, sizeof status.errbuf,
+                         "Error %d writing to log file at offset %" APR_OFF_T_FMT ". "
+                         "%10d messages lost (%s)\n",
+                         rv, cur_offset, status.nMessCount, strerrbuf);
+            nWrite = strlen(status.errbuf);
+            apr_file_trunc(status.nLogFD, 0);
+            if (apr_file_write(status.nLogFD, status.errbuf, &nWrite) != APR_SUCCESS) {
+                fprintf(stderr, "Error writing to the file %s\n", status.filename);
                 exit(2);
-                }
-            }
-            else {
-                nMessCount++;
             }
         }
         else {
-           /* now worry about reading 'n writing all the time */
-           bypass_io = 0;
+            status.nMessCount++;
         }
     }
     /* Of course we never, but prevent compiler warnings */
     return 0;
 }
