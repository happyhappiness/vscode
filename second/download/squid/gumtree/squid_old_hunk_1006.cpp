HttpReply *
Ftp::Relay::createHttpReply(const Http::StatusCode httpStatus, const int64_t clen)
{
    HttpReply *const reply = Ftp::HttpReplyWrapper(ctrl.replycode, ctrl.last_reply, httpStatus, clen);
    if (ctrl.message) {
        for (wordlist *W = ctrl.message; W && W->next; W = W->next)
            reply->header.putStr(HDR_FTP_PRE, httpHeaderQuoteString(W->key).c_str());
        // no hdrCacheInit() is needed for after HDR_FTP_PRE addition
    }
    return reply;
}

void
Ftp::Relay::handleDataRequest()
