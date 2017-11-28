bool
Ftp::Server::handlePassRequest(String &cmd, String &params)
{
    changeState(fssHandlePass, "handlePassRequest");
    return true;
}