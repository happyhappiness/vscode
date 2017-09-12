@@ -80,21 +80,54 @@
 #include <string.h>
 #include <assert.h>
 #include "zmalloc.h"
-#include "zip.c"
+
+#define ZIPMAP_BIGLEN 254
+#define ZIPMAP_END 255
 
 /* The following defines the max value for the <free> field described in the
  * comments above, that is, the max number of trailing bytes in a value. */
 #define ZIPMAP_VALUE_MAX_FREE 4
 
+/* The following macro returns the number of bytes needed to encode the length
+ * for the integer value _l, that is, 1 byte for lengths < ZIPMAP_BIGLEN and
+ * 5 bytes for all the other lengths. */
+#define ZIPMAP_LEN_BYTES(_l) (((_l) < ZIPMAP_BIGLEN) ? 1 : sizeof(unsigned int)+1)
+
 /* Create a new empty zipmap. */
 unsigned char *zipmapNew(void) {
     unsigned char *zm = zmalloc(2);
 
     zm[0] = 0; /* Length */
-    zm[1] = ZIP_END;
+    zm[1] = ZIPMAP_END;
     return zm;
 }
 
+/* Decode the encoded length pointed by 'p' */
+static unsigned int zipmapDecodeLength(unsigned char *p) {
+    unsigned int len = *p;
+
+    if (len < ZIPMAP_BIGLEN) return len;
+    memcpy(&len,p+1,sizeof(unsigned int));
+    return len;
+}
+
+/* Encode the length 'l' writing it in 'p'. If p is NULL it just returns
+ * the amount of bytes required to encode such a length. */
+static unsigned int zipmapEncodeLength(unsigned char *p, unsigned int len) {
+    if (p == NULL) {
+        return ZIPMAP_LEN_BYTES(len);
+    } else {
+        if (len < ZIPMAP_BIGLEN) {
+            p[0] = len;
+            return 1;
+        } else {
+            p[0] = ZIPMAP_BIGLEN;
+            memcpy(p+1,&len,sizeof(len));
+            return 1+sizeof(len);
+        }
+    }
+}
+
 /* Search for a matching key, returning a pointer to the entry inside the
  * zipmap. Returns NULL if the key is not found.
  *
@@ -105,12 +138,12 @@ static unsigned char *zipmapLookupRaw(unsigned char *zm, unsigned char *key, uns
     unsigned char *p = zm+1, *k = NULL;
     unsigned int l,llen;
 
-    while(*p != ZIP_END) {
+    while(*p != ZIPMAP_END) {
         unsigned char free;
 
         /* Match or skip the key */
-        l = zipDecodeLength(p);
-        llen = zipEncodeLength(NULL,l);
+        l = zipmapDecodeLength(p);
+        llen = zipmapEncodeLength(NULL,l);
         if (k == NULL && l == klen && !memcmp(p+llen,key,l)) {
             /* Only return when the user doesn't care
              * for the total length of the zipmap. */
@@ -122,8 +155,8 @@ static unsigned char *zipmapLookupRaw(unsigned char *zm, unsigned char *key, uns
         }
         p += llen+l;
         /* Skip the value as well */
-        l = zipDecodeLength(p);
-        p += zipEncodeLength(NULL,l);
+        l = zipmapDecodeLength(p);
+        p += zipmapEncodeLength(NULL,l);
         free = p[0];
         p += l+1+free; /* +1 to skip the free byte */
     }
@@ -135,23 +168,24 @@ static unsigned long zipmapRequiredLength(unsigned int klen, unsigned int vlen)
     unsigned int l;
 
     l = klen+vlen+3;
-    if (klen >= ZIP_BIGLEN) l += 4;
-    if (vlen >= ZIP_BIGLEN) l += 4;
+    if (klen >= ZIPMAP_BIGLEN) l += 4;
+    if (vlen >= ZIPMAP_BIGLEN) l += 4;
     return l;
 }
 
 /* Return the total amount used by a key (encoded length + payload) */
 static unsigned int zipmapRawKeyLength(unsigned char *p) {
-    return zipRawEntryLength(p);
+    unsigned int l = zipmapDecodeLength(p);
+    return zipmapEncodeLength(NULL,l) + l;
 }
 
 /* Return the total amount used by a value
  * (encoded length + single byte free count + payload) */
 static unsigned int zipmapRawValueLength(unsigned char *p) {
-    unsigned int l = zipDecodeLength(p);
+    unsigned int l = zipmapDecodeLength(p);
     unsigned int used;
     
-    used = zipEncodeLength(NULL,l);
+    used = zipmapEncodeLength(NULL,l);
     used += p[used] + 1 + l;
     return used;
 }
@@ -164,6 +198,12 @@ static unsigned int zipmapRawEntryLength(unsigned char *p) {
     return l + zipmapRawValueLength(p+l);
 }
 
+static inline unsigned char *zipmapResize(unsigned char *zm, unsigned int len) {
+    zm = zrealloc(zm, len);
+    zm[len-1] = ZIPMAP_END;
+    return zm;
+}
+
 /* Set key to value, creating the key if it does not already exist.
  * If 'update' is not NULL, *update is set to 1 if the key was
  * already preset, otherwise to 0. */
@@ -178,12 +218,12 @@ unsigned char *zipmapSet(unsigned char *zm, unsigned char *key, unsigned int kle
     p = zipmapLookupRaw(zm,key,klen,&zmlen);
     if (p == NULL) {
         /* Key not found: enlarge */
-        zm = zipResize(zm, zmlen+reqlen);
+        zm = zipmapResize(zm, zmlen+reqlen);
         p = zm+zmlen-1;
         zmlen = zmlen+reqlen;
 
         /* Increase zipmap length (this is an insert) */
-        if (zm[0] < ZIP_BIGLEN) zm[0]++;
+        if (zm[0] < ZIPMAP_BIGLEN) zm[0]++;
     } else {
         /* Key found. Is there enough space for the new value? */
         /* Compute the total length: */
@@ -194,7 +234,7 @@ unsigned char *zipmapSet(unsigned char *zm, unsigned char *key, unsigned int kle
              * it can be resized. Then, move the tail backwards so this
              * pair fits at the current position. */
             offset = p-zm;
-            zm = zipResize(zm, zmlen-freelen+reqlen);
+            zm = zipmapResize(zm, zmlen-freelen+reqlen);
             p = zm+offset;
 
             /* The +1 in the number of bytes to be moved is caused by the
@@ -216,7 +256,7 @@ unsigned char *zipmapSet(unsigned char *zm, unsigned char *key, unsigned int kle
         offset = p-zm;
         memmove(p+reqlen, p+freelen, zmlen-(offset+freelen+1));
         zmlen -= empty;
-        zm = zipResize(zm, zmlen);
+        zm = zipmapResize(zm, zmlen);
         p = zm+offset;
         vempty = 0;
     } else {
@@ -225,11 +265,11 @@ unsigned char *zipmapSet(unsigned char *zm, unsigned char *key, unsigned int kle
 
     /* Just write the key + value and we are done. */
     /* Key: */
-    p += zipEncodeLength(p,klen);
+    p += zipmapEncodeLength(p,klen);
     memcpy(p,key,klen);
     p += klen;
     /* Value: */
-    p += zipEncodeLength(p,vlen);
+    p += zipmapEncodeLength(p,vlen);
     *p++ = vempty;
     memcpy(p,val,vlen);
     return zm;
@@ -243,10 +283,10 @@ unsigned char *zipmapDel(unsigned char *zm, unsigned char *key, unsigned int kle
     if (p) {
         freelen = zipmapRawEntryLength(p);
         memmove(p, p+freelen, zmlen-((p-zm)+freelen+1));
-        zm = zipResize(zm, zmlen-freelen);
+        zm = zipmapResize(zm, zmlen-freelen);
 
         /* Decrease zipmap length */
-        if (zm[0] < ZIP_BIGLEN) zm[0]--;
+        if (zm[0] < ZIPMAP_BIGLEN) zm[0]--;
 
         if (deleted) *deleted = 1;
     } else {
@@ -272,17 +312,17 @@ unsigned char *zipmapRewind(unsigned char *zm) {
  * }
  */
 unsigned char *zipmapNext(unsigned char *zm, unsigned char **key, unsigned int *klen, unsigned char **value, unsigned int *vlen) {
-    if (zm[0] == ZIP_END) return NULL;
+    if (zm[0] == ZIPMAP_END) return NULL;
     if (key) {
         *key = zm;
-        *klen = zipDecodeLength(zm);
-        *key += ZIP_LEN_BYTES(*klen);
+        *klen = zipmapDecodeLength(zm);
+        *key += ZIPMAP_LEN_BYTES(*klen);
     }
     zm += zipmapRawKeyLength(zm);
     if (value) {
         *value = zm+1;
-        *vlen = zipDecodeLength(zm);
-        *value += ZIP_LEN_BYTES(*vlen);
+        *vlen = zipmapDecodeLength(zm);
+        *value += ZIPMAP_LEN_BYTES(*vlen);
     }
     zm += zipmapRawValueLength(zm);
     return zm;
@@ -295,8 +335,8 @@ int zipmapGet(unsigned char *zm, unsigned char *key, unsigned int klen, unsigned
 
     if ((p = zipmapLookupRaw(zm,key,klen,NULL)) == NULL) return 0;
     p += zipmapRawKeyLength(p);
-    *vlen = zipDecodeLength(p);
-    *value = p + ZIP_LEN_BYTES(*vlen) + 1;
+    *vlen = zipmapDecodeLength(p);
+    *value = p + ZIPMAP_LEN_BYTES(*vlen) + 1;
     return 1;
 }
 
@@ -308,14 +348,14 @@ int zipmapExists(unsigned char *zm, unsigned char *key, unsigned int klen) {
 /* Return the number of entries inside a zipmap */
 unsigned int zipmapLen(unsigned char *zm) {
     unsigned int len = 0;
-    if (zm[0] < ZIP_BIGLEN) {
+    if (zm[0] < ZIPMAP_BIGLEN) {
         len = zm[0];
     } else {
         unsigned char *p = zipmapRewind(zm);
         while((p = zipmapNext(p,NULL,NULL,NULL,NULL)) != NULL) len++;
 
         /* Re-store length if small enough */
-        if (len < ZIP_BIGLEN) zm[0] = len;
+        if (len < ZIPMAP_BIGLEN) zm[0] = len;
     }
     return len;
 }
@@ -325,21 +365,21 @@ void zipmapRepr(unsigned char *p) {
 
     printf("{status %u}",*p++);
     while(1) {
-        if (p[0] == ZIP_END) {
+        if (p[0] == ZIPMAP_END) {
             printf("{end}");
             break;
         } else {
             unsigned char e;
 
-            l = zipDecodeLength(p);
+            l = zipmapDecodeLength(p);
             printf("{key %u}",l);
-            p += zipEncodeLength(NULL,l);
+            p += zipmapEncodeLength(NULL,l);
             fwrite(p,l,1,stdout);
             p += l;
 
-            l = zipDecodeLength(p);
+            l = zipmapDecodeLength(p);
             printf("{value %u}",l);
-            p += zipEncodeLength(NULL,l);
+            p += zipmapEncodeLength(NULL,l);
             e = *p++;
             fwrite(p,l,1,stdout);
             p += l+e;