void
icapLogRotate()
{
    for (CustomLog* log = Config.Log.icaplogs; log; log = log->next) {
        if (log->logfile) {
            logfileRotate(log->logfile, Config.Log.rotateNumber);
        }
    }
}