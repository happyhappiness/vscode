MemBuf *
httpPackedReply(http_status status, const char *ctype, int64_t clen, time_t lmt, time_t expires)
{
    HttpReply *rep = new HttpReply;
    rep->setHeaders(status, ctype, NULL, clen, lmt, expires);
    MemBuf *mb = rep->pack();
    delete rep;
    return mb;
}