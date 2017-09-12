@@ -409,6 +409,7 @@ static unsigned char *__ziplistCascadeUpdate(unsigned char *zl, unsigned char *p
 
             /* Advance the cursor */
             p += rawlen;
+            curlen += extra;
         } else {
             if (next.prevrawlensize > rawlensize) {
                 /* This would result in shrinking, which we want to avoid.
@@ -781,6 +782,10 @@ void ziplistRepr(unsigned char *zl) {
 
 #ifdef ZIPLIST_TEST_MAIN
 #include <sys/time.h>
+#include "adlist.h"
+#include "sds.h"
+
+#define debug(f, ...) { if (DEBUG) printf(f, __VA_ARGS__); }
 
 unsigned char *createList() {
     unsigned char *zl = ziplistNew();
@@ -864,6 +869,32 @@ void pop(unsigned char *zl, int where) {
     }
 }
 
+void randstring(char *target, unsigned int min, unsigned int max) {
+    int p, len = min+rand()%(max-min+1);
+    int minval, maxval;
+    switch(rand() % 3) {
+    case 0:
+        minval = 0;
+        maxval = 255;
+    break;
+    case 1:
+        minval = 48;
+        maxval = 122;
+    break;
+    case 2:
+        minval = 48;
+        maxval = 52;
+    break;
+    default:
+        assert(NULL);
+    }
+
+    while(p < len)
+        target[p++] = minval+rand()%(maxval-minval+1);
+    return;
+}
+
+
 int main(int argc, char **argv) {
     unsigned char *zl, *p;
     unsigned char *entry;
@@ -1137,10 +1168,10 @@ int main(int argc, char **argv) {
         /* Pop values again and compare their value. */
         p = ziplistIndex(zl,0);
         assert(ziplistGet(p,&entry,&elen,&value));
-        assert(strncmp(v1,entry,elen) == 0);
+        assert(strncmp(v1,(char*)entry,elen) == 0);
         p = ziplistIndex(zl,1);
         assert(ziplistGet(p,&entry,&elen,&value));
-        assert(strncmp(v2,entry,elen) == 0);
+        assert(strncmp(v2,(char*)entry,elen) == 0);
         printf("SUCCESS\n\n");
     }
 
@@ -1192,50 +1223,78 @@ int main(int argc, char **argv) {
 
     printf("Stress with random payloads of different encoding:\n");
     {
-        int i, idx, where, len;
-        long long v;
+        int i,j,len,where;
         unsigned char *p;
-        char buf[0x4041]; /* max length of generated string */
-        zl = ziplistNew();
-        for (i = 0; i < 100000; i++) {
-            where = (rand() & 1) ? ZIPLIST_HEAD : ZIPLIST_TAIL;
-            if (rand() & 1) {
-                /* equally likely create a 16, 32 or 64 bit int */
-                v = (rand() & INT16_MAX) + ((1ll << 32) >> ((rand() % 3)*16));
-                v *= 2*(rand() & 1)-1; /* randomly flip sign */
-                sprintf(buf, "%lld", v);
+        char buf[1024];
+        list *ref;
+        listNode *refnode;
+
+        /* Hold temp vars from ziplist */
+        unsigned char *sstr;
+        unsigned int slen;
+        long long sval;
+
+        /* In the regression for the cascade bug, it was triggered
+         * with a random seed of 2. */
+        srand(2);
+
+        for (i = 0; i < 20000; i++) {
+            zl = ziplistNew();
+            ref = listCreate();
+            listSetFreeMethod(ref,sdsfree);
+            len = rand() % 256;
+
+            /* Create lists */
+            for (j = 0; j < len; j++) {
+                where = (rand() & 1) ? ZIPLIST_HEAD : ZIPLIST_TAIL;
+                switch(rand() % 4) {
+                case 0:
+                    sprintf(buf,"%lld",(0LL + rand()) >> 20);
+                    break;
+                case 1:
+                    sprintf(buf,"%lld",(0LL + rand()));
+                    break;
+                case 2:
+                    sprintf(buf,"%lld",(0LL + rand()) << 20);
+                    break;
+                case 3:
+                    randstring(buf,0,256);
+                break;
+                default:
+                    assert(NULL);
+                }
+
+                /* Add to ziplist */
                 zl = ziplistPush(zl, (unsigned char*)buf, strlen(buf), where);
-            } else {
-                /* equally likely generate 6, 14 or >14 bit length */
-                v = rand() & 0x3f;
-                v += 0x4000 >> ((rand() % 3)*8);
-                memset(buf, 'x', v);
-                zl = ziplistPush(zl, (unsigned char*)buf, v, where);
-            }
 
-            /* delete a random element */
-            if ((len = ziplistLen(zl)) >= 10) {
-                idx = rand() % len;
-                // printf("Delete index %d\n", idx);
-                // ziplistRepr(zl);
-                ziplistDeleteRange(zl, idx, 1);
-                // ziplistRepr(zl);
-                len--;
+                /* Add to reference list */
+                if (where == ZIPLIST_HEAD) {
+                    listAddNodeHead(ref,sdsnew(buf));
+                } else if (where == ZIPLIST_TAIL) {
+                    listAddNodeTail(ref,sdsnew(buf));
+                } else {
+                    assert(NULL);
+                }
             }
 
-            /* iterate from front to back */
-            idx = 0;
-            p = ziplistIndex(zl, 0);
-            while((p = ziplistNext(zl,p)))
-                idx++;
-            assert(len == idx+1);
-
-            /* iterate from back to front */
-            idx = 0;
-            p = ziplistIndex(zl, -1);
-            while((p = ziplistPrev(zl,p)))
-                idx++;
-            assert(len == idx+1);
+            assert(listLength(ref) == ziplistLen(zl));
+            for (j = 0; j < len; j++) {
+                /* Naive way to get elements, but similar to the stresser
+                 * executed from the Tcl test suite. */
+                p = ziplistIndex(zl,j);
+                refnode = listIndex(ref,j);
+
+                assert(ziplistGet(p,&sstr,&slen,&sval));
+                if (sstr == NULL) {
+                    sprintf(buf,"%lld",sval);
+                } else {
+                    memcpy(buf,sstr,slen);
+                    buf[slen] = '\0';
+                }
+                assert(strcmp(buf,listNodeValue(refnode)) == 0);
+            }
+            zfree(zl);
+            listRelease(ref);
         }
         printf("SUCCESS\n\n");
     }