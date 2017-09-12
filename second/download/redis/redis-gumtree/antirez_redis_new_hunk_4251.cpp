    return l + zipmapRawValueLength(p+l);
}

/* Set key to value, creating the key if it does not already exist.
 * If 'update' is not NULL, *update is set to 1 if the key was
 * already preset, otherwise to 0. */
unsigned char *zipmapSet(unsigned char *zm, unsigned char *key, unsigned int klen, unsigned char *val, unsigned int vlen, int *update) {
    unsigned int oldlen = 0, freeoff = 0, freelen;
    unsigned int reqlen = zipmapRequiredLength(klen,vlen);
    unsigned int empty, vempty;
    unsigned char *p;
   
    freelen = reqlen;
    if (update) *update = 0;
    p = zipmapLookupRaw(zm,key,klen,&oldlen,&freeoff,&freelen);
    if (p == NULL && freelen == 0) {
        /* Key not found, and not space for the new key. Enlarge */
        zm = zrealloc(zm,oldlen+reqlen);
        p = zm+oldlen-1;
        zm[oldlen+reqlen-1] = ZIPMAP_END;
        freelen = reqlen;
    } else if (p == NULL) {
        /* Key not found, but there is enough free space. */
        p = zm+freeoff;
