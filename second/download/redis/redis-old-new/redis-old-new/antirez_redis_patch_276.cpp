@@ -34,27 +34,6 @@
  * Helpers and low level bit functions.
  * -------------------------------------------------------------------------- */
 
-/* This helper function used by GETBIT / SETBIT parses the bit offset argument
- * making sure an error is returned if it is negative or if it overflows
- * Redis 512 MB limit for the string value. */
-static int getBitOffsetFromArgument(client *c, robj *o, size_t *offset) {
-    long long loffset;
-    char *err = "bit offset is not an integer or out of range";
-
-    if (getLongLongFromObjectOrReply(c,o,&loffset,err) != C_OK)
-        return C_ERR;
-
-    /* Limit offset to 512MB in bytes */
-    if ((loffset < 0) || ((unsigned long long)loffset >> 3) >= (512*1024*1024))
-    {
-        addReplyError(c,err);
-        return C_ERR;
-    }
-
-    *offset = (size_t)loffset;
-    return C_OK;
-}
-
 /* Count number of bits set in the binary array pointed by 's' and long
  * 'count' bytes. The implementation of this function is required to
  * work with a input string length up to 512 MB. */
@@ -199,6 +178,201 @@ long redisBitpos(void *s, unsigned long count, int bit) {
     return 0; /* Just to avoid warnings. */
 }
 
+/* The following set.*Bitfield and get.*Bitfield functions implement setting
+ * and getting arbitrary size (up to 64 bits) signed and unsigned integers
+ * at arbitrary positions into a bitmap.
+ *
+ * The representation considers the bitmap as having the bit number 0 to be
+ * the most significant bit of the first byte, and so forth, so for example
+ * setting a 5 bits unsigned integer to value 23 at offset 7 into a bitmap
+ * previously set to all zeroes, will produce the following representation:
+ *
+ * +--------+--------+
+ * |00000001|01110000|
+ * +--------+--------+
+ *
+ * When offsets and integer sizes are aligned to bytes boundaries, this is the
+ * same as big endian, however when such alignment does not exist, its important
+ * to also understand how the bits inside a byte are ordered.
+ *
+ * Note that this format follows the same convention as SETBIT and related
+ * commands.
+ */
+
+void setUnsignedBitfield(unsigned char *p, uint64_t offset, uint64_t bits, uint64_t value) {
+    uint64_t byte, bit, byteval, bitval, j;
+
+    for (j = 0; j < bits; j++) {
+        bitval = (value & (1<<(bits-1-j))) != 0;
+        byte = offset >> 3;
+        bit = 7 - (offset & 0x7);
+        byteval = p[byte];
+        byteval &= ~(1 << bit);
+        byteval |= bitval << bit;
+        p[byte] = byteval & 0xff;
+        offset++;
+    }
+}
+
+void setSignedBitfield(unsigned char *p, uint64_t offset, uint64_t bits, int64_t value) {
+    uint64_t uv;
+
+    if (value >= 0)
+        uv = value;
+    else
+        uv = UINT64_MAX + value + 1;
+    setUnsignedBitfield(p,offset,bits,uv);
+}
+
+uint64_t getUnsignedBitfield(unsigned char *p, uint64_t offset, uint64_t bits) {
+    uint64_t byte, bit, byteval, bitval, j, value = 0;
+
+    for (j = 0; j < bits; j++) {
+        byte = offset >> 3;
+        bit = 7 - (offset & 0x7);
+        byteval = p[byte];
+        bitval = (byteval >> bit) & 1;
+        value = (value<<1) | bitval;
+        offset++;
+    }
+    return value;
+}
+
+int64_t getSignedBitfield(unsigned char *p, uint64_t offset, uint64_t bits) {
+    int64_t value = getUnsignedBitfield(p,offset,bits);
+    /* If the top significant bit is 1, propagate it to all the
+     * higher bits for two complement representation of signed
+     * integers. */
+    if (value & (1 << (bits-1)))
+        value |= ((uint64_t)-1) << bits;
+    return value;
+}
+
+/* The following two functions detect overflow of a value in the context
+ * of storing it as an unsigned or signed integer with the specified
+ * number of bits. The functions both take the value and a possible increment.
+ * If no overflow could happen and the value+increment fit inside the limits,
+ * then zero is returned, otherwise in case of overflow, 1 is returned,
+ * otherwise in case of underflow, -1 is returned.
+ *
+ * When non-zero is returned (oferflow or underflow), if not NULL, *limit is
+ * set to the value the operation should result when an overflow happens,
+ * depending on the specified overflow semantics:
+ *
+ * For BFOVERFLOW_SAT if 1 is returned, *limit it is set maximum value that
+ * you can store in that integer. when -1 is returned, *limit is set to the
+ * minimum value that an integer of that size can represent.
+ *
+ * For BFOVERFLOW_WRAP *limit is set by performing the operation in order to
+ * "wrap" around towards zero for unsigned integers, or towards the most
+ * negative number that is possible to represent for signed integers. */
+
+#define BFOVERFLOW_WRAP 0
+#define BFOVERFLOW_SAT 1
+#define BFOVERFLOW_FAIL 2 /* Used by the BITFIELD command implementation. */
+
+int checkUnsignedBitfieldOverflow(uint64_t value, int64_t incr, uint64_t bits, int owtype, uint64_t *limit) {
+    uint64_t max = (bits == 64) ? UINT64_MAX : ((1<<bits)-1);
+    int64_t maxincr = max-value;
+    int64_t minincr = -value;
+
+    if (value > max || (incr > 0 && incr > maxincr)) {
+        if (limit) {
+            if (owtype == BFOVERFLOW_WRAP) {
+                goto handle_wrap;
+            } else if (owtype == BFOVERFLOW_SAT) {
+                *limit = max;
+            }
+        }
+        return 1;
+    } else if (incr < 0 && incr < minincr) {
+        if (limit) {
+            if (owtype == BFOVERFLOW_WRAP) {
+                goto handle_wrap;
+            } else if (owtype == BFOVERFLOW_SAT) {
+                *limit = 0;
+            }
+        }
+        return -1;
+    }
+    return 0;
+
+handle_wrap:
+    {
+        uint64_t mask = ((int64_t)-1) << bits;
+        uint64_t res = value+incr;
+
+        res &= ~mask;
+        *limit = res;
+    }
+    return 1;
+}
+
+int checkSignedBitfieldOverflow(int64_t value, int64_t incr, uint64_t bits, int owtype, int64_t *limit) {
+    int64_t max = (bits == 64) ? INT64_MAX : ((1<<(bits-1))-1);
+    int64_t min = (-max)-1;
+
+    /* Note that maxincr and minincr could overflow, but we use the values
+     * only after checking 'value' range, so when we use it no overflow
+     * happens. */
+    int64_t maxincr = max-value;
+    int64_t minincr = min-value;
+
+    if (value > max || (value >= 0 && incr > 0 && incr > maxincr)) {
+        if (limit) {
+            if (owtype == BFOVERFLOW_WRAP) {
+                goto handle_wrap;
+            } else if (owtype == BFOVERFLOW_SAT) {
+                *limit = max;
+            }
+        }
+        return 1;
+    } else if (value < min || (value < 0 && incr < 0 && incr < minincr)) {
+        if (limit) {
+            if (owtype == BFOVERFLOW_WRAP) {
+                goto handle_wrap;
+            } else if (owtype == BFOVERFLOW_SAT) {
+                *limit = min;
+            }
+        }
+        return -1;
+    }
+    return 0;
+
+handle_wrap:
+    {
+        uint64_t mask = ((int64_t)-1) << bits;
+        uint64_t msb = (uint64_t)1 << (bits-1);
+        uint64_t a = value, b = incr, c;
+        c = a+b; /* Perform addition as unsigned so that's defined. */
+
+        /* If the sign bit is set, propagate to all the higher order
+         * bits, to cap the negative value. If it's clear, mask to
+         * the positive integer limit. */
+        if (c & msb) {
+            c |= mask;
+        } else {
+            c &= ~mask;
+        }
+        *limit = c;
+    }
+    return 1;
+}
+
+/* Debugging function. Just show bits in the specified bitmap. Not used
+ * but here for not having to rewrite it when debugging is needed. */
+void printBits(unsigned char *p, unsigned long count) {
+    unsigned long j, i, byte;
+
+    for (j = 0; j < count; j++) {
+        byte = p[j];
+        for (i = 0x80; i > 0; i /= 2)
+            printf("%c", (byte & i) ? '1' : '0');
+        printf("|");
+    }
+    printf("\n");
+}
+
 /* -----------------------------------------------------------------------------
  * Bits related string commands: GETBIT, SETBIT, BITCOUNT, BITOP.
  * -------------------------------------------------------------------------- */
@@ -208,12 +382,90 @@ long redisBitpos(void *s, unsigned long count, int bit) {
 #define BITOP_XOR   2
 #define BITOP_NOT   3
 
+#define BITFIELDOP_GET 0
+#define BITFIELDOP_SET 1
+#define BITFIELDOP_INCRBY 2
+
+/* This helper function used by GETBIT / SETBIT parses the bit offset argument
+ * making sure an error is returned if it is negative or if it overflows
+ * Redis 512 MB limit for the string value. */
+int getBitOffsetFromArgument(client *c, robj *o, size_t *offset) {
+    long long loffset;
+    char *err = "bit offset is not an integer or out of range";
+
+    if (getLongLongFromObjectOrReply(c,o,&loffset,err) != C_OK)
+        return C_ERR;
+
+    /* Limit offset to 512MB in bytes */
+    if ((loffset < 0) || ((unsigned long long)loffset >> 3) >= (512*1024*1024))
+    {
+        addReplyError(c,err);
+        return C_ERR;
+    }
+
+    *offset = (size_t)loffset;
+    return C_OK;
+}
+
+/* This helper function for BITFIELD parses a bitfield type in the form
+ * <sign><bits> where sign is 'u' or 'i' for unsigned and signed, and
+ * the bits is a value between 1 and 64. However 64 bits unsigned integers
+ * are reported as an error because of current limitations of Redis protocol
+ * to return unsigned integer values greater than INT64_MAX.
+ *
+ * On error C_ERR is returned and an error is sent to the client. */
+int getBitfieldTypeFromArgument(client *c, robj *o, int *sign, int *bits) {
+    char *p = o->ptr;
+    char *err = "Invalid bitfield type. Use something like i16 u8. Note that u64 is not supported but i64 is.";
+    long long llbits;
+
+    if (p[0] == 'i') {
+        *sign = 1;
+    } else if (p[0] == 'u') {
+        *sign = 0;
+    } else {
+        addReplyError(c,err);
+        return C_ERR;
+    }
+
+    if ((string2ll(p+1,strlen(p+1),&llbits)) == 0 ||
+        llbits < 1 ||
+        (*sign == 1 && llbits > 63) ||
+        (*sign == 0 && llbits > 64))
+    {
+        addReplyError(c,err);
+        return C_ERR;
+    }
+    *bits = llbits;
+    return C_OK;
+}
+
+/* This is an helper function for commands implementations that need to write
+ * bits to a string object. The command creates or pad with zeroes the string
+ * so that the 'maxbit' bit can be addressed. The object is finally
+ * returned. Otherwise if the key holds a wrong type NULL is returned and
+ * an error is sent to the client. */
+robj *lookupStringForBitCommand(client *c, size_t maxbit) {
+    size_t byte = maxbit >> 3;
+    robj *o = lookupKeyWrite(c->db,c->argv[1]);
+
+    if (o == NULL) {
+        o = createObject(OBJ_STRING,sdsnewlen(NULL, byte+1));
+        dbAdd(c->db,c->argv[1],o);
+    } else {
+        if (checkType(c,o,OBJ_STRING)) return NULL;
+        o = dbUnshareStringValue(c->db,c->argv[1],o);
+        o->ptr = sdsgrowzero(o->ptr,byte+1);
+    }
+    return o;
+}
+
 /* SETBIT key offset bitvalue */
 void setbitCommand(client *c) {
     robj *o;
     char *err = "bit is not an integer or out of range";
     size_t bitoffset;
-    int byte, bit;
+    ssize_t byte, bit;
     int byteval, bitval;
     long on;
 
@@ -229,18 +481,10 @@ void setbitCommand(client *c) {
         return;
     }
 
-    byte = bitoffset >> 3;
-    o = lookupKeyWrite(c->db,c->argv[1]);
-    if (o == NULL) {
-        o = createObject(OBJ_STRING,sdsnewlen(NULL, byte+1));
-        dbAdd(c->db,c->argv[1],o);
-    } else {
-        if (checkType(c,o,OBJ_STRING)) return;
-        o = dbUnshareStringValue(c->db,c->argv[1],o);
-        o->ptr = sdsgrowzero(o->ptr,byte+1);
-    }
+    if ((o = lookupStringForBitCommand(c,bitoffset)) == NULL) return;
 
     /* Get current values */
+    byte = bitoffset >> 3;
     byteval = ((uint8_t*)o->ptr)[byte];
     bit = 7 - (bitoffset & 0x7);
     bitval = byteval & (1 << bit);
@@ -596,3 +840,201 @@ void bitposCommand(client *c) {
         addReplyLongLong(c,pos);
     }
 }
+
+/* BITFIELD key subcommmand-1 arg ... subcommand-2 arg ... subcommand-N ...
+ *
+ * Supported subcommands:
+ *
+ * GET <type> <offset>
+ * SET <type> <offset> <value>
+ * INCRBY <type> <offset> <increment>
+ * OVERFLOW [WRAP|SAT|FAIL]
+ */
+
+struct bitfieldOp {
+    uint64_t offset;    /* Bitfield offset. */
+    int64_t i64;        /* Increment amount (INCRBY) or SET value */
+    int opcode;         /* Operation id. */
+    int owtype;         /* Overflow type to use. */
+    int bits;           /* Integer bitfield bits width. */
+    int sign;           /* True if signed, otherwise unsigned op. */
+};
+
+void bitfieldCommand(client *c) {
+    robj *o;
+    size_t bitoffset;
+    int j, numops = 0, changes = 0;
+    struct bitfieldOp *ops = NULL; /* Array of ops to execute at end. */
+    int owtype = BFOVERFLOW_WRAP; /* Overflow type. */
+
+    for (j = 2; j < c->argc; j++) {
+        int remargs = c->argc-j-1; /* Remaining args other than current. */
+        char *subcmd = c->argv[j]->ptr; /* Current command name. */
+        int opcode; /* Current operation code. */
+        long long i64 = 0;  /* Signed SET value. */
+        int sign = 0; /* Signed or unsigned type? */
+        int bits = 0; /* Bitfield width in bits. */
+
+        if (!strcasecmp(subcmd,"get") && remargs >= 2)
+            opcode = BITFIELDOP_GET;
+        else if (!strcasecmp(subcmd,"set") && remargs >= 3)
+            opcode = BITFIELDOP_SET;
+        else if (!strcasecmp(subcmd,"incrby") && remargs >= 3)
+            opcode = BITFIELDOP_INCRBY;
+        else if (!strcasecmp(subcmd,"overflow") && remargs >= 1) {
+            char *owtypename = c->argv[j+1]->ptr;
+            j++;
+            if (!strcasecmp(owtypename,"wrap"))
+                owtype = BFOVERFLOW_WRAP;
+            else if (!strcasecmp(owtypename,"sat"))
+                owtype = BFOVERFLOW_SAT;
+            else if (!strcasecmp(owtypename,"fail"))
+                owtype = BFOVERFLOW_FAIL;
+            else {
+                addReplyError(c,"Invalid OVERFLOW type specified");
+                zfree(ops);
+                return;
+            }
+            continue;
+        } else {
+            addReply(c,shared.syntaxerr);
+            zfree(ops);
+            return;
+        }
+
+        /* Get the type and offset arguments, common to all the ops. */
+        if (getBitfieldTypeFromArgument(c,c->argv[j+1],&sign,&bits) != C_OK) {
+            zfree(ops);
+            return;
+        }
+
+        if (getBitOffsetFromArgument(c,c->argv[j+2],&bitoffset) != C_OK) {
+            zfree(ops);
+            return;
+        }
+
+        /* INCRBY and SET require another argument. */
+        if (opcode != BITFIELDOP_GET) {
+            if (getLongLongFromObjectOrReply(c,c->argv[j+3],&i64,NULL) != C_OK){
+                zfree(ops);
+                return;
+            }
+        }
+
+        /* Populate the array of operations we'll process. */
+        ops = zrealloc(ops,sizeof(*ops)*(numops+1));
+        ops[numops].offset = bitoffset;
+        ops[numops].i64 = i64;
+        ops[numops].opcode = opcode;
+        ops[numops].owtype = owtype;
+        ops[numops].bits = bits;
+        ops[numops].sign = sign;
+        numops++;
+
+        j += 3 - (opcode == BITFIELDOP_GET);
+    }
+
+    addReplyMultiBulkLen(c,numops);
+
+    /* Actually process the operations. */
+    for (j = 0; j < numops; j++) {
+        struct bitfieldOp *thisop = ops+j;
+
+        /* Execute the operation. */
+        if (thisop->opcode == BITFIELDOP_SET ||
+            thisop->opcode == BITFIELDOP_INCRBY)
+        {
+            /* SET and INCRBY: We handle both with the same code path
+             * for simplicity. SET return value is the previous value so
+             * we need fetch & store as well. */
+
+            if ((o = lookupStringForBitCommand(c,bitoffset)) == NULL) return;
+
+            if (thisop->sign) {
+                int64_t oldval, newval, wrapped;
+                int overflow;
+
+                oldval = getSignedBitfield(o->ptr,thisop->offset,
+                        thisop->bits);
+
+                if (thisop->opcode == BITFIELDOP_INCRBY) {
+                    newval = oldval + thisop->i64;
+                    overflow = checkSignedBitfieldOverflow(oldval,
+                            thisop->i64,thisop->bits,thisop->owtype,&wrapped);
+                    if (overflow) newval = wrapped;
+                    addReplyLongLong(c,newval);
+                } else {
+                    newval = thisop->i64;
+                    overflow = checkSignedBitfieldOverflow(newval,
+                            0,thisop->bits,thisop->owtype,&wrapped);
+                    if (overflow) newval = wrapped;
+                    addReplyLongLong(c,oldval);
+                }
+                /* If the overflow type is "FAIL", don't write. */
+                if (!(overflow && thisop->owtype == BFOVERFLOW_FAIL)) {
+                    setSignedBitfield(o->ptr,thisop->offset,
+                                      thisop->bits,newval);
+                }
+            } else {
+                uint64_t oldval, newval, wrapped;
+                int overflow;
+
+                oldval = getUnsignedBitfield(o->ptr,thisop->offset,
+                        thisop->bits);
+
+                if (thisop->opcode == BITFIELDOP_INCRBY) {
+                    newval = oldval + thisop->i64;
+                    overflow = checkUnsignedBitfieldOverflow(oldval,
+                            thisop->i64,thisop->bits,thisop->owtype,&wrapped);
+                    if (overflow) newval = wrapped;
+                    addReplyLongLong(c,newval);
+                } else {
+                    newval = thisop->i64;
+                    overflow = checkUnsignedBitfieldOverflow(newval,
+                            0,thisop->bits,thisop->owtype,&wrapped);
+                    if (overflow) newval = wrapped;
+                    addReplyLongLong(c,oldval);
+                }
+                setUnsignedBitfield(o->ptr,thisop->offset,thisop->bits,newval);
+            }
+            changes++;
+        } else {
+            /* GET */
+            o = lookupKeyRead(c->db,c->argv[1]);
+            size_t olen = (o == NULL) ? 0 : sdslen(o->ptr);
+            unsigned char buf[9];
+
+            /* For GET we use a trick: before executing the operation
+             * copy up to 9 bytes to a local buffer, so that we can easily
+             * execute up to 64 bit operations that are at actual string
+             * object boundaries. */
+            memset(buf,0,9);
+            unsigned char *src = o ? o->ptr : NULL;
+            int i;
+            size_t byte = thisop->offset >> 3;
+            for (i = 0; i < 9; i++) {
+                if (src == NULL || i+byte >= olen) break;
+                buf[i] = src[i+byte];
+            }
+
+            /* Now operate on the copied buffer which is guaranteed
+             * to be zero-padded. */
+            if (thisop->sign) {
+                int64_t val = getSignedBitfield(buf,thisop->offset-(byte*8),
+                                            thisop->bits);
+                addReplyLongLong(c,val);
+            } else {
+                uint64_t val = getUnsignedBitfield(buf,thisop->offset-(byte*8),
+                                            thisop->bits);
+                addReplyLongLong(c,val);
+            }
+        }
+    }
+
+    if (changes) {
+        signalModifiedKey(c->db,c->argv[1]);
+        notifyKeyspaceEvent(NOTIFY_STRING,"setbit",c->argv[1],c->db->id);
+        server.dirty += changes;
+    }
+    zfree(ops);
+}