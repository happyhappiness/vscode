    rv.l = 0;
    if ((flags & NTLM_NEGOTIATE_ASCII) == 0) {
        /* UNICODE string */
        unsigned short *s = (unsigned short *)rv.str;
        rv.str = d = buf;

        for (l >>= 1; l; ++s, --l) {
            unsigned short c = le16toh(*s);
            if (c > 254 || c == '\0') {
                fprintf(stderr, "ntlmssp: bad unicode: %04x\n", c);
                return rv;
            }
            *d = c;
            ++d;
            ++rv.l;
        }
    } else {
        /* ASCII/OEM string */
        char *sc = rv.str;
