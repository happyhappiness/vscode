    if (subject->encoding == REDIS_ENCODING_ZIPLIST)
        decrRefCount(obj);

    if (lLength(subject) == 0) dbDelete(c->db,c->argv[1]);
    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",removed));
}

