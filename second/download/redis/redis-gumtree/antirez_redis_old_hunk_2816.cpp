    if (getLongLongFromObjectOrReply(c,o,&value,NULL) != REDIS_OK) return;

    oldvalue = value;
    value += incr;
    if ((incr < 0 && value > oldvalue) || (incr > 0 && value < oldvalue)) {
        addReplyError(c,"increment or decrement would overflow");
        return;
    }
    new = createStringObjectFromLongLong(value);
    if (o)
        dbOverwrite(c->db,c->argv[1],new);
