void
Ftp::Server::writeErrorReply(const HttpReply *reply, const int scode)
{
    const HttpRequest *request = pipeline.front()->http->request;
    assert(request);

    MemBuf mb;
    mb.init();

    if (request->errType != ERR_NONE)
        mb.appendf("%i-%s\r\n", scode, errorPageName(request->errType));

    if (request->errDetail > 0) {
        // XXX: > 0 may not always mean that this is an errno
        mb.appendf("%i-Error: (%d) %s\r\n", scode,
                   request->errDetail,
                   strerror(request->errDetail));
    }

#if USE_ADAPTATION
    // XXX: Remove hard coded names. Use an error page template instead.
    const Adaptation::History::Pointer ah = request->adaptHistory();
    if (ah != NULL) { // XXX: add adapt::<all_h but use lastMeta here
        const String info = ah->allMeta.getByName("X-Response-Info");
        const String desc = ah->allMeta.getByName("X-Response-Desc");
        if (info.size())
            mb.appendf("%i-Information: %s\r\n", scode, info.termedBuf());
        if (desc.size())
            mb.appendf("%i-Description: %s\r\n", scode, desc.termedBuf());
    }
#endif

    Must(reply);
    const char *reason = reply->header.has(Http::HdrType::FTP_REASON) ?
                         reply->header.getStr(Http::HdrType::FTP_REASON):
                         reply->sline.reason();

    mb.appendf("%i %s\r\n", scode, reason); // error terminating line

    // TODO: errorpage.cc should detect FTP client and use
    // configurable FTP-friendly error templates which we should
    // write to the client "as is" instead of hiding most of the info

    writeReply(mb);
}