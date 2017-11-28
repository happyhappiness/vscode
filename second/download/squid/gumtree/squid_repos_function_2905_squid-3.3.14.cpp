void
HttpRequest::hdrCacheInit()
{
    HttpMsg::hdrCacheInit();

    assert(!range);
    range = header.getRange();
}