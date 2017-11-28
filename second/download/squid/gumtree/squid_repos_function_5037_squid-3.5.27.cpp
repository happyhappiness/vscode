bool
Ftp::Server::handleUploadRequest(String &cmd, String &params)
{
    if (!checkDataConnPre())
        return false;

    changeState(fssHandleUploadRequest, "handleDataRequest");

    return true;
}