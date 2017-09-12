@@ -48,6 +48,9 @@
 #define ZIPLIST_TAIL_OFFSET(zl) (*((zl)+sizeof(unsigned int)))
 #define ZIPLIST_LENGTH(zl) (*((zl)+2*sizeof(unsigned int)))
 #define ZIPLIST_HEADER_SIZE (2*sizeof(unsigned int)+1)
+#define ZIPLIST_ENTRY_HEAD(zl) ((zl)+ZIPLIST_HEADER_SIZE)
+#define ZIPLIST_ENTRY_TAIL(zl) ((zl)+ZIPLIST_TAIL_OFFSET(zl))
+#define ZIPLIST_ENTRY_END(zl) ((zl)+ZIPLIST_BYTES(zl)-1)
 #define ZIPLIST_INCR_LENGTH(zl,incr) { \
     if (ZIPLIST_LENGTH(zl) < ZIP_BIGLEN) ZIPLIST_LENGTH(zl)+=incr; }
 
@@ -236,19 +239,6 @@ static unsigned char *ziplistResize(unsigned char *zl, unsigned int len) {
     return zl;
 }
 
-static unsigned char *ziplistHead(unsigned char *zl) {
-    return zl+ZIPLIST_HEADER_SIZE;
-}
-
-static unsigned char *ziplistTail(unsigned char *zl) {
-    unsigned char *p, *q;
-    p = q = ziplistHead(zl);
-    while (*p != ZIP_END) {
-        q = p;
-        p += zipRawEntryLength(p);
-    }
-    return q;
-
 /* Delete "num" entries, starting at "p". Returns pointer to the ziplist. */
 static unsigned char *__ziplistDelete(unsigned char *zl, unsigned char *p, int num) {
     unsigned int i, totlen, deleted = 0;
@@ -300,7 +290,7 @@ static unsigned char *__ziplistInsert(unsigned char *zl, unsigned char *p, unsig
         entry = zipEntry(p);
         prevlen = entry.prevrawlen;
     } else {
-        tail = ziplistTail(zl);
+        tail = ZIPLIST_ENTRY_TAIL(zl);
         if (tail[0] != ZIP_END) {
             prevlen = zipRawEntryLength(tail);
         }
@@ -355,7 +345,7 @@ static unsigned char *__ziplistInsert(unsigned char *zl, unsigned char *p, unsig
 
 unsigned char *ziplistPush(unsigned char *zl, unsigned char *s, unsigned int slen, int where) {
     unsigned char *p;
-    p = (where == ZIPLIST_HEAD) ? ziplistHead(zl) : (zl+ZIPLIST_BYTES(zl)-1);
+    p = (where == ZIPLIST_HEAD) ? ZIPLIST_ENTRY_HEAD(zl) : ZIPLIST_ENTRY_END(zl);
     return __ziplistInsert(zl,p,s,slen);
 }
 
@@ -366,7 +356,7 @@ unsigned char *ziplistPop(unsigned char *zl, sds *target, int where) {
     if (target) *target = NULL;
 
     /* Get pointer to element to remove */
-    p = (where == ZIPLIST_HEAD) ? ziplistHead(zl) : ziplistTail(zl);
+    p = (where == ZIPLIST_HEAD) ? ZIPLIST_ENTRY_HEAD(zl) : ZIPLIST_ENTRY_TAIL(zl);
     if (*p == ZIP_END) return zl;
 
     entry = zipEntry(p);
@@ -496,7 +486,7 @@ void ziplistRepr(unsigned char *zl) {
     zlentry entry;
 
     printf("{total bytes %d} {length %u}\n",ZIPLIST_BYTES(zl), ZIPLIST_LENGTH(zl));
-    p = ziplistHead(zl);
+    p = ZIPLIST_ENTRY_HEAD(zl);
     while(*p != ZIP_END) {
         entry = zipEntry(p);
         printf("{offset %ld, header %u, payload %u} ",p-zl,entry.headersize,entry.len);