void
Ftp::Gateway::timeout(const CommTimeoutCbParams &io)
{
    if (SENT_PASV == state) {
        /* stupid ftp.netscape.com, of FTP server behind stupid firewall rules */
        flags.pasv_supported = false;
        debugs(9, DBG_IMPORTANT, "FTP Gateway timeout in SENT_PASV state");

        // cancel the data connection setup.
        if (data.opener != NULL) {
            data.opener->cancel("timeout");
            data.opener = NULL;
        }
        data.close();
    }

    Ftp::Client::timeout(io);
}