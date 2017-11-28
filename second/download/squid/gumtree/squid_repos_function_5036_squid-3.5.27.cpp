bool
Ftp::Server::handleDataRequest(String &cmd, String &params)
{
    if (!checkDataConnPre())
        return false;

    master->userDataDone = 0;
    originDataDownloadAbortedOnError = false;

    changeState(fssHandleDataRequest, "handleDataRequest");

    return true;
}