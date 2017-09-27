{
#ifdef AP_LOG_EXEC
    time_t timevar;
    struct tm *lt;

    if (!log) {
        if ((log = fopen(AP_LOG_EXEC, "a")) == NULL) {
            fprintf(stderr, "suexec failure: could not open log file\n");
            perror("fopen");
            exit(1);
        }
    }

