void
Ftp::Client::writeCommand(const char *buf)
{
    char *ebuf;
    /* trace FTP protocol communications at level 2 */
    debugs(9, 2, "ftp<< " << buf);

    if (Config.Ftp.telnet)
        ebuf = escapeIAC(buf);
    else
        ebuf = xstrdup(buf);

    safe_free(ctrl.last_command);

    safe_free(ctrl.last_reply);

    ctrl.last_command = ebuf;

    if (!Comm::IsConnOpen(ctrl.conn)) {
        debugs(9, 2, "cannot send to closing ctrl " << ctrl.conn);
        // TODO: assert(ctrl.closer != NULL);
        return;
    }

    typedef CommCbMemFunT<Client, CommIoCbParams> Dialer;
    AsyncCall::Pointer call = JobCallback(9, 5, Dialer, this,
                                          Ftp::Client::writeCommandCallback);
    Comm::Write(ctrl.conn, ctrl.last_command, strlen(ctrl.last_command), call, NULL);

    scheduleReadControlReply(0);
}