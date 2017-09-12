@@ -42,10 +42,11 @@
 
 /* Memory layout of a zipmap, for the map "foo" => "bar", "hello" => "world":
  *
- * <status><len>"foo"<len><free>"bar"<len>"hello"<len><free>"world"
+ * <zmlen><len>"foo"<len><free>"bar"<len>"hello"<len><free>"world"
  *
- * <status> is 1 byte status. Currently only 1 bit is used: if the least
- * significant bit is set, it means the zipmap needs to be defragmented.
+ * <zmlen> is 1 byte length that holds the current size of the zipmap.
+ * When the zipmap length is greater than or equal to 254, this value
+ * is not used and the zipmap needs to be traversed to find out the length.
  *
  * <len> is the length of the following string (key or value).
  * <len> lengths are encoded in a single value or in a 5 bytes value.
@@ -62,22 +63,15 @@
  * or even in order to add a key/value pair if it fits.
  *
  * <free> is always an unsigned 8 bit number, because if after an
- * update operation there are more than a few free bytes, they'll be converted
- * into empty space prefixed by the special value 254.
+ * update operation there are more than a few free bytes, the zipmap will be
+ * reallocated to make sure it is as small as possible.
  *
  * The most compact representation of the above two elements hash is actually:
  *
- * "\x00\x03foo\x03\x00bar\x05hello\x05\x00world\xff"
+ * "\x02\x03foo\x03\x00bar\x05hello\x05\x00world\xff"
  *
- * Empty space is marked using a 254 bytes + a <len> (coded as already
- * specified). The length includes the 254 bytes in the count and the
- * space taken by the <len> field. So for instance removing the "foo" key
- * from the zipmap above will lead to the following representation:
- *
- * "\x00\xfd\x10........\x05hello\x05\x00world\xff"
- *
- * Note that because empty space, keys, values, are all prefixed length
- * "objects", the lookup will take O(N) where N is the numeber of elements
+ * Note that because keys and values are prefixed length "objects",
+ * the lookup will take O(N) where N is the number of elements
  * in the zipmap and *not* the number of bytes needed to represent the zipmap.
  * This lowers the constant times considerably.
  */
@@ -87,15 +81,12 @@
 #include <assert.h>
 #include "zmalloc.h"
 
-#define ZIPMAP_BIGLEN 253
-#define ZIPMAP_EMPTY 254
+#define ZIPMAP_BIGLEN 254
 #define ZIPMAP_END 255
 
-#define ZIPMAP_STATUS_FRAGMENTED 1
-
 /* The following defines the max value for the <free> field described in the
  * comments above, that is, the max number of trailing bytes in a value. */
-#define ZIPMAP_VALUE_MAX_FREE 5
+#define ZIPMAP_VALUE_MAX_FREE 4
 
 /* The following macro returns the number of bytes needed to encode the length
  * for the integer value _l, that is, 1 byte for lengths < ZIPMAP_BIGLEN and
@@ -106,7 +97,7 @@
 unsigned char *zipmapNew(void) {
     unsigned char *zm = zmalloc(2);
 
-    zm[0] = 0; /* Status */
+    zm[0] = 0; /* Length */
     zm[1] = ZIPMAP_END;
     return zm;
 }
@@ -142,50 +133,34 @@ static unsigned int zipmapEncodeLength(unsigned char *p, unsigned int len) {
  *
  * If NULL is returned, and totlen is not NULL, it is set to the entire
  * size of the zimap, so that the calling function will be able to
- * reallocate the original zipmap to make room for more entries.
- *
- * If NULL is returned, and freeoff and freelen are not NULL, they are set
- * to the offset of the first empty space that can hold '*freelen' bytes
- * (freelen is an integer pointer used both to signal the required length
- * and to get the reply from the function). If there is not a suitable
- * free space block to hold the requested bytes, *freelen is set to 0. */
-static unsigned char *zipmapLookupRaw(unsigned char *zm, unsigned char *key, unsigned int klen, unsigned int *totlen, unsigned int *freeoff, unsigned int *freelen) {
-    unsigned char *p = zm+1;
+ * reallocate the original zipmap to make room for more entries. */
+static unsigned char *zipmapLookupRaw(unsigned char *zm, unsigned char *key, unsigned int klen, unsigned int *totlen) {
+    unsigned char *p = zm+1, *k = NULL;
     unsigned int l;
-    unsigned int reqfreelen = 0; /* initialized just to prevent warning */
 
-    if (freelen) {
-        reqfreelen = *freelen;
-        *freelen = 0;
-        assert(reqfreelen != 0);
-    }
     while(*p != ZIPMAP_END) {
-        if (*p == ZIPMAP_EMPTY) {
-            l = zipmapDecodeLength(p+1);
-            /* if the user want a free space report, and this space is
-             * enough, and we did't already found a suitable space... */
-            if (freelen && l >= reqfreelen && *freelen == 0) {
-                *freelen = l;
-                *freeoff = p-zm;
+        unsigned char free;
+
+        /* Match or skip the key */
+        l = zipmapDecodeLength(p);
+        if (k == NULL && l == klen && !memcmp(p+1,key,l)) {
+            /* Only return when the user doesn't care
+             * for the total length of the zipmap. */
+            if (totlen != NULL) {
+                k = p;
+            } else {
+                return p;
             }
-            p += l;
-            zm[0] |= ZIPMAP_STATUS_FRAGMENTED;
-        } else {
-            unsigned char free;
-
-            /* Match or skip the key */
-            l = zipmapDecodeLength(p);
-            if (l == klen && !memcmp(p+1,key,l)) return p;
-            p += zipmapEncodeLength(NULL,l) + l;
-            /* Skip the value as well */
-            l = zipmapDecodeLength(p);
-            p += zipmapEncodeLength(NULL,l);
-            free = p[0];
-            p += l+1+free; /* +1 to skip the free byte */
         }
+        p += zipmapEncodeLength(NULL,l) + l;
+        /* Skip the value as well */
+        l = zipmapDecodeLength(p);
+        p += zipmapEncodeLength(NULL,l);
+        free = p[0];
+        p += l+1+free; /* +1 to skip the free byte */
     }
     if (totlen != NULL) *totlen = (unsigned int)(p-zm)+1;
-    return NULL;
+    return k;
 }
 
 static unsigned long zipmapRequiredLength(unsigned int klen, unsigned int vlen) {
@@ -220,64 +195,70 @@ static unsigned int zipmapRawValueLength(unsigned char *p) {
  * free space if any). */
 static unsigned int zipmapRawEntryLength(unsigned char *p) {
     unsigned int l = zipmapRawKeyLength(p);
-
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
 unsigned char *zipmapSet(unsigned char *zm, unsigned char *key, unsigned int klen, unsigned char *val, unsigned int vlen, int *update) {
-    unsigned int oldlen = 0, freeoff = 0, freelen;
-    unsigned int reqlen = zipmapRequiredLength(klen,vlen);
+    unsigned int zmlen, offset;
+    unsigned int freelen, reqlen = zipmapRequiredLength(klen,vlen);
     unsigned int empty, vempty;
     unsigned char *p;
    
     freelen = reqlen;
     if (update) *update = 0;
-    p = zipmapLookupRaw(zm,key,klen,&oldlen,&freeoff,&freelen);
-    if (p == NULL && freelen == 0) {
-        /* Key not found, and not space for the new key. Enlarge */
-        zm = zrealloc(zm,oldlen+reqlen);
-        p = zm+oldlen-1;
-        zm[oldlen+reqlen-1] = ZIPMAP_END;
-        freelen = reqlen;
-    } else if (p == NULL) {
-        /* Key not found, but there is enough free space. */
-        p = zm+freeoff;
-        /* note: freelen is already set in this case */
-    } else {
-        unsigned char *b = p;
+    p = zipmapLookupRaw(zm,key,klen,&zmlen);
+    if (p == NULL) {
+        /* Key not found: enlarge */
+        zm = zipmapResize(zm, zmlen+reqlen);
+        p = zm+zmlen-1;
+        zmlen = zmlen+reqlen;
 
+        /* Increase zipmap length (this is an insert) */
+        if (zm[0] < ZIPMAP_BIGLEN) zm[0]++;
+    } else {
         /* Key found. Is there enough space for the new value? */
         /* Compute the total length: */
         if (update) *update = 1;
-        freelen = zipmapRawKeyLength(b);
-        b += freelen;
-        freelen += zipmapRawValueLength(b);
+        freelen = zipmapRawEntryLength(p);
         if (freelen < reqlen) {
-            /* Mark this entry as free and recurse */
-            p[0] = ZIPMAP_EMPTY;
-            zipmapEncodeLength(p+1,freelen);
-            zm[0] |= ZIPMAP_STATUS_FRAGMENTED;
-            return zipmapSet(zm,key,klen,val,vlen,NULL);
+            /* Store the offset of this key within the current zipmap, so
+             * it can be resized. Then, move the tail backwards so this
+             * pair fits at the current position. */
+            offset = p-zm;
+            zm = zipmapResize(zm, zmlen-freelen+reqlen);
+            p = zm+offset;
+
+            /* The +1 in the number of bytes to be moved is caused by the
+             * end-of-zipmap byte. Note: the *original* zmlen is used. */
+            memmove(p+reqlen, p+freelen, zmlen-(offset+freelen+1));
+            zmlen = zmlen-freelen+reqlen;
+            freelen = reqlen;
         }
     }
 
-    /* Ok we have a suitable block where to write the new key/value
-     * entry. */
+    /* We now have a suitable block where the key/value entry can
+     * be written. If there is too much free space, move the tail
+     * of the zipmap a few bytes to the front and shrink the zipmap,
+     * as we want zipmaps to be very space efficient. */
     empty = freelen-reqlen;
-    /* If there is too much free space mark it as a free block instead
-     * of adding it as trailing empty space for the value, as we want
-     * zipmaps to be very space efficient. */
-    if (empty > ZIPMAP_VALUE_MAX_FREE) {
-        unsigned char *e;
-
-        e = p+reqlen;
-        e[0] = ZIPMAP_EMPTY;
-        zipmapEncodeLength(e+1,empty);
+    if (empty >= ZIPMAP_VALUE_MAX_FREE) {
+        /* First, move the tail <empty> bytes to the front, then resize
+         * the zipmap to be <empty> bytes smaller. */
+        offset = p-zm;
+        memmove(p+reqlen, p+freelen, zmlen-(offset+freelen+1));
+        zmlen -= empty;
+        zm = zipmapResize(zm, zmlen);
+        p = zm+offset;
         vempty = 0;
-        zm[0] |= ZIPMAP_STATUS_FRAGMENTED;
     } else {
         vempty = empty;
     }
@@ -297,13 +278,16 @@ unsigned char *zipmapSet(unsigned char *zm, unsigned char *key, unsigned int kle
 /* Remove the specified key. If 'deleted' is not NULL the pointed integer is
  * set to 0 if the key was not found, to 1 if it was found and deleted. */
 unsigned char *zipmapDel(unsigned char *zm, unsigned char *key, unsigned int klen, int *deleted) {
-    unsigned char *p = zipmapLookupRaw(zm,key,klen,NULL,NULL,NULL);
+    unsigned int zmlen, freelen;
+    unsigned char *p = zipmapLookupRaw(zm,key,klen,&zmlen);
     if (p) {
-        unsigned int freelen = zipmapRawEntryLength(p);
+        freelen = zipmapRawEntryLength(p);
+        memmove(p, p+freelen, zmlen-((p-zm)+freelen+1));
+        zm = zipmapResize(zm, zmlen-freelen);
+
+        /* Decrease zipmap length */
+        if (zm[0] < ZIPMAP_BIGLEN) zm[0]--;
 
-        p[0] = ZIPMAP_EMPTY;
-        zipmapEncodeLength(p+1,freelen);
-        zm[0] |= ZIPMAP_STATUS_FRAGMENTED;
         if (deleted) *deleted = 1;
     } else {
         if (deleted) *deleted = 0;
@@ -328,8 +312,6 @@ unsigned char *zipmapRewind(unsigned char *zm) {
  * }
  */
 unsigned char *zipmapNext(unsigned char *zm, unsigned char **key, unsigned int *klen, unsigned char **value, unsigned int *vlen) {
-    while(zm[0] == ZIPMAP_EMPTY)
-        zm += zipmapDecodeLength(zm+1);
     if (zm[0] == ZIPMAP_END) return NULL;
     if (key) {
         *key = zm;
@@ -351,7 +333,7 @@ unsigned char *zipmapNext(unsigned char *zm, unsigned char **key, unsigned int *
 int zipmapGet(unsigned char *zm, unsigned char *key, unsigned int klen, unsigned char **value, unsigned int *vlen) {
     unsigned char *p;
 
-    if ((p = zipmapLookupRaw(zm,key,klen,NULL,NULL,NULL)) == NULL) return 0;
+    if ((p = zipmapLookupRaw(zm,key,klen,NULL)) == NULL) return 0;
     p += zipmapRawKeyLength(p);
     *vlen = zipmapDecodeLength(p);
     *value = p + ZIPMAP_LEN_BYTES(*vlen) + 1;
@@ -360,15 +342,21 @@ int zipmapGet(unsigned char *zm, unsigned char *key, unsigned int klen, unsigned
 
 /* Return 1 if the key exists, otherwise 0 is returned. */
 int zipmapExists(unsigned char *zm, unsigned char *key, unsigned int klen) {
-    return zipmapLookupRaw(zm,key,klen,NULL,NULL,NULL) != NULL;
+    return zipmapLookupRaw(zm,key,klen,NULL) != NULL;
 }
 
 /* Return the number of entries inside a zipmap */
 unsigned int zipmapLen(unsigned char *zm) {
-    unsigned char *p = zipmapRewind(zm);
     unsigned int len = 0;
+    if (zm[0] < ZIPMAP_BIGLEN) {
+        len = zm[0];
+    } else {
+        unsigned char *p = zipmapRewind(zm);
+        while((p = zipmapNext(p,NULL,NULL,NULL,NULL)) != NULL) len++;
 
-    while((p = zipmapNext(p,NULL,NULL,NULL,NULL)) != NULL) len++;
+        /* Re-store length if small enough */
+        if (len < ZIPMAP_BIGLEN) zm[0] = len;
+    }
     return len;
 }
 
@@ -380,10 +368,6 @@ void zipmapRepr(unsigned char *p) {
         if (p[0] == ZIPMAP_END) {
             printf("{end}");
             break;
-        } else if (p[0] == ZIPMAP_EMPTY) {
-            l = zipmapDecodeLength(p+1);
-            printf("{%u empty block}", l);
-            p += l;
         } else {
             unsigned char e;
 