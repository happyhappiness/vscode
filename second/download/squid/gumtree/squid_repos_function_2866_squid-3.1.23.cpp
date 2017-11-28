void
HttpRequest::initHTTP(const HttpRequestMethod& aMethod, protocol_t aProtocol, const char *aUrlpath)
{
    method = aMethod;
    protocol = aProtocol;
    urlpath = aUrlpath;
}