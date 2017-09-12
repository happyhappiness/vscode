        }
        totlen = sdslen(o->ptr);
    }
    touchWatchedKey(c->db,c->argv[1]);
    server.dirty++;
    addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",(unsigned long)totlen));
}
