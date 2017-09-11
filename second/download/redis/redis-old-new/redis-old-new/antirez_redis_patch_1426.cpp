@@ -98,7 +98,9 @@
 /* We know a positive increment can only be 1 because entries can only be
  * pushed one at a time. */
 #define ZIPLIST_INCR_LENGTH(zl,incr) { \
-    if (ZIPLIST_LENGTH(zl) < UINT16_MAX) ZIPLIST_LENGTH(zl)+=incr; }
+    if (ZIPLIST_LENGTH(zl) < UINT16_MAX) \
+        ZIPLIST_LENGTH(zl) += intrev16ifbe(incr); \
+}
 
 typedef struct zlentry {
     unsigned int prevrawlensize, prevrawlen;
@@ -335,8 +337,8 @@ static unsigned int zipRawEntryLength(unsigned char *p) {
 unsigned char *ziplistNew(void) {
     unsigned int bytes = ZIPLIST_HEADER_SIZE+1;
     unsigned char *zl = zmalloc(bytes);
-    ZIPLIST_BYTES(zl) = bytes;
-    ZIPLIST_TAIL_OFFSET(zl) = ZIPLIST_HEADER_SIZE;
+    ZIPLIST_BYTES(zl) = intrev32ifbe(bytes);
+    ZIPLIST_TAIL_OFFSET(zl) = intrev32ifbe(ZIPLIST_HEADER_SIZE);
     ZIPLIST_LENGTH(zl) = 0;
     zl[bytes-1] = ZIP_END;
     return zl;
@@ -345,7 +347,7 @@ unsigned char *ziplistNew(void) {
 /* Resize the ziplist. */
 static unsigned char *ziplistResize(unsigned char *zl, unsigned int len) {
     zl = zrealloc(zl,len);
-    ZIPLIST_BYTES(zl) = len;
+    ZIPLIST_BYTES(zl) = intrev32ifbe(len);
     zl[len-1] = ZIP_END;
     return zl;
 }
@@ -371,7 +373,7 @@ static unsigned char *ziplistResize(unsigned char *zl, unsigned int len) {
  * The pointer "p" points to the first entry that does NOT need to be
  * updated, i.e. consecutive fields MAY need an update. */
 static unsigned char *__ziplistCascadeUpdate(unsigned char *zl, unsigned char *p) {
-    size_t curlen = ZIPLIST_BYTES(zl), rawlen, rawlensize;
+    size_t curlen = intrev32ifbe(ZIPLIST_BYTES(zl)), rawlen, rawlensize;
     size_t offset, noffset, extra;
     unsigned char *np;
     zlentry cur, next;
@@ -401,8 +403,8 @@ static unsigned char *__ziplistCascadeUpdate(unsigned char *zl, unsigned char *p
             noffset = np-zl;
 
             /* Update tail offset when next element is not the tail element. */
-            if ((zl+ZIPLIST_TAIL_OFFSET(zl)) != np)
-                ZIPLIST_TAIL_OFFSET(zl) += extra;
+            if ((zl+intrev32ifbe(ZIPLIST_TAIL_OFFSET(zl))) != np)
+                ZIPLIST_TAIL_OFFSET(zl) += intrev32ifbe(extra);
 
             /* Move the tail to the back. */
             memmove(np+rawlensize,
@@ -453,25 +455,27 @@ static unsigned char *__ziplistDelete(unsigned char *zl, unsigned char *p, unsig
             zipPrevEncodeLength(p-nextdiff,first.prevrawlen);
 
             /* Update offset for tail */
-            ZIPLIST_TAIL_OFFSET(zl) -= totlen;
+            ZIPLIST_TAIL_OFFSET(zl) -= intrev32ifbe(totlen);
 
             /* When the tail contains more than one entry, we need to take
              * "nextdiff" in account as well. Otherwise, a change in the
              * size of prevlen doesn't have an effect on the *tail* offset. */
             tail = zipEntry(p);
             if (p[tail.headersize+tail.len] != ZIP_END)
-                ZIPLIST_TAIL_OFFSET(zl) += nextdiff;
+                ZIPLIST_TAIL_OFFSET(zl) += intrev32ifbe(nextdiff);
 
             /* Move tail to the front of the ziplist */
-            memmove(first.p,p-nextdiff,ZIPLIST_BYTES(zl)-(p-zl)-1+nextdiff);
+            memmove(first.p,p-nextdiff,
+                intrev32ifbe(ZIPLIST_BYTES(zl))-(p-zl)-1+nextdiff);
         } else {
             /* The entire tail was deleted. No need to move memory. */
-            ZIPLIST_TAIL_OFFSET(zl) = (first.p-zl)-first.prevrawlen;
+            ZIPLIST_TAIL_OFFSET(zl) =
+                intrev32ifbe((first.p-zl)-first.prevrawlen);
         }
 
         /* Resize and update length */
         offset = first.p-zl;
-        zl = ziplistResize(zl, ZIPLIST_BYTES(zl)-totlen+nextdiff);
+        zl = ziplistResize(zl, intrev32ifbe(ZIPLIST_BYTES(zl))-totlen+nextdiff);
         ZIPLIST_INCR_LENGTH(zl,-deleted);
         p = zl+offset;
 
@@ -485,7 +489,7 @@ static unsigned char *__ziplistDelete(unsigned char *zl, unsigned char *p, unsig
 
 /* Insert item at "p". */
 static unsigned char *__ziplistInsert(unsigned char *zl, unsigned char *p, unsigned char *s, unsigned int slen) {
-    size_t curlen = ZIPLIST_BYTES(zl), reqlen, prevlen = 0;
+    size_t curlen = intrev32ifbe(ZIPLIST_BYTES(zl)), reqlen, prevlen = 0;
     size_t offset;
     int nextdiff = 0;
     unsigned char encoding = 0;
@@ -538,17 +542,17 @@ static unsigned char *__ziplistInsert(unsigned char *zl, unsigned char *p, unsig
         zipPrevEncodeLength(p+reqlen,reqlen);
 
         /* Update offset for tail */
-        ZIPLIST_TAIL_OFFSET(zl) += reqlen;
+        ZIPLIST_TAIL_OFFSET(zl) += intrev32ifbe(reqlen);
 
         /* When the tail contains more than one entry, we need to take
          * "nextdiff" in account as well. Otherwise, a change in the
          * size of prevlen doesn't have an effect on the *tail* offset. */
         tail = zipEntry(p+reqlen);
         if (p[reqlen+tail.headersize+tail.len] != ZIP_END)
-            ZIPLIST_TAIL_OFFSET(zl) += nextdiff;
+            ZIPLIST_TAIL_OFFSET(zl) += intrev32ifbe(nextdiff);
     } else {
         /* This element will be the new tail. */
-        ZIPLIST_TAIL_OFFSET(zl) = p-zl;
+        ZIPLIST_TAIL_OFFSET(zl) = intrev32ifbe(p-zl);
     }
 
     /* When nextdiff != 0, the raw length of the next entry has changed, so
@@ -720,8 +724,8 @@ unsigned int ziplistCompare(unsigned char *p, unsigned char *sstr, unsigned int
 /* Return length of ziplist. */
 unsigned int ziplistLen(unsigned char *zl) {
     unsigned int len = 0;
-    if (ZIPLIST_LENGTH(zl) < UINT16_MAX) {
-        len = ZIPLIST_LENGTH(zl);
+    if (intrev16ifbe(ZIPLIST_LENGTH(zl)) < UINT16_MAX) {
+        len = intrev16ifbe(ZIPLIST_LENGTH(zl));
     } else {
         unsigned char *p = zl+ZIPLIST_HEADER_SIZE;
         while (*p != ZIP_END) {
@@ -730,14 +734,14 @@ unsigned int ziplistLen(unsigned char *zl) {
         }
 
         /* Re-store length if small enough */
-        if (len < UINT16_MAX) ZIPLIST_LENGTH(zl) = len;
+        if (len < UINT16_MAX) ZIPLIST_LENGTH(zl) = intrev16ifbe(len);
     }
     return len;
 }
 
 /* Return ziplist blob size in bytes. */
 size_t ziplistBlobLen(unsigned char *zl) {
-    return ZIPLIST_BYTES(zl);
+    return intrev32ifbe(ZIPLIST_BYTES(zl));
 }
 
 void ziplistRepr(unsigned char *zl) {
@@ -749,9 +753,9 @@ void ziplistRepr(unsigned char *zl) {
         "{total bytes %d} "
         "{length %u}\n"
         "{tail offset %u}\n",
-        ZIPLIST_BYTES(zl),
-        ZIPLIST_LENGTH(zl),
-        ZIPLIST_TAIL_OFFSET(zl));
+        intrev32ifbe(ZIPLIST_BYTES(zl)),
+        intrev16ifbe(ZIPLIST_LENGTH(zl)),
+        intrev32ifbe(ZIPLIST_TAIL_OFFSET(zl)));
     p = ZIPLIST_ENTRY_HEAD(zl);
     while(*p != ZIP_END) {
         entry = zipEntry(p);
@@ -852,7 +856,7 @@ void stress(int pos, int num, int maxsize, int dnum) {
             zl = ziplistDeleteRange(zl,0,1);
         }
         printf("List size: %8d, bytes: %8d, %dx push+pop (%s): %6lld usec\n",
-            i,ZIPLIST_BYTES(zl),num,posstr[pos],usec()-start);
+            i,intrev32ifbe(ZIPLIST_BYTES(zl)),num,posstr[pos],usec()-start);
         zfree(zl);
     }
 }