           "\n----------");

    Comm::Write(clientConnection, &mb, call);
}

static void
Ftp::PrintReply(MemBuf &mb, const HttpReply *reply, const char *const)
{
    const HttpHeader &header = reply->header;

    HttpHeaderPos pos = HttpHeaderInitPos;
    while (const HttpHeaderEntry *e = header.getEntry(&pos)) {
        if (e->id == Http::HdrType::FTP_PRE) {
            String raw;
            if (httpHeaderParseQuotedString(e->value.rawBuf(), e->value.size(), &raw))
                mb.appendf("%s\r\n", raw.termedBuf());
        }
    }

    if (header.has(Http::HdrType::FTP_STATUS)) {
        const char *reason = header.getStr(Http::HdrType::FTP_REASON);
        mb.appendf("%i %s\r\n", header.getInt(Http::HdrType::FTP_STATUS),
                   (reason ? reason : 0));
    }
}

void
Ftp::Server::wroteEarlyReply(const CommIoCbParams &io)
{
