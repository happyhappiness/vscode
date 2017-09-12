@@ -226,6 +226,14 @@ static unsigned int zipPrevEncodeLength(unsigned char *p, unsigned int len) {
     }
 }
 
+/* Encode the length of the previous entry and write it to "p". This only
+ * uses the larger encoding (required in __ziplistCascadeUpdate). */
+static void zipPrevEncodeLengthForceLarge(unsigned char *p, unsigned int len) {
+    if (p == NULL) return;
+    p[0] = ZIP_BIGLEN;
+    memcpy(p+1,&len,sizeof(len));
+}
+
 /* Return the difference in number of bytes needed to store the new length
  * "len" on the entry pointed to by "p". */
 static int zipPrevLenByteDiff(unsigned char *p, unsigned int len) {
@@ -344,11 +352,86 @@ static unsigned char *ziplistResize(unsigned char *zl, unsigned int len) {
     return zl;
 }
 
+/* When an entry is inserted, we need to set the prevlen field of the next
+ * entry to equal the length of the inserted entry. It can occur that this
+ * length cannot be encoded in 1 byte and the next entry needs to be grow
+ * a bit larger to hold the 5-byte encoded prevlen. This can be done for free,
+ * because this only happens when an entry is already being inserted (which
+ * causes a realloc and memmove). However, encoding the prevlen may require
+ * that this entry is grown as well. This effect may cascade throughout
+ * the ziplist when there are consecutive entries with a size close to
+ * ZIP_BIGLEN, so we need to check that the prevlen can be encoded in every
+ * consecutive entry.
+ *
+ * Note that this effect can also happen in reverse, where the bytes required
+ * to encode the prevlen field can shrink. This effect is deliberately ignored,
+ * because it can cause a "flapping" effect where a chain prevlen fields is
+ * first grown and then shrunk again after consecutive inserts. Rather, the
+ * field is allowed to stay larger than necessary, because a large prevlen
+ * field implies the ziplist is holding large entries anyway.
+ *
+ * The pointer "p" points to the first entry that does NOT need to be
+ * updated, i.e. consecutive fields MAY need an update. */
+static unsigned char *__ziplistCascadeUpdate(unsigned char *zl, unsigned char *p) {
+    unsigned int curlen = ZIPLIST_BYTES(zl), rawlen, rawlensize;
+    unsigned int offset, noffset, extra;
+    unsigned char *np;
+    zlentry cur, next;
+
+    while (p[0] != ZIP_END) {
+        cur = zipEntry(p);
+        rawlen = cur.headersize + cur.len;
+        rawlensize = zipPrevEncodeLength(NULL,rawlen);
+
+        /* Abort if there is no next entry. */
+        if (p[rawlen] == ZIP_END) break;
+        next = zipEntry(p+rawlen);
+
+        /* Abort when "prevlen" has not changed. */
+        if (next.prevrawlen == rawlen) break;
+
+        if (next.prevrawlensize < rawlensize) {
+            /* The "prevlen" field of "next" needs more bytes to hold
+             * the raw length of "cur". */
+            offset = p-zl;
+            extra = rawlensize-next.prevrawlensize;
+            zl = ziplistResize(zl,curlen+extra);
+            ZIPLIST_TAIL_OFFSET(zl) += extra;
+            p = zl+offset;
+
+            /* Move the tail to the back. */
+            np = p+rawlen;
+            noffset = np-zl;
+            memmove(np+rawlensize,
+                np+next.prevrawlensize,
+                curlen-noffset-next.prevrawlensize-1);
+            zipPrevEncodeLength(np,rawlen);
+
+            /* Advance the cursor */
+            p += rawlen;
+        } else {
+            if (next.prevrawlensize > rawlensize) {
+                /* This would result in shrinking, which we want to avoid.
+                 * So, set "rawlen" in the available bytes. */
+                zipPrevEncodeLengthForceLarge(p+rawlen,rawlen);
+            } else {
+                zipPrevEncodeLength(p+rawlen,rawlen);
+            }
+
+            /* Stop here, as the raw length of "next" has not changed. */
+            break;
+        }
+    }
+    return zl;
+}
+
 /* Delete "num" entries, starting at "p". Returns pointer to the ziplist. */
 static unsigned char *__ziplistDelete(unsigned char *zl, unsigned char *p, unsigned int num) {
     unsigned int i, totlen, deleted = 0;
-    int nextdiff = 0;
-    zlentry first = zipEntry(p);
+    int offset, nextdiff = 0;
+    zlentry first, tail;
+
+    first = zipEntry(p);
     for (i = 0; p[0] != ZIP_END && i < num; i++) {
         p += zipRawEntryLength(p);
         deleted++;
@@ -365,7 +448,14 @@ static unsigned char *__ziplistDelete(unsigned char *zl, unsigned char *p, unsig
             zipPrevEncodeLength(p-nextdiff,first.prevrawlen);
 
             /* Update offset for tail */
-            ZIPLIST_TAIL_OFFSET(zl) -= totlen+nextdiff;
+            ZIPLIST_TAIL_OFFSET(zl) -= totlen;
+
+            /* When the tail contains more than one entry, we need to take
+             * "nextdiff" in account as well. Otherwise, a change in the
+             * size of prevlen doesn't have an effect on the *tail* offset. */
+            tail = zipEntry(p);
+            if (p[tail.headersize+tail.len] != ZIP_END)
+                ZIPLIST_TAIL_OFFSET(zl) += nextdiff;
 
             /* Move tail to the front of the ziplist */
             memmove(first.p,p-nextdiff,ZIPLIST_BYTES(zl)-(p-zl)-1+nextdiff);
@@ -375,8 +465,15 @@ static unsigned char *__ziplistDelete(unsigned char *zl, unsigned char *p, unsig
         }
 
         /* Resize and update length */
+        offset = first.p-zl;
         zl = ziplistResize(zl, ZIPLIST_BYTES(zl)-totlen+nextdiff);
         ZIPLIST_INCR_LENGTH(zl,-deleted);
+        p = zl+offset;
+
+        /* When nextdiff != 0, the raw length of the next entry has changed, so
+         * we need to cascade the update throughout the ziplist */
+        if (nextdiff != 0)
+            zl = __ziplistCascadeUpdate(zl,p);
     }
     return zl;
 }
@@ -385,19 +482,18 @@ static unsigned char *__ziplistDelete(unsigned char *zl, unsigned char *p, unsig
 static unsigned char *__ziplistInsert(unsigned char *zl, unsigned char *p, unsigned char *s, unsigned int slen) {
     unsigned int curlen = ZIPLIST_BYTES(zl), reqlen, prevlen = 0;
     unsigned int offset, nextdiff = 0;
-    unsigned char *tail;
     unsigned char encoding = 0;
     long long value;
-    zlentry entry;
+    zlentry entry, tail;
 
     /* Find out prevlen for the entry that is inserted. */
     if (p[0] != ZIP_END) {
         entry = zipEntry(p);
         prevlen = entry.prevrawlen;
     } else {
-        tail = ZIPLIST_ENTRY_TAIL(zl);
-        if (tail[0] != ZIP_END) {
-            prevlen = zipRawEntryLength(tail);
+        unsigned char *ptail = ZIPLIST_ENTRY_TAIL(zl);
+        if (ptail[0] != ZIP_END) {
+            prevlen = zipRawEntryLength(ptail);
         }
     }
 
@@ -429,15 +525,32 @@ static unsigned char *__ziplistInsert(unsigned char *zl, unsigned char *p, unsig
     if (p[0] != ZIP_END) {
         /* Subtract one because of the ZIP_END bytes */
         memmove(p+reqlen,p-nextdiff,curlen-offset-1+nextdiff);
+
         /* Encode this entry's raw length in the next entry. */
         zipPrevEncodeLength(p+reqlen,reqlen);
+
         /* Update offset for tail */
-        ZIPLIST_TAIL_OFFSET(zl) += reqlen+nextdiff;
+        ZIPLIST_TAIL_OFFSET(zl) += reqlen;
+
+        /* When the tail contains more than one entry, we need to take
+         * "nextdiff" in account as well. Otherwise, a change in the
+         * size of prevlen doesn't have an effect on the *tail* offset. */
+        tail = zipEntry(p+reqlen);
+        if (p[reqlen+tail.headersize+tail.len] != ZIP_END)
+            ZIPLIST_TAIL_OFFSET(zl) += nextdiff;
     } else {
         /* This element will be the new tail. */
         ZIPLIST_TAIL_OFFSET(zl) = p-zl;
     }
 
+    /* When nextdiff != 0, the raw length of the next entry has changed, so
+     * we need to cascade the update throughout the ziplist */
+    if (nextdiff != 0) {
+        offset = p-zl;
+        zl = __ziplistCascadeUpdate(zl,p+reqlen);
+        p = zl+offset;
+    }
+
     /* Write the entry */
     p += zipPrevEncodeLength(p,prevlen);
     p += zipEncodeLength(p,encoding,slen);
@@ -510,6 +623,7 @@ unsigned char *ziplistPrev(unsigned char *zl, unsigned char *p) {
         return NULL;
     } else {
         entry = zipEntry(p);
+        assert(entry.prevrawlen > 0);
         return p-entry.prevrawlen;
     }
 }
@@ -615,21 +729,52 @@ unsigned int ziplistSize(unsigned char *zl) {
 
 void ziplistRepr(unsigned char *zl) {
     unsigned char *p;
+    int index = 0;
     zlentry entry;
 
-    printf("{total bytes %d} {length %u}\n",ZIPLIST_BYTES(zl), ZIPLIST_LENGTH(zl));
+    printf(
+        "{total bytes %d} "
+        "{length %u}\n"
+        "{tail offset %u}\n",
+        ZIPLIST_BYTES(zl),
+        ZIPLIST_LENGTH(zl),
+        ZIPLIST_TAIL_OFFSET(zl));
     p = ZIPLIST_ENTRY_HEAD(zl);
     while(*p != ZIP_END) {
         entry = zipEntry(p);
-        printf("{offset %ld, header %u, payload %u} ",p-zl,entry.headersize,entry.len);
+        printf(
+            "{"
+                "addr 0x%08lx, "
+                "index %2d, "
+                "offset %5ld, "
+                "rl: %5u, "
+                "hs %2u, "
+                "pl: %5u, "
+                "pls: %2u, "
+                "payload %5u"
+            "} ",
+            (long unsigned int)p,
+            index,
+            p-zl,
+            entry.headersize+entry.len,
+            entry.headersize,
+            entry.prevrawlen,
+            entry.prevrawlensize,
+            entry.len);
         p += entry.headersize;
         if (ZIP_IS_STR(entry.encoding)) {
-            fwrite(p,entry.len,1,stdout);
+            if (entry.len > 40) {
+                fwrite(p,40,1,stdout);
+                printf("...");
+            } else {
+                fwrite(p,entry.len,1,stdout);
+            }
         } else {
             printf("%lld", (long long) zipLoadInteger(p,entry.encoding));
         }
         printf("\n");
         p += entry.len;
+        index++;
     }
     printf("{end}\n\n");
 }
@@ -1019,7 +1164,57 @@ int main(int argc, char **argv) {
             printf("ERROR: \"1025\"\n");
             return 1;
         }
-        printf("SUCCESS\n");
+        printf("SUCCESS\n\n");
+    }
+
+    printf("Stress with random payloads of different encoding:\n");
+    {
+        int i, idx, where, len;
+        long long v;
+        unsigned char *p;
+        char buf[0x4041]; /* max length of generated string */
+        zl = ziplistNew();
+        for (i = 0; i < 100000; i++) {
+            where = (rand() & 1) ? ZIPLIST_HEAD : ZIPLIST_TAIL;
+            if (rand() & 1) {
+                /* equally likely create a 16, 32 or 64 bit int */
+                v = (rand() & INT16_MAX) + ((1ll << 32) >> ((rand() % 3)*16));
+                v *= 2*(rand() & 1)-1; /* randomly flip sign */
+                sprintf(buf, "%lld", v);
+                zl = ziplistPush(zl, (unsigned char*)buf, strlen(buf), where);
+            } else {
+                /* equally likely generate 6, 14 or >14 bit length */
+                v = rand() & 0x3f;
+                v += 0x4000 >> ((rand() % 3)*8);
+                memset(buf, 'x', v);
+                zl = ziplistPush(zl, (unsigned char*)buf, v, where);
+            }
+
+            /* delete a random element */
+            if ((len = ziplistLen(zl)) >= 10) {
+                idx = rand() % len;
+                // printf("Delete index %d\n", idx);
+                // ziplistRepr(zl);
+                ziplistDeleteRange(zl, idx, 1);
+                // ziplistRepr(zl);
+                len--;
+            }
+
+            /* iterate from front to back */
+            idx = 0;
+            p = ziplistIndex(zl, 0);
+            while((p = ziplistNext(zl,p)))
+                idx++;
+            assert(len == idx+1);
+
+            /* iterate from back to front */
+            idx = 0;
+            p = ziplistIndex(zl, -1);
+            while((p = ziplistPrev(zl,p)))
+                idx++;
+            assert(len == idx+1);
+        }
+        printf("SUCCESS\n\n");
     }
 
     printf("Stress with variable ziplist size:\n");