            addReply(c,shared.wrongtypeerr);
            return;
        }

        append = getDecodedObject(c->argv[2]);
        if (o->encoding == REDIS_ENCODING_RAW &&
            (sdslen(o->ptr) + sdslen(append->ptr)) > 512*1024*1024)
        {
            addReplyError(c,"string exceeds maximum allowed size (512MB)");
            decrRefCount(append);
            return;
        }

        /* If the object is shared or encoded, we have to make a copy */
        if (o->refcount != 1 || o->encoding != REDIS_ENCODING_RAW) {
            robj *decoded = getDecodedObject(o);
            o = createStringObject(decoded->ptr, sdslen(decoded->ptr));
            decrRefCount(decoded);
            dbReplace(c->db,c->argv[1],o);
        }

        /* Append the value */
        o->ptr = sdscatlen(o->ptr,append->ptr,sdslen(append->ptr));
        decrRefCount(append);
        totlen = sdslen(o->ptr);
    }
    touchWatchedKey(c->db,c->argv[1]);
    server.dirty++;
    addReplyLongLong(c,totlen);
}

void strlenCommand(redisClient *c) {
    robj *o;

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,REDIS_STRING)) return;

    if (o->encoding == REDIS_ENCODING_RAW) {
        addReplyLongLong(c,sdslen(o->ptr));
    } else if (o->encoding == REDIS_ENCODING_INT) {
        char llbuf[32];
        int len = ll2string(llbuf,sizeof(llbuf),(long)o->ptr);
        addReplyLongLong(c,len);
    } else {
        redisPanic("Unknown string encoding");
    }
}

