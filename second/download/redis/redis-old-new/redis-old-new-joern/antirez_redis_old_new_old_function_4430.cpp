static robj *createSetObject(void) {
    dict *d = dictCreate(&setDictType,NULL);
    if (!d) oom("dictCreate");
    return createObject(REDIS_SET,d);
}