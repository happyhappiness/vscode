void
icapLogClose()
{
    CustomLog *log;

    for (log = Config.Log.icaplogs; log; log = log->next) {
        if (log->logfile) {
            logfileClose(log->logfile);
            log->logfile = NULL;
        }
    }
}