            robj *lenobj;

            lenobj = createObject(REDIS_STRING,
                sdscatprintf(sdsempty(),"%d\r\n",sdslen(argv[j]->ptr)));
            lenobj->refcount = 0;
            outv[outc++] = lenobj;
        }
