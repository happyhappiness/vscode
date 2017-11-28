bool
Ftp::Server::handleFeatRequest(String &, String &)
{
    changeState(fssHandleFeat, "handleFeatRequest");
    return true;
}