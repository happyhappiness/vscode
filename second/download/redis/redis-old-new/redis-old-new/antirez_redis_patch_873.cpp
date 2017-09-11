@@ -327,6 +327,35 @@ int sdsll2str(char *s, long long value) {
     return l;
 }
 
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
 /* Create an sds string from a long long value. It is much faster than:
  *
  * sdscatprintf(sdsempty(),"%lld\n", value);
@@ -410,8 +439,10 @@ sds sdscatprintf(sds s, const char *fmt, ...) {
  *
  * %s - C String
  * %S - SDS string
- * %i - signed integer
+ * %i - signed int
  * %I - 64 bit signed integer (long long, int64_t)
+ * %u - unsigned int
+ * %U - 64 bit unsigned integer (unsigned long long, uint64_t)
  * %% - Verbatim "%" character.
  */
 sds sdscatfmt(sds s, char const *fmt, ...) {
@@ -428,9 +459,13 @@ sds sdscatfmt(sds s, char const *fmt, ...) {
         char next, *str;
         size_t l;
         long long num;
+        unsigned long long unum;
 
         /* Make sure there is always space for at least 1 char. */
-        if (sh->free == 0) s = sdsMakeRoomFor(s,1);
+        if (sh->free == 0) {
+            s = sdsMakeRoomFor(s,1);
+            sh = (void*) (s-(sizeof(struct sdshdr)));
+        }
 
         switch(*f) {
         case '%':
@@ -441,7 +476,10 @@ sds sdscatfmt(sds s, char const *fmt, ...) {
             case 'S':
                 str = va_arg(ap,char*);
                 l = (next == 's') ? strlen(str) : sdslen(str);
-                if (sh->free < l) s = sdsMakeRoomFor(s,l);
+                if (sh->free < l) {
+                    s = sdsMakeRoomFor(s,l);
+                    sh = (void*) (s-(sizeof(struct sdshdr)));
+                }
                 memcpy(s+i,str,l);
                 sh->len += l;
                 sh->free -= l;
@@ -456,7 +494,29 @@ sds sdscatfmt(sds s, char const *fmt, ...) {
                 {
                     char buf[SDS_LLSTR_SIZE];
                     l = sdsll2str(buf,num);
-                    if (sh->free < l) s = sdsMakeRoomFor(s,l);
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
                     memcpy(s+i,buf,l);
                     sh->len += l;
                     sh->free -= l;
@@ -944,6 +1004,13 @@ int main(void) {
                      "9223372036854775807--",60) == 0)
 
         sdsfree(x);
+        x = sdsnew("--");
+        x = sdscatfmt(x, "%u,%U--", UINT_MAX, ULLONG_MAX);
+        test_cond("sdscatfmt() seems working with unsigned numbers",
+            sdslen(x) == 35 &&
+            memcmp(x,"--4294967295,18446744073709551615--",35) == 0)
+
+        sdsfree(x);
         x = sdsnew("xxciaoyyy");
         sdstrim(x,"xy");
         test_cond("sdstrim() correctly trims characters",