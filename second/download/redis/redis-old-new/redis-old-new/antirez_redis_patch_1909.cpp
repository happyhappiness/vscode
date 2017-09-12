@@ -33,7 +33,6 @@
 #include "sds.h"
 #include <stdio.h>
 #include <stdlib.h>
-#include <stdarg.h>
 #include <string.h>
 #include <ctype.h>
 #include "zmalloc.h"
@@ -156,8 +155,8 @@ sds sdscpy(sds s, char *t) {
     return sdscpylen(s, t, strlen(t));
 }
 
-sds sdscatprintf(sds s, const char *fmt, ...) {
-    va_list ap;
+sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
+    va_list cpy;
     char *buf, *t;
     size_t buflen = 16;
 
@@ -169,9 +168,8 @@ sds sdscatprintf(sds s, const char *fmt, ...) {
         if (buf == NULL) return NULL;
 #endif
         buf[buflen-2] = '\0';
-        va_start(ap, fmt);
-        vsnprintf(buf, buflen, fmt, ap);
-        va_end(ap);
+        va_copy(cpy,ap);
+        vsnprintf(buf, buflen, fmt, cpy);
         if (buf[buflen-2] != '\0') {
             zfree(buf);
             buflen *= 2;
@@ -184,6 +182,15 @@ sds sdscatprintf(sds s, const char *fmt, ...) {
     return t;
 }
 
+sds sdscatprintf(sds s, const char *fmt, ...) {
+    va_list ap;
+    char *t;
+    va_start(ap, fmt);
+    t = sdscatvprintf(s,fmt,ap);
+    va_end(ap);
+    return t;
+}
+
 sds sdstrim(sds s, const char *cset) {
     struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
     char *start, *end, *sp, *ep;
@@ -216,13 +223,16 @@ sds sdsrange(sds s, int start, int end) {
     }
     newlen = (start > end) ? 0 : (end-start)+1;
     if (newlen != 0) {
-        if (start >= (signed)len) start = len-1;
-        if (end >= (signed)len) end = len-1;
-        newlen = (start > end) ? 0 : (end-start)+1;
+        if (start >= (signed)len) {
+            newlen = 0;
+        } else if (end >= (signed)len) {
+            end = len-1;
+            newlen = (start > end) ? 0 : (end-start)+1;
+        }
     } else {
         start = 0;
     }
-    if (start != 0) memmove(sh->buf, sh->buf+start, newlen);
+    if (start && newlen) memmove(sh->buf, sh->buf+start, newlen);
     sh->buf[newlen] = 0;
     sh->free = sh->free+(sh->len-newlen);
     sh->len = newlen;
@@ -382,3 +392,182 @@ sds sdscatrepr(sds s, char *p, size_t len) {
     }
     return sdscatlen(s,"\"",1);
 }
+
+/* Split a line into arguments, where every argument can be in the
+ * following programming-language REPL-alike form:
+ *
+ * foo bar "newline are supported\n" and "\xff\x00otherstuff"
+ *
+ * The number of arguments is stored into *argc, and an array
+ * of sds is returned. The caller should sdsfree() all the returned
+ * strings and finally zfree() the array itself.
+ *
+ * Note that sdscatrepr() is able to convert back a string into
+ * a quoted string in the same format sdssplitargs() is able to parse.
+ */
+sds *sdssplitargs(char *line, int *argc) {
+    char *p = line;
+    char *current = NULL;
+    char **vector = NULL;
+
+    *argc = 0;
+    while(1) {
+        /* skip blanks */
+        while(*p && isspace(*p)) p++;
+        if (*p) {
+            /* get a token */
+            int inq=0; /* set to 1 if we are in "quotes" */
+            int done=0;
+
+            if (current == NULL) current = sdsempty();
+            while(!done) {
+                if (inq) {
+                    if (*p == '\\' && *(p+1)) {
+                        char c;
+
+                        p++;
+                        switch(*p) {
+                        case 'n': c = '\n'; break;
+                        case 'r': c = '\r'; break;
+                        case 't': c = '\t'; break;
+                        case 'b': c = '\b'; break;
+                        case 'a': c = '\a'; break;
+                        default: c = *p; break;
+                        }
+                        current = sdscatlen(current,&c,1);
+                    } else if (*p == '"') {
+                        /* closing quote must be followed by a space */
+                        if (*(p+1) && !isspace(*(p+1))) goto err;
+                        done=1;
+                    } else if (!*p) {
+                        /* unterminated quotes */
+                        goto err;
+                    } else {
+                        current = sdscatlen(current,p,1);
+                    }
+                } else {
+                    switch(*p) {
+                    case ' ':
+                    case '\n':
+                    case '\r':
+                    case '\t':
+                    case '\0':
+                        done=1;
+                        break;
+                    case '"':
+                        inq=1;
+                        break;
+                    default:
+                        current = sdscatlen(current,p,1);
+                        break;
+                    }
+                }
+                if (*p) p++;
+            }
+            /* add the token to the vector */
+            vector = zrealloc(vector,((*argc)+1)*sizeof(char*));
+            vector[*argc] = current;
+            (*argc)++;
+            current = NULL;
+        } else {
+            return vector;
+        }
+    }
+
+err:
+    while((*argc)--)
+        sdsfree(vector[*argc]);
+    zfree(vector);
+    if (current) sdsfree(current);
+    return NULL;
+}
+
+#ifdef SDS_TEST_MAIN
+#include <stdio.h>
+#include "testhelp.h"
+
+int main(void) {
+    {
+        sds x = sdsnew("foo"), y;
+
+        test_cond("Create a string and obtain the length",
+            sdslen(x) == 3 && memcmp(x,"foo\0",4) == 0)
+
+        sdsfree(x);
+        x = sdsnewlen("foo",2);
+        test_cond("Create a string with specified length",
+            sdslen(x) == 2 && memcmp(x,"fo\0",3) == 0)
+
+        x = sdscat(x,"bar");
+        test_cond("Strings concatenation",
+            sdslen(x) == 5 && memcmp(x,"fobar\0",6) == 0);
+
+        x = sdscpy(x,"a");
+        test_cond("sdscpy() against an originally longer string",
+            sdslen(x) == 1 && memcmp(x,"a\0",2) == 0)
+
+        x = sdscpy(x,"xyzxxxxxxxxxxyyyyyyyyyykkkkkkkkkk");
+        test_cond("sdscpy() against an originally shorter string",
+            sdslen(x) == 33 &&
+            memcmp(x,"xyzxxxxxxxxxxyyyyyyyyyykkkkkkkkkk\0",33) == 0)
+
+        sdsfree(x);
+        x = sdscatprintf(sdsempty(),"%d",123);
+        test_cond("sdscatprintf() seems working in the base case",
+            sdslen(x) == 3 && memcmp(x,"123\0",4) ==0)
+
+        sdsfree(x);
+        x = sdstrim(sdsnew("xxciaoyyy"),"xy");
+        test_cond("sdstrim() correctly trims characters",
+            sdslen(x) == 4 && memcmp(x,"ciao\0",5) == 0)
+
+        y = sdsrange(sdsdup(x),1,1);
+        test_cond("sdsrange(...,1,1)",
+            sdslen(y) == 1 && memcmp(y,"i\0",2) == 0)
+
+        sdsfree(y);
+        y = sdsrange(sdsdup(x),1,-1);
+        test_cond("sdsrange(...,1,-1)",
+            sdslen(y) == 3 && memcmp(y,"iao\0",4) == 0)
+
+        sdsfree(y);
+        y = sdsrange(sdsdup(x),-2,-1);
+        test_cond("sdsrange(...,-2,-1)",
+            sdslen(y) == 2 && memcmp(y,"ao\0",3) == 0)
+
+        sdsfree(y);
+        y = sdsrange(sdsdup(x),2,1);
+        test_cond("sdsrange(...,2,1)",
+            sdslen(y) == 0 && memcmp(y,"\0",1) == 0)
+
+        sdsfree(y);
+        y = sdsrange(sdsdup(x),1,100);
+        test_cond("sdsrange(...,1,100)",
+            sdslen(y) == 3 && memcmp(y,"iao\0",4) == 0)
+
+        sdsfree(y);
+        y = sdsrange(sdsdup(x),100,100);
+        test_cond("sdsrange(...,100,100)",
+            sdslen(y) == 0 && memcmp(y,"\0",1) == 0)
+
+        sdsfree(y);
+        sdsfree(x);
+        x = sdsnew("foo");
+        y = sdsnew("foa");
+        test_cond("sdscmp(foo,foa)", sdscmp(x,y) > 0)
+
+        sdsfree(y);
+        sdsfree(x);
+        x = sdsnew("bar");
+        y = sdsnew("bar");
+        test_cond("sdscmp(bar,bar)", sdscmp(x,y) == 0)
+
+        sdsfree(y);
+        sdsfree(x);
+        x = sdsnew("aar");
+        y = sdsnew("bar");
+        test_cond("sdscmp(bar,bar)", sdscmp(x,y) < 0)
+    }
+    test_report()
+}
+#endif