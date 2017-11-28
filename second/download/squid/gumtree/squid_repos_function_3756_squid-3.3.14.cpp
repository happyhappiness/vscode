char *
Ip::Address::ToURL(char* buf, unsigned int blen) const
{
    char *p = buf;

    // Ensure we have a buffer.

    if (buf == NULL) {
        return NULL;
    }

    p += ToHostname(p, blen);

    if (m_SocketAddr.sin6_port > 0 && p <= (buf+blen-7) ) {
        // ':port' (short int) needs at most 6 bytes plus 1 for 0-terminator
        snprintf(p, 7, ":%d", GetPort() );
    }

    // force a null-terminated string
    buf[blen-1] = '\0';

    return buf;
}