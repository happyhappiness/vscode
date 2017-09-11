@@ -94,12 +94,99 @@ size_t redisPopcount(void *s, long count) {
                 ((((aux3 + (aux3 >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24) +
                 ((((aux4 + (aux4 >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24);
     }
-    /* Count the remaining bytes */
+    /* Count the remaining bytes. */
     p = (unsigned char*)p4;
     while(count--) bits += bitsinbyte[*p++];
     return bits;
 }
 
+/* Return the position of the first bit set to one (if 'bit' is 1) or
+ * zero (if 'bit' is 0) in the bitmap starting at 's' and long 'count' bytes.
+ *
+ * The function is guaranteed to return a value >= 0 if 'bit' is 0 since if
+ * no zero bit is found, it returns count*8 assuming the string is zero
+ * padded on the right. However if 'bit' is 1 it is possible that there is
+ * not a single set bit in the bitmap. In this special case -1 is returned. */
+long redisBitpos(void *s, long count, int bit) {
+    unsigned long *l;
+    unsigned char *c;
+    unsigned long skipval, word = 0, one;
+    long pos = 0; /* Position of bit, to return to the caller. */
+    int j;
+
+    /* Process whole words first, seeking for first word that is not
+     * all ones or all zeros respectively if we are lookig for zeros
+     * or ones. This is much faster with large strings having contiguous
+     * blocks of 1 or 0 bits compared to the vanilla bit per bit processing.
+     *
+     * Note that if we start from an address that is not aligned
+     * to sizeof(unsigned long) we consume it byte by byte until it is
+     * aligned. */
+
+    /* Skip initial bits not aligned to sizeof(unsigned long) byte by byte. */
+    skipval = bit ? 0 : UCHAR_MAX;
+    c = (unsigned char*) s;
+    while((unsigned long)c & (sizeof(*l)-1) && count) {
+        if (*c != skipval) break;
+        c++;
+        count--;
+        pos += 8;
+    }
+
+    /* Skip bits with full word step. */
+    skipval = bit ? 0 : ULONG_MAX;
+    l = (unsigned long*) c;
+    while (count >= sizeof(*l)) {
+        if (*l != skipval) break;
+        l++;
+        count -= sizeof(*l);
+        pos += sizeof(*l)*8;
+    }
+
+    /* Load bytes into "word" considering the first byte as the most significant
+     * (we basically consider it as written in big endian, since we consider the
+     * string as a set of bits from left to right, with the first bit at position
+     * zero.
+     *
+     * Note that the loading is designed to work even when the bytes left
+     * (count) are less than a full word. We pad it with zero on the right. */
+    c = (unsigned char*)l;
+    for (j = 0; j < sizeof(*l); j++) {
+        word <<= 8;
+        if (count) {
+            word |= *c;
+            c++;
+            count--;
+        }
+    }
+
+    /* Special case:
+     * If bits in the string are all zero and we are looking for one,
+     * return -1 to signal that there is not a single "1" in the whole
+     * string. This can't happen when we are looking for "0" as we assume
+     * that the right of the string is zero padded. */
+    if (bit == 1 && word == 0) return -1;
+
+    /* Last word left, scan bit by bit. The first thing we need is to
+     * have a single "1" set in the most significant position in an
+     * unsigned long. We don't know the size of the long so we use a
+     * simple trick. */
+    one = ULONG_MAX; /* All bits set to 1.*/
+    one >>= 1;       /* All bits set to 1 but the MSB. */
+    one = ~one;      /* All bits set to 0 but the MSB. */
+
+    while(one) {
+        if (((one & word) != 0) == bit) return pos;
+        pos++;
+        one >>= 1;
+    }
+
+    /* If we reached this point, there is a bug in the algorithm, since
+     * the case of no match is handled as a special case before. */
+    redisPanic("End of redisBitpos() reached.");
+    return 0; /* Just to avoid warnigns. */
+}
+
 /* -----------------------------------------------------------------------------
  * Bits related string commands: GETBIT, SETBIT, BITCOUNT, BITOP.
  * -------------------------------------------------------------------------- */
@@ -417,3 +504,84 @@ void bitcountCommand(redisClient *c) {
         addReplyLongLong(c,redisPopcount(p+start,bytes));
     }
 }
+
+/* BITPOS key bit [start end] */
+void bitposCommand(redisClient *c) {
+    robj *o;
+    long bit, start, end, strlen;
+    unsigned char *p;
+    char llbuf[32];
+
+    /* Parse the bit argument to understand what we are looking for, set
+     * or clear bits. */
+    if (getLongFromObjectOrReply(c,c->argv[2],&bit,NULL) != REDIS_OK)
+        return;
+    if (bit != 0 && bit != 1) {
+        addReplyError(c, "The bit argument must be 1 or 0.");
+        return;
+    }
+
+    /* If the key does not exist, from our point of view it is an infinite
+     * array of 0 bits. If the user is looking for the fist clear bit return 0,
+     * If the user is looking for the first set bit, return -1. */
+    if ((o = lookupKeyRead(c->db,c->argv[1])) == NULL) {
+        addReplyLongLong(c, bit ? -1 : 0);
+        return;
+    }
+    if (checkType(c,o,REDIS_STRING)) return;
+
+    /* Set the 'p' pointer to the string, that can be just a stack allocated
+     * array if our string was integer encoded. */
+    if (o->encoding == REDIS_ENCODING_INT) {
+        p = (unsigned char*) llbuf;
+        strlen = ll2string(llbuf,sizeof(llbuf),(long)o->ptr);
+    } else {
+        p = (unsigned char*) o->ptr;
+        strlen = sdslen(o->ptr);
+    }
+
+    /* Parse start/end range if any. */
+    if (c->argc == 5) {
+        if (getLongFromObjectOrReply(c,c->argv[3],&start,NULL) != REDIS_OK)
+            return;
+        if (getLongFromObjectOrReply(c,c->argv[4],&end,NULL) != REDIS_OK)
+            return;
+        /* Convert negative indexes */
+        if (start < 0) start = strlen+start;
+        if (end < 0) end = strlen+end;
+        if (start < 0) start = 0;
+        if (end < 0) end = 0;
+        if (end >= strlen) end = strlen-1;
+    } else if (c->argc == 3) {
+        /* The whole string. */
+        start = 0;
+        end = strlen-1;
+    } else {
+        /* Syntax error. */
+        addReply(c,shared.syntaxerr);
+        return;
+    }
+
+    /* For empty ranges (start > end) we return -1 as an empty range does
+     * not contain a 0 nor a 1. */
+    if (start > end) {
+        addReplyLongLong(c, -1);
+    } else {
+        long bytes = end-start+1;
+        long pos = redisBitpos(p+start,bytes,bit);
+
+        /* If we are looking for clear bits, and our range does not includes
+         * the end of the string, but terminates before, we can't consider the
+         * right of the range as zero padded.
+         *
+         * so if redisBitpos() returns the first bit outside the string,
+         * we return -1 to the caller, to mean, in the specified range there
+         * is not a single "0" bit. */
+        if (end != strlen-1 && bit == 0 && pos == bytes*8) {
+            addReplyLongLong(c,-1);
+            return;
+        }
+        if (pos != -1) pos += start*8; /* Adjust for the bytes we skipped. */
+        addReplyLongLong(c,pos);
+    }
+}