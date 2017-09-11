                (long long) sdsavail(val->ptr),
                (long long) getStringObjectSdsUsedMemory(val));
        }
    } else if (!strcasecmp(c->argv[1]->ptr,"ziplist") && c->argc == 3) {
        robj *o;

        if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nokeyerr))
                == NULL) return;

        if (o->encoding != OBJ_ENCODING_ZIPLIST) {
            addReplyError(c,"Not an sds encoded string.");
        } else {
            ziplistRepr(o->ptr);
            addReplyStatus(c,"Ziplist structure printed on stdout");
        }
    } else if (!strcasecmp(c->argv[1]->ptr,"populate") &&
               (c->argc == 3 || c->argc == 4)) {
        long keys, j;
