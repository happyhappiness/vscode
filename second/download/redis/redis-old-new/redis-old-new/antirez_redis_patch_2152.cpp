@@ -87,12 +87,9 @@
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
 #define ZIPMAP_VALUE_MAX_FREE 5
@@ -142,13 +139,7 @@ static unsigned int zipmapEncodeLength(unsigned char *p, unsigned int len) {
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
+ * reallocate the original zipmap to make room for more entries. */
 static unsigned char *zipmapLookupRaw(unsigned char *zm, unsigned char *key, unsigned int klen, unsigned int *totlen) {
     unsigned char *p = zm+1, *k = NULL;
     unsigned int l;
@@ -325,8 +316,6 @@ unsigned char *zipmapRewind(unsigned char *zm) {
  * }
  */
 unsigned char *zipmapNext(unsigned char *zm, unsigned char **key, unsigned int *klen, unsigned char **value, unsigned int *vlen) {
-    while(zm[0] == ZIPMAP_EMPTY)
-        zm += zipmapDecodeLength(zm+1);
     if (zm[0] == ZIPMAP_END) return NULL;
     if (key) {
         *key = zm;
@@ -383,10 +372,6 @@ void zipmapRepr(unsigned char *p) {
         if (p[0] == ZIPMAP_END) {
             printf("{end}");
             break;
-        } else if (p[0] == ZIPMAP_EMPTY) {
-            l = zipmapDecodeLength(p+1);
-            printf("{%u empty block}", l);
-            p += l;
         } else {
             unsigned char e;
 