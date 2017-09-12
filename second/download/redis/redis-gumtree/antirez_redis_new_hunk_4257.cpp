            return;
        }
        zs = zsetobj->ptr;
        deleted = zslDeleteRangeByScore(zs->zsl,min,max,zs->dict);
        if (htNeedsResize(zs->dict)) dictResize(zs->dict);
        server.dirty += deleted;
        addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",deleted));
