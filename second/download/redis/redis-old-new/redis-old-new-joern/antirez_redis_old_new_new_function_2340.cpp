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