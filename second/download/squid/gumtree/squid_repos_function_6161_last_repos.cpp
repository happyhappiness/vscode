void
accessLogRotate(void)
{
    CustomLog *log;
#if USE_FORW_VIA_DB

    fvdbClear();
#endif

    for (log = Config.Log.accesslogs; log; log = log->next) {
        if (log->logfile) {
            int16_t rc = (log->rotateCount >= 0 ? log->rotateCount : Config.Log.rotateNumber);
            logfileRotate(log->logfile, rc);
        }
    }

#if HEADERS_LOG

    logfileRotate(headerslog, Config.Log.rotateNumber);

#endif
}