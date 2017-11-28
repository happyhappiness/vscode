    MemBuf *rv = temp->pack();
    delete temp;
    return rv;
}

void
HttpReply::setHeaders(http_status status, const char *reason,
                      const char *ctype, int64_t clen, time_t lmt, time_t expiresTime)
{
    HttpHeader *hdr;
    HttpVersion ver(1,1);
    httpStatusLineSet(&sline, ver, status, reason);
    hdr = &header;
    hdr->putStr(HDR_SERVER, visible_appname_string);
    hdr->putStr(HDR_MIME_VERSION, "1.0");
    hdr->putTime(HDR_DATE, squid_curtime);

    if (ctype) {
