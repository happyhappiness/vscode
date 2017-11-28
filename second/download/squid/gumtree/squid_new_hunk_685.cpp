    rv.l = 0;
    if ((flags & NTLM_NEGOTIATE_ASCII) == 0) {
        /* UNICODE string */
        unsigned short *s = (unsigned short *)rv.str;
        rv.str = d = buf;

        for (uint32_t len = (l>>1); len; ++s, --len) {
            uint16_t c = le16toh(*s);
            if (c > 254 || c == '\0') {
                fprintf(stderr, "ntlmssp: bad unicode: %04x\n", c);
                return rv;
            }
            *d = static_cast<char>(c&0xFF);
            ++d;
            ++rv.l;
        }
    } else {
        /* ASCII/OEM string */
        char *sc = rv.str;
