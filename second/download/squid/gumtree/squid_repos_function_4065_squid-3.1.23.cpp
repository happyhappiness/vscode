void
icapLogRotate()
{
    for (customlog* log = Config.Log.icaplogs; log; log = log->next) {
        if (log->logfile) {
            logfileRotate(log->logfile);
        }
    }
}