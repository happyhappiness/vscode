void
HttpRequest::initHTTP(const HttpRequestMethod& aMethod, AnyP::ProtocolType aProtocol, const char *aUrlpath)
{
    method = aMethod;
    url.setScheme(aProtocol);
    urlpath = aUrlpath;
}