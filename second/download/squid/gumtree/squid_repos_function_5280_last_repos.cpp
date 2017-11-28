void
Ftp::Relay::readUserOrPassReply()
{
    if (100 <= ctrl.replycode && ctrl.replycode < 200)
        return; //Just ignore

    if (weAreTrackingDir()) { // we are tracking
        stopDirTracking(); // and forward the delayed response below
    } else if (ctrl.replycode == 230) { // successful login
        if (startDirTracking())
            return;
    }

    forwardReply();
}