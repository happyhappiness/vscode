void
Ftp::Server::notePeerConnection(Comm::ConnectionPointer conn)
{
    // find request
    Http::StreamPointer context = pipeline.front();
    Must(context != nullptr);
    ClientHttpRequest *const http = context->http;
    Must(http != NULL);
    HttpRequest *const request = http->request;
    Must(request != NULL);
    // make FTP peer connection exclusive to our request
    pinBusyConnection(conn, request);
}