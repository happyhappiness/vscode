    return zm;
}

/* This function is used to iterate through all the zipmap elements.
 * In the first call the first argument is the pointer to the zipmap + 1.
 * In the next calls what zipmapNext returns is used as first argument.
 * Example:
 *
 * unsigned char *i = my_zipmap+1;
 * while((i = zipmapNext(i,&key,&klen,&value,&vlen)) != NULL) {
 *     printf("%d bytes key at $p\n", klen, key);
 *     printf("%d bytes value at $p\n", vlen, value);
 * }
 */
unsigned char *zipmapNext(unsigned char *zm, unsigned char **key,
            unsigned int *klen, unsigned char **value, unsigned int *vlen) {
    while(zm[0] == ZIPMAP_EMPTY)
        zm += zipmapDecodeLength(zm+1);
    if (zm[0] == ZIPMAP_END) return NULL;
    if (key) {
        *key = zm;
        *klen = zipmapDecodeLength(zm);
        *key += (*klen < ZIPMAP_BIGLEN) ? 1 : sizeof(unsigned int);
    }
    zm += zipmapRawKeyLength(zm);
    if (value) {
        *value = zm+1;
        *vlen = zipmapDecodeLength(zm);
        *value += (*vlen < ZIPMAP_BIGLEN) ? 1 : sizeof(unsigned int);
    }
    zm += zipmapRawValueLength(zm);
    return zm;
}

void zipmapRepr(unsigned char *p) {
    unsigned int l;

