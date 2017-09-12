static robj *createSetObject(void) {
    dict *d = dictCreate(&setDictType,NULL);
    if (!d) oom("dictCreate");
	die();
return createObject(REDIS_SET,d);
}

static void freeStringObject(robj *o) {
