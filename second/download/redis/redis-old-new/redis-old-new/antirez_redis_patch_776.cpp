@@ -200,7 +200,10 @@ size_t sdsAllocSize(sds s) {
 void sdsIncrLen(sds s, int incr) {
     struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
 
-    assert(sh->free >= incr);
+    if (incr >= 0)
+        assert(sh->free >= (unsigned int)incr);
+    else
+        assert(sh->len >= (unsigned int)(-incr));
     sh->len += incr;
     sh->free -= incr;
     assert(sh->free >= 0);
@@ -388,6 +391,7 @@ sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
         buf[buflen-2] = '\0';
         va_copy(cpy,ap);
         vsnprintf(buf, buflen, fmt, cpy);
+        va_end(ap);
         if (buf[buflen-2] != '\0') {
             if (buf != staticbuf) zfree(buf);
             buflen *= 2;
@@ -457,7 +461,7 @@ sds sdscatfmt(sds s, char const *fmt, ...) {
     i = initlen; /* Position of the next byte to write to dest str. */
     while(*f) {
         char next, *str;
-        int l;
+        unsigned int l;
         long long num;
         unsigned long long unum;
 