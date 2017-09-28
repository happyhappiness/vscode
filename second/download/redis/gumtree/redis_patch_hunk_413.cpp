         pos++;
         one >>= 1;
     }
 
     /* If we reached this point, there is a bug in the algorithm, since
      * the case of no match is handled as a special case before. */
-    redisPanic("End of redisBitpos() reached.");
+    serverPanic("End of redisBitpos() reached.");
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
+        bitval = (value & ((uint64_t)1<<(bits-1-j))) != 0;
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
+    if (value & ((uint64_t)1 << (bits-1)))
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
+    uint64_t max = (bits == 64) ? UINT64_MAX : (((uint64_t)1<<bits)-1);
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
+    int64_t max = (bits == 64) ? INT64_MAX : (((int64_t)1<<(bits-1))-1);
+    int64_t min = (-max)-1;
+
+    /* Note that maxincr and minincr could overflow, but we use the values
+     * only after checking 'value' range, so when we use it no overflow
+     * happens. */
+    int64_t maxincr = max-value;
+    int64_t minincr = min-value;
+
+    if (value > max || (bits != 64 && incr > maxincr) || (value >= 0 && incr > 0 && incr > maxincr))
+    {
+        if (limit) {
+            if (owtype == BFOVERFLOW_WRAP) {
+                goto handle_wrap;
+            } else if (owtype == BFOVERFLOW_SAT) {
+                *limit = max;
+            }
+        }
+        return 1;
+    } else if (value < min || (bits != 64 && incr < minincr) || (value < 0 && incr < 0 && incr < minincr)) {
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
 
 #define BITOP_AND   0
 #define BITOP_OR    1
 #define BITOP_XOR   2
 #define BITOP_NOT   3
 
+#define BITFIELDOP_GET 0
+#define BITFIELDOP_SET 1
+#define BITFIELDOP_INCRBY 2
+
+/* This helper function used by GETBIT / SETBIT parses the bit offset argument
+ * making sure an error is returned if it is negative or if it overflows
+ * Redis 512 MB limit for the string value.
+ *
+ * If the 'hash' argument is true, and 'bits is positive, then the command
+ * will also parse bit offsets prefixed by "#". In such a case the offset
+ * is multiplied by 'bits'. This is useful for the BITFIELD command. */
+int getBitOffsetFromArgument(client *c, robj *o, size_t *offset, int hash, int bits) {
+    long long loffset;
+    char *err = "bit offset is not an integer or out of range";
+    char *p = o->ptr;
+    size_t plen = sdslen(p);
+    int usehash = 0;
+
+    /* Handle #<offset> form. */
+    if (p[0] == '#' && hash && bits > 0) usehash = 1;
+
+    if (string2ll(p+usehash,plen-usehash,&loffset) == 0) {
+        addReplyError(c,err);
+        return C_ERR;
+    }
+
+    /* Adjust the offset by 'bits' for #<offset> form. */
+    if (usehash) loffset *= bits;
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
+        (*sign == 1 && llbits > 64) ||
+        (*sign == 0 && llbits > 63))
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
-void setbitCommand(redisClient *c) {
+void setbitCommand(client *c) {
     robj *o;
     char *err = "bit is not an integer or out of range";
     size_t bitoffset;
-    int byte, bit;
+    ssize_t byte, bit;
     int byteval, bitval;
     long on;
 
-    if (getBitOffsetFromArgument(c,c->argv[2],&bitoffset) != REDIS_OK)
+    if (getBitOffsetFromArgument(c,c->argv[2],&bitoffset,0,0) != C_OK)
         return;
 
-    if (getLongFromObjectOrReply(c,c->argv[3],&on,err) != REDIS_OK)
+    if (getLongFromObjectOrReply(c,c->argv[3],&on,err) != C_OK)
         return;
 
     /* Bits can only be set or cleared... */
     if (on & ~1) {
         addReplyError(c,err);
         return;
     }
 
-    o = lookupKeyWrite(c->db,c->argv[1]);
-    if (o == NULL) {
-        o = createObject(REDIS_STRING,sdsempty());
-        dbAdd(c->db,c->argv[1],o);
-    } else {
-        if (checkType(c,o,REDIS_STRING)) return;
-        o = dbUnshareStringValue(c->db,c->argv[1],o);
-    }
-
-    /* Grow sds value to the right length if necessary */
-    byte = bitoffset >> 3;
-    o->ptr = sdsgrowzero(o->ptr,byte+1);
+    if ((o = lookupStringForBitCommand(c,bitoffset)) == NULL) return;
 
     /* Get current values */
+    byte = bitoffset >> 3;
     byteval = ((uint8_t*)o->ptr)[byte];
     bit = 7 - (bitoffset & 0x7);
     bitval = byteval & (1 << bit);
 
     /* Update byte with new bit value and return original value */
     byteval &= ~(1 << bit);
     byteval |= ((on & 0x1) << bit);
     ((uint8_t*)o->ptr)[byte] = byteval;
     signalModifiedKey(c->db,c->argv[1]);
-    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"setbit",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(NOTIFY_STRING,"setbit",c->argv[1],c->db->id);
     server.dirty++;
     addReply(c, bitval ? shared.cone : shared.czero);
 }
 
 /* GETBIT key offset */
-void getbitCommand(redisClient *c) {
+void getbitCommand(client *c) {
     robj *o;
     char llbuf[32];
     size_t bitoffset;
     size_t byte, bit;
     size_t bitval = 0;
 
-    if (getBitOffsetFromArgument(c,c->argv[2],&bitoffset) != REDIS_OK)
+    if (getBitOffsetFromArgument(c,c->argv[2],&bitoffset,0,0) != C_OK)
         return;
 
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
-        checkType(c,o,REDIS_STRING)) return;
+        checkType(c,o,OBJ_STRING)) return;
 
     byte = bitoffset >> 3;
     bit = 7 - (bitoffset & 0x7);
     if (sdsEncodedObject(o)) {
         if (byte < sdslen(o->ptr))
             bitval = ((uint8_t*)o->ptr)[byte] & (1 << bit);
