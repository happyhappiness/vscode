void HttpMsg::hdrCacheInit()
{
    content_length = header.getInt64(Http::HdrType::CONTENT_LENGTH);
    assert(NULL == cache_control);
    cache_control = header.getCc();
}