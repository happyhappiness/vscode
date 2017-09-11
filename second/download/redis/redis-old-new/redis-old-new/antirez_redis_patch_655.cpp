@@ -404,14 +404,12 @@ static int64_t zipLoadInteger(unsigned char *p, unsigned char encoding) {
 }
 
 /* Return a struct with all information about an entry. */
-static zlentry zipEntry(unsigned char *p) {
-    zlentry e;
-
-    ZIP_DECODE_PREVLEN(p, e.prevrawlensize, e.prevrawlen);
-    ZIP_DECODE_LENGTH(p + e.prevrawlensize, e.encoding, e.lensize, e.len);
-    e.headersize = e.prevrawlensize + e.lensize;
-    e.p = p;
-    return e;
+static void zipEntry(unsigned char *p, zlentry *e) {
+
+    ZIP_DECODE_PREVLEN(p, e->prevrawlensize, e->prevrawlen);
+    ZIP_DECODE_LENGTH(p + e->prevrawlensize, e->encoding, e->lensize, e->len);
+    e->headersize = e->prevrawlensize + e->lensize;
+    e->p = p;
 }
 
 /* Create a new empty ziplist. */
@@ -460,13 +458,13 @@ static unsigned char *__ziplistCascadeUpdate(unsigned char *zl, unsigned char *p
     zlentry cur, next;
 
     while (p[0] != ZIP_END) {
-        cur = zipEntry(p);
+        zipEntry(p, &cur);
         rawlen = cur.headersize + cur.len;
         rawlensize = zipPrevEncodeLength(NULL,rawlen);
 
         /* Abort if there is no next entry. */
         if (p[rawlen] == ZIP_END) break;
-        next = zipEntry(p+rawlen);
+        zipEntry(p+rawlen, &next);
 
         /* Abort when "prevlen" has not changed. */
         if (next.prevrawlen == rawlen) break;
@@ -521,7 +519,7 @@ static unsigned char *__ziplistDelete(unsigned char *zl, unsigned char *p, unsig
     int nextdiff = 0;
     zlentry first, tail;
 
-    first = zipEntry(p);
+    zipEntry(p, &first);
     for (i = 0; p[0] != ZIP_END && i < num; i++) {
         p += zipRawEntryLength(p);
         deleted++;
@@ -545,7 +543,7 @@ static unsigned char *__ziplistDelete(unsigned char *zl, unsigned char *p, unsig
             /* When the tail contains more than one entry, we need to take
              * "nextdiff" in account as well. Otherwise, a change in the
              * size of prevlen doesn't have an effect on the *tail* offset. */
-            tail = zipEntry(p);
+            zipEntry(p, &tail);
             if (p[tail.headersize+tail.len] != ZIP_END) {
                 ZIPLIST_TAIL_OFFSET(zl) =
                    intrev32ifbe(intrev32ifbe(ZIPLIST_TAIL_OFFSET(zl))+nextdiff);
@@ -635,7 +633,7 @@ static unsigned char *__ziplistInsert(unsigned char *zl, unsigned char *p, unsig
         /* When the tail contains more than one entry, we need to take
          * "nextdiff" in account as well. Otherwise, a change in the
          * size of prevlen doesn't have an effect on the *tail* offset. */
-        tail = zipEntry(p+reqlen);
+        zipEntry(p+reqlen, &tail);
         if (p[reqlen+tail.headersize+tail.len] != ZIP_END) {
             ZIPLIST_TAIL_OFFSET(zl) =
                 intrev32ifbe(intrev32ifbe(ZIPLIST_TAIL_OFFSET(zl))+nextdiff);
@@ -748,7 +746,7 @@ unsigned int ziplistGet(unsigned char *p, unsigned char **sstr, unsigned int *sl
     if (p == NULL || p[0] == ZIP_END) return 0;
     if (sstr) *sstr = NULL;
 
-    entry = zipEntry(p);
+    zipEntry(p, &entry);
     if (ZIP_IS_STR(entry.encoding)) {
         if (sstr) {
             *slen = entry.len;
@@ -796,7 +794,7 @@ unsigned int ziplistCompare(unsigned char *p, unsigned char *sstr, unsigned int
     long long zval, sval;
     if (p[0] == ZIP_END) return 0;
 
-    entry = zipEntry(p);
+    zipEntry(p, &entry);
     if (ZIP_IS_STR(entry.encoding)) {
         /* Raw compare */
         if (entry.len == slen) {
@@ -913,7 +911,7 @@ void ziplistRepr(unsigned char *zl) {
         intrev32ifbe(ZIPLIST_TAIL_OFFSET(zl)));
     p = ZIPLIST_ENTRY_HEAD(zl);
     while(*p != ZIP_END) {
-        entry = zipEntry(p);
+        zipEntry(p, &entry);
         printf(
             "{"
                 "addr 0x%08lx, "
@@ -1076,10 +1074,10 @@ static void verify(unsigned char *zl, zlentry *e) {
 
     for (i = 0; i < len; i++) {
         memset(&e[i], 0, sizeof(zlentry));
-        e[i] = zipEntry(ziplistIndex(zl, i));
+        zipEntry(ziplistIndex(zl, i), &e[i]);
 
         memset(&_e, 0, sizeof(zlentry));
-        _e = zipEntry(ziplistIndex(zl, -len+i));
+        zipEntry(ziplistIndex(zl, -len+i), &_e);
 
         assert(memcmp(&e[i], &_e, sizeof(zlentry)) == 0);
     }