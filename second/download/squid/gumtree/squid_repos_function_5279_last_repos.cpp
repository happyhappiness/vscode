void
Ftp::Relay::readCwdOrCdupReply()
{
    assert(serverState() == fssHandleCwd ||
           serverState() == fssHandleCdup);

    debugs(9, 5, "got code " << ctrl.replycode << ", msg: " << ctrl.last_reply);

    if (100 <= ctrl.replycode && ctrl.replycode < 200)
        return;

    if (weAreTrackingDir()) { // we are tracking
        stopDirTracking(); // and forward the delayed response below
    } else if (startDirTracking())
        return;

    forwardReply();
}