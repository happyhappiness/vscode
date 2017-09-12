    }
    dictReleaseIterator(di);

    if (!dstkey) {
        lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",cardinality);
    } else {
