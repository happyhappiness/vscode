void
Ftp::Client::initReadBuf()
{
    if (data.readBuf == NULL) {
        data.readBuf = new MemBuf;
        data.readBuf->init(4096, SQUID_TCP_SO_RCVBUF);
    }
}