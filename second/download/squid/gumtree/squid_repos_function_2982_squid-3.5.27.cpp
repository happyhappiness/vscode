bool
HttpRequest::canHandle1xx() const
{
    // old clients do not support 1xx unless they sent Expect: 100-continue
    // (we reject all other HDR_EXPECT values so just check for HDR_EXPECT)
    if (http_ver <= Http::ProtocolVersion(1,0) && !header.has(HDR_EXPECT))
        return false;

    // others must support 1xx control messages
    return true;
}