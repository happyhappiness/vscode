
    delete readBuf;

    if (httpChunkDecoder)
        delete httpChunkDecoder;

    cbdataReferenceDone(_peer);

    debugs(11,5, HERE << "HttpStateData " << this << " destroyed; " << serverConnection);
}

const Comm::ConnectionPointer &
HttpStateData::dataConnection() const
{
    return serverConnection;
}

void
HttpStateData::httpStateConnClosed(const CommCloseCbParams &params)
{
    debugs(11, 5, "httpStateFree: FD " << params.fd << ", httpState=" << params.data);
    mustStop("HttpStateData::httpStateConnClosed");
}

int
httpCachable(const HttpRequestMethod& method)
{
    /* GET and HEAD are cachable. Others are not. */
