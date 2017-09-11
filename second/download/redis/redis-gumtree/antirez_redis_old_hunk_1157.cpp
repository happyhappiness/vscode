        val = dictGetVal(de);
        key = dictGetKey(de);

        if (val->type != REDIS_STRING || !sdsEncodedObject(val)) {
            addReplyError(c,"Not an sds encoded string.");
        } else {
            addReplyStatusFormat(c,
