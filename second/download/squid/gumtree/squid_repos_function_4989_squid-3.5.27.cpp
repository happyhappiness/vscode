void
Ftp::Server::processParsedRequest(ClientSocketContext *context, const Http::ProtocolVersion &)
{
    Must(getConcurrentRequestCount() == 1);

    // Process FTP request asynchronously to make sure FTP
    // data connection accept callback is fired first.
    CallJobHere(33, 4, CbcPointer<Server>(this),
                Ftp::Server, doProcessRequest);
}