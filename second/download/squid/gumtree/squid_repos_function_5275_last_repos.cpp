void
Ftp::Relay::readEpsvReply()
{
    if (100 <= ctrl.replycode && ctrl.replycode < 200)
        return; // ignore preliminary replies

    if (handleEpsvReply(updateMaster().clientDataAddr)) {
        if (ctrl.message == NULL)
            return; // didn't get complete reply yet

        forwardReply();
    } else
        forwardError();
}