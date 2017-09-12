void bitfieldCommand(client *c) {
    robj *o;
    size_t bitoffset;
    int j, numops = 0, changes = 0;
    struct bitfieldOp *ops = NULL; /* Array of ops to execute at end. */
    int owtype = BFOVERFLOW_WRAP; /* Overflow type. */

    for (j = 2; j < c->argc; j++) {
        int remargs = c->argc-j-1; /* Remaining args other than current. */
        char *subcmd = c->argv[j]->ptr; /* Current command name. */
        int opcode; /* Current operation code. */
        long long i64 = 0;  /* Signed SET value. */
        int sign = 0; /* Signed or unsigned type? */
        int bits = 0; /* Bitfield width in bits. */

        if (!strcasecmp(subcmd,"get") && remargs >= 2)
            opcode = BITFIELDOP_GET;
        else if (!strcasecmp(subcmd,"set") && remargs >= 3)
            opcode = BITFIELDOP_SET;
        else if (!strcasecmp(subcmd,"incrby") && remargs >= 3)
            opcode = BITFIELDOP_INCRBY;
        else if (!strcasecmp(subcmd,"overflow") && remargs >= 1) {
            char *owtypename = c->argv[j+1]->ptr;
            j++;
            if (!strcasecmp(owtypename,"wrap"))
                owtype = BFOVERFLOW_WRAP;
            else if (!strcasecmp(owtypename,"sat"))
                owtype = BFOVERFLOW_SAT;
            else if (!strcasecmp(owtypename,"fail"))
                owtype = BFOVERFLOW_FAIL;
            else {
                addReplyError(c,"Invalid OVERFLOW type specified");
                zfree(ops);
                return;
            }
            continue;
        } else {
            addReply(c,shared.syntaxerr);
            zfree(ops);
            return;
        }

        /* Get the type and offset arguments, common to all the ops. */
        if (getBitfieldTypeFromArgument(c,c->argv[j+1],&sign,&bits) != C_OK) {
            zfree(ops);
            return;
        }

        if (getBitOffsetFromArgument(c,c->argv[j+2],&bitoffset) != C_OK) {
            zfree(ops);
            return;
        }

        /* INCRBY and SET require another argument. */
        if (opcode != BITFIELDOP_GET) {
            if (getLongLongFromObjectOrReply(c,c->argv[j+3],&i64,NULL) != C_OK){
                zfree(ops);
                return;
            }
        }

        /* Populate the array of operations we'll process. */
        ops = zrealloc(ops,sizeof(*ops)*(numops+1));
        ops[numops].offset = bitoffset;
        ops[numops].i64 = i64;
        ops[numops].opcode = opcode;
        ops[numops].owtype = owtype;
        ops[numops].bits = bits;
        ops[numops].sign = sign;
        numops++;

        j += 3 - (opcode == BITFIELDOP_GET);
    }

    addReplyMultiBulkLen(c,numops);

    /* Actually process the operations. */
    for (j = 0; j < numops; j++) {
        struct bitfieldOp *thisop = ops+j;

        /* Execute the operation. */
        if (thisop->opcode == BITFIELDOP_SET ||
            thisop->opcode == BITFIELDOP_INCRBY)
        {
            /* SET and INCRBY: We handle both with the same code path
             * for simplicity. SET return value is the previous value so
             * we need fetch & store as well. */

            if ((o = lookupStringForBitCommand(c,bitoffset)) == NULL) return;

            if (thisop->sign) {
                int64_t oldval, newval, wrapped;
                int overflow;

                oldval = getSignedBitfield(o->ptr,thisop->offset,
                        thisop->bits);

                if (thisop->opcode == BITFIELDOP_INCRBY) {
                    newval = oldval + thisop->i64;
                    overflow = checkSignedBitfieldOverflow(oldval,
                            thisop->i64,thisop->bits,thisop->owtype,&wrapped);
                    if (overflow) newval = wrapped;
                    addReplyLongLong(c,newval);
                } else {
                    newval = thisop->i64;
                    overflow = checkSignedBitfieldOverflow(newval,
                            0,thisop->bits,thisop->owtype,&wrapped);
                    if (overflow) newval = wrapped;
                    addReplyLongLong(c,oldval);
                }
                /* If the overflow type is "FAIL", don't write. */
                if (!(overflow && thisop->owtype == BFOVERFLOW_FAIL)) {
                    setSignedBitfield(o->ptr,thisop->offset,
                                      thisop->bits,newval);
                }
            } else {
                uint64_t oldval, newval, wrapped;
                int overflow;

                oldval = getUnsignedBitfield(o->ptr,thisop->offset,
                        thisop->bits);

                if (thisop->opcode == BITFIELDOP_INCRBY) {
                    newval = oldval + thisop->i64;
                    overflow = checkUnsignedBitfieldOverflow(oldval,
                            thisop->i64,thisop->bits,thisop->owtype,&wrapped);
                    if (overflow) newval = wrapped;
                    addReplyLongLong(c,newval);
                } else {
                    newval = thisop->i64;
                    overflow = checkUnsignedBitfieldOverflow(newval,
                            0,thisop->bits,thisop->owtype,&wrapped);
                    if (overflow) newval = wrapped;
                    addReplyLongLong(c,oldval);
                }
                setUnsignedBitfield(o->ptr,thisop->offset,thisop->bits,newval);
            }
            changes++;
        } else {
            /* GET */
            o = lookupKeyRead(c->db,c->argv[1]);
            size_t olen = (o == NULL) ? 0 : sdslen(o->ptr);
            unsigned char buf[9];

            /* For GET we use a trick: before executing the operation
             * copy up to 9 bytes to a local buffer, so that we can easily
             * execute up to 64 bit operations that are at actual string
             * object boundaries. */
            memset(buf,0,9);
            unsigned char *src = o ? o->ptr : NULL;
            int i;
            size_t byte = thisop->offset >> 3;
            for (i = 0; i < 9; i++) {
                if (src == NULL || i+byte >= olen) break;
                buf[i] = src[i+byte];
            }

            /* Now operate on the copied buffer which is guaranteed
             * to be zero-padded. */
            if (thisop->sign) {
                int64_t val = getSignedBitfield(buf,thisop->offset-(byte*8),
                                            thisop->bits);
                addReplyLongLong(c,val);
            } else {
                uint64_t val = getUnsignedBitfield(buf,thisop->offset-(byte*8),
                                            thisop->bits);
                addReplyLongLong(c,val);
            }
        }
    }

    if (changes) {
        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent(NOTIFY_STRING,"setbit",c->argv[1],c->db->id);
        server.dirty += changes;
    }
    zfree(ops);
}