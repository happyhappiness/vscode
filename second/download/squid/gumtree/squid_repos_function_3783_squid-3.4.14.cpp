char *
Ip::Address::toUrl(char* buf, unsigned int blen) const
{
    char *p = buf;

    // Ensure we have a buffer.

    if (buf == NULL) {
        return NULL;
    }

    p += toHostStr(p, blen);

    if (mSocketAddr_.sin6_port > 0 && p <= (buf+blen-7) ) {
        // ':port' (short int) needs at most 6 bytes plus 1 for 0-terminator
        snprintf(p, 7, ":%d", port() );
    }

    // force a null-terminated string
    buf[blen-1] = '\0';

    return buf;
}