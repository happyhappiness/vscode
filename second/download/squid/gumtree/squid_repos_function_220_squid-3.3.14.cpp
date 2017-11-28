static void open_log(const char *logfilename)
{
    logfile = fopen(logfilename, "a");
    if ( logfile == NULL ) {
        perror(logfilename);
        logfile = stderr;
    }
}