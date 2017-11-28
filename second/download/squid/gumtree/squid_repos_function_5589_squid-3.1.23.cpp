lstring
ntlm_fetch_string(char *packet, int32_t length, strhdr * str)
{
    int16_t l;			/* length */
    int32_t o;			/* offset */
    lstring rv;

    lstring_zero(rv);

    l = le16toh(str->len);
    o = le32toh(str->offset);
    /* debug("fetch_string(plength=%d,l=%d,o=%d)\n",length,l,o); */

    if (l < 0 || l > MAX_FIELD_LENGTH || o + l > length || o == 0) {
        /* debug("ntlmssp: insane data (l: %d, o: %d)\n", l,o); */
        return rv;
    }
    rv.str = packet + o;
    rv.l = l;

    return rv;
}