bool
Ftp::Server::handleEprtRequest(String &cmd, String &params)
{
    debugs(9, 3, "Process an EPRT " << params);

    if (gotEpsvAll) {
        setReply(500, "Rejecting EPRT after EPSV ALL");
        return false;
    }

    if (!params.size()) {
        setReply(501, "Missing parameter");
        return false;
    }

    Ip::Address cltAddr;
    if (!Ftp::ParseProtoIpPort(params.termedBuf(), cltAddr)) {
        setReply(501, "Invalid parameter");
        return false;
    }

    if (!createDataConnection(cltAddr))
        return false;

    changeState(fssHandleEprt, "handleEprtRequest");
    setDataCommand();
    return true; // forward our fake PASV request
}