    char *err = "bit offset is not an integer or out of range";
    char *p = o->ptr;
    size_t plen = sdslen(p);
    int usehash = 0;

    /* Handle #<offset> form. */
    if (p[0] == '#' && hash && bits > 0) usehash = 1;

    if (string2ll(p+usehash,plen-usehash,&loffset) == 0) {
        addReplyError(c,err);
        return C_ERR;
    }

    /* Adjust the offset by 'bits' for #<offset> form. */
    if (usehash) loffset *= bits;

    /* Limit offset to 512MB in bytes */
    if ((loffset < 0) || ((unsigned long long)loffset >> 3) >= (512*1024*1024))
