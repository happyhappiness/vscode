bool
Ftp::Server::handleCdupRequest(String &, String &)
{
    changeState(fssHandleCdup, "handleCdupRequest");
    return true;
}