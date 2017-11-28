void
HttpReply::hdrCacheInit()
{
    HttpMsg::hdrCacheInit();

    http_ver = sline.version;
    content_length = header.getInt64(HDR_CONTENT_LENGTH);
    date = header.getTime(HDR_DATE);
    last_modified = header.getTime(HDR_LAST_MODIFIED);
    surrogate_control = header.getSc();
    content_range = header.getContRange();
    keep_alive = persistent() ? 1 : 0;
    const char *str = header.getStr(HDR_CONTENT_TYPE);

    if (str)
        content_type.limitInit(str, strcspn(str, ";\t "));
    else
        content_type = String();

    /* be sure to set expires after date and cache-control */
    expires = hdrExpirationTime();
}