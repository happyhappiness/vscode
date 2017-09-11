@@ -67,11 +67,10 @@
 #include <assert.h>
 #include <limits.h>
 #include "zmalloc.h"
+#include "util.h"
 #include "ziplist.h"
 #include "endian.h"
 
-int ll2string(char *s, size_t len, long long value);
-
 #define ZIP_END 255
 #define ZIP_BIGLEN 254
 
@@ -252,22 +251,9 @@ static int zipPrevLenByteDiff(unsigned char *p, unsigned int len) {
  * Stores the integer value in 'v' and its encoding in 'encoding'. */
 static int zipTryEncoding(unsigned char *entry, unsigned int entrylen, long long *v, unsigned char *encoding) {
     long long value;
-    char *eptr;
-    char buf[32];
 
     if (entrylen >= 32 || entrylen == 0) return 0;
-    if (entry[0] == '-' || (entry[0] >= '0' && entry[0] <= '9')) {
-        int slen;
-
-        /* Perform a back-and-forth conversion to make sure that
-         * the string turned into an integer is not losing any info. */
-        memcpy(buf,entry,entrylen);
-        buf[entrylen] = '\0';
-        value = strtoll(buf,&eptr,10);
-        if (eptr[0] != '\0') return 0;
-        slen = ll2string(buf,32,value);
-        if (entrylen != (unsigned)slen || memcmp(buf,entry,slen)) return 0;
-
+    if (string2ll((char*)entry,entrylen,&value)) {
         /* Great, the string can be encoded. Check what's the smallest
          * of our encoding types that can hold this value. */
         if (value >= INT16_MIN && value <= INT16_MAX) {
@@ -385,8 +371,8 @@ static unsigned char *ziplistResize(unsigned char *zl, unsigned int len) {
  * The pointer "p" points to the first entry that does NOT need to be
  * updated, i.e. consecutive fields MAY need an update. */
 static unsigned char *__ziplistCascadeUpdate(unsigned char *zl, unsigned char *p) {
-    unsigned int curlen = ZIPLIST_BYTES(zl), rawlen, rawlensize;
-    unsigned int offset, noffset, extra;
+    size_t curlen = ZIPLIST_BYTES(zl), rawlen, rawlensize;
+    size_t offset, noffset, extra;
     unsigned char *np;
     zlentry cur, next;
 
@@ -408,12 +394,17 @@ static unsigned char *__ziplistCascadeUpdate(unsigned char *zl, unsigned char *p
             offset = p-zl;
             extra = rawlensize-next.prevrawlensize;
             zl = ziplistResize(zl,curlen+extra);
-            ZIPLIST_TAIL_OFFSET(zl) += extra;
             p = zl+offset;
 
-            /* Move the tail to the back. */
+            /* Current pointer and offset for next element. */
             np = p+rawlen;
             noffset = np-zl;
+
+            /* Update tail offset when next element is not the tail element. */
+            if ((zl+ZIPLIST_TAIL_OFFSET(zl)) != np)
+                ZIPLIST_TAIL_OFFSET(zl) += extra;
+
+            /* Move the tail to the back. */
             memmove(np+rawlensize,
                 np+next.prevrawlensize,
                 curlen-noffset-next.prevrawlensize-1);
@@ -441,7 +432,8 @@ static unsigned char *__ziplistCascadeUpdate(unsigned char *zl, unsigned char *p
 /* Delete "num" entries, starting at "p". Returns pointer to the ziplist. */
 static unsigned char *__ziplistDelete(unsigned char *zl, unsigned char *p, unsigned int num) {
     unsigned int i, totlen, deleted = 0;
-    int offset, nextdiff = 0;
+    size_t offset;
+    int nextdiff = 0;
     zlentry first, tail;
 
     first = zipEntry(p);
@@ -493,8 +485,9 @@ static unsigned char *__ziplistDelete(unsigned char *zl, unsigned char *p, unsig
 
 /* Insert item at "p". */
 static unsigned char *__ziplistInsert(unsigned char *zl, unsigned char *p, unsigned char *s, unsigned int slen) {
-    unsigned int curlen = ZIPLIST_BYTES(zl), reqlen, prevlen = 0;
-    unsigned int offset, nextdiff = 0;
+    size_t curlen = ZIPLIST_BYTES(zl), reqlen, prevlen = 0;
+    size_t offset;
+    int nextdiff = 0;
     unsigned char encoding = 0;
     long long value;
     zlentry entry, tail;
@@ -678,7 +671,7 @@ unsigned char *ziplistInsert(unsigned char *zl, unsigned char *p, unsigned char
  * Also update *p in place, to be able to iterate over the
  * ziplist, while deleting entries. */
 unsigned char *ziplistDelete(unsigned char *zl, unsigned char **p) {
-    unsigned int offset = *p-zl;
+    size_t offset = *p-zl;
     zl = __ziplistDelete(zl,*p,1);
 
     /* Store pointer to current element in p, because ziplistDelete will
@@ -887,7 +880,7 @@ void pop(unsigned char *zl, int where) {
     }
 }
 
-void randstring(char *target, unsigned int min, unsigned int max) {
+int randstring(char *target, unsigned int min, unsigned int max) {
     int p, len = min+rand()%(max-min+1);
     int minval, maxval;
     switch(rand() % 3) {
@@ -909,10 +902,9 @@ void randstring(char *target, unsigned int min, unsigned int max) {
 
     while(p < len)
         target[p++] = minval+rand()%(maxval-minval+1);
-    return;
+    return len;
 }
 
-
 int main(int argc, char **argv) {
     unsigned char *zl, *p;
     unsigned char *entry;
@@ -1245,6 +1237,7 @@ int main(int argc, char **argv) {
         int i,j,len,where;
         unsigned char *p;
         char buf[1024];
+        int buflen;
         list *ref;
         listNode *refnode;
 
@@ -1253,10 +1246,6 @@ int main(int argc, char **argv) {
         unsigned int slen;
         long long sval;
 
-        /* In the regression for the cascade bug, it was triggered
-         * with a random seed of 2. */
-        srand(2);
-
         for (i = 0; i < 20000; i++) {
             zl = ziplistNew();
             ref = listCreate();
@@ -1266,31 +1255,32 @@ int main(int argc, char **argv) {
             /* Create lists */
             for (j = 0; j < len; j++) {
                 where = (rand() & 1) ? ZIPLIST_HEAD : ZIPLIST_TAIL;
-                switch(rand() % 4) {
-                case 0:
-                    sprintf(buf,"%lld",(0LL + rand()) >> 20);
-                    break;
-                case 1:
-                    sprintf(buf,"%lld",(0LL + rand()));
-                    break;
-                case 2:
-                    sprintf(buf,"%lld",(0LL + rand()) << 20);
-                    break;
-                case 3:
-                    randstring(buf,0,256);
-                break;
-                default:
-                    assert(NULL);
+                if (rand() % 2) {
+                    buflen = randstring(buf,1,sizeof(buf)-1);
+                } else {
+                    switch(rand() % 3) {
+                    case 0:
+                        buflen = sprintf(buf,"%lld",(0LL + rand()) >> 20);
+                        break;
+                    case 1:
+                        buflen = sprintf(buf,"%lld",(0LL + rand()));
+                        break;
+                    case 2:
+                        buflen = sprintf(buf,"%lld",(0LL + rand()) << 20);
+                        break;
+                    default:
+                        assert(NULL);
+                    }
                 }
 
                 /* Add to ziplist */
-                zl = ziplistPush(zl, (unsigned char*)buf, strlen(buf), where);
+                zl = ziplistPush(zl, (unsigned char*)buf, buflen, where);
 
                 /* Add to reference list */
                 if (where == ZIPLIST_HEAD) {
-                    listAddNodeHead(ref,sdsnew(buf));
+                    listAddNodeHead(ref,sdsnewlen(buf, buflen));
                 } else if (where == ZIPLIST_TAIL) {
-                    listAddNodeTail(ref,sdsnew(buf));
+                    listAddNodeTail(ref,sdsnewlen(buf, buflen));
                 } else {
                     assert(NULL);
                 }
@@ -1305,12 +1295,13 @@ int main(int argc, char **argv) {
 
                 assert(ziplistGet(p,&sstr,&slen,&sval));
                 if (sstr == NULL) {
-                    sprintf(buf,"%lld",sval);
+                    buflen = sprintf(buf,"%lld",sval);
                 } else {
-                    memcpy(buf,sstr,slen);
-                    buf[slen] = '\0';
+                    buflen = slen;
+                    memcpy(buf,sstr,buflen);
+                    buf[buflen] = '\0';
                 }
-                assert(strcmp(buf,listNodeValue(refnode)) == 0);
+                assert(memcmp(buf,listNodeValue(refnode),buflen) == 0);
             }
             zfree(zl);
             listRelease(ref);