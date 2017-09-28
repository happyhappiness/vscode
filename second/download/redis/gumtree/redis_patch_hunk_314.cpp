     } else {
         long bytes = end-start+1;
 
         addReplyLongLong(c,redisPopcount(p+start,bytes));
     }
 }
+
+/* BITPOS key bit [start [end]] */
+void bitposCommand(redisClient *c) {
+    robj *o;
+    long bit, start, end, strlen;
+    unsigned char *p;
+    char llbuf[32];
+    int end_given = 0;
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
+    if (c->argc == 4 || c->argc == 5) {
+        if (getLongFromObjectOrReply(c,c->argv[3],&start,NULL) != REDIS_OK)
+            return;
+        if (c->argc == 5) {
+            if (getLongFromObjectOrReply(c,c->argv[4],&end,NULL) != REDIS_OK)
+                return;
+            end_given = 1;
+        } else {
+            end = strlen-1;
+        }
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
+        /* If we are looking for clear bits, and the user specified an exact
+         * range with start-end, we can't consider the right of the range as
+         * zero padded (as we do when no explicit end is given).
+         *
+         * So if redisBitpos() returns the first bit outside the range,
+         * we return -1 to the caller, to mean, in the specified range there
+         * is not a single "0" bit. */
+        if (end_given && bit == 0 && pos == bytes*8) {
+            addReplyLongLong(c,-1);
+            return;
+        }
+        if (pos != -1) pos += start*8; /* Adjust for the bytes we skipped. */
+        addReplyLongLong(c,pos);
+    }
+}
