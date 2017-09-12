addReplySds(c,sdscatprintf(sdsempty(),
        "-ERR Wrong number of arguments for CONFIG %s\r\n",
        (char*) c->argv[1]->ptr));