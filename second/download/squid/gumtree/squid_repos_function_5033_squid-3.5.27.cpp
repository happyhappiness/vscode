bool
Ftp::Server::handlePasvRequest(String &cmd, String &params)
{
    if (gotEpsvAll) {
        setReply(500, "Bad PASV command");
        return false;
    }

    if (params.size() > 0) {
        setReply(501, "Unexpected parameter");
        return false;
    }

    changeState(fssHandlePasv, "handlePasvRequest");
    // no need to fake PASV request via setDataCommand() in true PASV case
    return true;
}