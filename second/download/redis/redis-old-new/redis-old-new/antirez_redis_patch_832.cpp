@@ -1,6 +1,6 @@
-/* SDSLib, A C dynamic strings library
+/* SDS (Simple Dynamic Strings), A C dynamic strings library.
  *
- * Copyright (c) 2006-2012, Salvatore Sanfilippo <antirez at gmail dot com>
+ * Copyright (c) 2006-2014, Salvatore Sanfilippo <antirez at gmail dot com>
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -33,8 +33,8 @@
 #include <string.h>
 #include <ctype.h>
 #include <assert.h>
+
 #include "sds.h"
-#include "zmalloc.h"
 
 /* Create a new sds string with the content specified by the 'init' pointer
  * and 'initlen'.
@@ -52,9 +52,9 @@ sds sdsnewlen(const void *init, size_t initlen) {
     struct sdshdr *sh;
 
     if (init) {
-        sh = zmalloc(sizeof(struct sdshdr)+initlen+1);
+        sh = malloc(sizeof *sh+initlen+1);
     } else {
-        sh = zcalloc(sizeof(struct sdshdr)+initlen+1);
+        sh = calloc(sizeof *sh+initlen+1,1);
     }
     if (sh == NULL) return NULL;
     sh->len = initlen;
@@ -85,7 +85,7 @@ sds sdsdup(const sds s) {
 /* Free an sds string. No operation is performed if 's' is NULL. */
 void sdsfree(sds s) {
     if (s == NULL) return;
-    zfree(s-sizeof(struct sdshdr));
+    free(s-sizeof(struct sdshdr));
 }
 
 /* Set the sds string length to the length as obtained with strlen(), so
@@ -103,7 +103,7 @@ void sdsfree(sds s) {
  * the output will be "6" as the string was modified but the logical length
  * remains 6 bytes. */
 void sdsupdatelen(sds s) {
-    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
+    struct sdshdr *sh = (void*) (s-sizeof *sh);;
     int reallen = strlen(s);
     sh->free += (sh->len-reallen);
     sh->len = reallen;
@@ -114,7 +114,7 @@ void sdsupdatelen(sds s) {
  * so that next append operations will not require allocations up to the
  * number of bytes previously available. */
 void sdsclear(sds s) {
-    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
+    struct sdshdr *sh = (void*) (s-sizeof *sh);;
     sh->free += sh->len;
     sh->len = 0;
     sh->buf[0] = '\0';
@@ -133,13 +133,13 @@ sds sdsMakeRoomFor(sds s, size_t addlen) {
 
     if (free >= addlen) return s;
     len = sdslen(s);
-    sh = (void*) (s-(sizeof(struct sdshdr)));
+    sh = (void*) (s-sizeof *sh);;
     newlen = (len+addlen);
     if (newlen < SDS_MAX_PREALLOC)
         newlen *= 2;
     else
         newlen += SDS_MAX_PREALLOC;
-    newsh = zrealloc(sh, sizeof(struct sdshdr)+newlen+1);
+    newsh = realloc(sh, sizeof *newsh+newlen+1);
     if (newsh == NULL) return NULL;
 
     newsh->free = newlen - len;
@@ -155,8 +155,8 @@ sds sdsMakeRoomFor(sds s, size_t addlen) {
 sds sdsRemoveFreeSpace(sds s) {
     struct sdshdr *sh;
 
-    sh = (void*) (s-(sizeof(struct sdshdr)));
-    sh = zrealloc(sh, sizeof(struct sdshdr)+sh->len+1);
+    sh = (void*) (s-sizeof *sh);;
+    sh = realloc(sh, sizeof *sh+sh->len+1);
     sh->free = 0;
     return sh->buf;
 }
@@ -169,7 +169,7 @@ sds sdsRemoveFreeSpace(sds s) {
  * 4) The implicit null term.
  */
 size_t sdsAllocSize(sds s) {
-    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
+    struct sdshdr *sh = (void*) (s-sizeof *sh);;
 
     return sizeof(*sh)+sh->len+sh->free+1;
 }
@@ -198,7 +198,7 @@ size_t sdsAllocSize(sds s) {
  * sdsIncrLen(s, nread);
  */
 void sdsIncrLen(sds s, int incr) {
-    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
+    struct sdshdr *sh = (void*) (s-sizeof *sh);;
 
     assert(sh->free >= incr);
     sh->len += incr;
@@ -213,15 +213,15 @@ void sdsIncrLen(sds s, int incr) {
  * if the specified length is smaller than the current length, no operation
  * is performed. */
 sds sdsgrowzero(sds s, size_t len) {
-    struct sdshdr *sh = (void*)(s-(sizeof(struct sdshdr)));
+    struct sdshdr *sh = (void*) (s-sizeof *sh);
     size_t totlen, curlen = sh->len;
 
     if (len <= curlen) return s;
     s = sdsMakeRoomFor(s,len-curlen);
     if (s == NULL) return NULL;
 
     /* Make sure added region doesn't contain garbage */
-    sh = (void*)(s-(sizeof(struct sdshdr)));
+    sh = (void*)(s-sizeof *sh);
     memset(s+curlen,0,(len-curlen+1)); /* also set trailing \0 byte */
     totlen = sh->len+sh->free;
     sh->len = len;
@@ -240,7 +240,7 @@ sds sdscatlen(sds s, const void *t, size_t len) {
 
     s = sdsMakeRoomFor(s,len);
     if (s == NULL) return NULL;
-    sh = (void*) (s-(sizeof(struct sdshdr)));
+    sh = (void*) (s-sizeof *sh);;
     memcpy(s+curlen, t, len);
     sh->len = curlen+len;
     sh->free = sh->free-len;
@@ -267,13 +267,13 @@ sds sdscatsds(sds s, const sds t) {
 /* Destructively modify the sds string 's' to hold the specified binary
  * safe string pointed by 't' of length 'len' bytes. */
 sds sdscpylen(sds s, const char *t, size_t len) {
-    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
+    struct sdshdr *sh = (void*) (s-sizeof *sh);;
     size_t totlen = sh->free+sh->len;
 
     if (totlen < len) {
         s = sdsMakeRoomFor(s,len-sh->len);
         if (s == NULL) return NULL;
-        sh = (void*) (s-(sizeof(struct sdshdr)));
+        sh = (void*) (s-sizeof *sh);;
         totlen = sh->free+sh->len;
     }
     memcpy(s, t, len);
@@ -296,20 +296,20 @@ sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
     size_t buflen = 16;
 
     while(1) {
-        buf = zmalloc(buflen);
+        buf = malloc(buflen);
         if (buf == NULL) return NULL;
         buf[buflen-2] = '\0';
         va_copy(cpy,ap);
         vsnprintf(buf, buflen, fmt, cpy);
         if (buf[buflen-2] != '\0') {
-            zfree(buf);
+            free(buf);
             buflen *= 2;
             continue;
         }
         break;
     }
     t = sdscat(s, buf);
-    zfree(buf);
+    free(buf);
     return t;
 }
 
@@ -352,8 +352,8 @@ sds sdscatprintf(sds s, const char *fmt, ...) {
  *
  * Output will be just "Hello World".
  */
-sds sdstrim(sds s, const char *cset) {
-    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
+void sdstrim(sds s, const char *cset) {
+    struct sdshdr *sh = (void*) (s-sizeof *sh);;
     char *start, *end, *sp, *ep;
     size_t len;
 
@@ -366,7 +366,6 @@ sds sdstrim(sds s, const char *cset) {
     sh->buf[len] = '\0';
     sh->free = sh->free+(sh->len-len);
     sh->len = len;
-    return s;
 }
 
 /* Turn the string into a smaller (or equal) string containing only the
@@ -383,10 +382,10 @@ sds sdstrim(sds s, const char *cset) {
  * Example:
  *
  * s = sdsnew("Hello World");
- * sdstrim(s,1,-1); => "ello Worl"
+ * sdsrange(s,1,-1); => "ello World"
  */
 void sdsrange(sds s, int start, int end) {
-    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
+    struct sdshdr *sh = (void*) (s-sizeof *sh);;
     size_t newlen, len = sdslen(s);
 
     if (len == 0) return;
@@ -474,7 +473,7 @@ sds *sdssplitlen(const char *s, int len, const char *sep, int seplen, int *count
 
     if (seplen < 1 || len < 0) return NULL;
 
-    tokens = zmalloc(sizeof(sds)*slots);
+    tokens = malloc(sizeof(sds)*slots);
     if (tokens == NULL) return NULL;
 
     if (len == 0) {
@@ -487,7 +486,7 @@ sds *sdssplitlen(const char *s, int len, const char *sep, int seplen, int *count
             sds *newtokens;
 
             slots *= 2;
-            newtokens = zrealloc(tokens,sizeof(sds)*slots);
+            newtokens = realloc(tokens,sizeof(sds)*slots);
             if (newtokens == NULL) goto cleanup;
             tokens = newtokens;
         }
@@ -511,7 +510,7 @@ sds *sdssplitlen(const char *s, int len, const char *sep, int seplen, int *count
     {
         int i;
         for (i = 0; i < elements; i++) sdsfree(tokens[i]);
-        zfree(tokens);
+        free(tokens);
         *count = 0;
         return NULL;
     }
@@ -522,7 +521,7 @@ void sdsfreesplitres(sds *tokens, int count) {
     if (!tokens) return;
     while(count--)
         sdsfree(tokens[count]);
-    zfree(tokens);
+    free(tokens);
 }
 
 /* Create an sds string from a long long value. It is much faster than:
@@ -582,7 +581,7 @@ int is_hex_digit(char c) {
            (c >= 'A' && c <= 'F');
 }
 
-/* Helper function for sdssplitargs() that converts an hex digit into an
+/* Helper function for sdssplitargs() that converts a hex digit into an
  * integer from 0 to 15 */
 int hex_digit_to_int(char c) {
     switch(c) {
@@ -715,21 +714,21 @@ sds *sdssplitargs(const char *line, int *argc) {
                 if (*p) p++;
             }
             /* add the token to the vector */
-            vector = zrealloc(vector,((*argc)+1)*sizeof(char*));
+            vector = realloc(vector,((*argc)+1)*sizeof(char*));
             vector[*argc] = current;
             (*argc)++;
             current = NULL;
         } else {
             /* Even on empty input string return something not NULL. */
-            if (vector == NULL) vector = zmalloc(sizeof(void*));
+            if (vector == NULL) vector = malloc(sizeof(void*));
             return vector;
         }
     }
 
 err:
     while((*argc)--)
         sdsfree(vector[*argc]);
-    zfree(vector);
+    free(vector);
     if (current) sdsfree(current);
     *argc = 0;
     return NULL;
@@ -760,13 +759,25 @@ sds sdsmapchars(sds s, const char *from, const char *to, size_t setlen) {
 
 /* Join an array of C strings using the specified separator (also a C string).
  * Returns the result as an sds string. */
-sds sdsjoin(char **argv, int argc, char *sep) {
+sds sdsjoin(char **argv, int argc, char *sep, size_t seplen) {
     sds join = sdsempty();
     int j;
 
     for (j = 0; j < argc; j++) {
         join = sdscat(join, argv[j]);
-        if (j != argc-1) join = sdscat(join,sep);
+        if (j != argc-1) join = sdscatlen(join,sep,seplen);
+    }
+    return join;
+}
+
+/* Like sdsjoin, but joins an array of SDS strings. */
+sds sdsjoinsds(sds *argv, int argc, const char *sep, size_t seplen) {
+    sds join = sdsempty();
+    int j;
+
+    for (j = 0; j < argc; j++) {
+        join = sdscatsds(join, argv[j]);
+        if (j != argc-1) join = sdscatlen(join,sep,seplen);
     }
     return join;
 }
@@ -807,36 +818,43 @@ int main(void) {
             sdslen(x) == 3 && memcmp(x,"123\0",4) ==0)
 
         sdsfree(x);
-        x = sdstrim(sdsnew("xxciaoyyy"),"xy");
+        x = sdsnew("xxciaoyyy");
+        sdstrim(x,"xy");
         test_cond("sdstrim() correctly trims characters",
             sdslen(x) == 4 && memcmp(x,"ciao\0",5) == 0)
 
-        y = sdsrange(sdsdup(x),1,1);
+        y = sdsdup(x);
+        sdsrange(y,1,1);
         test_cond("sdsrange(...,1,1)",
             sdslen(y) == 1 && memcmp(y,"i\0",2) == 0)
 
         sdsfree(y);
-        y = sdsrange(sdsdup(x),1,-1);
+        y = sdsdup(x);
+        sdsrange(y,1,-1);
         test_cond("sdsrange(...,1,-1)",
             sdslen(y) == 3 && memcmp(y,"iao\0",4) == 0)
 
         sdsfree(y);
-        y = sdsrange(sdsdup(x),-2,-1);
+        y = sdsdup(x);
+        sdsrange(y,-2,-1);
         test_cond("sdsrange(...,-2,-1)",
             sdslen(y) == 2 && memcmp(y,"ao\0",3) == 0)
 
         sdsfree(y);
-        y = sdsrange(sdsdup(x),2,1);
+        y = sdsdup(x);
+        sdsrange(y,2,1);
         test_cond("sdsrange(...,2,1)",
             sdslen(y) == 0 && memcmp(y,"\0",1) == 0)
 
         sdsfree(y);
-        y = sdsrange(sdsdup(x),1,100);
+        y = sdsdup(x);
+        sdsrange(y,1,100);
         test_cond("sdsrange(...,1,100)",
             sdslen(y) == 3 && memcmp(y,"iao\0",4) == 0)
 
         sdsfree(y);
-        y = sdsrange(sdsdup(x),100,100);
+        y = sdsdup(x);
+        sdsrange(y,100,100);
         test_cond("sdsrange(...,100,100)",
             sdslen(y) == 0 && memcmp(y,"\0",1) == 0)
 
@@ -858,6 +876,13 @@ int main(void) {
         y = sdsnew("bar");
         test_cond("sdscmp(bar,bar)", sdscmp(x,y) < 0)
 
+        sdsfree(y);
+        sdsfree(x);
+        x = sdsnewlen("\a\n\0foo\r",7);
+        y = sdscatrepr(sdsempty(),x,sdslen(x));
+        test_cond("sdscatrepr(...data...)",
+            memcmp(y,"\"\\a\\n\\x00foo\\r\"",15) == 0)
+
         {
             int oldfree;
 