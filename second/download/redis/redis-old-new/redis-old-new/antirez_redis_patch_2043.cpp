@@ -21,7 +21,6 @@
 #include <assert.h>
 #include <limits.h>
 #include "zmalloc.h"
-#include "sds.h"
 #include "ziplist.h"
 
 /* Important note: the ZIP_END value is used to depict the end of the
@@ -382,30 +381,6 @@ unsigned char *ziplistPush(unsigned char *zl, unsigned char *s, unsigned int sle
     return __ziplistInsert(zl,p,s,slen);
 }
 
-unsigned char *ziplistPop(unsigned char *zl, sds *target, int where) {
-    zlentry entry;
-    unsigned char *p;
-    long long value;
-    if (target) *target = NULL;
-
-    /* Get pointer to element to remove */
-    p = (where == ZIPLIST_HEAD) ? ZIPLIST_ENTRY_HEAD(zl) : ZIPLIST_ENTRY_TAIL(zl);
-    if (*p == ZIP_END) return zl;
-
-    entry = zipEntry(p);
-    if (target) {
-        if (entry.encoding == ZIP_ENC_RAW) {
-            *target = sdsnewlen(p+entry.headersize,entry.len);
-        } else {
-            value = zipLoadInteger(p+entry.headersize,entry.encoding);
-            *target = sdscatprintf(sdsempty(), "%lld", value);
-        }
-    }
-
-    zl = __ziplistDelete(zl,p,1);
-    return zl;
-}
-
 /* Returns an offset to use for iterating with ziplistNext. When the given
  * index is negative, the list is traversed back to front. When the list
  * doesn't contain an element at the provided index, NULL is returned. */
@@ -644,33 +619,53 @@ void stress(int pos, int num, int maxsize, int dnum) {
     }
 }
 
+void pop(unsigned char *zl, int where) {
+    unsigned char *p, *vstr;
+    unsigned int vlen;
+    long long vlong;
+
+    p = ziplistIndex(zl,where == ZIPLIST_HEAD ? 0 : -1);
+    if (ziplistGet(p,&vstr,&vlen,&vlong)) {
+        if (where == ZIPLIST_HEAD)
+            printf("Pop head: ");
+        else
+            printf("Pop tail: ");
+
+        if (vstr)
+            fwrite(vstr,vlen,1,stdout);
+        else
+            printf("%lld", vlong);
+
+        printf("\n");
+        ziplistDeleteRange(zl,-1,1);
+    } else {
+        printf("ERROR: Could not pop\n");
+        exit(1);
+    }
+}
+
 int main(int argc, char **argv) {
     unsigned char *zl, *p;
     unsigned char *entry;
     unsigned int elen;
     long long value;
-    sds s;
 
     zl = createIntList();
     ziplistRepr(zl);
 
     zl = createList();
     ziplistRepr(zl);
 
-    zl = ziplistPop(zl, &s, ZIPLIST_TAIL);
-    printf("Pop tail: %s (length %ld)\n", s, sdslen(s));
+    pop(zl,ZIPLIST_TAIL);
     ziplistRepr(zl);
 
-    zl = ziplistPop(zl, &s, ZIPLIST_HEAD);
-    printf("Pop head: %s (length %ld)\n", s, sdslen(s));
+    pop(zl,ZIPLIST_HEAD);
     ziplistRepr(zl);
 
-    zl = ziplistPop(zl, &s, ZIPLIST_TAIL);
-    printf("Pop tail: %s (length %ld)\n", s, sdslen(s));
+    pop(zl,ZIPLIST_TAIL);
     ziplistRepr(zl);
 
-    zl = ziplistPop(zl, &s, ZIPLIST_TAIL);
-    printf("Pop tail: %s (length %ld)\n", s, sdslen(s));
+    pop(zl,ZIPLIST_TAIL);
     ziplistRepr(zl);
 
     printf("Get element at index 3:\n");