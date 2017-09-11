            d = o->ptr;
            di = dictGetIterator(d);
            asize = sizeof(*o)+sizeof(dict)+(sizeof(struct dictEntry*)*dictSlots(d));
            while((de = dictNext(di)) != NULL && samples < sample_size) {
                ele = dictGetKey(de);
                elesize += (ele->encoding == OBJ_ENCODING_RAW) ?
                                (sizeof(*o)+sdsAllocSize(ele->ptr)) : sizeof(*o);
                ele = dictGetVal(de);
                elesize += (ele->encoding == OBJ_ENCODING_RAW) ?
                                (sizeof(*o)+sdsAllocSize(ele->ptr)) : sizeof(*o);
                elesize += sizeof(struct dictEntry);
                samples++;
                printf("%zu samples: %zu usage\n", samples, elesize);
            }
            dictReleaseIterator(di);
            if (samples) asize += (double)elesize/samples*dictSize(d);
        } else {
            serverPanic("Unknown hash encoding");
        }
