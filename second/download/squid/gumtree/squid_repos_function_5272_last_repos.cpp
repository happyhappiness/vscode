void
Ftp::Relay::readReply()
{
    assert(serverState() == fssConnected ||
           serverState() == fssHandleUploadRequest);

    if (100 <= ctrl.replycode && ctrl.replycode < 200)
        forwardPreliminaryReply(&Ftp::Relay::scheduleReadControlReply);
    else
        forwardReply();
}