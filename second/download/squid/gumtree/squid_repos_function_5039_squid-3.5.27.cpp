bool
Ftp::Server::handleEpsvRequest(String &cmd, String &params)
{
    debugs(9, 3, "Process an EPSV command with params: " << params);
    if (params.size() <= 0) {
        // treat parameterless EPSV as "use the protocol of the ctrl conn"
    } else if (params.caseCmp("ALL") == 0) {
        setReply(200, "EPSV ALL ok");
        gotEpsvAll = true;
        return false;
    } else if (params.cmp("2") == 0) {
        if (!Ip::EnableIpv6) {
            setReply(522, "Network protocol not supported, use (1)");
            return false;
        }
    } else if (params.cmp("1") != 0) {
        setReply(501, "Unsupported EPSV parameter");
        return false;
    }

    changeState(fssHandleEpsv, "handleEpsvRequest");
    setDataCommand();
    return true; // forward our fake PASV request
}