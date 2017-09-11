        checkType(c,o,REDIS_STRING)) return;
    addReplyLongLong(c,stringObjectLen(o));
}
