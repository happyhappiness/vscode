@@ -35,7 +35,7 @@
 #include <ctype.h>
 #include <assert.h>
 #include "sds.h"
-#include "zmalloc.h"
+#include "sdsalloc.h"
 
 static inline int sdsHdrSize(char type) {
     switch(type&SDS_TYPE_MASK) {
@@ -87,7 +87,7 @@ sds sdsnewlen(const void *init, size_t initlen) {
     int hdrlen = sdsHdrSize(type);
     unsigned char *fp; /* flags pointer. */
 
-    sh = zmalloc(hdrlen+initlen+1);
+    sh = s_malloc(hdrlen+initlen+1);
     if (!init)
         memset(sh, 0, hdrlen+initlen+1);
     if (sh == NULL) return NULL;
@@ -153,7 +153,7 @@ sds sdsdup(const sds s) {
 /* Free an sds string. No operation is performed if 's' is NULL. */
 void sdsfree(sds s) {
     if (s == NULL) return;
-    zfree((char*)s-sdsHdrSize(s[-1]));
+    s_free((char*)s-sdsHdrSize(s[-1]));
 }
 
 /* Set the sds string length to the length as obtained with strlen(), so
@@ -217,16 +217,16 @@ sds sdsMakeRoomFor(sds s, size_t addlen) {
 
     hdrlen = sdsHdrSize(type);
     if (oldtype==type) {
-        newsh = zrealloc(sh, hdrlen+newlen+1);
+        newsh = s_realloc(sh, hdrlen+newlen+1);
         if (newsh == NULL) return NULL;
         s = (char*)newsh+hdrlen;
     } else {
         /* Since the header size changes, need to move the string forward,
          * and can't use realloc */
-        newsh = zmalloc(hdrlen+newlen+1);
+        newsh = s_malloc(hdrlen+newlen+1);
         if (newsh == NULL) return NULL;
         memcpy((char*)newsh+hdrlen, s, len+1);
-        zfree(sh);
+        s_free(sh);
         s = (char*)newsh+hdrlen;
         s[-1] = type;
         sdssetlen(s, len);
@@ -251,14 +251,14 @@ sds sdsRemoveFreeSpace(sds s) {
     type = sdsReqType(len);
     hdrlen = sdsHdrSize(type);
     if (oldtype==type) {
-        newsh = zrealloc(sh, hdrlen+len+1);
+        newsh = s_realloc(sh, hdrlen+len+1);
         if (newsh == NULL) return NULL;
         s = (char*)newsh+hdrlen;
     } else {
-        newsh = zmalloc(hdrlen+len+1);
+        newsh = s_malloc(hdrlen+len+1);
         if (newsh == NULL) return NULL;
         memcpy((char*)newsh+hdrlen, s, len+1);
-        zfree(sh);
+        s_free(sh);
         s = (char*)newsh+hdrlen;
         s[-1] = type;
         sdssetlen(s, len);
@@ -279,11 +279,10 @@ size_t sdsAllocSize(sds s) {
     return sdsHdrSize(s[-1])+alloc+1;
 }
 
-/* Return the size consumed from the allocator,
- * including internal fragmentation */
-size_t sdsZmallocSize(sds s) {
-    struct sdshdr *sh = (void*) (s-sdsHdrSize(s[-1]));
-    return zmalloc_size(sh);
+/* Return the pointer of the actual SDS allocation (normally SDS strings
+ * are referenced by the start of the string buffer). */
+void *sdsAllocPtr(sds s) {
+    return (void*) (s-sdsHdrSize(s[-1]));
 }
 
 /* Increment the sds length and decrements the left free space at the
@@ -506,7 +505,7 @@ sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
     /* We try to start using a static buffer for speed.
      * If not possible we revert to heap allocation. */
     if (buflen > sizeof(staticbuf)) {
-        buf = zmalloc(buflen);
+        buf = s_malloc(buflen);
         if (buf == NULL) return NULL;
     } else {
         buflen = sizeof(staticbuf);
@@ -520,9 +519,9 @@ sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
         vsnprintf(buf, buflen, fmt, cpy);
         va_end(cpy);
         if (buf[buflen-2] != '\0') {
-            if (buf != staticbuf) zfree(buf);
+            if (buf != staticbuf) s_free(buf);
             buflen *= 2;
-            buf = zmalloc(buflen);
+            buf = s_malloc(buflen);
             if (buf == NULL) return NULL;
             continue;
         }
@@ -531,7 +530,7 @@ sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
 
     /* Finally concat the obtained string to the SDS string and return it. */
     t = sdscat(s, buf);
-    if (buf != staticbuf) zfree(buf);
+    if (buf != staticbuf) s_free(buf);
     return t;
 }
 
@@ -798,7 +797,7 @@ sds *sdssplitlen(const char *s, int len, const char *sep, int seplen, int *count
 
     if (seplen < 1 || len < 0) return NULL;
 
-    tokens = zmalloc(sizeof(sds)*slots);
+    tokens = s_malloc(sizeof(sds)*slots);
     if (tokens == NULL) return NULL;
 
     if (len == 0) {
@@ -811,7 +810,7 @@ sds *sdssplitlen(const char *s, int len, const char *sep, int seplen, int *count
             sds *newtokens;
 
             slots *= 2;
-            newtokens = zrealloc(tokens,sizeof(sds)*slots);
+            newtokens = s_realloc(tokens,sizeof(sds)*slots);
             if (newtokens == NULL) goto cleanup;
             tokens = newtokens;
         }
@@ -835,7 +834,7 @@ sds *sdssplitlen(const char *s, int len, const char *sep, int seplen, int *count
     {
         int i;
         for (i = 0; i < elements; i++) sdsfree(tokens[i]);
-        zfree(tokens);
+        s_free(tokens);
         *count = 0;
         return NULL;
     }
@@ -846,7 +845,7 @@ void sdsfreesplitres(sds *tokens, int count) {
     if (!tokens) return;
     while(count--)
         sdsfree(tokens[count]);
-    zfree(tokens);
+    s_free(tokens);
 }
 
 /* Append to the sds string "s" an escaped string representation where
@@ -1020,21 +1019,21 @@ sds *sdssplitargs(const char *line, int *argc) {
                 if (*p) p++;
             }
             /* add the token to the vector */
-            vector = zrealloc(vector,((*argc)+1)*sizeof(char*));
+            vector = s_realloc(vector,((*argc)+1)*sizeof(char*));
             vector[*argc] = current;
             (*argc)++;
             current = NULL;
         } else {
             /* Even on empty input string return something not NULL. */
-            if (vector == NULL) vector = zmalloc(sizeof(void*));
+            if (vector == NULL) vector = s_malloc(sizeof(void*));
             return vector;
         }
     }
 
 err:
     while((*argc)--)
         sdsfree(vector[*argc]);
-    zfree(vector);
+    s_free(vector);
     if (current) sdsfree(current);
     *argc = 0;
     return NULL;
@@ -1088,7 +1087,7 @@ sds sdsjoinsds(sds *argv, int argc, const char *sep, size_t seplen) {
     return join;
 }
 
-#if defined(REDIS_TEST) || defined(SDS_TEST_MAIN)
+#if defined(SDS_TEST_MAIN)
 #include <stdio.h>
 #include "testhelp.h"
 #include "limits.h"