int
Ssl::ClientBio::read(char *buf, int size, BIO *table)
{
    if (abortReason) {
        debugs(83, 3, "BIO on FD " << fd_ << " is aborted");
        BIO_clear_retry_flags(table);
        return -1;
    }

    if (helloState < atHelloReceived) {
        int bytes = readAndBuffer(buf, size, table, "TLS client Hello");
        if (bytes <= 0)
            return bytes;
    }

    if (helloState == atHelloNone) {
        const int helloSize = features.parseMsgHead(rbuf);
        if (helloSize == 0) {
            // Not enough bytes to get hello message size
            BIO_set_retry_read(table);
            return -1;
        } else if (helloSize < 0) {
            return -1;
        }

        helloState = atHelloStarted; //Next state
    }

    if (helloState == atHelloStarted) {
        const unsigned char *head = (const unsigned char *)rbuf.content();
        const char *s = objToString(head, rbuf.contentSize());
        debugs(83, 7, "SSL Header: " << s);

        if (!features.helloRecord(rbuf)) {
            BIO_set_retry_read(table);
            return -1;
        }
        features.get(rbuf);
        helloState = atHelloReceived;
    }

    if (holdRead_) {
        debugs(83, 7, "Hold flag is set, retry latter. (Hold " << size << "bytes)");
        BIO_set_retry_read(table);
        return -1;
    }

    if (helloState == atHelloReceived) {
        if (rbuf.hasContent()) {
            int bytes = (size <= rbuf.contentSize() ? size : rbuf.contentSize());
            memcpy(buf, rbuf.content(), bytes);
            rbuf.consume(bytes);
            return bytes;
        } else
            return Ssl::Bio::read(buf, size, table);
    }

    return -1;
}