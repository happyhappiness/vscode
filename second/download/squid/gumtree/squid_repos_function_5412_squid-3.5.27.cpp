void
Ftp::Relay::readFeatReply()
{
    assert(serverState() == fssHandleFeat);

    if (100 <= ctrl.replycode && ctrl.replycode < 200)
        return; // ignore preliminary replies

    forwardReply();
}