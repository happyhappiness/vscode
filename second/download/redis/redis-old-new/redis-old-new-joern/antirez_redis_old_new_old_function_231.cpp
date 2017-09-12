size_t objectComputeSize(robj *o) {
    robj *ele;
    list *l;
    listNode *ln;
    dict *d;
    dictIterator *di;
    listIter li;
    struct dictEntry *de;
    size_t asize = 0, elesize;

    if (o->type == OBJ_STRING) {
        if(o->encoding == OBJ_ENCODING_INT) {
            asize = sizeof(*o);
        }
        else if(o->encoding == OBJ_ENCODING_RAW) {
            asize = sdsAllocSize(o->ptr)+sizeof(*o);
        } else if(o->encoding == OBJ_ENCODING_EMBSTR) {
            asize = sdslen(o->ptr)+2+sizeof(*o);
        } else {
            serverPanic("Unknown string encoding");
        }
    } else if (o->type == OBJ_LIST) {
        if (o->encoding == OBJ_ENCODING_QUICKLIST) {
            quicklist *ql = o->ptr;
            quicklistNode *node = ql->head;
            asize = sizeof(*o)+sizeof(quicklist);
            do {
                asize += sizeof(quicklistNode)+ziplistBlobLen(node->zl);
            } while ((node = node->next));
        } else if (o->encoding == OBJ_ENCODING_ZIPLIST) {
            asize = sizeof(*o)+ziplistBlobLen(o->ptr);
        } else if (o->encoding == OBJ_ENCODING_LINKEDLIST) {
            l = o->ptr;
            asize = sizeof(*o)+sizeof(list);
            listRewind(l,&li);
            while((ln = listNext(&li))) {
                ele = ln->value;
                elesize = (ele->encoding == OBJ_ENCODING_RAW) ?
                                (sizeof(*o)+sdsAllocSize(ele->ptr)) : sizeof(*o);
                asize += (sizeof(listNode)+elesize);
            }
        } else {
            serverPanic("Unknown list encoding");
        }
    } else if (o->type == OBJ_SET) {
        if (o->encoding == OBJ_ENCODING_HT) {
            d = o->ptr;
            di = dictGetIterator(d);
            asize = sizeof(*o)+sizeof(dict)+(sizeof(struct dictEntry*)*dictSlots(d));
            while((de = dictNext(di)) != NULL) {
                ele = dictGetKey(de);
                elesize = (ele->encoding == OBJ_ENCODING_RAW) ?
                                (sizeof(*o)+sdsAllocSize(ele->ptr)) : sizeof(*o);
                asize += (sizeof(struct dictEntry)+elesize);
            }
            dictReleaseIterator(di);
        } else if (o->encoding == OBJ_ENCODING_INTSET) {
            intset *is = o->ptr;
            asize = sizeof(*o)+sizeof(*is)+is->encoding*is->length;
        } else {
            serverPanic("Unknown set encoding");
        }
    } else if (o->type == OBJ_ZSET) {
        if (o->encoding == OBJ_ENCODING_ZIPLIST) {
            asize = sizeof(*o)+(ziplistBlobLen(o->ptr));
        } else if (o->encoding == OBJ_ENCODING_SKIPLIST) {
            d = ((zset*)o->ptr)->dict;
            di = dictGetIterator(d);
            asize = sizeof(*o)+sizeof(zset)+(sizeof(struct dictEntry*)*dictSlots(d));
            while((de = dictNext(di)) != NULL) {
                ele = dictGetKey(de);
                elesize = (ele->encoding == OBJ_ENCODING_RAW) ?
                                (sizeof(*o)+sdsAllocSize(ele->ptr)) : sizeof(*o);
                asize += (sizeof(struct dictEntry)+elesize);
                asize += sizeof(zskiplistNode)*dictSize(d);
            }
            dictReleaseIterator(di);
        } else {
            serverPanic("Unknown sorted set encoding");
        }
    } else if (o->type == OBJ_HASH) {
        if (o->encoding == OBJ_ENCODING_ZIPLIST) {
            asize = sizeof(*o)+(ziplistBlobLen(o->ptr));
        } else if (o->encoding == OBJ_ENCODING_HT) {
            d = o->ptr;
            di = dictGetIterator(d);
            asize = sizeof(*o)+sizeof(dict)+(sizeof(struct dictEntry*)*dictSlots(d));
            while((de = dictNext(di)) != NULL) {
                ele = dictGetKey(de);
                elesize = (ele->encoding == OBJ_ENCODING_RAW) ?
                                (sizeof(*o)+sdsAllocSize(ele->ptr)) : sizeof(*o);
                ele = dictGetVal(de);
                elesize = (ele->encoding == OBJ_ENCODING_RAW) ?
                                (sizeof(*o)+sdsAllocSize(ele->ptr)) : sizeof(*o);
                asize += (sizeof(struct dictEntry)+elesize);
            }
            dictReleaseIterator(di);
        } else {
            serverPanic("Unknown hash encoding");
        }
    } else {
        serverPanic("Unknown object type");
    }
    return asize;
}