bool
httpHeaderHasConnDir(const HttpHeader * hdr, const char *directive)
{
    String list;

    /* what type of header do we have? */
    if (hdr->has(HDR_CONNECTION)) {
        list = hdr->getList(HDR_CONNECTION);
        return strListIsMember(&list, directive, ',') != 0;
    }

#if USE_HTTP_VIOLATIONS
    if (hdr->has(HDR_PROXY_CONNECTION)) {
        list = hdr->getList(HDR_PROXY_CONNECTION);
        return strListIsMember(&list, directive, ',') != 0;
    }
#endif

    // else, no connection header for it to exist in
    return false;
}