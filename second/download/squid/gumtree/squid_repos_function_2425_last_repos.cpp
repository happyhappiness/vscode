const SBuf &
HttpRequest::effectiveRequestUri() const
{
    if (method.id() == Http::METHOD_CONNECT || url.getScheme() == AnyP::PROTO_AUTHORITY_FORM)
        return url.authority(true); // host:port
    return url.absolute();
}