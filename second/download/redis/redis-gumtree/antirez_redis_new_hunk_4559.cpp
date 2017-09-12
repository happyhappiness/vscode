    shared.crlf = createObject(REDIS_STRING,sdsnew("\r\n"));
    shared.ok = createObject(REDIS_STRING,sdsnew("+OK\r\n"));
    shared.err = createObject(REDIS_STRING,sdsnew("-ERR\r\n"));
    shared.emptybulk = createObject(REDIS_STRING,sdsnew("$0\r\n\r\n"));
    shared.czero = createObject(REDIS_STRING,sdsnew(":0\r\n"));
    shared.cone = createObject(REDIS_STRING,sdsnew(":1\r\n"));
    shared.nullbulk = createObject(REDIS_STRING,sdsnew("$-1\r\n"));
    shared.nullmultibulk = createObject(REDIS_STRING,sdsnew("*-1\r\n"));
    shared.emptymultibulk = createObject(REDIS_STRING,sdsnew("*0\r\n"));
    /* no such key */
    shared.minus1 = createObject(REDIS_STRING,sdsnew("-1\r\n"));
    shared.pong = createObject(REDIS_STRING,sdsnew("+PONG\r\n"));
    shared.wrongtypeerr = createObject(REDIS_STRING,sdsnew(
        "-ERR Operation against a key holding the wrong kind of value\r\n"));
    shared.nokeyerr = createObject(REDIS_STRING,sdsnew(
        "-ERR no such key\r\n"));
    shared.syntaxerr = createObject(REDIS_STRING,sdsnew(
        "-ERR syntax error\r\n"));
    shared.sameobjecterr = createObject(REDIS_STRING,sdsnew(
        "-ERR source and destination objects are the same\r\n"));
    shared.outofrangeerr = createObject(REDIS_STRING,sdsnew(
        "-ERR index out of range\r\n"));
    shared.space = createObject(REDIS_STRING,sdsnew(" "));
    shared.colon = createObject(REDIS_STRING,sdsnew(":"));
    shared.plus = createObject(REDIS_STRING,sdsnew("+"));
    shared.select0 = createStringObject("select 0\r\n",10);
    shared.select1 = createStringObject("select 1\r\n",10);
    shared.select2 = createStringObject("select 2\r\n",10);
