            robj *lenobj;

            lenobj = createObject(REDIS_STRING,
                sdscatprintf(sdsempty(),"%lu\r\n",
                    stringObjectLen(argv[j])));
            lenobj->refcount = 0;
            outv[outc++] = lenobj;
