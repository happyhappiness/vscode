static void
ftpReadPasv(Ftp::Gateway * ftpState)
{
    Ip::Address srvAddr; // unused
    if (ftpState->handlePasvReply(srvAddr))
        ftpState->connectDataChannel();
    else {
        ftpFail(ftpState);
        // Currently disabled, does not work correctly:
        // ftpSendEPRT(ftpState);
        return;
    }
}