@@ -1,6 +1,6 @@
-/* SDS (Simple Dynamic Strings), A C dynamic strings library.
+/* SDSLib, A C dynamic strings library
  *
- * Copyright (c) 2006-2014, Salvatore Sanfilippo <antirez at gmail dot com>
+ * Copyright (c) 2006-2012, Salvatore Sanfilippo <antirez at gmail dot com>
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -33,8 +33,8 @@
 #include <string.h>
 #include <ctype.h>
 #include <assert.h>
-
 #include "sds.h"
+#include "zmalloc.h"
 
 /* Create a new sds string with the content specified by the 'init' pointer
  * and 'initlen'.
@@ -52,9 +52,9 @@ sds sdsnewlen(const void *init, size_t initlen) {
     struct sdshdr *sh;
 
     if (init) {
-        sh = malloc(sizeof *sh+initlen+1);
+        sh = zmalloc(sizeof(struct sdshdr)+initlen+1);
     } else {
-        sh = calloc(sizeof *sh+initlen+1,1);
+        sh = zcalloc(sizeof(struct sdshdr)+initlen+1);
     }
     if (sh == NULL) return NULL;
     sh->len = initlen;
@@ -85,7 +85,7 @@ sds sdsdup(const sds s) {
 /* Free an sds string. No operation is performed if 's' is NULL. */
 void sdsfree(sds s) {
     if (s == NULL) return;
-    free(s-sizeof(struct sdshdr));
+    zfree(s-sizeof(struct sdshdr));
 }
 
 /* Set the sds string length to the length as obtained with strlen(), so
@@ -103,7 +103,7 @@ void sdsfree(sds s) {
  * the output will be "6" as the string was modified but the logical length
  * remains 6 bytes. */
 void sdsupdatelen(sds s) {
-    struct sdshdr *sh = (void*) (s-sizeof *sh);;
+    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
     int reallen = strlen(s);
     sh->free += (sh->len-reallen);
     sh->len = reallen;
@@ -114,7 +114,7 @@ void sdsupdatelen(sds s) {
  * so that next append operations will not require allocations up to the
  * number of bytes previously available. */
 void sdsclear(sds s) {
-    struct sdshdr *sh = (void*) (s-sizeof *sh);;
+    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
     sh->free += sh->len;
     sh->len = 0;
     sh->buf[0] = '\0';
@@ -133,13 +133,13 @@ sds sdsMakeRoomFor(sds s, size_t addlen) {
 
     if (free >= addlen) return s;
     len = sdslen(s);
-    sh = (void*) (s-sizeof *sh);;
+    sh = (void*) (s-(sizeof(struct sdshdr)));
     newlen = (len+addlen);
     if (newlen < SDS_MAX_PREALLOC)
         newlen *= 2;
     else
         newlen += SDS_MAX_PREALLOC;
-    newsh = realloc(sh, sizeof *newsh+newlen+1);
+    newsh = zrealloc(sh, sizeof(struct sdshdr)+newlen+1);
     if (newsh == NULL) return NULL;
 
     newsh->free = newlen - len;
@@ -155,8 +155,8 @@ sds sdsMakeRoomFor(sds s, size_t addlen) {
 sds sdsRemoveFreeSpace(sds s) {
     struct sdshdr *sh;
 
-    sh = (void*) (s-sizeof *sh);;
-    sh = realloc(sh, sizeof *sh+sh->len+1);
+    sh = (void*) (s-(sizeof(struct sdshdr)));
+    sh = zrealloc(sh, sizeof(struct sdshdr)+sh->len+1);
     sh->free = 0;
     return sh->buf;
 }
@@ -169,7 +169,7 @@ sds sdsRemoveFreeSpace(sds s) {
  * 4) The implicit null term.
  */
 size_t sdsAllocSize(sds s) {
-    struct sdshdr *sh = (void*) (s-sizeof *sh);;
+    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
 
     return sizeof(*sh)+sh->len+sh->free+1;
 }
@@ -198,7 +198,7 @@ size_t sdsAllocSize(sds s) {
  * sdsIncrLen(s, nread);
  */
 void sdsIncrLen(sds s, int incr) {
-    struct sdshdr *sh = (void*) (s-sizeof *sh);;
+    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
 
     assert(sh->free >= incr);
     sh->len += incr;
@@ -213,15 +213,15 @@ void sdsIncrLen(sds s, int incr) {
  * if the specified length is smaller than the current length, no operation
  * is performed. */
 sds sdsgrowzero(sds s, size_t len) {
-    struct sdshdr *sh = (void*) (s-sizeof *sh);
+    struct sdshdr *sh = (void*)(s-(sizeof(struct sdshdr)));
     size_t totlen, curlen = sh->len;
 
     if (len <= curlen) return s;
     s = sdsMakeRoomFor(s,len-curlen);
     if (s == NULL) return NULL;
 
     /* Make sure added region doesn't contain garbage */
-    sh = (void*)(s-sizeof *sh);
+    sh = (void*)(s-(sizeof(struct sdshdr)));
     memset(s+curlen,0,(len-curlen+1)); /* also set trailing \0 byte */
     totlen = sh->len+sh->free;
     sh->len = len;
@@ -240,7 +240,7 @@ sds sdscatlen(sds s, const void *t, size_t len) {
 
     s = sdsMakeRoomFor(s,len);
     if (s == NULL) return NULL;
-    sh = (void*) (s-sizeof *sh);;
+    sh = (void*) (s-(sizeof(struct sdshdr)));
     memcpy(s+curlen, t, len);
     sh->len = curlen+len;
     sh->free = sh->free-len;
@@ -267,13 +267,13 @@ sds sdscatsds(sds s, const sds t) {
 /* Destructively modify the sds string 's' to hold the specified binary
  * safe string pointed by 't' of length 'len' bytes. */
 sds sdscpylen(sds s, const char *t, size_t len) {
-    struct sdshdr *sh = (void*) (s-sizeof *sh);;
+    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
     size_t totlen = sh->free+sh->len;
 
     if (totlen < len) {
         s = sdsMakeRoomFor(s,len-sh->len);
         if (s == NULL) return NULL;
-        sh = (void*) (s-sizeof *sh);;
+        sh = (void*) (s-(sizeof(struct sdshdr)));
         totlen = sh->free+sh->len;
     }
     memcpy(s, t, len);
@@ -289,27 +289,118 @@ sds sdscpy(sds s, const char *t) {
     return sdscpylen(s, t, strlen(t));
 }
 
+/* Helper for sdscatlonglong() doing the actual number -> string
+ * conversion. 's' must point to a string with room for at least
+ * SDS_LLSTR_SIZE bytes.
+ *
+ * The function returns the lenght of the null-terminated string
+ * representation stored at 's'. */
+#define SDS_LLSTR_SIZE 21
+int sdsll2str(char *s, long long value) {
+    char *p, aux;
+    unsigned long long v;
+    size_t l;
+
+    /* Generate the string representation, this method produces
+     * an reversed string. */
+    v = (value < 0) ? -value : value;
+    p = s;
+    do {
+        *p++ = '0'+(v%10);
+        v /= 10;
+    } while(v);
+    if (value < 0) *p++ = '-';
+
+    /* Compute length and add null term. */
+    l = p-s;
+    *p = '\0';
+
+    /* Reverse the string. */
+    p--;
+    while(s < p) {
+        aux = *s;
+        *s = *p;
+        *p = aux;
+        s++;
+        p--;
+    }
+    return l;
+}
+
+/* Identical sdsll2str(), but for unsigned long long type. */
+int sdsull2str(char *s, unsigned long long v) {
+    char *p, aux;
+    size_t l;
+
+    /* Generate the string representation, this method produces
+     * an reversed string. */
+    p = s;
+    do {
+        *p++ = '0'+(v%10);
+        v /= 10;
+    } while(v);
+
+    /* Compute length and add null term. */
+    l = p-s;
+    *p = '\0';
+
+    /* Reverse the string. */
+    p--;
+    while(s < p) {
+        aux = *s;
+        *s = *p;
+        *p = aux;
+        s++;
+        p--;
+    }
+    return l;
+}
+
+/* Create an sds string from a long long value. It is much faster than:
+ *
+ * sdscatprintf(sdsempty(),"%lld\n", value);
+ */
+sds sdsfromlonglong(long long value) {
+    char buf[SDS_LLSTR_SIZE];
+    int len = sdsll2str(buf,value);
+
+    return sdsnewlen(buf,len);
+}
+
 /* Like sdscatpritf() but gets va_list instead of being variadic. */
 sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
     va_list cpy;
-    char *buf, *t;
-    size_t buflen = 16;
+    char staticbuf[1024], *buf = staticbuf, *t;
+    size_t buflen = strlen(fmt)*2;
 
-    while(1) {
-        buf = malloc(buflen);
+    /* We try to start using a static buffer for speed.
+     * If not possible we revert to heap allocation. */
+    if (buflen > sizeof(staticbuf)) {
+        buf = zmalloc(buflen);
         if (buf == NULL) return NULL;
+    } else {
+        buflen = sizeof(staticbuf);
+    }
+
+    /* Try with buffers two times bigger every time we fail to
+     * fit the string in the current buffer size. */
+    while(1) {
         buf[buflen-2] = '\0';
         va_copy(cpy,ap);
         vsnprintf(buf, buflen, fmt, cpy);
         if (buf[buflen-2] != '\0') {
-            free(buf);
+            if (buf != staticbuf) zfree(buf);
             buflen *= 2;
+            buf = zmalloc(buflen);
+            if (buf == NULL) return NULL;
             continue;
         }
         break;
     }
+
+    /* Finally concat the obtained string to the SDS string and return it. */
     t = sdscat(s, buf);
-    free(buf);
+    if (buf != staticbuf) zfree(buf);
     return t;
 }
 
@@ -338,6 +429,122 @@ sds sdscatprintf(sds s, const char *fmt, ...) {
     return t;
 }
 
+/* This function is similar to sdscatprintf, but much faster as it does
+ * not rely on sprintf() family functions implemented by the libc that
+ * are often very slow. Moreover directly handling the sds string as
+ * new data is concatenated provides a performance improvement.
+ *
+ * However this function only handles an incompatible subset of printf-alike
+ * format specifiers:
+ *
+ * %s - C String
+ * %S - SDS string
+ * %i - signed int
+ * %I - 64 bit signed integer (long long, int64_t)
+ * %u - unsigned int
+ * %U - 64 bit unsigned integer (unsigned long long, uint64_t)
+ * %% - Verbatim "%" character.
+ */
+sds sdscatfmt(sds s, char const *fmt, ...) {
+    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
+    size_t initlen = sdslen(s);
+    const char *f = fmt;
+    int i;
+    va_list ap;
+
+    va_start(ap,fmt);
+    f = fmt;    /* Next format specifier byte to process. */
+    i = initlen; /* Position of the next byte to write to dest str. */
+    while(*f) {
+        char next, *str;
+        size_t l;
+        long long num;
+        unsigned long long unum;
+
+        /* Make sure there is always space for at least 1 char. */
+        if (sh->free == 0) {
+            s = sdsMakeRoomFor(s,1);
+            sh = (void*) (s-(sizeof(struct sdshdr)));
+        }
+
+        switch(*f) {
+        case '%':
+            next = *(f+1);
+            f++;
+            switch(next) {
+            case 's':
+            case 'S':
+                str = va_arg(ap,char*);
+                l = (next == 's') ? strlen(str) : sdslen(str);
+                if (sh->free < l) {
+                    s = sdsMakeRoomFor(s,l);
+                    sh = (void*) (s-(sizeof(struct sdshdr)));
+                }
+                memcpy(s+i,str,l);
+                sh->len += l;
+                sh->free -= l;
+                i += l;
+                break;
+            case 'i':
+            case 'I':
+                if (next == 'i')
+                    num = va_arg(ap,int);
+                else
+                    num = va_arg(ap,long long);
+                {
+                    char buf[SDS_LLSTR_SIZE];
+                    l = sdsll2str(buf,num);
+                    if (sh->free < l) {
+                        s = sdsMakeRoomFor(s,l);
+                        sh = (void*) (s-(sizeof(struct sdshdr)));
+                    }
+                    memcpy(s+i,buf,l);
+                    sh->len += l;
+                    sh->free -= l;
+                    i += l;
+                }
+                break;
+            case 'u':
+            case 'U':
+                if (next == 'u')
+                    unum = va_arg(ap,unsigned int);
+                else
+                    unum = va_arg(ap,unsigned long long);
+                {
+                    char buf[SDS_LLSTR_SIZE];
+                    l = sdsull2str(buf,unum);
+                    if (sh->free < l) {
+                        s = sdsMakeRoomFor(s,l);
+                        sh = (void*) (s-(sizeof(struct sdshdr)));
+                    }
+                    memcpy(s+i,buf,l);
+                    sh->len += l;
+                    sh->free -= l;
+                    i += l;
+                }
+                break;
+            default: /* Handle %% and generally %<unknown>. */
+                s[i++] = next;
+                sh->len += 1;
+                sh->free -= 1;
+                break;
+            }
+            break;
+        default:
+            s[i++] = *f;
+            sh->len += 1;
+            sh->free -= 1;
+            break;
+        }
+        f++;
+    }
+    va_end(ap);
+
+    /* Add null-term */
+    s[i] = '\0';
+    return s;
+}
+
 /* Remove the part of the string from left and from right composed just of
  * contiguous characters found in 'cset', that is a null terminted C string.
  *
@@ -352,8 +559,8 @@ sds sdscatprintf(sds s, const char *fmt, ...) {
  *
  * Output will be just "Hello World".
  */
-void sdstrim(sds s, const char *cset) {
-    struct sdshdr *sh = (void*) (s-sizeof *sh);;
+sds sdstrim(sds s, const char *cset) {
+    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
     char *start, *end, *sp, *ep;
     size_t len;
 
@@ -366,6 +573,7 @@ void sdstrim(sds s, const char *cset) {
     sh->buf[len] = '\0';
     sh->free = sh->free+(sh->len-len);
     sh->len = len;
+    return s;
 }
 
 /* Turn the string into a smaller (or equal) string containing only the
@@ -385,7 +593,7 @@ void sdstrim(sds s, const char *cset) {
  * sdsrange(s,1,-1); => "ello World"
  */
 void sdsrange(sds s, int start, int end) {
-    struct sdshdr *sh = (void*) (s-sizeof *sh);;
+    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
     size_t newlen, len = sdslen(s);
 
     if (len == 0) return;
@@ -473,7 +681,7 @@ sds *sdssplitlen(const char *s, int len, const char *sep, int seplen, int *count
 
     if (seplen < 1 || len < 0) return NULL;
 
-    tokens = malloc(sizeof(sds)*slots);
+    tokens = zmalloc(sizeof(sds)*slots);
     if (tokens == NULL) return NULL;
 
     if (len == 0) {
@@ -486,7 +694,7 @@ sds *sdssplitlen(const char *s, int len, const char *sep, int seplen, int *count
             sds *newtokens;
 
             slots *= 2;
-            newtokens = realloc(tokens,sizeof(sds)*slots);
+            newtokens = zrealloc(tokens,sizeof(sds)*slots);
             if (newtokens == NULL) goto cleanup;
             tokens = newtokens;
         }
@@ -510,7 +718,7 @@ sds *sdssplitlen(const char *s, int len, const char *sep, int seplen, int *count
     {
         int i;
         for (i = 0; i < elements; i++) sdsfree(tokens[i]);
-        free(tokens);
+        zfree(tokens);
         *count = 0;
         return NULL;
     }
@@ -521,26 +729,7 @@ void sdsfreesplitres(sds *tokens, int count) {
     if (!tokens) return;
     while(count--)
         sdsfree(tokens[count]);
-    free(tokens);
-}
-
-/* Create an sds string from a long long value. It is much faster than:
- *
- * sdscatprintf(sdsempty(),"%lld\n", value);
- */
-sds sdsfromlonglong(long long value) {
-    char buf[32], *p;
-    unsigned long long v;
-
-    v = (value < 0) ? -value : value;
-    p = buf+31; /* point to the last character */
-    do {
-        *p-- = '0'+(v%10);
-        v /= 10;
-    } while(v);
-    if (value < 0) *p-- = '-';
-    p++;
-    return sdsnewlen(p,32-(p-buf));
+    zfree(tokens);
 }
 
 /* Append to the sds string "s" an escaped string representation where
@@ -714,21 +903,21 @@ sds *sdssplitargs(const char *line, int *argc) {
                 if (*p) p++;
             }
             /* add the token to the vector */
-            vector = realloc(vector,((*argc)+1)*sizeof(char*));
+            vector = zrealloc(vector,((*argc)+1)*sizeof(char*));
             vector[*argc] = current;
             (*argc)++;
             current = NULL;
         } else {
             /* Even on empty input string return something not NULL. */
-            if (vector == NULL) vector = malloc(sizeof(void*));
+            if (vector == NULL) vector = zmalloc(sizeof(void*));
             return vector;
         }
     }
 
 err:
     while((*argc)--)
         sdsfree(vector[*argc]);
-    free(vector);
+    zfree(vector);
     if (current) sdsfree(current);
     *argc = 0;
     return NULL;
@@ -759,32 +948,21 @@ sds sdsmapchars(sds s, const char *from, const char *to, size_t setlen) {
 
 /* Join an array of C strings using the specified separator (also a C string).
  * Returns the result as an sds string. */
-sds sdsjoin(char **argv, int argc, char *sep, size_t seplen) {
+sds sdsjoin(char **argv, int argc, char *sep) {
     sds join = sdsempty();
     int j;
 
     for (j = 0; j < argc; j++) {
         join = sdscat(join, argv[j]);
-        if (j != argc-1) join = sdscatlen(join,sep,seplen);
-    }
-    return join;
-}
-
-/* Like sdsjoin, but joins an array of SDS strings. */
-sds sdsjoinsds(sds *argv, int argc, const char *sep, size_t seplen) {
-    sds join = sdsempty();
-    int j;
-
-    for (j = 0; j < argc; j++) {
-        join = sdscatsds(join, argv[j]);
-        if (j != argc-1) join = sdscatlen(join,sep,seplen);
+        if (j != argc-1) join = sdscat(join,sep);
     }
     return join;
 }
 
 #ifdef SDS_TEST_MAIN
 #include <stdio.h>
 #include "testhelp.h"
+#include "limits.h"
 
 int main(void) {
     {
@@ -815,7 +993,22 @@ int main(void) {
         sdsfree(x);
         x = sdscatprintf(sdsempty(),"%d",123);
         test_cond("sdscatprintf() seems working in the base case",
-            sdslen(x) == 3 && memcmp(x,"123\0",4) ==0)
+            sdslen(x) == 3 && memcmp(x,"123\0",4) == 0)
+
+        sdsfree(x);
+        x = sdsnew("--");
+        x = sdscatfmt(x, "Hello %s World %I,%I--", "Hi!", LLONG_MIN,LLONG_MAX);
+        test_cond("sdscatfmt() seems working in the base case",
+            sdslen(x) == 60 &&
+            memcmp(x,"--Hello Hi! World -9223372036854775808,"
+                     "9223372036854775807--",60) == 0)
+
+        sdsfree(x);
+        x = sdsnew("--");
+        x = sdscatfmt(x, "%u,%U--", UINT_MAX, ULLONG_MAX);
+        test_cond("sdscatfmt() seems working with unsigned numbers",
+            sdslen(x) == 35 &&
+            memcmp(x,"--4294967295,18446744073709551615--",35) == 0)
 
         sdsfree(x);
         x = sdsnew("xxciaoyyy");