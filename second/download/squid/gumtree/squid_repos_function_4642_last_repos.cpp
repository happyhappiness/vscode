bool
Ftp::Server::handleRequest(HttpRequest *request)
{
    debugs(33, 9, request);
    Must(request);

    HttpHeader &header = request->header;
    Must(header.has(Http::HdrType::FTP_COMMAND));
    String &cmd = header.findEntry(Http::HdrType::FTP_COMMAND)->value;
    Must(header.has(Http::HdrType::FTP_ARGUMENTS));
    String &params = header.findEntry(Http::HdrType::FTP_ARGUMENTS)->value;

    if (Debug::Enabled(9, 2)) {
        MemBuf mb;
        mb.init();
        request->pack(&mb);

        debugs(9, 2, "FTP Client " << clientConnection);
        debugs(9, 2, "FTP Client REQUEST:\n---------\n" << mb.buf <<
               "\n----------");
    }

    // TODO: When HttpHeader uses SBuf, change keys to SBuf
    typedef std::map<const std::string, RequestHandler> RequestHandlers;
    static RequestHandlers handlers;
    if (!handlers.size()) {
        handlers["LIST"] = &Ftp::Server::handleDataRequest;
        handlers["NLST"] = &Ftp::Server::handleDataRequest;
        handlers["MLSD"] = &Ftp::Server::handleDataRequest;
        handlers["FEAT"] = &Ftp::Server::handleFeatRequest;
        handlers["PASV"] = &Ftp::Server::handlePasvRequest;
        handlers["PORT"] = &Ftp::Server::handlePortRequest;
        handlers["RETR"] = &Ftp::Server::handleDataRequest;
        handlers["EPRT"] = &Ftp::Server::handleEprtRequest;
        handlers["EPSV"] = &Ftp::Server::handleEpsvRequest;
        handlers["CWD"] = &Ftp::Server::handleCwdRequest;
        handlers["PASS"] = &Ftp::Server::handlePassRequest;
        handlers["CDUP"] = &Ftp::Server::handleCdupRequest;
    }

    RequestHandler handler = NULL;
    if (request->method == Http::METHOD_PUT)
        handler = &Ftp::Server::handleUploadRequest;
    else {
        const RequestHandlers::const_iterator hi = handlers.find(cmd.termedBuf());
        if (hi != handlers.end())
            handler = hi->second;
    }

    if (!handler) {
        debugs(9, 7, "forwarding " << cmd << " as is, no post-processing");
        return true;
    }

    return (this->*handler)(cmd, params);
}