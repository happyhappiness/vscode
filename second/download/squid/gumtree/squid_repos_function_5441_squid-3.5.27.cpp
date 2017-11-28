void
Ftp::Client::handleControlReply()
{
    debugs(9, 3, status());

    size_t bytes_used = 0;
    wordlistDestroy(&ctrl.message);

    if (!parseControlReply(bytes_used)) {
        /* didn't get complete reply yet */

        if (ctrl.offset == ctrl.size) {
            ctrl.buf = static_cast<char*>(memReallocBuf(ctrl.buf, ctrl.size << 1, &ctrl.size));
        }

        scheduleReadControlReply(0);
        return;
    }

    assert(ctrl.message); // the entire FTP server response, line by line
    assert(ctrl.replycode >= 0); // FTP status code (from the last line)
    assert(ctrl.last_reply); // FTP reason (from the last line)

    if (ctrl.offset == bytes_used) {
        /* used it all up */
        ctrl.offset = 0;
    } else {
        /* Got some data past the complete reply */
        assert(bytes_used < ctrl.offset);
        ctrl.offset -= bytes_used;
        memmove(ctrl.buf, ctrl.buf + bytes_used, ctrl.offset);
    }

    debugs(9, 3, "state=" << state << ", code=" << ctrl.replycode);
}