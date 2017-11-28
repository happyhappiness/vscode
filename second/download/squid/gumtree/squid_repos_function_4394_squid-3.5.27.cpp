int
Ssl::Bio::readAndBuffer(char *buf, int size, BIO *table, const char *description)
{
    prepReadBuf();

    size = min((int)rbuf.potentialSpaceSize(), size);
    if (size <= 0) {
        debugs(83, DBG_IMPORTANT, "Not enough space to hold " <<
               rbuf.contentSize() << "+ byte " << description);
        return -1;
    }

    const int bytes = Ssl::Bio::read(buf, size, table);
    debugs(83, 5, "read " << bytes << " out of " << size << " bytes"); // move to Ssl::Bio::read()

    if (bytes > 0) {
        rbuf.append(buf, bytes);
        debugs(83, 5, "recorded " << bytes << " bytes of " << description);
    }
    return bytes;
}