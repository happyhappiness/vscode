static unsigned int dictEncObjHash(const void *key) {
    robj *o = (robj*) key;

    o = getDecodedObject(o);
    unsigned int hash = dictGenHashFunction(o->ptr, sdslen((sds)o->ptr));
    decrRefCount(o);
    return hash;
}

/* Sets type and expires */
