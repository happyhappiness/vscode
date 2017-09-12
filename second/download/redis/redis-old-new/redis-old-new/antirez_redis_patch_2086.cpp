@@ -136,14 +136,15 @@ static unsigned int zipmapEncodeLength(unsigned char *p, unsigned int len) {
  * reallocate the original zipmap to make room for more entries. */
 static unsigned char *zipmapLookupRaw(unsigned char *zm, unsigned char *key, unsigned int klen, unsigned int *totlen) {
     unsigned char *p = zm+1, *k = NULL;
-    unsigned int l;
+    unsigned int l,llen;
 
     while(*p != ZIPMAP_END) {
         unsigned char free;
 
         /* Match or skip the key */
         l = zipmapDecodeLength(p);
-        if (k == NULL && l == klen && !memcmp(p+1,key,l)) {
+        llen = zipmapEncodeLength(NULL,l);
+        if (k == NULL && l == klen && !memcmp(p+llen,key,l)) {
             /* Only return when the user doesn't care
              * for the total length of the zipmap. */
             if (totlen != NULL) {
@@ -152,7 +153,7 @@ static unsigned char *zipmapLookupRaw(unsigned char *zm, unsigned char *key, uns
                 return p;
             }
         }
-        p += zipmapEncodeLength(NULL,l) + l;
+        p += llen+l;
         /* Skip the value as well */
         l = zipmapDecodeLength(p);
         p += zipmapEncodeLength(NULL,l);
@@ -403,7 +404,6 @@ int main(void) {
     zm = zipmapSet(zm,(unsigned char*) "surname",7, (unsigned char*) "foo",3,NULL);
     zm = zipmapSet(zm,(unsigned char*) "age",3, (unsigned char*) "foo",3,NULL);
     zipmapRepr(zm);
-    exit(1);
 
     zm = zipmapSet(zm,(unsigned char*) "hello",5, (unsigned char*) "world!",6,NULL);
     zm = zipmapSet(zm,(unsigned char*) "foo",3, (unsigned char*) "bar",3,NULL);
@@ -416,6 +416,21 @@ int main(void) {
     zipmapRepr(zm);
     zm = zipmapDel(zm,(unsigned char*) "new",3,NULL);
     zipmapRepr(zm);
+
+    printf("\nLook up large key:\n");
+    {
+        unsigned char buf[512];
+        unsigned char *value;
+        unsigned int vlen, i;
+        for (i = 0; i < 512; i++) buf[i] = 'a';
+
+        zm = zipmapSet(zm,buf,512,(unsigned char*) "long",4,NULL);
+        if (zipmapGet(zm,buf,512,&value,&vlen)) {
+            printf("  <long key> is associated to the %d bytes value: %.*s\n",
+                vlen, vlen, value);
+        }
+    }
+
     printf("\nPerform a direct lookup:\n");
     {
         unsigned char *value;