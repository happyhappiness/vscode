void
icapLogOpen()
{
    CustomLog *log;

    for (log = Config.Log.icaplogs; log; log = log->next) {
        if (log->type == Log::Format::CLF_NONE)
            continue;

        log->logfile = logfileOpen(log->filename, log->bufferSize, log->fatal);

        IcapLogfileStatus = LOG_ENABLE;
    }
}