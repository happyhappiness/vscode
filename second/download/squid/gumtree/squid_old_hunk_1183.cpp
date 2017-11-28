           "\n----------");

    Comm::Write(clientConnection, &mb, call);
}

static void
Ftp::PrintReply(MemBuf &mb, const HttpReply *reply, const char *const prefix)
{
    const HttpHeader &header = reply->header;

    HttpHeaderPos pos = HttpHeaderInitPos;
    while (const HttpHeaderEntry *e = header.getEntry(&pos)) {
        if (e->id == HDR_FTP_PRE) {
            String raw;
            if (httpHeaderParseQuotedString(e->value.rawBuf(), e->value.size(), &raw))
                mb.Printf("%s\r\n", raw.termedBuf());
        }
    }

    if (header.has(HDR_FTP_STATUS)) {
        const char *reason = header.getStr(HDR_FTP_REASON);
        mb.Printf("%i %s\r\n", header.getInt(HDR_FTP_STATUS),
                  (reason ? reason : 0));
    }
}

void
Ftp::Server::wroteEarlyReply(const CommIoCbParams &io)
{
