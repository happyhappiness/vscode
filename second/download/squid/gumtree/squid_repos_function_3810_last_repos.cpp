int
Ssl::ServerBio::giveBuffered(char *buf, const int size)
{
    if (rbuf.length() <= rbufConsumePos)
        return -1; // buffered nothing yet

    const int unsent = rbuf.length() - rbufConsumePos;
    const int bytes = (size <= unsent ? size : unsent);
    memcpy(buf, rbuf.rawContent() + rbufConsumePos, bytes);
    rbufConsumePos += bytes;
    debugs(83, 7, bytes << "<=" << size << " bytes to OpenSSL");
    return bytes;
}