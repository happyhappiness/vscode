@@ -173,12 +173,12 @@ static int zipPrevLenByteDiff(unsigned char *p, unsigned int len) {
 /* Check if string pointed to by 'entry' can be encoded as an integer.
  * Stores the integer value in 'v' and its encoding in 'encoding'.
  * Warning: this function requires a NULL-terminated string! */
-static int zipTryEncoding(unsigned char *entry, long long *v, char *encoding) {
+static int zipTryEncoding(char *entry, long long *v, char *encoding) {
     long long value;
     char *eptr;
 
     if (entry[0] == '-' || (entry[0] >= '0' && entry[0] <= '9')) {
-        value = strtoll((char*)entry,&eptr,10);
+        value = strtoll(entry,&eptr,10);
         if (eptr[0] != '\0') return 0;
         if (value >= SHRT_MIN && value <= SHRT_MAX) {
             *encoding = ZIP_ENC_SHORT;
@@ -306,7 +306,7 @@ static unsigned char *__ziplistDelete(unsigned char *zl, unsigned char *p, int n
 }
 
 /* Insert item at "p". */
-static unsigned char *__ziplistInsert(unsigned char *zl, unsigned char *p, unsigned char *s, unsigned int slen) {
+static unsigned char *__ziplistInsert(unsigned char *zl, unsigned char *p, char *s, unsigned int slen) {
     unsigned int curlen = ZIPLIST_BYTES(zl), reqlen, prevlen = 0;
     unsigned int offset, nextdiff = 0;
     unsigned char *tail;
@@ -372,7 +372,7 @@ static unsigned char *__ziplistInsert(unsigned char *zl, unsigned char *p, unsig
     return zl;
 }
 
-unsigned char *ziplistPush(unsigned char *zl, unsigned char *s, unsigned int slen, int where) {
+unsigned char *ziplistPush(unsigned char *zl, char *s, unsigned int slen, int where) {
     unsigned char *p;
     p = (where == ZIPLIST_HEAD) ? ZIPLIST_ENTRY_HEAD(zl) : ZIPLIST_ENTRY_END(zl);
     return __ziplistInsert(zl,p,s,slen);
@@ -422,7 +422,7 @@ unsigned char *ziplistNext(unsigned char *p) {
  * on the encoding of the entry. 'e' is always set to NULL to be able
  * to find out whether the string pointer or the integer value was set.
  * Return 0 if 'p' points to the end of the zipmap, 1 otherwise. */
-unsigned int ziplistGet(unsigned char *p, unsigned char **sstr, unsigned int *slen, long long *sval) {
+unsigned int ziplistGet(unsigned char *p, char **sstr, unsigned int *slen, long long *sval) {
     zlentry entry;
     if (*p == ZIP_END) return 0;
     if (sstr) *sstr = NULL;
@@ -431,7 +431,7 @@ unsigned int ziplistGet(unsigned char *p, unsigned char **sstr, unsigned int *sl
     if (entry.encoding == ZIP_ENC_RAW) {
         if (sstr) {
             *slen = entry.len;
-            *sstr = p+entry.headersize;
+            *sstr = (char*)p+entry.headersize;
         }
     } else {
         if (sval) {
@@ -461,9 +461,9 @@ unsigned char *ziplistDelete(unsigned char *zl, unsigned char **p) {
 }
 
 /* Compare entry pointer to by 'p' with 'entry'. Return 1 if equal. */
-unsigned int ziplistCompare(unsigned char *p, unsigned char *sstr, unsigned int slen) {
+unsigned int ziplistCompare(unsigned char *p, char *sstr, unsigned int slen) {
     zlentry entry;
-    unsigned char sencoding;
+    char sencoding;
     long long val, sval;
     if (*p == ZIP_END) return 0;
 
@@ -535,10 +535,10 @@ void ziplistRepr(unsigned char *zl) {
 
 unsigned char *createList() {
     unsigned char *zl = ziplistNew();
-    zl = ziplistPush(zl, (unsigned char*)"foo", 3, ZIPLIST_TAIL);
-    zl = ziplistPush(zl, (unsigned char*)"quux", 4, ZIPLIST_TAIL);
-    zl = ziplistPush(zl, (unsigned char*)"hello", 5, ZIPLIST_HEAD);
-    zl = ziplistPush(zl, (unsigned char*)"1024", 4, ZIPLIST_TAIL);
+    zl = ziplistPush(zl, "foo", 3, ZIPLIST_TAIL);
+    zl = ziplistPush(zl, "quux", 4, ZIPLIST_TAIL);
+    zl = ziplistPush(zl, "hello", 5, ZIPLIST_HEAD);
+    zl = ziplistPush(zl, "1024", 4, ZIPLIST_TAIL);
     return zl;
 }
 
@@ -562,7 +562,8 @@ unsigned char *createIntList() {
 }
 
 int main(int argc, char **argv) {
-    unsigned char *zl, *p, *q, *entry;
+    unsigned char *zl, *p;
+    char *entry;
     unsigned int elen;
     long long value;
     sds s;
@@ -716,21 +717,21 @@ int main(int argc, char **argv) {
         p = ziplistIndex(zl, 0);
         if (!ziplistCompare(p,"hello",5)) {
             printf("ERROR: not \"hello\"\n");
-            return;
+            return 1;
         }
         if (ziplistCompare(p,"hella",5)) {
             printf("ERROR: \"hella\"\n");
-            return;
+            return 1;
         }
 
         p = ziplistIndex(zl, 3);
         if (!ziplistCompare(p,"1024",4)) {
             printf("ERROR: not \"1024\"\n");
-            return;
+            return 1;
         }
         if (ziplistCompare(p,"1025",4)) {
             printf("ERROR: \"1025\"\n");
-            return;
+            return 1;
         }
         printf("SUCCESS\n");
     }