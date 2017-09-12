@@ -97,6 +97,11 @@
  * comments above, that is, the max number of trailing bytes in a value. */
 #define ZIPMAP_VALUE_MAX_FREE 5
 
+/* The following macro returns the number of bytes needed to encode the length
+ * for the integer value _l, that is, 1 byte for lengths < ZIPMAP_BIGLEN and
+ * 5 bytes for all the other lengths. */
+#define ZIPMAP_LEN_BYTES(_l) (((_l) < ZIPMAP_BIGLEN) ? 1 : sizeof(unsigned int)+1)
+
 /* Create a new empty zipmap. */
 unsigned char *zipmapNew(void) {
     unsigned char *zm = zmalloc(2);
@@ -119,7 +124,7 @@ static unsigned int zipmapDecodeLength(unsigned char *p) {
  * the amount of bytes required to encode such a length. */
 static unsigned int zipmapEncodeLength(unsigned char *p, unsigned int len) {
     if (p == NULL) {
-        return (len < ZIPMAP_BIGLEN) ? 1 : 1+sizeof(unsigned int);
+        return ZIPMAP_LEN_BYTES(len);
     } else {
         if (len < ZIPMAP_BIGLEN) {
             p[0] = len;
@@ -219,23 +224,24 @@ static unsigned int zipmapRawEntryLength(unsigned char *p) {
     return l + zipmapRawValueLength(p+l);
 }
 
-/* Set key to value, creating the key if it does not already exist. */
-unsigned char *zipmapSet(unsigned char *zm, unsigned char *key, unsigned int klen, unsigned char *val, unsigned int vlen) {
+/* Set key to value, creating the key if it does not already exist.
+ * If 'update' is not NULL, *update is set to 1 if the key was
+ * already preset, otherwise to 0. */
+unsigned char *zipmapSet(unsigned char *zm, unsigned char *key, unsigned int klen, unsigned char *val, unsigned int vlen, int *update) {
     unsigned int oldlen = 0, freeoff = 0, freelen;
     unsigned int reqlen = zipmapRequiredLength(klen,vlen);
     unsigned int empty, vempty;
     unsigned char *p;
    
     freelen = reqlen;
+    if (update) *update = 0;
     p = zipmapLookupRaw(zm,key,klen,&oldlen,&freeoff,&freelen);
     if (p == NULL && freelen == 0) {
-        printf("HERE oldlen:%u required:%u\n",oldlen,reqlen);
         /* Key not found, and not space for the new key. Enlarge */
         zm = zrealloc(zm,oldlen+reqlen);
         p = zm+oldlen-1;
         zm[oldlen+reqlen-1] = ZIPMAP_END;
         freelen = reqlen;
-        printf("New total length is: %u\n", oldlen+reqlen);
     } else if (p == NULL) {
         /* Key not found, but there is enough free space. */
         p = zm+freeoff;
@@ -245,6 +251,7 @@ unsigned char *zipmapSet(unsigned char *zm, unsigned char *key, unsigned int kle
 
         /* Key found. Is there enough space for the new value? */
         /* Compute the total length: */
+        if (update) *update = 1;
         freelen = zipmapRawKeyLength(b);
         b += freelen;
         freelen += zipmapRawValueLength(b);
@@ -253,7 +260,7 @@ unsigned char *zipmapSet(unsigned char *zm, unsigned char *key, unsigned int kle
             p[0] = ZIPMAP_EMPTY;
             zipmapEncodeLength(p+1,freelen);
             zm[0] |= ZIPMAP_STATUS_FRAGMENTED;
-            return zipmapSet(zm,key,klen,val,vlen);
+            return zipmapSet(zm,key,klen,val,vlen,NULL);
         }
     }
 
@@ -304,37 +311,58 @@ unsigned char *zipmapDel(unsigned char *zm, unsigned char *key, unsigned int kle
     return zm;
 }
 
+/* Call it before to iterate trought elements via zipmapNext() */
+unsigned char *zipmapRewind(unsigned char *zm) {
+    return zm+1;
+}
+
 /* This function is used to iterate through all the zipmap elements.
  * In the first call the first argument is the pointer to the zipmap + 1.
  * In the next calls what zipmapNext returns is used as first argument.
  * Example:
  *
- * unsigned char *i = my_zipmap+1;
+ * unsigned char *i = zipmapRewind(my_zipmap);
  * while((i = zipmapNext(i,&key,&klen,&value,&vlen)) != NULL) {
  *     printf("%d bytes key at $p\n", klen, key);
  *     printf("%d bytes value at $p\n", vlen, value);
  * }
  */
-unsigned char *zipmapNext(unsigned char *zm, unsigned char **key,
-            unsigned int *klen, unsigned char **value, unsigned int *vlen) {
+unsigned char *zipmapNext(unsigned char *zm, unsigned char **key, unsigned int *klen, unsigned char **value, unsigned int *vlen) {
     while(zm[0] == ZIPMAP_EMPTY)
         zm += zipmapDecodeLength(zm+1);
     if (zm[0] == ZIPMAP_END) return NULL;
     if (key) {
         *key = zm;
         *klen = zipmapDecodeLength(zm);
-        *key += (*klen < ZIPMAP_BIGLEN) ? 1 : sizeof(unsigned int);
+        *key += ZIPMAP_LEN_BYTES(*klen);
     }
     zm += zipmapRawKeyLength(zm);
     if (value) {
         *value = zm+1;
         *vlen = zipmapDecodeLength(zm);
-        *value += (*vlen < ZIPMAP_BIGLEN) ? 1 : sizeof(unsigned int);
+        *value += ZIPMAP_LEN_BYTES(*vlen);
     }
     zm += zipmapRawValueLength(zm);
     return zm;
 }
 
+/* Search a key and retrieve the pointer and len of the associated value.
+ * If the key is found the function returns 1, otherwise 0. */
+int zipmapGet(unsigned char *zm, unsigned char *key, unsigned int klen, unsigned char **value, unsigned int *vlen) {
+    unsigned char *p;
+
+    if ((p = zipmapLookupRaw(zm,key,klen,NULL,NULL,NULL)) == NULL) return 0;
+    p += zipmapRawKeyLength(p);
+    *vlen = zipmapDecodeLength(p);
+    *value = p + ZIPMAP_LEN_BYTES(*vlen) + 1;
+    return 1;
+}
+
+/* Return 1 if the key exists, otherwise 0 is returned. */
+int zipmapExists(unsigned char *zm, unsigned char *key, unsigned int klen) {
+    return zipmapLookupRaw(zm,key,klen,NULL,NULL,NULL) != NULL;
+}
+
 void zipmapRepr(unsigned char *p) {
     unsigned int l;
 
@@ -372,29 +400,41 @@ void zipmapRepr(unsigned char *p) {
     printf("\n");
 }
 
+#ifdef ZIPMAP_TEST_MAIN
 int main(void) {
     unsigned char *zm;
 
     zm = zipmapNew();
-    zm = zipmapSet(zm,(unsigned char*) "hello",5, (unsigned char*) "world!",6);
-    zm = zipmapSet(zm,(unsigned char*) "foo",3, (unsigned char*) "bar",3);
-    zm = zipmapSet(zm,(unsigned char*) "foo",3, (unsigned char*) "!",1);
+    zm = zipmapSet(zm,(unsigned char*) "hello",5, (unsigned char*) "world!",6,NULL);
+    zm = zipmapSet(zm,(unsigned char*) "foo",3, (unsigned char*) "bar",3,NULL);
+    zm = zipmapSet(zm,(unsigned char*) "foo",3, (unsigned char*) "!",1,NULL);
     zipmapRepr(zm);
-    zm = zipmapSet(zm,(unsigned char*) "foo",3, (unsigned char*) "12345",5);
+    zm = zipmapSet(zm,(unsigned char*) "foo",3, (unsigned char*) "12345",5,NULL);
     zipmapRepr(zm);
-    zm = zipmapSet(zm,(unsigned char*) "new",3, (unsigned char*) "xx",2);
+    zm = zipmapSet(zm,(unsigned char*) "new",3, (unsigned char*) "xx",2,NULL);
     zipmapRepr(zm);
     zm = zipmapDel(zm,(unsigned char*) "new",3,NULL);
     zipmapRepr(zm);
-    printf("Iterate trought elements:\n");
+    printf("\nPerform a direct lookup:\n");
+    {
+        unsigned char *value;
+        unsigned int vlen;
+
+        if (zipmapGet(zm,(unsigned char*) "foo",3,&value,&vlen)) {
+            printf("  foo is associated to the %d bytes value: %.*s\n",
+                vlen, vlen, value);
+        }
+    }
+    printf("\nIterate trought elements:\n");
     {
-        unsigned char *i = zm+1;
+        unsigned char *i = zipmapRewind(zm);
         unsigned char *key, *value;
         unsigned int klen, vlen;
 
         while((i = zipmapNext(i,&key,&klen,&value,&vlen)) != NULL) {
-            printf("%d:%.*s => %d:%.*s\n", klen, klen, key, vlen, vlen, value);
+            printf("  %d:%.*s => %d:%.*s\n", klen, klen, key, vlen, vlen, value);
         }
     }
     return 0;
 }
+#endif