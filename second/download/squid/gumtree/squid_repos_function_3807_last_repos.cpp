int
Ssl::ServerBio::readAndGive(char *buf, const int size, BIO *table)
{
    // If we have unused buffered bytes, give those bytes to OpenSSL now,
    // before reading more. TODO: Read if we have buffered less than size?
    if (rbufConsumePos < rbuf.length())
        return giveBuffered(buf, size);

    if (record_) {
        const int result = readAndBuffer(table);
        if (result <= 0)
            return result;
        return giveBuffered(buf, size);
    }

    return Ssl::Bio::read(buf, size, table);
}