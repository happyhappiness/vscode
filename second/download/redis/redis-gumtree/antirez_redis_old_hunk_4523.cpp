        } else {
            dictAdd(dstset->ptr,ele,NULL);
            incrRefCount(ele);
            server.dirty++;
        }
    }
    dictReleaseIterator(di);

    if (!dstkey)
        lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",cardinality);
    else
        addReply(c,shared.ok);
    zfree(dv);
}

