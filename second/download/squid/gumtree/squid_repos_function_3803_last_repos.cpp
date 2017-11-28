int
Ssl::ClientBio::read(char *buf, int size, BIO *table)
{
    if (abortReason) {
        debugs(83, 3, "BIO on FD " << fd_ << " is aborted");
        BIO_clear_retry_flags(table);
        return -1;
    }

    if (holdRead_) {
        debugs(83, 7, "Hold flag is set, retry latter. (Hold " << size << "bytes)");
        BIO_set_retry_read(table);
        return -1;
    }

    if (!rbuf.isEmpty()) {
        int bytes = (size <= (int)rbuf.length() ? size : rbuf.length());
        memcpy(buf, rbuf.rawContent(), bytes);
        rbuf.consume(bytes);
        return bytes;
    } else
        return Ssl::Bio::read(buf, size, table);

    return -1;
}