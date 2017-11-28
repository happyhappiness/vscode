bool
Ftp::Server::handlePortRequest(String &cmd, String &params)
{
    // TODO: Should PORT errors trigger closeDataConnection() cleanup?

    if (gotEpsvAll) {
        setReply(500, "Rejecting PORT after EPSV ALL");
        return false;
    }

    if (!params.size()) {
        setReply(501, "Missing parameter");
        return false;
    }

    Ip::Address cltAddr;
    if (!Ftp::ParseIpPort(params.termedBuf(), NULL, cltAddr)) {
        setReply(501, "Invalid parameter");
        return false;
    }

    if (!createDataConnection(cltAddr))
        return false;

    changeState(fssHandlePort, "handlePortRequest");
    setDataCommand();
    return true; // forward our fake PASV request
}