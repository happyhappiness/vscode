void
HttpRequest::initHTTP(const HttpRequestMethod& aMethod, AnyP::ProtocolType aProtocol, const char *aUrlpath)
{
    method = aMethod;
    protocol = aProtocol;
    urlpath = aUrlpath;
}