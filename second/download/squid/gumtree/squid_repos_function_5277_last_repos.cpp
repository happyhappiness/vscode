bool
Ftp::Relay::startDirTracking()
{
    if (!fwd->request->clientConnectionManager->port->ftp_track_dirs)
        return false;

    debugs(9, 5, "start directory tracking");
    savedReply.message = ctrl.message;
    savedReply.lastCommand = ctrl.last_command;
    savedReply.lastReply = ctrl.last_reply;
    savedReply.replyCode = ctrl.replycode;

    ctrl.last_command = NULL;
    ctrl.last_reply = NULL;
    ctrl.message = NULL;
    ctrl.offset = 0;
    writeCommand("PWD\r\n");
    return true;
}