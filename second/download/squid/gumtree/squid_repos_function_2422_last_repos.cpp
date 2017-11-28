bool
HttpRequest::canHandle1xx() const
{
    // old clients do not support 1xx unless they sent Expect: 100-continue
    // (we reject all other Http::HdrType::EXPECT values so just check for Http::HdrType::EXPECT)
    if (http_ver <= Http::ProtocolVersion(1,0) && !header.has(Http::HdrType::EXPECT))
        return false;

    // others must support 1xx control messages
    return true;
}