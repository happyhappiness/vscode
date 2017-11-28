void
HttpReply::setHeaders(Http::StatusCode status, const char *reason,
                      const char *ctype, int64_t clen, time_t lmt, time_t expiresTime)
{
    HttpHeader *hdr;
    sline.set(Http::ProtocolVersion(), status, reason);
    hdr = &header;
    hdr->putStr(Http::HdrType::SERVER, visible_appname_string);
    hdr->putStr(Http::HdrType::MIME_VERSION, "1.0");
    hdr->putTime(Http::HdrType::DATE, squid_curtime);

    if (ctype) {
        hdr->putStr(Http::HdrType::CONTENT_TYPE, ctype);
        content_type = ctype;
    } else
        content_type = String();

    if (clen >= 0)
        hdr->putInt64(Http::HdrType::CONTENT_LENGTH, clen);

    if (expiresTime >= 0)
        hdr->putTime(Http::HdrType::EXPIRES, expiresTime);

    if (lmt > 0)        /* this used to be lmt != 0 @?@ */
        hdr->putTime(Http::HdrType::LAST_MODIFIED, lmt);

    date = squid_curtime;

    content_length = clen;

    expires = expiresTime;

    last_modified = lmt;
}