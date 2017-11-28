
    debug_log_file = xstrdup(logfile);	/* keep a static copy */

    if (debug_log && debug_log != stderr)
        fclose(debug_log);

    debug_log = fopen(logfile, "a+");

    if (!debug_log) {
        fprintf(stderr, "WARNING: Cannot write log file: %s\n", logfile);
        perror(logfile);
        fprintf(stderr, "         messages will be sent to 'stderr'.\n");
        fflush(stderr);
