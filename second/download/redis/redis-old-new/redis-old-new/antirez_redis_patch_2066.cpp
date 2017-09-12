@@ -51,6 +51,13 @@
 #define ZIPLIST_INCR_LENGTH(zl,incr) { \
     if (ZIPLIST_LENGTH(zl) < ZIP_BIGLEN) ZIPLIST_LENGTH(zl)+=incr; }
 
+typedef struct zlentry {
+    unsigned int prevrawlensize, prevrawlen;
+    unsigned int lensize, len;
+    unsigned int headersize;
+    unsigned char encoding;
+} zlentry;
+
 /* Return bytes needed to store integer encoded by 'encoding' */
 static unsigned int zipEncodingSize(char encoding) {
     if (encoding == ZIP_ENC_SHORT) {
@@ -192,6 +199,16 @@ static long long zipLoadInteger(unsigned char *p, char encoding) {
     return ret;
 }
 
+/* Return a struct with all information about an entry. */
+static zlentry zipEntry(unsigned char *p) {
+    zlentry e;
+    e.prevrawlen = zipDecodeLength(p,&e.prevrawlensize);
+    e.len = zipDecodeLength(p+e.prevrawlensize,&e.lensize);
+    e.headersize = e.prevrawlensize+e.lensize;
+    e.encoding = ZIP_ENCODING(p+e.prevrawlensize);
+    return e;
+}
+
 /* Return the total amount used by an entry (encoded length + payload). */
 static unsigned int zipRawEntryLength(unsigned char *p) {
     unsigned int prevlensize, lensize, len;
@@ -297,9 +314,8 @@ unsigned char *ziplistPush(unsigned char *zl, unsigned char *entry, unsigned int
 
 unsigned char *ziplistPop(unsigned char *zl, sds *target, int where) {
     unsigned int curlen = ZIPLIST_BYTES(zl), rawlen;
-    unsigned int prevrawlensize, prevrawlen, lensize, len, headerlen;
+    zlentry entry;
     int nextdiff = 0;
-    unsigned char encoding;
     unsigned char *p;
     long long value;
     if (target) *target = NULL;
@@ -308,16 +324,13 @@ unsigned char *ziplistPop(unsigned char *zl, sds *target, int where) {
     p = (where == ZIPLIST_HEAD) ? ziplistHead(zl) : ziplistTail(zl);
     if (*p == ZIP_END) return zl;
 
-    prevrawlen = zipDecodeLength(p,&prevrawlensize);
-    len = zipDecodeLength(p+prevrawlensize,&lensize);
-    headerlen = prevrawlensize+lensize;
-    rawlen = headerlen+len;
+    entry = zipEntry(p);
+    rawlen = entry.headersize+entry.len;
     if (target) {
-        encoding = ZIP_ENCODING(p+prevrawlensize);
-        if (encoding == ZIP_ENC_RAW) {
-            *target = sdsnewlen(p+headerlen,len);
+        if (entry.encoding == ZIP_ENC_RAW) {
+            *target = sdsnewlen(p+entry.headersize,entry.len);
         } else {
-            value = zipLoadInteger(p+headerlen,encoding);
+            value = zipLoadInteger(p+entry.headersize,entry.encoding);
             *target = sdscatprintf(sdsempty(), "%lld", value);
         }
     }
@@ -342,7 +355,7 @@ unsigned char *ziplistPop(unsigned char *zl, sds *target, int where) {
         ZIPLIST_TAIL_OFFSET(zl) -= rawlen+nextdiff;
     } else {
         /* Subtract the length of the previous element from the tail offset. */
-        ZIPLIST_TAIL_OFFSET(zl) -= prevrawlen;
+        ZIPLIST_TAIL_OFFSET(zl) -= entry.prevrawlen;
     }
 
     /* Resize and update length */
@@ -372,21 +385,19 @@ unsigned char *ziplistNext(unsigned char *p) {
  * to find out whether the string pointer or the integer value was set.
  * Return 0 if 'p' points to the end of the zipmap, 1 otherwise. */
 unsigned int ziplistGet(unsigned char *p, unsigned char **e, unsigned int *elen, long long *v) {
-    unsigned int prevrawlensize, lensize, len, headerlen;
+    zlentry entry;
     if (*p == ZIP_END) return 0;
     if (e) *e = NULL;
 
-    zipDecodeLength(p,&prevrawlensize);
-    len = zipDecodeLength(p+prevrawlensize,&lensize);
-    headerlen = prevrawlensize+lensize;
-    if (ZIP_ENCODING(p+prevrawlensize) == ZIP_ENC_RAW) {
+    entry = zipEntry(p);
+    if (entry.encoding == ZIP_ENC_RAW) {
         if (e) {
-            *elen = len;
-            *e = p+headerlen;
+            *elen = entry.len;
+            *e = p+entry.headersize;
         }
     } else {
         if (v) {
-            *v = zipLoadInteger(p+headerlen,ZIP_ENCODING(p+prevrawlensize));
+            *v = zipLoadInteger(p+entry.headersize,entry.encoding);
         }
     }
     return 1;
@@ -435,27 +446,25 @@ unsigned char *ziplistDelete(unsigned char *zl, unsigned char **p) {
 }
 
 /* Compare entry pointer to by 'p' with 'entry'. Return 1 if equal. */
-unsigned int ziplistCompare(unsigned char *p, unsigned char *entry, unsigned int elen) {
-    unsigned int prevrawlensize, lensize, len, headerlen;
-    char encoding;
-    long long val, eval;
+unsigned int ziplistCompare(unsigned char *p, unsigned char *s, unsigned int slen) {
+    zlentry entry;
+    unsigned char sencoding;
+    long long val, sval;
     if (*p == ZIP_END) return 0;
 
-    zipDecodeLength(p,&prevrawlensize);
-    len = zipDecodeLength(p+prevrawlensize,&lensize);
-    headerlen = prevrawlensize+lensize;
-    if (ZIP_ENCODING(p+prevrawlensize) == ZIP_ENC_RAW) {
+    entry = zipEntry(p);
+    if (entry.encoding == ZIP_ENC_RAW) {
         /* Raw compare */
-        if (len == elen) {
-            return memcmp(p+headerlen,entry,elen) == 0;
+        if (entry.len == slen) {
+            return memcmp(p+entry.headersize,s,slen) == 0;
         } else {
             return 0;
         }
     } else {
-        if (zipTryEncoding(entry,&eval,&encoding)) {
+        if (zipTryEncoding(s,&sval,&sencoding)) {
             /* Do integer compare */
-            val = zipLoadInteger(p+headerlen,ZIP_ENCODING(p+prevrawlensize));
-            return val == eval;
+            val = zipLoadInteger(p+entry.headersize,entry.encoding);
+            return val == sval;
         } else {
             /* Ziplist entry is integer encoded, but given entry is not. */
         }