    int16_t l;			/* length */
    int32_t o;			/* offset */
    static char buf[NTLM_MAX_FIELD_LENGTH];
    lstring rv;
    char *d;

    rv.str = NULL;
    rv.l = -1;

    l = le16toh(str->len);
    o = le32toh(str->offset);
    // debug("ntlm_fetch_string(plength=%d,l=%d,o=%d)\n",packet_size,l,o);

    if (l < 0 || l > NTLM_MAX_FIELD_LENGTH || o + l > packet_size || o == 0) {
        debug("ntlm_fetch_string: insane data (pkt-sz: %d, fetch len: %d, offset: %d)\n", packet_size,l,o);
        return rv;
    }
    rv.str = (char *)packet + o;
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

        for (; l>=0; ++sc, --l) {
            if (*sc == '\0' || !xisprint(*sc)) {
                fprintf(stderr, "ntlmssp: bad ascii: %04x\n", *sc);
                return rv;
            }
            ++rv.l;
        }
    }

    return rv;
}

