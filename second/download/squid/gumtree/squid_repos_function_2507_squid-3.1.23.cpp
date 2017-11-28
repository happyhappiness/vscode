void
FtpStateData::ftpTimeout(const CommTimeoutCbParams &io)
{
    debugs(9, 4, "ftpTimeout: FD " << io.fd << ": '" << entry->url() << "'" );

    if (SENT_PASV == state && io.fd == data.fd) {
        /* stupid ftp.netscape.com */
        fwd->dontRetry(false);
        fwd->ftpPasvFailed(true);
        debugs(9, DBG_IMPORTANT, "ftpTimeout: timeout in SENT_PASV state" );
    }

    failed(ERR_READ_TIMEOUT, 0);
    /* failed() closes ctrl.fd and frees ftpState */
}