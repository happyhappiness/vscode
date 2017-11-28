void
accessLogRotate(void)
{
    CustomLog *log;
#if USE_FORW_VIA_DB

    fvdbClear();
#endif

    for (log = Config.Log.accesslogs; log; log = log->next) {
        if (log->logfile) {
            logfileRotate(log->logfile);
        }
    }

#if HEADERS_LOG

    logfileRotate(headerslog);

#endif
}