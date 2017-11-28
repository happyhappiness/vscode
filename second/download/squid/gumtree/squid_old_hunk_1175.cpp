Ftp::Server::writeCustomReply(const int code, const char *msg, const HttpReply *reply)
{
    debugs(33, 7, code << ' ' << msg);
    assert(99 < code && code < 1000);

    const bool sendDetails = reply != NULL &&
                             reply->header.has(HDR_FTP_STATUS) && reply->header.has(HDR_FTP_REASON);

    MemBuf mb;
    mb.init();
    if (sendDetails) {
        mb.Printf("%i-%s\r\n", code, msg);
        mb.Printf(" Server reply:\r\n");
        Ftp::PrintReply(mb, reply, " ");
        mb.Printf("%i \r\n", code);
    } else
        mb.Printf("%i %s\r\n", code, msg);

    writeReply(mb);
}

void
Ftp::Server::changeState(const ServerState newState, const char *reason)
