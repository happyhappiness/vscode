void
Ftp::Client::timeout(const CommTimeoutCbParams &io)
{
    debugs(9, 4, io.conn << ": '" << entry->url() << "'" );

    if (abortOnBadEntry("entry went bad while waiting for a timeout"))
        return;

    failed(ERR_READ_TIMEOUT, 0);
    /* failed() closes ctrl.conn and frees ftpState */
}