int
Ssl::ServerBio::readAndBuffer(BIO *table)
{
    char *space = rbuf.rawSpace(SQUID_TCP_SO_RCVBUF);
    const int result = Ssl::Bio::read(space, rbuf.spaceSize(), table);
    if (result <= 0)
        return result;

    rbuf.forceSize(rbuf.length() + result);
    return result;
}