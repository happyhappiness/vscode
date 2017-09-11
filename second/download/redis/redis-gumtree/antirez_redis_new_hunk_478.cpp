
/* This helper function used by GETBIT / SETBIT parses the bit offset argument
 * making sure an error is returned if it is negative or if it overflows
 * Redis 512 MB limit for the string value.
 *
 * If the 'hash' argument is true, and 'bits is positive, then the command
 * will also parse bit offsets prefixed by "#". In such a case the offset
 * is multiplied by 'bits'. This is useful for the BITFIELD command. */
int getBitOffsetFromArgument(client *c, robj *o, size_t *offset, int hash, int bits) {
    long long loffset;
    char *err = "bit offset is not an integer or out of range";
    char *p = o->ptr;
    size_t plen = sdslen(p);

    /* Handle #<offset> form. */
    if (hash && bits > 0) {
        p++;
        plen--;
    }

    if (string2ll(p,plen,&loffset) == 0) {
        addReplyError(c,err);
        return C_ERR;
    }

    /* Adjust the offset by 'bits' for #<offset> form. */
    if (hash && bits > 0) loffset *= bits;

    /* Limit offset to 512MB in bytes */
    if ((loffset < 0) || ((unsigned long long)loffset >> 3) >= (512*1024*1024))
