void
icapLogOpen()
{
    customlog *log;

    for (log = Config.Log.icaplogs; log; log = log->next) {
        if (log->type == CLF_NONE)
            continue;

        if (log->type == CLF_AUTO)
            log->type = CLF_ICAP_SQUID;

        log->logfile = logfileOpen(log->filename, MAX_URL << 1, 1);

        IcapLogfileStatus = LOG_ENABLE;
    }
}