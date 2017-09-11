@@ -289,6 +289,55 @@ sds sdscpy(sds s, const char *t) {
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
@@ -351,6 +400,91 @@ sds sdscatprintf(sds s, const char *fmt, ...) {
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
+ * %i - signed integer
+ * %I - 64 bit signed integer (long long, int64_t)
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
+
+        /* Make sure there is always space for at least 1 char. */
+        if (sh->free == 0) s = sdsMakeRoomFor(s,1);
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
+                if (sh->free < l) s = sdsMakeRoomFor(s,l);
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
+                    if (sh->free < l) s = sdsMakeRoomFor(s,l);
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
@@ -538,25 +672,6 @@ void sdsfreesplitres(sds *tokens, int count) {
     zfree(tokens);
 }
 
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
-}
-
 /* Append to the sds string "s" an escaped string representation where
  * all the non-printable characters (tested with isprint()) are turned into
  * escapes in the form "\n\r\a...." or "\x<hex-number>".
@@ -787,6 +902,7 @@ sds sdsjoin(char **argv, int argc, char *sep) {
 #ifdef SDS_TEST_MAIN
 #include <stdio.h>
 #include "testhelp.h"
+#include "limits.h"
 
 int main(void) {
     {
@@ -817,39 +933,54 @@ int main(void) {
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
 
@@ -871,6 +1002,13 @@ int main(void) {
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
 