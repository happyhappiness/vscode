    addReplyLongLong(c,stringObjectLen(o));
}

#define BITOP_AND   0
#define BITOP_OR    1
#define BITOP_XOR   2
#define BITOP_NOT   3
/* BITOP op_name target_key src_key1 src_key2 src_key3 ... src_keyN */
void bitopCommand(redisClient *c) {
    char *opname = c->argv[1]->ptr;
    robj *o, *targetkey = c->argv[2];
    long op, j, numkeys;
    unsigned char **src; /* Array of source strings pointers. */
    long *len, maxlen = 0; /* Array of length of src strings, and max len. */
    unsigned char *res = NULL; /* Resulting string. */

    /* Parse the operation name. */
    if ((opname[0] == 'a' || opname[0] == 'A') && !strcasecmp(opname,"and"))
        op = BITOP_AND;
    else if((opname[0] == 'o' || opname[0] == 'O') && !strcasecmp(opname,"or"))
        op = BITOP_OR;
    else if((opname[0] == 'x' || opname[0] == 'X') && !strcasecmp(opname,"xor"))
        op = BITOP_XOR;
    else if((opname[0] == 'n' || opname[0] == 'N') && !strcasecmp(opname,"not"))
        op = BITOP_NOT;
    else {
        addReply(c,shared.syntaxerr);
        return;
    }

    /* Sanity check: NOT accepts only a single key argument. */
    if (op == BITOP_NOT && c->argc != 4) {
        addReplyError(c,"BITOP NOT must be called with a single source key.");
        return;
    }

    /* Lookup keys, and store pointers to the string objects into an array. */
    numkeys = c->argc - 3;
    src = zmalloc(sizeof(unsigned char*) * numkeys);
    len = zmalloc(sizeof(long) * numkeys);
    for (j = 0; j < numkeys; j++) {
        o = lookupKeyRead(c->db,c->argv[j+3]);
        /* Handle non-existing keys as empty strings. */
        if (o == NULL) {
            src[j] = NULL;
            len[j] = 0;
            continue;
        }
        /* Return an error if one of the keys is not a string. */
        if (checkType(c,o,REDIS_STRING)) {
            zfree(src);
            zfree(len);
            return;
        }
        src[j] = o->ptr;
        len[j] = sdslen(o->ptr);
        if (len[j] > maxlen) maxlen = len[j];
    }

    /* Compute the bit operation, if at least one string is not empty. */
    if (maxlen) {
        res = (unsigned char*) sdsnewlen(NULL,maxlen);
        unsigned char output, byte;
        long i;

        for (j = 0; j < maxlen; j++) {
            output = (len[0] <= j) ? 0 : src[0][j];
            if (op == BITOP_NOT) output = ~output;
            for (i = 1; i < numkeys; i++) {
                byte = (len[i] <= j) ? 0 : src[i][j];
                switch(op) {
                case BITOP_AND: output &= byte; break;
                case BITOP_OR:  output |= byte; break;
                case BITOP_XOR: output ^= byte; break;
                }
            }
            res[j] = output;
        }
    }
    zfree(src);
    zfree(len);

    /* Store the computed value into the target key */
    if (maxlen) {
        o = createObject(REDIS_STRING,res);
        setKey(c->db,targetkey,o);
        decrRefCount(o);
    } else if (dbDelete(c->db,targetkey)) {
        signalModifiedKey(c->db,targetkey);
    }
    server.dirty++;
    addReplyLongLong(c,maxlen); /* Return the output string length in bytes. */
}

/* BITCOUNT key [start end] */
void bitcountCommand(redisClient *c) {
    static const unsigned char bitsinbyte[256] = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8};
    robj *o;
    long start, end;
    unsigned char *p;
    char llbuf[32];
    size_t strlen;

    /* Lookup, check for type, and return 0 for non existing keys. */
    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,REDIS_STRING)) return;

    /* Set the 'p' pointer to the string, that can be just a stack allocated
     * array if our string was integer encoded. */
    if (o->encoding == REDIS_ENCODING_INT) {
        p = (unsigned char*) llbuf;
        strlen = ll2string(llbuf,sizeof(llbuf),(long)o->ptr);
    } else {
        p = (unsigned char*) o->ptr;
        strlen = sdslen(o->ptr);
    }

    /* Parse start/end range if any. */
    if (c->argc == 4) {
        if (getLongFromObjectOrReply(c,c->argv[2],&start,NULL) != REDIS_OK)
            return;
        if (getLongFromObjectOrReply(c,c->argv[3],&end,NULL) != REDIS_OK)
            return;
        /* Convert negative indexes */
        if (start < 0) start = strlen+start;
        if (end < 0) end = strlen+end;
        if (start < 0) start = 0;
        if (end < 0) end = 0;
        if ((unsigned)end >= strlen) end = strlen-1;
    } else if (c->argc == 2) {
        /* The whole string. */
        start = 0;
        end = strlen-1;
    } else {
        /* Syntax error. */
        addReply(c,shared.syntaxerr);
        return;
    }

    /* Precondition: end >= 0 && end < strlen, so the only condition where
     * zero can be returned is: start > end. */
    if (start > end) {
        addReply(c,shared.czero);
    } else {
        long bits = 0, bytes = end-start+1;

        /* We can finally count bits. */
        p += start;
        while(bytes--) bits += bitsinbyte[*p++];
        addReplyLongLong(c,bits);
    }
}
