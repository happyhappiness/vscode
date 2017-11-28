HttpReply *
Ftp::HttpReplyWrapper(const int ftpStatus, const char *ftpReason, const Http::StatusCode httpStatus, const int64_t clen)
{
    HttpReply *const reply = new HttpReply;

    Http::ProtocolVersion httpVersion = Http::ProtocolVersion(
                                            Ftp::ProtocolVersion().major, Ftp::ProtocolVersion().minor);
    reply->sline.set(httpVersion, httpStatus);

    HttpHeader &header = reply->header;
    header.putTime(HDR_DATE, squid_curtime);
    {
        HttpHdrCc cc;
        cc.Private(String());
        header.putCc(&cc);
    }
    if (ftpStatus > 0)
        header.putInt(HDR_FTP_STATUS, ftpStatus);
    if (ftpReason)
        header.putStr(HDR_FTP_REASON, ftpReason);
    if (clen >= 0)
        header.putInt64(HDR_CONTENT_LENGTH, clen);
    reply->hdrCacheInit();
    return reply;
}