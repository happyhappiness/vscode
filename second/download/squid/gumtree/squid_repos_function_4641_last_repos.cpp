void
Ftp::Server::wroteReply(const CommIoCbParams &io)
{
    if (io.flag == Comm::ERR_CLOSING)
        return;

    if (io.flag != Comm::OK) {
        debugs(33, 3, "FTP reply writing failed: " << xstrerr(io.xerrno));
        io.conn->close();
        return;
    }

    Http::StreamPointer context = pipeline.front();
    assert(context->http);
    context->http->out.size += io.size;
    context->http->out.headers_sz += io.size;

    if (master->serverState == fssError) {
        debugs(33, 5, "closing on FTP server error");
        io.conn->close();
        return;
    }

    const clientStream_status_t socketState = context->socketState();
    debugs(33, 5, "FTP client stream state " << socketState);
    switch (socketState) {
    case STREAM_UNPLANNED_COMPLETE:
    case STREAM_FAILED:
        io.conn->close();
        return;

    case STREAM_NONE:
    case STREAM_COMPLETE:
        flags.readMore = true;
        changeState(fssConnected, "Ftp::Server::wroteReply");
        if (bodyParser)
            finishDechunkingRequest(false);
        context->finished();
        kick();
        return;
    }
}