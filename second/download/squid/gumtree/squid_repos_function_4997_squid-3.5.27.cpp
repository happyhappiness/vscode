void
Ftp::Server::notePeerConnection(Comm::ConnectionPointer conn)
{
    // find request
    ClientSocketContext::Pointer context = getCurrentContext();
    Must(context != NULL);
    ClientHttpRequest *const http = context->http;
    Must(http != NULL);
    HttpRequest *const request = http->request;
    Must(request != NULL);
    // make FTP peer connection exclusive to our request
    pinBusyConnection(conn, request);
}