bool
Ftp::Server::handlePassRequest(String &, String &)
{
    changeState(fssHandlePass, "handlePassRequest");
    return true;
}