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
