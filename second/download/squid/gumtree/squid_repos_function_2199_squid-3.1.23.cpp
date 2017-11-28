int
httpHeaderHasConnDir(const HttpHeader * hdr, const char *directive)
{
    String list;
    int res;
    /* what type of header do we have? */

#if HTTP_VIOLATIONS
    if (hdr->has(HDR_PROXY_CONNECTION))
        list = hdr->getList(HDR_PROXY_CONNECTION);
    else
#endif
        if (hdr->has(HDR_CONNECTION))
            list = hdr->getList(HDR_CONNECTION);
        else
            return 0;

    res = strListIsMember(&list, directive, ',');

    list.clean();

    return res;
}