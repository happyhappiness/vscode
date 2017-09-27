                if (nLogFDprev == NULL) {
                    fprintf(stderr, "Could not open log file '%s' (%s)\n", buf2, error);
                    exit(2);
                }
                else {
                    nLogFD = nLogFDprev;
                    apr_pool_destroy(pfile);
                    pfile = pfile_prev;
                    /* Try to keep this error message constant length
                     * in case it occurs several times. */
                    apr_snprintf(errbuf, sizeof errbuf,
                                 "Resetting log file due to error opening "
                                 "new log file, %10d messages lost: %-25.25s\n",
                                 nMessCount, error);
