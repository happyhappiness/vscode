static void
debugOpenLog(const char *logfile)
{
    if (logfile == NULL) {
        debug_log = stderr;
        return;
    }

    if (debug_log_file)
        xfree(debug_log_file);

    debug_log_file = xstrdup(logfile);  /* keep a static copy */

    if (debug_log && debug_log != stderr)
        fclose(debug_log);

    // Bug 4423: ignore the stdio: logging module name if present
    const char *logfilename;
    if (strncmp(logfile, "stdio:",6) == 0)
        logfilename = logfile + 6;
    else
        logfilename = logfile;

    debug_log = fopen(logfilename, "a+");

    if (!debug_log) {
        fprintf(stderr, "WARNING: Cannot write log file: %s\n", logfile);
        perror(logfile);
        fprintf(stderr, "         messages will be sent to 'stderr'.\n");
        fflush(stderr);
        debug_log = stderr;
    }

#if _SQUID_WINDOWS_
    setmode(fileno(debug_log), O_TEXT);
#endif
}