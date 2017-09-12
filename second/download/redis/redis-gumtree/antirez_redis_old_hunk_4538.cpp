    shared.crlf = createObject(REDIS_STRING,sdsnew("\r\n"));
    shared.ok = createObject(REDIS_STRING,sdsnew("+OK\r\n"));
    shared.err = createObject(REDIS_STRING,sdsnew("-ERR\r\n"));
    shared.zerobulk = createObject(REDIS_STRING,sdsnew("0\r\n\r\n"));
    shared.nil = createObject(REDIS_STRING,sdsnew("nil\r\n"));
    shared.zero = createObject(REDIS_STRING,sdsnew("0\r\n"));
    shared.one = createObject(REDIS_STRING,sdsnew("1\r\n"));
    /* no such key */
    shared.minus1 = createObject(REDIS_STRING,sdsnew("-1\r\n"));
    /* operation against key holding a value of the wrong type */
    shared.minus2 = createObject(REDIS_STRING,sdsnew("-2\r\n"));
    /* src and dest objects are the same */
    shared.minus3 = createObject(REDIS_STRING,sdsnew("-3\r\n"));
    /* out of range argument */
    shared.minus4 = createObject(REDIS_STRING,sdsnew("-4\r\n"));
    shared.pong = createObject(REDIS_STRING,sdsnew("+PONG\r\n"));
    shared.wrongtypeerr = createObject(REDIS_STRING,sdsnew(
        "-ERR Operation against a key holding the wrong kind of value\r\n"));
    shared.wrongtypeerrbulk = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%d\r\n%s",-sdslen(shared.wrongtypeerr->ptr)+2,shared.wrongtypeerr->ptr));
    shared.nokeyerr = createObject(REDIS_STRING,sdsnew(
        "-ERR no such key\r\n"));
    shared.nokeyerrbulk = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%d\r\n%s",-sdslen(shared.nokeyerr->ptr)+2,shared.nokeyerr->ptr));
    shared.syntaxerr = createObject(REDIS_STRING,sdsnew(
        "-ERR syntax error\r\n"));
    shared.syntaxerrbulk = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%d\r\n%s",-sdslen(shared.syntaxerr->ptr)+2,shared.syntaxerr->ptr));
    shared.space = createObject(REDIS_STRING,sdsnew(" "));
    shared.select0 = createStringObject("select 0\r\n",10);
    shared.select1 = createStringObject("select 1\r\n",10);
    shared.select2 = createStringObject("select 2\r\n",10);
