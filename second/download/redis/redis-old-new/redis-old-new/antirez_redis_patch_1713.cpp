@@ -144,7 +144,7 @@ static unsigned char *zipmapLookupRaw(unsigned char *zm, unsigned char *key, uns
         /* Match or skip the key */
         l = zipmapDecodeLength(p);
         llen = zipmapEncodeLength(NULL,l);
-        if (k == NULL && l == klen && !memcmp(p+llen,key,l)) {
+        if (key != NULL && k == NULL && l == klen && !memcmp(p+llen,key,l)) {
             /* Only return when the user doesn't care
              * for the total length of the zipmap. */
             if (totlen != NULL) {
@@ -364,14 +364,12 @@ unsigned int zipmapLen(unsigned char *zm) {
  * the zipmap on disk (or everywhere is needed) just writing the returned
  * amount of bytes of the C array starting at the zipmap pointer. */
 size_t zipmapBlobLen(unsigned char *zm) {
-    unsigned char *p = zipmapRewind(zm);
-    unsigned char *old = p;
-    while((p = zipmapNext(p,NULL,NULL,NULL,NULL)) != NULL) {
-        old = p;
-    }
-    return (old-zm)+1;
+    unsigned int totlen;
+    zipmapLookupRaw(zm,NULL,0,&totlen);
+    return totlen;
 }
 
+#ifdef ZIPMAP_TEST_MAIN
 void zipmapRepr(unsigned char *p) {
     unsigned int l;
 
@@ -405,7 +403,6 @@ void zipmapRepr(unsigned char *p) {
     printf("\n");
 }
 
-#ifdef ZIPMAP_TEST_MAIN
 int main(void) {
     unsigned char *zm;
 