void
Ftp::Server::processParsedRequest(Http::StreamPointer &)
{
    Must(pipeline.count() == 1);

    // Process FTP request asynchronously to make sure FTP
    // data connection accept callback is fired first.
    CallJobHere(33, 4, CbcPointer<Server>(this),
                Ftp::Server, doProcessRequest);
}