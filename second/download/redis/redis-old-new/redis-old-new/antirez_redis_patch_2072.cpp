@@ -15,8 +15,10 @@
  */
 
 #include <stdio.h>
+#include <stdlib.h>
 #include <string.h>
 #include <assert.h>
+#include <limits.h>
 #include "zmalloc.h"
 #include "sds.h"
 #include "ziplist.h"
@@ -60,13 +62,21 @@ static unsigned char *ziplistTail(unsigned char *zl) {
 }
 
 unsigned char *ziplistPush(unsigned char *zl, unsigned char *entry, unsigned int elen, int where) {
-    unsigned int curlen = ZIPLIST_BYTES(zl);
-    unsigned int reqlen = zipEncodeLength(NULL,elen)+elen;
+    unsigned int curlen = ZIPLIST_BYTES(zl), reqlen;
     unsigned char *p;
+    char encoding = ZIP_ENC_RAW;
+    long long value;
 
-    /* Resize the ziplist */
-    zl = ziplistResize(zl,curlen+reqlen);
+    /* See if the entry can be encoded */
+    if (zipTryEncoding(entry,&value,&encoding)) {
+        reqlen = zipEncodingSize(encoding);
+    } else {
+        reqlen = elen;
+    }
+    reqlen += zipEncodeLength(NULL,encoding,elen);
 
+    /* Resize the ziplist and move if needed */
+    zl = ziplistResize(zl,curlen+reqlen);
     if (where == ZIPLIST_HEAD) {
         p = zl+ZIPLIST_HEADER_SIZE;
         if (*p != ZIP_END) {
@@ -78,31 +88,44 @@ unsigned char *ziplistPush(unsigned char *zl, unsigned char *entry, unsigned int
     }
 
     /* Write the entry */
-    p += zipEncodeLength(p,elen);
-    memcpy(p,entry,elen);
+    p += zipEncodeLength(p,encoding,elen);
+    if (encoding != ZIP_ENC_RAW) {
+        zipSaveInteger(p,value,encoding);
+    } else {
+        memcpy(p,entry,elen);
+    }
     ZIPLIST_INCR_LENGTH(zl,1);
     return zl;
 }
 
-unsigned char *ziplistPop(unsigned char *zl, sds *value, int where) {
-    unsigned int curlen = ZIPLIST_BYTES(zl), len, rlen;
+unsigned char *ziplistPop(unsigned char *zl, sds *target, int where) {
+    unsigned int curlen = ZIPLIST_BYTES(zl), rawlen;
+    unsigned int len, lensize;
     unsigned char *p;
-    if (value) *value = NULL;
+    long long value;
+    if (target) *target = NULL;
 
     /* Get pointer to element to remove */
     p = (where == ZIPLIST_HEAD) ? ziplistHead(zl) : ziplistTail(zl);
     if (*p == ZIP_END) return zl;
-    len = zipDecodeLength(p);
-    if (value) *value = sdsnewlen(p+zipEncodeLength(NULL,len),len);
+    len = zipDecodeLength(p,&lensize);
+    if (target) {
+        if (ZIP_ENCODING(p) == ZIP_ENC_RAW) {
+            *target = sdsnewlen(p+lensize,len);
+        } else {
+            value = zipLoadInteger(p+lensize,ZIP_ENCODING(p));
+            *target = sdscatprintf(sdsempty(), "%lld", value);
+        }
+    }
 
     /* Move list to front when popping from the head */
-    rlen = zipRawEntryLength(p);
+    rawlen = lensize+len;
     if (where == ZIPLIST_HEAD) {
-        memmove(p,p+rlen,curlen-ZIPLIST_HEADER_SIZE-len);
+        memmove(p,p+rawlen,curlen-ZIPLIST_HEADER_SIZE-len);
     }
 
     /* Resize and update length */
-    zl = ziplistResize(zl,curlen-rlen);
+    zl = ziplistResize(zl,curlen-rawlen);
     ZIPLIST_INCR_LENGTH(zl,-1);
     return zl;
 }
@@ -121,10 +144,11 @@ unsigned char *ziplistIndex(unsigned char *zl, unsigned int index) {
 /* Store entry at current position in sds *value and return pointer
  * to the next entry. */
 unsigned char *ziplistNext(unsigned char *p, unsigned char **q, unsigned char **entry, unsigned int *elen) {
+    unsigned int lensize;
     if (*p == ZIP_END) return NULL;
     if (entry) {
-        *elen = zipDecodeLength(p);
-        *entry = p+ZIP_LEN_BYTES(*elen);
+        *elen = zipDecodeLength(p,&lensize);
+        *entry = p+lensize;
     }
     if (q != NULL) *q = p;
     p += zipRawEntryLength(p);
@@ -174,16 +198,22 @@ unsigned char *ziplistDelete(unsigned char *zl, unsigned char **p) {
 }
 
 void ziplistRepr(unsigned char *zl) {
-    unsigned char *p;
-    unsigned int l;
+    unsigned char *p, encoding;
+    unsigned int l, lsize;
+    long long value;
 
-    printf("{bytes %d} {length %u}\n",ZIPLIST_BYTES(zl), ZIPLIST_LENGTH(zl));
+    printf("{total bytes %d} {length %u}\n",ZIPLIST_BYTES(zl), ZIPLIST_LENGTH(zl));
     p = ziplistHead(zl);
     while(*p != ZIP_END) {
-        l = zipDecodeLength(p);
-        printf("{key %u}",l);
-        p += zipEncodeLength(NULL,l);
-        fwrite(p,l,1,stdout);
+        l = zipDecodeLength(p,&lsize);
+        printf("{header %u, payload %u} ",lsize,l);
+        encoding = ZIP_ENCODING(p);
+        p += lsize;
+        if (encoding == ZIP_ENC_RAW) {
+            fwrite(p,l,1,stdout);
+        } else {
+            printf("%lld", zipLoadInteger(p,encoding));
+        }
         printf("\n");
         p += l;
     }
@@ -200,11 +230,33 @@ unsigned char *createList() {
     return zl;
 }
 
+unsigned char *createIntList() {
+    unsigned char *zl = ziplistNew();
+    char buf[32];
+
+    sprintf(buf, "100");
+    zl = ziplistPush(zl, buf, strlen(buf), ZIPLIST_TAIL);
+    sprintf(buf, "128000");
+    zl = ziplistPush(zl, buf, strlen(buf), ZIPLIST_TAIL);
+    sprintf(buf, "-100");
+    zl = ziplistPush(zl, buf, strlen(buf), ZIPLIST_HEAD);
+    sprintf(buf, "4294967296");
+    zl = ziplistPush(zl, buf, strlen(buf), ZIPLIST_HEAD);
+    sprintf(buf, "non integer");
+    zl = ziplistPush(zl, buf, strlen(buf), ZIPLIST_TAIL);
+    sprintf(buf, "much much longer non integer");
+    zl = ziplistPush(zl, buf, strlen(buf), ZIPLIST_TAIL);
+    return zl;
+}
+
 int main(int argc, char **argv) {
     unsigned char *zl, *p, *q, *entry;
     unsigned int elen;
     sds s;
 
+    zl = createIntList();
+    ziplistRepr(zl);
+
     zl = createList();
     ziplistRepr(zl);
 