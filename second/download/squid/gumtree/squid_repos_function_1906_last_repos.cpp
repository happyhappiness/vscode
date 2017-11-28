bool
httpHeaderHasConnDir(const HttpHeader * hdr, const char *directive)
{
    String list;

    /* what type of header do we have? */
    if (hdr->getList(Http::HdrType::CONNECTION, &list))
        return strListIsMember(&list, directive, ',') != 0;

#if USE_HTTP_VIOLATIONS
    if (hdr->getList(Http::HdrType::PROXY_CONNECTION, &list))
        return strListIsMember(&list, directive, ',') != 0;
#endif

    // else, no connection header for it to exist in
    return false;
}