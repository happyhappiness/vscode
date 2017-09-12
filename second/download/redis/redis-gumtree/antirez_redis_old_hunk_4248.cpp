            return;
        }
        zs = zsetobj->ptr;
        deleted = zslDeleteRange(zs->zsl,min,max,zs->dict);
        if (htNeedsResize(zs->dict)) dictResize(zs->dict);
        server.dirty += deleted;
        addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",deleted));
    }
}

static void zrangeGenericCommand(redisClient *c, int reverse) {
    robj *o;
    int start = atoi(c->argv[2]->ptr);
