        }
        sdsfreesplitres(v,vlen);
    } else {
        addReplySds(c,sdscatprintf(sdsempty(),
            "-ERR not supported CONFIG parameter %s\r\n",
            (char*)c->argv[2]->ptr));
        decrRefCount(o);
        return;
    }
