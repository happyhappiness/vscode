@@ -30,11 +30,11 @@
 
 #define SDS_ABORT_ON_OOM
 
-#include "sds.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <ctype.h>
+#include "sds.h"
 
 static void sdsOomAbort(void) {
     fprintf(stderr,"SDS: Out Of Memory (SDS_ABORT_ON_OOM defined)\n");
@@ -69,11 +69,6 @@ sds sdsnew(const char *init) {
     return sdsnewlen(init, initlen);
 }
 
-size_t sdslen(const sds s) {
-    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
-    return sh->len;
-}
-
 sds sdsdup(const sds s) {
     return sdsnewlen(s, sdslen(s));
 }
@@ -83,11 +78,6 @@ void sdsfree(sds s) {
     free(s-sizeof(struct sdshdr));
 }
 
-size_t sdsavail(sds s) {
-    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
-    return sh->free;
-}
-
 void sdsupdatelen(sds s) {
     struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
     int reallen = strlen(s);
@@ -115,6 +105,25 @@ static sds sdsMakeRoomFor(sds s, size_t addlen) {
     return newsh->buf;
 }
 
+/* Grow the sds to have the specified length. Bytes that were not part of
+ * the original length of the sds will be set to zero. */
+sds sdsgrowzero(sds s, size_t len) {
+    struct sdshdr *sh = (void*)(s-(sizeof(struct sdshdr)));
+    size_t totlen, curlen = sh->len;
+
+    if (len <= curlen) return s;
+    s = sdsMakeRoomFor(s,len-curlen);
+    if (s == NULL) return NULL;
+
+    /* Make sure added region doesn't contain garbage */
+    sh = (void*)(s-(sizeof(struct sdshdr)));
+    memset(s+curlen,0,(len-curlen+1)); /* also set trailing \0 byte */
+    totlen = sh->len+sh->free;
+    sh->len = len;
+    sh->free = totlen-sh->len;
+    return s;
+}
+
 sds sdscatlen(sds s, const void *t, size_t len) {
     struct sdshdr *sh;
     size_t curlen = sdslen(s);
@@ -222,13 +231,16 @@ sds sdsrange(sds s, int start, int end) {
     }
     newlen = (start > end) ? 0 : (end-start)+1;
     if (newlen != 0) {
-        if (start >= (signed)len) start = len-1;
-        if (end >= (signed)len) end = len-1;
-        newlen = (start > end) ? 0 : (end-start)+1;
+        if (start >= (signed)len) {
+            newlen = 0;
+        } else if (end >= (signed)len) {
+            end = len-1;
+            newlen = (start > end) ? 0 : (end-start)+1;
+        }
     } else {
         start = 0;
     }
-    if (start != 0) memmove(sh->buf, sh->buf+start, newlen);
+    if (start && newlen) memmove(sh->buf, sh->buf+start, newlen);
     sh->buf[newlen] = 0;
     sh->free = sh->free+(sh->len-newlen);
     sh->len = newlen;
@@ -477,3 +489,106 @@ sds *sdssplitargs(char *line, int *argc) {
     if (current) sdsfree(current);
     return NULL;
 }
+
+#ifdef SDS_TEST_MAIN
+#include <stdio.h>
+
+int __failed_tests = 0;
+int __test_num = 0;
+#define test_cond(descr,_c) do { \
+    __test_num++; printf("%d - %s: ", __test_num, descr); \
+    if(_c) printf("PASSED\n"); else {printf("FAILED\n"); __failed_tests++;} \
+} while(0);
+#define test_report() do { \
+    printf("%d tests, %d passed, %d failed\n", __test_num, \
+                    __test_num-__failed_tests, __failed_tests); \
+    if (__failed_tests) { \
+        printf("=== WARNING === We have failed tests here...\n"); \
+    } \
+} while(0);
+
+int main(void) {
+    {
+        sds x = sdsnew("foo"), y;
+
+        test_cond("Create a string and obtain the length",
+            sdslen(x) == 3 && memcmp(x,"foo\0",4) == 0)
+
+        sdsfree(x);
+        x = sdsnewlen("foo",2);
+        test_cond("Create a string with specified length",
+            sdslen(x) == 2 && memcmp(x,"fo\0",3) == 0)
+
+        x = sdscat(x,"bar");
+        test_cond("Strings concatenation",
+            sdslen(x) == 5 && memcmp(x,"fobar\0",6) == 0);
+
+        x = sdscpy(x,"a");
+        test_cond("sdscpy() against an originally longer string",
+            sdslen(x) == 1 && memcmp(x,"a\0",2) == 0)
+
+        x = sdscpy(x,"xyzxxxxxxxxxxyyyyyyyyyykkkkkkkkkk");
+        test_cond("sdscpy() against an originally shorter string",
+            sdslen(x) == 33 &&
+            memcmp(x,"xyzxxxxxxxxxxyyyyyyyyyykkkkkkkkkk\0",33) == 0)
+
+        sdsfree(x);
+        x = sdscatprintf(sdsempty(),"%d",123);
+        test_cond("sdscatprintf() seems working in the base case",
+            sdslen(x) == 3 && memcmp(x,"123\0",4) ==0)
+
+        sdsfree(x);
+        x = sdstrim(sdsnew("xxciaoyyy"),"xy");
+        test_cond("sdstrim() correctly trims characters",
+            sdslen(x) == 4 && memcmp(x,"ciao\0",5) == 0)
+
+        y = sdsrange(sdsdup(x),1,1);
+        test_cond("sdsrange(...,1,1)",
+            sdslen(y) == 1 && memcmp(y,"i\0",2) == 0)
+
+        sdsfree(y);
+        y = sdsrange(sdsdup(x),1,-1);
+        test_cond("sdsrange(...,1,-1)",
+            sdslen(y) == 3 && memcmp(y,"iao\0",4) == 0)
+
+        sdsfree(y);
+        y = sdsrange(sdsdup(x),-2,-1);
+        test_cond("sdsrange(...,-2,-1)",
+            sdslen(y) == 2 && memcmp(y,"ao\0",3) == 0)
+
+        sdsfree(y);
+        y = sdsrange(sdsdup(x),2,1);
+        test_cond("sdsrange(...,2,1)",
+            sdslen(y) == 0 && memcmp(y,"\0",1) == 0)
+
+        sdsfree(y);
+        y = sdsrange(sdsdup(x),1,100);
+        test_cond("sdsrange(...,1,100)",
+            sdslen(y) == 3 && memcmp(y,"iao\0",4) == 0)
+
+        sdsfree(y);
+        y = sdsrange(sdsdup(x),100,100);
+        test_cond("sdsrange(...,100,100)",
+            sdslen(y) == 0 && memcmp(y,"\0",1) == 0)
+
+        sdsfree(y);
+        sdsfree(x);
+        x = sdsnew("foo");
+        y = sdsnew("foa");
+        test_cond("sdscmp(foo,foa)", sdscmp(x,y) > 0)
+
+        sdsfree(y);
+        sdsfree(x);
+        x = sdsnew("bar");
+        y = sdsnew("bar");
+        test_cond("sdscmp(bar,bar)", sdscmp(x,y) == 0)
+
+        sdsfree(y);
+        sdsfree(x);
+        x = sdsnew("aar");
+        y = sdsnew("bar");
+        test_cond("sdscmp(bar,bar)", sdscmp(x,y) < 0)
+    }
+    test_report()
+}
+#endif