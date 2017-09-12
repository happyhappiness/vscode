        } else {
            dictAdd(dstset->ptr,ele,NULL);
            incrRefCount(ele);
        }
    }
    dictReleaseIterator(di);

    if (!dstkey) {
        lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",cardinality);
    } else {
        addReply(c,shared.ok);
        server.dirty++;
    }
    zfree(dv);
}

