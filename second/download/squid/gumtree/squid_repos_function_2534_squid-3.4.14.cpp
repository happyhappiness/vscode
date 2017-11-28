void
FtpStateData::ftpTimeout(const CommTimeoutCbParams &io)
{
    debugs(9, 4, HERE << io.conn << ": '" << entry->url() << "'" );

    if (abortOnBadEntry("entry went bad while waiting for a timeout"))
        return;

    if (SENT_PASV == state) {
        /* stupid ftp.netscape.com, of FTP server behind stupid firewall rules */
        flags.pasv_supported = false;
        debugs(9, DBG_IMPORTANT, "ftpTimeout: timeout in SENT_PASV state" );

        // cancel the data connection setup.
        if (data.opener != NULL) {
            data.opener->cancel("timeout");
            data.opener = NULL;
        }
        data.close();
    }

    failed(ERR_READ_TIMEOUT, 0);
    /* failed() closes ctrl.conn and frees ftpState */
}