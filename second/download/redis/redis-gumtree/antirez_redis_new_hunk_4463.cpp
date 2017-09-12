        } else {
            char *eptr;

            if (o->encoding == REDIS_ENCODING_RAW)
                value = strtoll(o->ptr, &eptr, 10);
            else if (o->encoding == REDIS_ENCODING_INT)
                value = (long)o->ptr;
            else
                assert(1 != 1);
        }
    }

    value += incr;
    o = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
    tryObjectEncoding(o);
    retval = dictAdd(c->db->dict,c->argv[1],o);
    if (retval == DICT_ERR) {
        dictReplace(c->db->dict,c->argv[1],o);
