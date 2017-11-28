void
HttpRequest::initHTTP(const HttpRequestMethod& aMethod, AnyP::ProtocolType aProtocol, const char *aSchemeImg, const char *aUrlpath)
{
    method = aMethod;
    url.setScheme(aProtocol, aSchemeImg);
    url.path(aUrlpath);
}