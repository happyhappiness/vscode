static void
ftpReadEPSV(Ftp::Gateway* ftpState)
{
    Ip::Address srvAddr; // unused
    if (ftpState->handleEpsvReply(srvAddr)) {
        if (ftpState->ctrl.message == NULL)
            return; // didn't get complete reply yet

        ftpState->connectDataChannel();
    }
}