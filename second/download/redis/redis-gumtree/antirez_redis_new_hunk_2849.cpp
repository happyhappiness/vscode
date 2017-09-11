        value = 0;
    }

    oldvalue = value;
    value += incr;
    if ((incr < 0 && value > oldvalue) || (incr > 0 && value < oldvalue)) {
        addReplyError(c,"increment or decrement would overflow");
        return;
    }
    new = createStringObjectFromLongLong(value);
    hashTypeTryObjectEncoding(o,&c->argv[2],NULL);
    hashTypeSet(o,c->argv[2],new);
