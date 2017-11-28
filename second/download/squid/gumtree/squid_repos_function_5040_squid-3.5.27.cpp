bool
Ftp::Server::handleCwdRequest(String &cmd, String &params)
{
    changeState(fssHandleCwd, "handleCwdRequest");
    return true;
}