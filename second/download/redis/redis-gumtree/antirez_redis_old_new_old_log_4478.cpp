addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",
        (int)sdslen(c->argv[1]->ptr)));