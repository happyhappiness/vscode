void
Ftp::Relay::stopDirTracking()
{
    debugs(9, 5, "got code from pwd: " << ctrl.replycode << ", msg: " << ctrl.last_reply);

    if (ctrl.replycode == 257)
        updateMaster().workingDir = Ftp::UnescapeDoubleQuoted(ctrl.last_reply);

    wordlistDestroy(&ctrl.message);
    safe_free(ctrl.last_command);
    safe_free(ctrl.last_reply);

    ctrl.message = savedReply.message;
    ctrl.last_command = savedReply.lastCommand;
    ctrl.last_reply = savedReply.lastReply;
    ctrl.replycode = savedReply.replyCode;

    savedReply.message = NULL;
    savedReply.lastReply = NULL;
    savedReply.lastCommand = NULL;
}