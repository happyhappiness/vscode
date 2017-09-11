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
