void
Ftp::Relay::sendCommand()
{
    if (!fwd->request->header.has(HDR_FTP_COMMAND)) {
        abortAll("Internal error: FTP relay request with no command");
        return;
    }

    HttpHeader &header = fwd->request->header;
    assert(header.has(HDR_FTP_COMMAND));
    const String &cmd = header.findEntry(HDR_FTP_COMMAND)->value;
    assert(header.has(HDR_FTP_ARGUMENTS));
    const String &params = header.findEntry(HDR_FTP_ARGUMENTS)->value;

    if (params.size() > 0)
        debugs(9, 5, "command: " << cmd << ", parameters: " << params);
    else
        debugs(9, 5, "command: " << cmd << ", no parameters");

    if (serverState() == fssHandlePasv ||
            serverState() == fssHandleEpsv ||
            serverState() == fssHandleEprt ||
            serverState() == fssHandlePort) {
        sendPassive();
        return;
    }

    SBuf buf;
    if (params.size() > 0)
        buf.Printf("%s %s%s", cmd.termedBuf(), params.termedBuf(), Ftp::crlf);
    else
        buf.Printf("%s%s", cmd.termedBuf(), Ftp::crlf);

    writeCommand(buf.c_str());

    state =
        serverState() == fssHandleCdup ? SENT_CDUP :
        serverState() == fssHandleCwd ? SENT_CWD :
        serverState() == fssHandleFeat ? SENT_FEAT :
        serverState() == fssHandleDataRequest ? SENT_DATA_REQUEST :
        serverState() == fssHandleUploadRequest ? SENT_DATA_REQUEST :
        serverState() == fssConnected ? SENT_USER :
        serverState() == fssHandlePass ? SENT_PASS :
        SENT_COMMAND;

    if (state == SENT_DATA_REQUEST) {
        CbcPointer<ConnStateData> &mgr = fwd->request->clientConnectionManager;
        if (mgr.valid()) {
            if (Ftp::Server *srv = dynamic_cast<Ftp::Server*>(mgr.get())) {
                typedef NullaryMemFunT<Ftp::Server> CbDialer;
                AsyncCall::Pointer call = JobCallback(11, 3, CbDialer, srv,
                                                      Ftp::Server::startWaitingForOrigin);
                ScheduleCallHere(call);
                originWaitInProgress = true;
            }
        }
    }
}