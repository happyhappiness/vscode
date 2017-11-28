static bool
isChunkedRequest(const HttpParser *hp)
{
    HttpRequest request;
    if (!request.parseHeader(HttpParserHdrBuf(hp), HttpParserHdrSz(hp)))
        return false;

    return request.header.chunked();
}