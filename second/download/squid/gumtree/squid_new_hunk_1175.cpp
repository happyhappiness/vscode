Ftp::Server::writeCustomReply(const int code, const char *msg, const HttpReply *reply)
{
    debugs(33, 7, code << ' ' << msg);
    assert(99 < code && code < 1000);

    const bool sendDetails = reply != NULL &&
                             reply->header.has(Http::HdrType::FTP_STATUS) && reply->header.has(Http::HdrType::FTP_REASON);

    MemBuf mb;
    mb.init();
    if (sendDetails) {
        mb.appendf("%i-%s\r\n", code, msg);
        mb.appendf(" Server reply:\r\n");
        Ftp::PrintReply(mb, reply, " ");
        mb.appendf("%i \r\n", code);
    } else
        mb.appendf("%i %s\r\n", code, msg);

    writeReply(mb);
}

void
Ftp::Server::changeState(const ServerState newState, const char *reason)
