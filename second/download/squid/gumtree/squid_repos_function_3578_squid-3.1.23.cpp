char *
storeSwapMetaPack(tlv * tlv_list, int *length)
{
    int buflen = 0;
    tlv *t;
    int j = 0;
    char *buf;
    assert(length != NULL);
    buflen++;			/* STORE_META_OK */
    buflen += sizeof(int);	/* size of header to follow */

    for (t = tlv_list; t; t = t->next)
        buflen += sizeof(char) + sizeof(int) + t->length;

    buf = (char *)xmalloc(buflen);

    buf[j++] = (char) STORE_META_OK;

    xmemcpy(&buf[j], &buflen, sizeof(int));

    j += sizeof(int);

    for (t = tlv_list; t; t = t->next) {
        buf[j++] = t->getType();
        xmemcpy(&buf[j], &t->length, sizeof(int));
        j += sizeof(int);
        xmemcpy(&buf[j], t->value, t->length);
        j += t->length;
    }

    assert((int) j == buflen);
    *length = buflen;
    return buf;
}