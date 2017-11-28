bool
Ftp::Server::handleCdupRequest(String &cmd, String &params)
{
    changeState(fssHandleCdup, "handleCdupRequest");
    return true;
}