void
Ftp::Relay::readTransferDoneReply()
{
    debugs(9, 3, status());

    if (ctrl.replycode != 226 && ctrl.replycode != 250) {
        debugs(9, DBG_IMPORTANT, "got FTP code " << ctrl.replycode <<
               " after reading response data");
    }

    debugs(9, 2, "Complete data downloading");

    serverComplete();
}