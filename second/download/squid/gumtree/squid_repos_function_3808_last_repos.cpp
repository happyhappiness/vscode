int
Ssl::ServerBio::readAndParse(char *buf, const int size, BIO *table)
{
    const int result = readAndBuffer(table);
    if (result <= 0)
        return result;

    try {
        if (!parser_.parseHello(rbuf)) {
            // need more data to finish parsing
            BIO_set_retry_read(table);
            return -1;
        }
        parsedHandshake = true; // done parsing (successfully)
    }
    catch (const std::exception &ex) {
        debugs(83, 2, "parsing error on FD " << fd_ << ": " << ex.what());
        parsedHandshake = true; // done parsing (due to an error)
        parseError = true;
    }

    if (holdRead_) {
        debugs(83, 7, "Hold flag is set, retry latter. (Hold " << size << "bytes)");
        BIO_set_retry_read(table);
        return -1;
    }

    return giveBuffered(buf, size);
}