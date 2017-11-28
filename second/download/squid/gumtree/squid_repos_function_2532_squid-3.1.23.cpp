void
FtpStateData::handleControlReply()
{
    wordlist **W;
    size_t bytes_used = 0;
    wordlistDestroy(&ctrl.message);
    ctrl.message = ftpParseControlReply(ctrl.buf,
                                        ctrl.offset, &ctrl.replycode, &bytes_used);

    if (ctrl.message == NULL) {
        /* didn't get complete reply yet */

        if (ctrl.offset == ctrl.size) {
            ctrl.buf = (char *)memReallocBuf(ctrl.buf, ctrl.size << 1, &ctrl.size);
        }

        scheduleReadControlReply(0);
        return;
    } else if (ctrl.offset == bytes_used) {
        /* used it all up */
        ctrl.offset = 0;
    } else {
        /* Got some data past the complete reply */
        assert(bytes_used < ctrl.offset);
        ctrl.offset -= bytes_used;
        xmemmove(ctrl.buf, ctrl.buf + bytes_used,
                 ctrl.offset);
    }

    /* Move the last line of the reply message to ctrl.last_reply */
    for (W = &ctrl.message; (*W)->next; W = &(*W)->next);
    safe_free(ctrl.last_reply);

    ctrl.last_reply = xstrdup((*W)->key);

    wordlistDestroy(W);

    /* Copy the rest of the message to cwd_message to be printed in
     * error messages
     */
    wordlistAddWl(&cwd_message, ctrl.message);

    debugs(9, 3, HERE << "state=" << state << ", code=" << ctrl.replycode);

    FTP_SM_FUNCS[state] (this);
}