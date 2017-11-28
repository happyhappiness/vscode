void
HttpReply::hdrCacheInit()
{
    HttpMsg::hdrCacheInit();

    http_ver = sline.version;
    content_length = header.getInt64(Http::HdrType::CONTENT_LENGTH);
    date = header.getTime(Http::HdrType::DATE);
    last_modified = header.getTime(Http::HdrType::LAST_MODIFIED);
    surrogate_control = header.getSc();
    content_range = header.getContRange();
    keep_alive = persistent() ? 1 : 0;
    const char *str = header.getStr(Http::HdrType::CONTENT_TYPE);

    if (str)
        content_type.limitInit(str, strcspn(str, ";\t "));
    else
        content_type = String();

    /* be sure to set expires after date and cache-control */
    expires = hdrExpirationTime();
}