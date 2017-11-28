bool
Ftp::Server::handleCwdRequest(String &, String &)
{
    changeState(fssHandleCwd, "handleCwdRequest");
    return true;
}