    if (getLongLongFromObjectOrReply(c,o,&value,NULL) != REDIS_OK) return;

    value += incr;
    o = createStringObjectFromLongLong(value);
    retval = dictAdd(c->db->dict,c->argv[1],o);
    if (retval == DICT_ERR) {
        dictReplace(c->db->dict,c->argv[1],o);
