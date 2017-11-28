void
Ftp::Server::writeForwardedForeign(const HttpReply *reply)
{
    changeState(fssConnected, "foreign reply");
    closeDataConnection();
    // 451: We intend to keep the control connection open.
    writeErrorReply(reply, 451);
}