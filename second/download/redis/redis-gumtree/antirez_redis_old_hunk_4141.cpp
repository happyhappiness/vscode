            o->encoding = REDIS_ENCODING_INT;
            o->ptr = (void*)((long)value);
        } else {
            o->ptr = sdscatprintf(sdsempty(),"%lld",value);
        }
    }
    return o;
