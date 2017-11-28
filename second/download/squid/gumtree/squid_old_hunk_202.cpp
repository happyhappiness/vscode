
    delete readBuf;

    if (httpChunkDecoder)
        delete httpChunkDecoder;

    HTTPMSGUNLOCK(orig_request);

    debugs(11,5, HERE << "HttpStateData " << this << " destroyed; FD " << fd);
}

int
HttpStateData::dataDescriptor() const
{
    return fd;
}
/*
static void
httpStateFree(int fd, void *data)
{
    HttpStateData *httpState = static_cast<HttpStateData *>(data);
    debugs(11, 5, "httpStateFree: FD " << fd << ", httpState=" << data);
    delete httpState;
}*/

void
HttpStateData::httpStateConnClosed(const CommCloseCbParams &params)
{
    debugs(11, 5, "httpStateFree: FD " << params.fd << ", httpState=" << params.data);
    deleteThis("HttpStateData::httpStateConnClosed");
}

int
httpCachable(const HttpRequestMethod& method)
{
    /* GET and HEAD are cachable. Others are not. */
