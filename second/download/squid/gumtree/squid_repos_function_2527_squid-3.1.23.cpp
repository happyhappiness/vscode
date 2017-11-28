void
FtpStateData::writeCommand(const char *buf)
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

    if (!canSend(ctrl.fd)) {
        debugs(9, 2, HERE << "cannot send to closing ctrl FD " << ctrl.fd);
        // TODO: assert(ctrl.closer != NULL);
        return;
    }

    typedef CommCbMemFunT<FtpStateData, CommIoCbParams> Dialer;
    AsyncCall::Pointer call = JobCallback(9, 5,
                                          Dialer, this, FtpStateData::ftpWriteCommandCallback);
    comm_write(ctrl.fd,
               ctrl.last_command,
               strlen(ctrl.last_command),
               call);

    scheduleReadControlReply(0);
}