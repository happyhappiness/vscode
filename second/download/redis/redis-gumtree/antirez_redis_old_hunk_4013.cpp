    if (subject->encoding == REDIS_ENCODING_ZIPLIST)
        obj = getDecodedObject(obj);

    lIterator *li;
    if (toremove < 0) {
        toremove = -toremove;
        li = lInitIterator(subject,-1,REDIS_HEAD);
    } else {
        li = lInitIterator(subject,0,REDIS_TAIL);
    }

    while (lNext(li,&entry)) {
        if (lEqual(&entry,obj)) {
            lDelete(&entry);
            server.dirty++;
            removed++;
            if (toremove && removed == toremove) break;
        }
    }
    lReleaseIterator(li);

    /* Clean up raw encoded object */
    if (subject->encoding == REDIS_ENCODING_ZIPLIST)
        decrRefCount(obj);

    if (lLength(subject) == 0) dbDelete(c->db,c->argv[1]);
    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",removed));
}

