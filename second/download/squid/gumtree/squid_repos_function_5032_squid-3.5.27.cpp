bool
Ftp::Server::handleFeatRequest(String &cmd, String &params)
{
    changeState(fssHandleFeat, "handleFeatRequest");
    return true;
}