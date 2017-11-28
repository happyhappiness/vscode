void
Ftp::Server::wroteEarlyReply(const CommIoCbParams &io)
{
    if (io.flag == Comm::ERR_CLOSING)
        return;

    if (io.flag != Comm::OK) {
        debugs(33, 3, "FTP reply writing failed: " << xstrerr(io.xerrno));
        io.conn->close();
        return;
    }

    ClientSocketContext::Pointer context = getCurrentContext();
    if (context != NULL && context->http) {
        context->http->out.size += io.size;
        context->http->out.headers_sz += io.size;
    }

    flags.readMore = true;
    readSomeData();
}