char *
rfc1738_do_escape(const char *url, int flags)
{
    static char *buf;
    static size_t bufsize = 0;
    const char *src;
    char *dst;
    unsigned int i, do_escape;

    if (buf == NULL || strlen(url) * 3 > bufsize) {
        xfree(buf);
        bufsize = strlen(url) * 3 + 1;
        buf = (char*)xcalloc(bufsize, 1);
    }
    for (src = url, dst = buf; *src != '\0' && dst < (buf + bufsize - 1); src++, dst++) {

        /* a-z, A-Z and 0-9 are SAFE. */
        if ((*src >= 'a' && *src <= 'z') || (*src >= 'A' && *src <= 'Z') || (*src >= '0' && *src <= '9')) {
            *dst = *src;
            continue;
        }

        do_escape = 0;

        /* RFC 1738 defines these chars as unsafe */
        if ((flags & RFC1738_ESCAPE_UNSAFE)) {
            for (i = 0; i < sizeof(rfc1738_unsafe_chars); i++) {
                if (*src == rfc1738_unsafe_chars[i]) {
                    do_escape = 1;
                    break;
                }
            }
            /* Handle % separately */
            if (!(flags & RFC1738_ESCAPE_NOPERCENT) && *src == '%')
                do_escape = 1;
            /* Handle space separately */
            else if (!(flags & RFC1738_ESCAPE_NOSPACE) && *src <= ' ')
                do_escape = 1;
        }
        /* RFC 1738 defines these chars as reserved */
        if ((flags & RFC1738_ESCAPE_RESERVED) && do_escape == 0) {
            for (i = 0; i < sizeof(rfc1738_reserved_chars); i++) {
                if (*src == rfc1738_reserved_chars[i]) {
                    do_escape = 1;
                    break;
                }
            }
        }
        if ((flags & RFC1738_ESCAPE_CTRLS) && do_escape == 0) {
            /* RFC 1738 says any control chars (0x00-0x1F) are encoded */
            if ((unsigned char) *src <= (unsigned char) 0x1F)
                do_escape = 1;
            /* RFC 1738 says 0x7f is encoded */
            else if (*src == (char) 0x7F)
                do_escape = 1;
            /* RFC 1738 says any non-US-ASCII are encoded */
            else if (((unsigned char) *src >= (unsigned char) 0x80))
                do_escape = 1;
        }
        /* Do the triplet encoding, or just copy the char */
        if (do_escape == 1) {
            (void) snprintf(dst, (bufsize-(dst-buf)), "%%%02X", (unsigned char) *src);
            dst += sizeof(char) * 2;
        } else {
            *dst = *src;
        }
    }
    *dst = '\0';
    return (buf);
}