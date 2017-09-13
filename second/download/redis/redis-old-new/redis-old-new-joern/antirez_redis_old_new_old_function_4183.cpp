unsigned char *zipmapSet(unsigned char *zm, unsigned char *key, unsigned int klen, unsigned char *val, unsigned int vlen) {
    unsigned int oldlen = 0, freeoff = 0, freelen;
    unsigned int reqlen = zipmapRequiredLength(klen,vlen);
    unsigned int empty, vempty;
    unsigned char *p;
   
    freelen = reqlen;
    p = zipmapLookupRaw(zm,key,klen,&oldlen,&freeoff,&freelen);
    if (p == NULL && freelen == 0) {
        printf("HERE oldlen:%u required:%u\n",oldlen,reqlen);
        /* Key not found, and not space for the new key. Enlarge */
        zm = zrealloc(zm,oldlen+reqlen);
        p = zm+oldlen-1;
        zm[oldlen+reqlen-1] = ZIPMAP_END;
        freelen = reqlen;
        printf("New total length is: %u\n", oldlen+reqlen);
    } else if (p == NULL) {
        /* Key not found, but there is enough free space. */
        p = zm+freeoff;
        /* note: freelen is already set in this case */
    } else {
        unsigned char *b = p;

        /* Key found. Is there enough space for the new value? */
        /* Compute the total length: */
        freelen = zipmapRawKeyLength(b);
        b += freelen;
        freelen += zipmapRawValueLength(b);
        if (freelen < reqlen) {
            /* Mark this entry as free and recurse */
            p[0] = ZIPMAP_EMPTY;
            zipmapEncodeLength(p+1,freelen);
            zm[0] |= ZIPMAP_STATUS_FRAGMENTED;
            return zipmapSet(zm,key,klen,val,vlen);
        }
    }

    /* Ok we have a suitable block where to write the new key/value
     * entry. */
    empty = freelen-reqlen;
    /* If there is too much free space mark it as a free block instead
     * of adding it as trailing empty space for the value, as we want
     * zipmaps to be very space efficient. */
    if (empty > ZIPMAP_VALUE_MAX_FREE) {
        unsigned char *e;

        e = p+reqlen;
        e[0] = ZIPMAP_EMPTY;
        zipmapEncodeLength(e+1,empty);
        vempty = 0;
        zm[0] |= ZIPMAP_STATUS_FRAGMENTED;
    } else {
        vempty = empty;
    }

    /* Just write the key + value and we are done. */
    /* Key: */
    p += zipmapEncodeLength(p,klen);
    memcpy(p,key,klen);
    p += klen;
    /* Value: */
    p += zipmapEncodeLength(p,vlen);
    *p++ = vempty;
    memcpy(p,val,vlen);
    return zm;
}