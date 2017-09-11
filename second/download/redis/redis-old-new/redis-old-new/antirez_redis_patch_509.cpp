@@ -1,6 +1,8 @@
-/* SDSLib, A C dynamic strings library
+/* SDSLib 2.0 -- A C dynamic strings library
  *
- * Copyright (c) 2006-2012, Salvatore Sanfilippo <antirez at gmail dot com>
+ * Copyright (c) 2006-2015, Salvatore Sanfilippo <antirez at gmail dot com>
+ * Copyright (c) 2015, Oran Agra
+ * Copyright (c) 2015, Redis Labs, Inc
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -34,7 +36,35 @@
 #include <ctype.h>
 #include <assert.h>
 #include "sds.h"
-#include "zmalloc.h"
+#include "sdsalloc.h"
+
+static inline int sdsHdrSize(char type) {
+    switch(type&SDS_TYPE_MASK) {
+        case SDS_TYPE_5:
+            return sizeof(struct sdshdr5);
+        case SDS_TYPE_8:
+            return sizeof(struct sdshdr8);
+        case SDS_TYPE_16:
+            return sizeof(struct sdshdr16);
+        case SDS_TYPE_32:
+            return sizeof(struct sdshdr32);
+        case SDS_TYPE_64:
+            return sizeof(struct sdshdr64);
+    }
+    return 0;
+}
+
+static inline char sdsReqType(size_t string_size) {
+    if (string_size < 32)
+        return SDS_TYPE_5;
+    if (string_size < 0xff)
+        return SDS_TYPE_8;
+    if (string_size < 0xffff)
+        return SDS_TYPE_16;
+    if (string_size < 0xffffffff)
+        return SDS_TYPE_32;
+    return SDS_TYPE_64;
+}
 
 /* Create a new sds string with the content specified by the 'init' pointer
  * and 'initlen'.
@@ -43,26 +73,65 @@
  * The string is always null-termined (all the sds strings are, always) so
  * even if you create an sds string with:
  *
- * mystring = sdsnewlen("abc",3");
+ * mystring = sdsnewlen("abc",3);
  *
  * You can print the string with printf() as there is an implicit \0 at the
  * end of the string. However the string is binary safe and can contain
  * \0 characters in the middle, as the length is stored in the sds header. */
 sds sdsnewlen(const void *init, size_t initlen) {
-    struct sdshdr *sh;
-
-    if (init) {
-        sh = zmalloc(sizeof(struct sdshdr)+initlen+1);
-    } else {
-        sh = zcalloc(sizeof(struct sdshdr)+initlen+1);
-    }
+    void *sh;
+    sds s;
+    char type = sdsReqType(initlen);
+    /* Empty strings are usually created in order to append. Use type 8
+     * since type 5 is not good at this. */
+    if (type == SDS_TYPE_5 && initlen == 0) type = SDS_TYPE_8;
+    int hdrlen = sdsHdrSize(type);
+    unsigned char *fp; /* flags pointer. */
+
+    sh = s_malloc(hdrlen+initlen+1);
+    if (!init)
+        memset(sh, 0, hdrlen+initlen+1);
     if (sh == NULL) return NULL;
-    sh->len = initlen;
-    sh->free = 0;
+    s = (char*)sh+hdrlen;
+    fp = ((unsigned char*)s)-1;
+    switch(type) {
+        case SDS_TYPE_5: {
+            *fp = type | (initlen << SDS_TYPE_BITS);
+            break;
+        }
+        case SDS_TYPE_8: {
+            SDS_HDR_VAR(8,s);
+            sh->len = initlen;
+            sh->alloc = initlen;
+            *fp = type;
+            break;
+        }
+        case SDS_TYPE_16: {
+            SDS_HDR_VAR(16,s);
+            sh->len = initlen;
+            sh->alloc = initlen;
+            *fp = type;
+            break;
+        }
+        case SDS_TYPE_32: {
+            SDS_HDR_VAR(32,s);
+            sh->len = initlen;
+            sh->alloc = initlen;
+            *fp = type;
+            break;
+        }
+        case SDS_TYPE_64: {
+            SDS_HDR_VAR(64,s);
+            sh->len = initlen;
+            sh->alloc = initlen;
+            *fp = type;
+            break;
+        }
+    }
     if (initlen && init)
-        memcpy(sh->buf, init, initlen);
-    sh->buf[initlen] = '\0';
-    return (char*)sh->buf;
+        memcpy(s, init, initlen);
+    s[initlen] = '\0';
+    return s;
 }
 
 /* Create an empty (zero length) sds string. Even in this case the string
@@ -71,7 +140,7 @@ sds sdsempty(void) {
     return sdsnewlen("",0);
 }
 
-/* Create a new sds string starting from a null termined C string. */
+/* Create a new sds string starting from a null terminated C string. */
 sds sdsnew(const char *init) {
     size_t initlen = (init == NULL) ? 0 : strlen(init);
     return sdsnewlen(init, initlen);
@@ -85,7 +154,7 @@ sds sdsdup(const sds s) {
 /* Free an sds string. No operation is performed if 's' is NULL. */
 void sdsfree(sds s) {
     if (s == NULL) return;
-    zfree(s-sizeof(struct sdshdr));
+    s_free((char*)s-sdsHdrSize(s[-1]));
 }
 
 /* Set the sds string length to the length as obtained with strlen(), so
@@ -103,21 +172,17 @@ void sdsfree(sds s) {
  * the output will be "6" as the string was modified but the logical length
  * remains 6 bytes. */
 void sdsupdatelen(sds s) {
-    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
     int reallen = strlen(s);
-    sh->free += (sh->len-reallen);
-    sh->len = reallen;
+    sdssetlen(s, reallen);
 }
 
-/* Modify an sds string on-place to make it empty (zero length).
+/* Modify an sds string in-place to make it empty (zero length).
  * However all the existing buffer is not discarded but set as free space
  * so that next append operations will not require allocations up to the
  * number of bytes previously available. */
 void sdsclear(sds s) {
-    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
-    sh->free += sh->len;
-    sh->len = 0;
-    sh->buf[0] = '\0';
+    sdssetlen(s, 0);
+    s[0] = '\0';
 }
 
 /* Enlarge the free space at the end of the sds string so that the caller
@@ -127,23 +192,48 @@ void sdsclear(sds s) {
  * Note: this does not change the *length* of the sds string as returned
  * by sdslen(), but only the free buffer space we have. */
 sds sdsMakeRoomFor(sds s, size_t addlen) {
-    struct sdshdr *sh, *newsh;
-    size_t free = sdsavail(s);
+    void *sh, *newsh;
+    size_t avail = sdsavail(s);
     size_t len, newlen;
+    char type, oldtype = s[-1] & SDS_TYPE_MASK;
+    int hdrlen;
+
+    /* Return ASAP if there is enough space left. */
+    if (avail >= addlen) return s;
 
-    if (free >= addlen) return s;
     len = sdslen(s);
-    sh = (void*) (s-(sizeof(struct sdshdr)));
+    sh = (char*)s-sdsHdrSize(oldtype);
     newlen = (len+addlen);
     if (newlen < SDS_MAX_PREALLOC)
         newlen *= 2;
     else
         newlen += SDS_MAX_PREALLOC;
-    newsh = zrealloc(sh, sizeof(struct sdshdr)+newlen+1);
-    if (newsh == NULL) return NULL;
 
-    newsh->free = newlen - len;
-    return newsh->buf;
+    type = sdsReqType(newlen);
+
+    /* Don't use type 5: the user is appending to the string and type 5 is
+     * not able to remember empty space, so sdsMakeRoomFor() must be called
+     * at every appending operation. */
+    if (type == SDS_TYPE_5) type = SDS_TYPE_8;
+
+    hdrlen = sdsHdrSize(type);
+    if (oldtype==type) {
+        newsh = s_realloc(sh, hdrlen+newlen+1);
+        if (newsh == NULL) return NULL;
+        s = (char*)newsh+hdrlen;
+    } else {
+        /* Since the header size changes, need to move the string forward,
+         * and can't use realloc */
+        newsh = s_malloc(hdrlen+newlen+1);
+        if (newsh == NULL) return NULL;
+        memcpy((char*)newsh+hdrlen, s, len+1);
+        s_free(sh);
+        s = (char*)newsh+hdrlen;
+        s[-1] = type;
+        sdssetlen(s, len);
+    }
+    sdssetalloc(s, newlen);
+    return s;
 }
 
 /* Reallocate the sds string so that it has no free space at the end. The
@@ -153,12 +243,29 @@ sds sdsMakeRoomFor(sds s, size_t addlen) {
  * After the call, the passed sds string is no longer valid and all the
  * references must be substituted with the new pointer returned by the call. */
 sds sdsRemoveFreeSpace(sds s) {
-    struct sdshdr *sh;
-
-    sh = (void*) (s-(sizeof(struct sdshdr)));
-    sh = zrealloc(sh, sizeof(struct sdshdr)+sh->len+1);
-    sh->free = 0;
-    return sh->buf;
+    void *sh, *newsh;
+    char type, oldtype = s[-1] & SDS_TYPE_MASK;
+    int hdrlen;
+    size_t len = sdslen(s);
+    sh = (char*)s-sdsHdrSize(oldtype);
+
+    type = sdsReqType(len);
+    hdrlen = sdsHdrSize(type);
+    if (oldtype==type) {
+        newsh = s_realloc(sh, hdrlen+len+1);
+        if (newsh == NULL) return NULL;
+        s = (char*)newsh+hdrlen;
+    } else {
+        newsh = s_malloc(hdrlen+len+1);
+        if (newsh == NULL) return NULL;
+        memcpy((char*)newsh+hdrlen, s, len+1);
+        s_free(sh);
+        s = (char*)newsh+hdrlen;
+        s[-1] = type;
+        sdssetlen(s, len);
+    }
+    sdssetalloc(s, len);
+    return s;
 }
 
 /* Return the total size of the allocation of the specifed sds string,
@@ -169,9 +276,14 @@ sds sdsRemoveFreeSpace(sds s) {
  * 4) The implicit null term.
  */
 size_t sdsAllocSize(sds s) {
-    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
+    size_t alloc = sdsalloc(s);
+    return sdsHdrSize(s[-1])+alloc+1;
+}
 
-    return sizeof(*sh)+sh->len+sh->free+1;
+/* Return the pointer of the actual SDS allocation (normally SDS strings
+ * are referenced by the start of the string buffer). */
+void *sdsAllocPtr(sds s) {
+    return (void*) (s-sdsHdrSize(s[-1]));
 }
 
 /* Increment the sds length and decrements the left free space at the
@@ -198,15 +310,44 @@ size_t sdsAllocSize(sds s) {
  * sdsIncrLen(s, nread);
  */
 void sdsIncrLen(sds s, int incr) {
-    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
-
-    if (incr >= 0)
-        assert(sh->free >= (unsigned int)incr);
-    else
-        assert(sh->len >= (unsigned int)(-incr));
-    sh->len += incr;
-    sh->free -= incr;
-    s[sh->len] = '\0';
+    unsigned char flags = s[-1];
+    size_t len;
+    switch(flags&SDS_TYPE_MASK) {
+        case SDS_TYPE_5: {
+            unsigned char *fp = ((unsigned char*)s)-1;
+            unsigned char oldlen = SDS_TYPE_5_LEN(flags);
+            assert((incr > 0 && oldlen+incr < 32) || (incr < 0 && oldlen >= (unsigned int)(-incr)));
+            *fp = SDS_TYPE_5 | ((oldlen+incr) << SDS_TYPE_BITS);
+            len = oldlen+incr;
+            break;
+        }
+        case SDS_TYPE_8: {
+            SDS_HDR_VAR(8,s);
+            assert((incr >= 0 && sh->alloc-sh->len >= incr) || (incr < 0 && sh->len >= (unsigned int)(-incr)));
+            len = (sh->len += incr);
+            break;
+        }
+        case SDS_TYPE_16: {
+            SDS_HDR_VAR(16,s);
+            assert((incr >= 0 && sh->alloc-sh->len >= incr) || (incr < 0 && sh->len >= (unsigned int)(-incr)));
+            len = (sh->len += incr);
+            break;
+        }
+        case SDS_TYPE_32: {
+            SDS_HDR_VAR(32,s);
+            assert((incr >= 0 && sh->alloc-sh->len >= (unsigned int)incr) || (incr < 0 && sh->len >= (unsigned int)(-incr)));
+            len = (sh->len += incr);
+            break;
+        }
+        case SDS_TYPE_64: {
+            SDS_HDR_VAR(64,s);
+            assert((incr >= 0 && sh->alloc-sh->len >= (uint64_t)incr) || (incr < 0 && sh->len >= (uint64_t)(-incr)));
+            len = (sh->len += incr);
+            break;
+        }
+        default: len = 0; /* Just to avoid compilation warnings. */
+    }
+    s[len] = '\0';
 }
 
 /* Grow the sds to have the specified length. Bytes that were not part of
@@ -215,19 +356,15 @@ void sdsIncrLen(sds s, int incr) {
  * if the specified length is smaller than the current length, no operation
  * is performed. */
 sds sdsgrowzero(sds s, size_t len) {
-    struct sdshdr *sh = (void*)(s-(sizeof(struct sdshdr)));
-    size_t totlen, curlen = sh->len;
+    size_t curlen = sdslen(s);
 
     if (len <= curlen) return s;
     s = sdsMakeRoomFor(s,len-curlen);
     if (s == NULL) return NULL;
 
     /* Make sure added region doesn't contain garbage */
-    sh = (void*)(s-(sizeof(struct sdshdr)));
     memset(s+curlen,0,(len-curlen+1)); /* also set trailing \0 byte */
-    totlen = sh->len+sh->free;
-    sh->len = len;
-    sh->free = totlen-sh->len;
+    sdssetlen(s, len);
     return s;
 }
 
@@ -237,15 +374,12 @@ sds sdsgrowzero(sds s, size_t len) {
  * After the call, the passed sds string is no longer valid and all the
  * references must be substituted with the new pointer returned by the call. */
 sds sdscatlen(sds s, const void *t, size_t len) {
-    struct sdshdr *sh;
     size_t curlen = sdslen(s);
 
     s = sdsMakeRoomFor(s,len);
     if (s == NULL) return NULL;
-    sh = (void*) (s-(sizeof(struct sdshdr)));
     memcpy(s+curlen, t, len);
-    sh->len = curlen+len;
-    sh->free = sh->free-len;
+    sdssetlen(s, curlen+len);
     s[curlen+len] = '\0';
     return s;
 }
@@ -269,19 +403,13 @@ sds sdscatsds(sds s, const sds t) {
 /* Destructively modify the sds string 's' to hold the specified binary
  * safe string pointed by 't' of length 'len' bytes. */
 sds sdscpylen(sds s, const char *t, size_t len) {
-    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
-    size_t totlen = sh->free+sh->len;
-
-    if (totlen < len) {
-        s = sdsMakeRoomFor(s,len-sh->len);
+    if (sdsalloc(s) < len) {
+        s = sdsMakeRoomFor(s,len-sdslen(s));
         if (s == NULL) return NULL;
-        sh = (void*) (s-(sizeof(struct sdshdr)));
-        totlen = sh->free+sh->len;
     }
     memcpy(s, t, len);
     s[len] = '\0';
-    sh->len = len;
-    sh->free = totlen-len;
+    sdssetlen(s, len);
     return s;
 }
 
@@ -295,7 +423,7 @@ sds sdscpy(sds s, const char *t) {
  * conversion. 's' must point to a string with room for at least
  * SDS_LLSTR_SIZE bytes.
  *
- * The function returns the lenght of the null-terminated string
+ * The function returns the length of the null-terminated string
  * representation stored at 's'. */
 #define SDS_LLSTR_SIZE 21
 int sdsll2str(char *s, long long value) {
@@ -369,7 +497,7 @@ sds sdsfromlonglong(long long value) {
     return sdsnewlen(buf,len);
 }
 
-/* Like sdscatpritf() but gets va_list instead of being variadic. */
+/* Like sdscatprintf() but gets va_list instead of being variadic. */
 sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
     va_list cpy;
     char staticbuf[1024], *buf = staticbuf, *t;
@@ -378,7 +506,7 @@ sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
     /* We try to start using a static buffer for speed.
      * If not possible we revert to heap allocation. */
     if (buflen > sizeof(staticbuf)) {
-        buf = zmalloc(buflen);
+        buf = s_malloc(buflen);
         if (buf == NULL) return NULL;
     } else {
         buflen = sizeof(staticbuf);
@@ -390,11 +518,11 @@ sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
         buf[buflen-2] = '\0';
         va_copy(cpy,ap);
         vsnprintf(buf, buflen, fmt, cpy);
-        va_end(ap);
+        va_end(cpy);
         if (buf[buflen-2] != '\0') {
-            if (buf != staticbuf) zfree(buf);
+            if (buf != staticbuf) s_free(buf);
             buflen *= 2;
-            buf = zmalloc(buflen);
+            buf = s_malloc(buflen);
             if (buf == NULL) return NULL;
             continue;
         }
@@ -403,7 +531,7 @@ sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
 
     /* Finally concat the obtained string to the SDS string and return it. */
     t = sdscat(s, buf);
-    if (buf != staticbuf) zfree(buf);
+    if (buf != staticbuf) s_free(buf);
     return t;
 }
 
@@ -415,7 +543,7 @@ sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
  *
  * Example:
  *
- * s = sdsempty("Sum is: ");
+ * s = sdsnew("Sum is: ");
  * s = sdscatprintf(s,"%d+%d = %d",a,b,a+b).
  *
  * Often you need to create a string from scratch with the printf-alike
@@ -449,7 +577,6 @@ sds sdscatprintf(sds s, const char *fmt, ...) {
  * %% - Verbatim "%" character.
  */
 sds sdscatfmt(sds s, char const *fmt, ...) {
-    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
     size_t initlen = sdslen(s);
     const char *f = fmt;
     int i;
@@ -460,14 +587,13 @@ sds sdscatfmt(sds s, char const *fmt, ...) {
     i = initlen; /* Position of the next byte to write to dest str. */
     while(*f) {
         char next, *str;
-        unsigned int l;
+        size_t l;
         long long num;
         unsigned long long unum;
 
         /* Make sure there is always space for at least 1 char. */
-        if (sh->free == 0) {
+        if (sdsavail(s)==0) {
             s = sdsMakeRoomFor(s,1);
-            sh = (void*) (s-(sizeof(struct sdshdr)));
         }
 
         switch(*f) {
@@ -479,13 +605,11 @@ sds sdscatfmt(sds s, char const *fmt, ...) {
             case 'S':
                 str = va_arg(ap,char*);
                 l = (next == 's') ? strlen(str) : sdslen(str);
-                if (sh->free < l) {
+                if (sdsavail(s) < l) {
                     s = sdsMakeRoomFor(s,l);
-                    sh = (void*) (s-(sizeof(struct sdshdr)));
                 }
                 memcpy(s+i,str,l);
-                sh->len += l;
-                sh->free -= l;
+                sdsinclen(s,l);
                 i += l;
                 break;
             case 'i':
@@ -497,13 +621,11 @@ sds sdscatfmt(sds s, char const *fmt, ...) {
                 {
                     char buf[SDS_LLSTR_SIZE];
                     l = sdsll2str(buf,num);
-                    if (sh->free < l) {
+                    if (sdsavail(s) < l) {
                         s = sdsMakeRoomFor(s,l);
-                        sh = (void*) (s-(sizeof(struct sdshdr)));
                     }
                     memcpy(s+i,buf,l);
-                    sh->len += l;
-                    sh->free -= l;
+                    sdsinclen(s,l);
                     i += l;
                 }
                 break;
@@ -516,27 +638,23 @@ sds sdscatfmt(sds s, char const *fmt, ...) {
                 {
                     char buf[SDS_LLSTR_SIZE];
                     l = sdsull2str(buf,unum);
-                    if (sh->free < l) {
+                    if (sdsavail(s) < l) {
                         s = sdsMakeRoomFor(s,l);
-                        sh = (void*) (s-(sizeof(struct sdshdr)));
                     }
                     memcpy(s+i,buf,l);
-                    sh->len += l;
-                    sh->free -= l;
+                    sdsinclen(s,l);
                     i += l;
                 }
                 break;
             default: /* Handle %% and generally %<unknown>. */
                 s[i++] = next;
-                sh->len += 1;
-                sh->free -= 1;
+                sdsinclen(s,1);
                 break;
             }
             break;
         default:
             s[i++] = *f;
-            sh->len += 1;
-            sh->free -= 1;
+            sdsinclen(s,1);
             break;
         }
         f++;
@@ -557,25 +675,23 @@ sds sdscatfmt(sds s, char const *fmt, ...) {
  * Example:
  *
  * s = sdsnew("AA...AA.a.aa.aHelloWorld     :::");
- * s = sdstrim(s,"A. :");
+ * s = sdstrim(s,"Aa. :");
  * printf("%s\n", s);
  *
  * Output will be just "Hello World".
  */
 sds sdstrim(sds s, const char *cset) {
-    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
     char *start, *end, *sp, *ep;
     size_t len;
 
     sp = start = s;
     ep = end = s+sdslen(s)-1;
     while(sp <= end && strchr(cset, *sp)) sp++;
-    while(ep > start && strchr(cset, *ep)) ep--;
+    while(ep > sp && strchr(cset, *ep)) ep--;
     len = (sp > ep) ? 0 : ((ep-sp)+1);
-    if (sh->buf != sp) memmove(sh->buf, sp, len);
-    sh->buf[len] = '\0';
-    sh->free = sh->free+(sh->len-len);
-    sh->len = len;
+    if (s != sp) memmove(s, sp, len);
+    s[len] = '\0';
+    sdssetlen(s,len);
     return s;
 }
 
@@ -596,7 +712,6 @@ sds sdstrim(sds s, const char *cset) {
  * sdsrange(s,1,-1); => "ello World"
  */
 void sdsrange(sds s, int start, int end) {
-    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
     size_t newlen, len = sdslen(s);
 
     if (len == 0) return;
@@ -619,10 +734,9 @@ void sdsrange(sds s, int start, int end) {
     } else {
         start = 0;
     }
-    if (start && newlen) memmove(sh->buf, sh->buf+start, newlen);
-    sh->buf[newlen] = 0;
-    sh->free = sh->free+(sh->len-newlen);
-    sh->len = newlen;
+    if (start && newlen) memmove(s, s+start, newlen);
+    s[newlen] = 0;
+    sdssetlen(s,newlen);
 }
 
 /* Apply tolower() to every character of the sds string 's'. */
@@ -643,8 +757,8 @@ void sdstoupper(sds s) {
  *
  * Return value:
  *
- *     1 if s1 > s2.
- *    -1 if s1 < s2.
+ *     positive if s1 > s2.
+ *     negative if s1 < s2.
  *     0 if s1 and s2 are exactly the same binary string.
  *
  * If two strings share exactly the same prefix, but one of the two has
@@ -684,7 +798,7 @@ sds *sdssplitlen(const char *s, int len, const char *sep, int seplen, int *count
 
     if (seplen < 1 || len < 0) return NULL;
 
-    tokens = zmalloc(sizeof(sds)*slots);
+    tokens = s_malloc(sizeof(sds)*slots);
     if (tokens == NULL) return NULL;
 
     if (len == 0) {
@@ -697,7 +811,7 @@ sds *sdssplitlen(const char *s, int len, const char *sep, int seplen, int *count
             sds *newtokens;
 
             slots *= 2;
-            newtokens = zrealloc(tokens,sizeof(sds)*slots);
+            newtokens = s_realloc(tokens,sizeof(sds)*slots);
             if (newtokens == NULL) goto cleanup;
             tokens = newtokens;
         }
@@ -721,7 +835,7 @@ sds *sdssplitlen(const char *s, int len, const char *sep, int seplen, int *count
     {
         int i;
         for (i = 0; i < elements; i++) sdsfree(tokens[i]);
-        zfree(tokens);
+        s_free(tokens);
         *count = 0;
         return NULL;
     }
@@ -732,7 +846,7 @@ void sdsfreesplitres(sds *tokens, int count) {
     if (!tokens) return;
     while(count--)
         sdsfree(tokens[count]);
-    zfree(tokens);
+    s_free(tokens);
 }
 
 /* Append to the sds string "s" an escaped string representation where
@@ -906,21 +1020,21 @@ sds *sdssplitargs(const char *line, int *argc) {
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
@@ -962,14 +1076,26 @@ sds sdsjoin(char **argv, int argc, char *sep) {
     return join;
 }
 
-#ifdef SDS_TEST_MAIN
+/* Like sdsjoin, but joins an array of SDS strings. */
+sds sdsjoinsds(sds *argv, int argc, const char *sep, size_t seplen) {
+    sds join = sdsempty();
+    int j;
+
+    for (j = 0; j < argc; j++) {
+        join = sdscatsds(join, argv[j]);
+        if (j != argc-1) join = sdscatlen(join,sep,seplen);
+    }
+    return join;
+}
+
+#if defined(SDS_TEST_MAIN)
 #include <stdio.h>
 #include "testhelp.h"
 #include "limits.h"
 
-int main(void) {
+#define UNUSED(x) (void)(x)
+int sdsTest(void) {
     {
-        struct sdshdr *sh;
         sds x = sdsnew("foo"), y;
 
         test_cond("Create a string and obtain the length",
@@ -1005,6 +1131,7 @@ int main(void) {
             sdslen(x) == 60 &&
             memcmp(x,"--Hello Hi! World -9223372036854775808,"
                      "9223372036854775807--",60) == 0)
+        printf("[%s]\n",x);
 
         sdsfree(x);
         x = sdsnew("--");
@@ -1014,6 +1141,18 @@ int main(void) {
             memcmp(x,"--4294967295,18446744073709551615--",35) == 0)
 
         sdsfree(x);
+        x = sdsnew(" x ");
+        sdstrim(x," x");
+        test_cond("sdstrim() works when all chars match",
+            sdslen(x) == 0)
+
+        sdsfree(x);
+        x = sdsnew(" x ");
+        sdstrim(x," ");
+        test_cond("sdstrim() works when a single char remains",
+            sdslen(x) == 1 && x[0] == 'x')
+
+        sdsfree(x);
         x = sdsnew("xxciaoyyy");
         sdstrim(x,"xy");
         test_cond("sdstrim() correctly trims characters",
@@ -1080,24 +1219,47 @@ int main(void) {
             memcmp(y,"\"\\a\\n\\x00foo\\r\"",15) == 0)
 
         {
-            int oldfree;
+            unsigned int oldfree;
+            char *p;
+            int step = 10, j, i;
 
             sdsfree(x);
+            sdsfree(y);
             x = sdsnew("0");
-            sh = (void*) (x-(sizeof(struct sdshdr)));
-            test_cond("sdsnew() free/len buffers", sh->len == 1 && sh->free == 0);
-            x = sdsMakeRoomFor(x,1);
-            sh = (void*) (x-(sizeof(struct sdshdr)));
-            test_cond("sdsMakeRoomFor()", sh->len == 1 && sh->free > 0);
-            oldfree = sh->free;
-            x[1] = '1';
-            sdsIncrLen(x,1);
-            test_cond("sdsIncrLen() -- content", x[0] == '0' && x[1] == '1');
-            test_cond("sdsIncrLen() -- len", sh->len == 2);
-            test_cond("sdsIncrLen() -- free", sh->free == oldfree-1);
+            test_cond("sdsnew() free/len buffers", sdslen(x) == 1 && sdsavail(x) == 0);
+
+            /* Run the test a few times in order to hit the first two
+             * SDS header types. */
+            for (i = 0; i < 10; i++) {
+                int oldlen = sdslen(x);
+                x = sdsMakeRoomFor(x,step);
+                int type = x[-1]&SDS_TYPE_MASK;
+
+                test_cond("sdsMakeRoomFor() len", sdslen(x) == oldlen);
+                if (type != SDS_TYPE_5) {
+                    test_cond("sdsMakeRoomFor() free", sdsavail(x) >= step);
+                    oldfree = sdsavail(x);
+                }
+                p = x+oldlen;
+                for (j = 0; j < step; j++) {
+                    p[j] = 'A'+j;
+                }
+                sdsIncrLen(x,step);
+            }
+            test_cond("sdsMakeRoomFor() content",
+                memcmp("0ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJ",x,101) == 0);
+            test_cond("sdsMakeRoomFor() final length",sdslen(x)==101);
+
+            sdsfree(x);
         }
     }
     test_report()
     return 0;
 }
 #endif
+
+#ifdef SDS_TEST_MAIN
+int main(void) {
+    return sdsTest();
+}
+#endif