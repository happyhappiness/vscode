@@ -23,6 +23,11 @@
 #include "sds.h"
 #include "ziplist.h"
 
+/* Important note: the ZIP_END value is used to depict the end of the
+ * ziplist structure. When a pointer contains an entry, the first couple
+ * of bytes contain the encoded length of the previous entry. This length
+ * is encoded as ZIP_ENC_RAW length, so the first two bits will contain 00
+ * and the byte will therefore never have a value of 255. */
 #define ZIP_END 255
 #define ZIP_BIGLEN 254
 
@@ -40,8 +45,9 @@
 
 /* Utility macros */
 #define ZIPLIST_BYTES(zl) (*((unsigned int*)(zl)))
-#define ZIPLIST_LENGTH(zl) (*((zl)+sizeof(unsigned int)))
-#define ZIPLIST_HEADER_SIZE (sizeof(unsigned int)+1)
+#define ZIPLIST_TAIL_OFFSET(zl) (*((zl)+sizeof(unsigned int)))
+#define ZIPLIST_LENGTH(zl) (*((zl)+2*sizeof(unsigned int)))
+#define ZIPLIST_HEADER_SIZE (2*sizeof(unsigned int)+1)
 #define ZIPLIST_INCR_LENGTH(zl,incr) { \
     if (ZIPLIST_LENGTH(zl) < ZIP_BIGLEN) ZIPLIST_LENGTH(zl)+=incr; }
 
@@ -116,6 +122,14 @@ static unsigned int zipEncodeLength(unsigned char *p, char encoding, unsigned in
     return len;
 }
 
+/* Return the difference in number of bytes needed to store the new length
+ * "len" on the entry pointed to by "p". */
+static int zipPrevLenByteDiff(unsigned char *p, unsigned int len) {
+    unsigned int prevlensize;
+    zipDecodeLength(p,&prevlensize);
+    return zipEncodeLength(NULL,ZIP_ENC_RAW,len)-prevlensize;
+}
+
 /* Check if string pointed to by 'entry' can be encoded as an integer.
  * Stores the integer value in 'v' and its encoding in 'encoding'.
  * Warning: this function requires a NULL-terminated string! */
@@ -180,16 +194,20 @@ static long long zipLoadInteger(unsigned char *p, char encoding) {
 
 /* Return the total amount used by an entry (encoded length + payload). */
 static unsigned int zipRawEntryLength(unsigned char *p) {
-    unsigned int lensize, len;
-    len = zipDecodeLength(p, &lensize);
-    return lensize + len;
+    unsigned int prevlensize, lensize, len;
+    /* Byte-size of encoded length of previous entry */
+    zipDecodeLength(p,&prevlensize);
+    /* Encoded length of this entry's payload */
+    len = zipDecodeLength(p+prevlensize, &lensize);
+    return prevlensize+lensize+len;
 }
 
 /* Create a new empty ziplist. */
 unsigned char *ziplistNew(void) {
     unsigned int bytes = ZIPLIST_HEADER_SIZE+1;
     unsigned char *zl = zmalloc(bytes);
     ZIPLIST_BYTES(zl) = bytes;
+    ZIPLIST_TAIL_OFFSET(zl) = ZIPLIST_HEADER_SIZE;
     ZIPLIST_LENGTH(zl) = 0;
     zl[bytes-1] = ZIP_END;
     return zl;
@@ -218,17 +236,30 @@ static unsigned char *ziplistTail(unsigned char *zl) {
 }
 
 unsigned char *ziplistPush(unsigned char *zl, unsigned char *entry, unsigned int elen, int where) {
-    unsigned int curlen = ZIPLIST_BYTES(zl), reqlen;
-    unsigned char *p;
+    unsigned int curlen = ZIPLIST_BYTES(zl), reqlen, prevlen;
+    unsigned char *p, *curtail;
     char encoding = ZIP_ENC_RAW;
     long long value;
 
+    /* We need to store the length of the current tail when the list
+     * is non-empty and we push at the tail. */
+    curtail = zl+ZIPLIST_TAIL_OFFSET(zl);
+    if (where == ZIPLIST_TAIL && curtail[0] != ZIP_END) {
+        prevlen = zipRawEntryLength(curtail);
+    } else {
+        prevlen = 0;
+    }
+
     /* See if the entry can be encoded */
     if (zipTryEncoding(entry,&value,&encoding)) {
         reqlen = zipEncodingSize(encoding);
     } else {
         reqlen = elen;
     }
+
+    /* We need space for both the length of the previous entry and
+     * the length of the payload. */
+    reqlen += zipEncodeLength(NULL,ZIP_ENC_RAW,prevlen);
     reqlen += zipEncodeLength(NULL,encoding,elen);
 
     /* Resize the ziplist and move if needed */
@@ -243,7 +274,17 @@ unsigned char *ziplistPush(unsigned char *zl, unsigned char *entry, unsigned int
         p = zl+curlen-1;
     }
 
+    /* Update tail offset if this is not the first element */
+    if (curtail[0] != ZIP_END) {
+        if (where == ZIPLIST_HEAD) {
+            ZIPLIST_TAIL_OFFSET(zl) += reqlen;
+        } else {
+            ZIPLIST_TAIL_OFFSET(zl) += prevlen;
+        }
+    }
+
     /* Write the entry */
+    p += zipEncodeLength(p,ZIP_ENC_RAW,prevlen);
     p += zipEncodeLength(p,encoding,elen);
     if (encoding != ZIP_ENC_RAW) {
         zipSaveInteger(p,value,encoding);
@@ -256,32 +297,56 @@ unsigned char *ziplistPush(unsigned char *zl, unsigned char *entry, unsigned int
 
 unsigned char *ziplistPop(unsigned char *zl, sds *target, int where) {
     unsigned int curlen = ZIPLIST_BYTES(zl), rawlen;
-    unsigned int len, lensize;
+    unsigned int prevrawlensize, prevrawlen, lensize, len, headerlen;
+    int nextdiff = 0;
+    unsigned char encoding;
     unsigned char *p;
     long long value;
     if (target) *target = NULL;
 
     /* Get pointer to element to remove */
     p = (where == ZIPLIST_HEAD) ? ziplistHead(zl) : ziplistTail(zl);
     if (*p == ZIP_END) return zl;
-    len = zipDecodeLength(p,&lensize);
+
+    prevrawlen = zipDecodeLength(p,&prevrawlensize);
+    len = zipDecodeLength(p+prevrawlensize,&lensize);
+    headerlen = prevrawlensize+lensize;
+    rawlen = headerlen+len;
     if (target) {
-        if (ZIP_ENCODING(p) == ZIP_ENC_RAW) {
-            *target = sdsnewlen(p+lensize,len);
+        encoding = ZIP_ENCODING(p+prevrawlensize);
+        if (encoding == ZIP_ENC_RAW) {
+            *target = sdsnewlen(p+headerlen,len);
         } else {
-            value = zipLoadInteger(p+lensize,ZIP_ENCODING(p));
+            value = zipLoadInteger(p+headerlen,encoding);
             *target = sdscatprintf(sdsempty(), "%lld", value);
         }
     }
 
-    /* Move list to front when popping from the head */
-    rawlen = lensize+len;
     if (where == ZIPLIST_HEAD) {
-        memmove(p,p+rawlen,curlen-ZIPLIST_HEADER_SIZE-len);
+        /* The next entry will now be the head of the list */
+        if (p[rawlen] != ZIP_END) {
+            /* Tricky: storing the length of the previous entry in the next
+             * entry (this previous length is always 0 when popping from the
+             * head), might reduce the number of bytes needed.
+             *
+             * In this special case (new length is 0), we know that the
+             * byte difference to store is always <= 0, which means that
+             * we always have space to store it. */
+            nextdiff = zipPrevLenByteDiff(p+rawlen,0);
+            zipEncodeLength(p+rawlen-nextdiff,ZIP_ENC_RAW,0);
+        }
+        /* Move list to the front */
+        memmove(p,p+rawlen-nextdiff,curlen-ZIPLIST_HEADER_SIZE-rawlen+nextdiff);
+
+        /* Subtract the gained space from the tail offset */
+        ZIPLIST_TAIL_OFFSET(zl) -= rawlen+nextdiff;
+    } else {
+        /* Subtract the length of the previous element from the tail offset. */
+        ZIPLIST_TAIL_OFFSET(zl) -= prevrawlen;
     }
 
     /* Resize and update length */
-    zl = ziplistResize(zl,curlen-rawlen);
+    zl = ziplistResize(zl,curlen-rawlen+nextdiff);
     ZIPLIST_INCR_LENGTH(zl,-1);
     return zl;
 }
@@ -307,18 +372,21 @@ unsigned char *ziplistNext(unsigned char *p) {
  * to find out whether the string pointer or the integer value was set.
  * Return 0 if 'p' points to the end of the zipmap, 1 otherwise. */
 unsigned int ziplistGet(unsigned char *p, unsigned char **e, unsigned int *elen, long long *v) {
-    unsigned int len, lensize;
+    unsigned int prevrawlensize, lensize, len, headerlen;
     if (*p == ZIP_END) return 0;
     if (e) *e = NULL;
-    len = zipDecodeLength(p,&lensize);
-    if (ZIP_ENCODING(p) == ZIP_ENC_RAW) {
+
+    zipDecodeLength(p,&prevrawlensize);
+    len = zipDecodeLength(p+prevrawlensize,&lensize);
+    headerlen = prevrawlensize+lensize;
+    if (ZIP_ENCODING(p+prevrawlensize) == ZIP_ENC_RAW) {
         if (e) {
             *elen = len;
-            *e = p+lensize;
+            *e = p+headerlen;
         }
     } else {
         if (v) {
-            *v = zipLoadInteger(p+lensize,ZIP_ENCODING(p));
+            *v = zipLoadInteger(p+headerlen,ZIP_ENCODING(p+prevrawlensize));
         }
     }
     return 1;
@@ -368,24 +436,26 @@ unsigned char *ziplistDelete(unsigned char *zl, unsigned char **p) {
 
 /* Compare entry pointer to by 'p' with 'entry'. Return 1 if equal. */
 unsigned int ziplistCompare(unsigned char *p, unsigned char *entry, unsigned int elen) {
-    unsigned int zlen, lensize;
+    unsigned int prevrawlensize, lensize, len, headerlen;
     char encoding;
-    long long zval, eval;
+    long long val, eval;
     if (*p == ZIP_END) return 0;
 
-    zlen = zipDecodeLength(p,&lensize);
-    if (ZIP_ENCODING(p) == ZIP_ENC_RAW) {
+    zipDecodeLength(p,&prevrawlensize);
+    len = zipDecodeLength(p+prevrawlensize,&lensize);
+    headerlen = prevrawlensize+lensize;
+    if (ZIP_ENCODING(p+prevrawlensize) == ZIP_ENC_RAW) {
         /* Raw compare */
-        if (zlen == elen) {
-            return memcmp(p+lensize,entry,elen) == 0;
+        if (len == elen) {
+            return memcmp(p+headerlen,entry,elen) == 0;
         } else {
             return 0;
         }
     } else {
         if (zipTryEncoding(entry,&eval,&encoding)) {
             /* Do integer compare */
-            zval = zipLoadInteger(p+lensize,ZIP_ENCODING(p));
-            return zval == eval;
+            val = zipLoadInteger(p+headerlen,ZIP_ENCODING(p+prevrawlensize));
+            return val == eval;
         } else {
             /* Ziplist entry is integer encoded, but given entry is not. */
         }
@@ -418,22 +488,23 @@ unsigned int ziplistSize(unsigned char *zl) {
 
 void ziplistRepr(unsigned char *zl) {
     unsigned char *p, encoding;
-    unsigned int l, lsize;
+    unsigned int prevrawlensize, prevrawlen, lensize, len;
 
     printf("{total bytes %d} {length %u}\n",ZIPLIST_BYTES(zl), ZIPLIST_LENGTH(zl));
     p = ziplistHead(zl);
     while(*p != ZIP_END) {
-        l = zipDecodeLength(p,&lsize);
-        printf("{header %u, payload %u} ",lsize,l);
-        encoding = ZIP_ENCODING(p);
-        p += lsize;
+        prevrawlen = zipDecodeLength(p,&prevrawlensize);
+        len = zipDecodeLength(p+prevrawlensize,&lensize);
+        printf("{offset %ld, header %u, payload %u} ",p-zl,prevrawlensize+lensize,len);
+        encoding = ZIP_ENCODING(p+prevrawlensize);
+        p += prevrawlensize+lensize;
         if (encoding == ZIP_ENC_RAW) {
-            fwrite(p,l,1,stdout);
+            fwrite(p,len,1,stdout);
         } else {
             printf("%lld", zipLoadInteger(p,encoding));
         }
         printf("\n");
-        p += l;
+        p += len;
     }
     printf("{end}\n\n");
 }
@@ -488,6 +559,14 @@ int main(int argc, char **argv) {
     printf("Pop head: %s (length %ld)\n", s, sdslen(s));
     ziplistRepr(zl);
 
+    zl = ziplistPop(zl, &s, ZIPLIST_TAIL);
+    printf("Pop tail: %s (length %ld)\n", s, sdslen(s));
+    ziplistRepr(zl);
+
+    zl = ziplistPop(zl, &s, ZIPLIST_TAIL);
+    printf("Pop tail: %s (length %ld)\n", s, sdslen(s));
+    ziplistRepr(zl);
+
     printf("Iterate list from 0 to end:\n");
     {
         zl = createList();
@@ -614,21 +693,21 @@ int main(int argc, char **argv) {
         zl = createList();
         p = ziplistIndex(zl, 0);
         if (!ziplistCompare(p,"hello",5)) {
-            printf("ERROR\n");
+            printf("ERROR: not \"hello\"\n");
             return;
         }
         if (ziplistCompare(p,"hella",5)) {
-            printf("ERROR\n");
+            printf("ERROR: \"hella\"\n");
             return;
         }
 
         p = ziplistIndex(zl, 3);
         if (!ziplistCompare(p,"1024",4)) {
-            printf("ERROR\n");
+            printf("ERROR: not \"1024\"\n");
             return;
         }
         if (ziplistCompare(p,"1025",4)) {
-            printf("ERROR\n");
+            printf("ERROR: \"1025\"\n");
             return;
         }
         printf("SUCCESS\n");