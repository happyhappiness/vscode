char *
ntlmGetString(ntlmhdr * hdr, strhdr * str, int flags)
{
    static char buf[512];
    unsigned short *s, c;
    char *d, *sc;
    int l, o;

    l = le16toh(str->len);
    o = le32toh(str->offset);

    /* Sanity checks. XXX values arbitrarialy chosen */
    if (l <= 0 || l >= 32 || o >= 256) {
        fprintf(stderr, "ntlmGetString: insane: l:%d o:%d\n", l, o);
        return (NULL);
    }
    if ((flags & NEGOTIATE_ASCII) == 0) {
        /* UNICODE string */
        s = (unsigned short *) ((char *) hdr + o);
        d = buf;

        for (l >>= 1; l; s++, l--) {
            c = le16toh(*s);
            if (c > 254 || c == '\0') {
                fprintf(stderr, "ntlmGetString: bad uni: %04x\n", c);
                return (NULL);
            }
            *d++ = c;
        }

        *d = 0;
    } else {
        /* ASCII/OEM string */
        sc = (char *) hdr + o;
        d = buf;

        for (; l; l--) {
            if (*sc == '\0' || !xisprint(*sc)) {
                fprintf(stderr, "ntlmGetString: bad ascii: %04x\n", *sc);
                return (NULL);
            }
            *d++ = *sc++;
        }

        *d = 0;
    }

    return (buf);
}