    return l + zipmapRawValueLength(p+l);
}

/* Set key to value, creating the key if it does not already exist. */
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
