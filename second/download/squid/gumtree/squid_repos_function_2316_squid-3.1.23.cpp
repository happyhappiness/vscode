void
accessLogClose(void)
{
    customlog *log;

    for (log = Config.Log.accesslogs; log; log = log->next) {
        if (log->logfile) {
            logfileClose(log->logfile);
            log->logfile = NULL;
        }
    }

#if HEADERS_LOG

    logfileClose(headerslog);

    headerslog = NULL;

#endif
}