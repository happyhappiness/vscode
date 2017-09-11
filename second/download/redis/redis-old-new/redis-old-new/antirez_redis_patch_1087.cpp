@@ -36,6 +36,18 @@
 #include "sds.h"
 #include "zmalloc.h"
 
+/* Create a new sds string with the content specified by the 'init' pointer
+ * and 'initlen'.
+ * If NULL is used for 'init' the string is initialized with zero bytes.
+ *
+ * The string is always null-termined (all the sds strings are, always) so
+ * even if you create an sds string with:
+ *
+ * mystring = sdsnewlen("abc",3");
+ *
+ * You can print the string with printf() as there is an implicit \0 at the
+ * end of the string. However the string is binary safe and can contain
+ * \0 characters in the middle, as the length is stored in the sds header. */
 sds sdsnewlen(const void *init, size_t initlen) {
     struct sdshdr *sh;
 
@@ -53,31 +65,54 @@ sds sdsnewlen(const void *init, size_t initlen) {
     return (char*)sh->buf;
 }
 
+/* Create an empty (zero length) sds string. Even in this case the string
+ * always has an implicit null term. */
 sds sdsempty(void) {
     return sdsnewlen("",0);
 }
 
+/* Create a new sds string starting from a null termined C string. */
 sds sdsnew(const char *init) {
     size_t initlen = (init == NULL) ? 0 : strlen(init);
     return sdsnewlen(init, initlen);
 }
 
+/* Duplicate an sds string. */
 sds sdsdup(const sds s) {
     return sdsnewlen(s, sdslen(s));
 }
 
+/* Free an sds string. No operation is performed if 's' is NULL. */
 void sdsfree(sds s) {
     if (s == NULL) return;
     zfree(s-sizeof(struct sdshdr));
 }
 
+/* Set the sds string length to the length as obtained with strlen(), so
+ * considering as content only up to the first null term character.
+ *
+ * This function is useful when the sds string is hacked manually in some
+ * way, like in the following example:
+ *
+ * s = sdsnew("foobar");
+ * s[2] = '\0';
+ * sdsupdatelen(s);
+ * printf("%d\n", sdslen(s));
+ *
+ * The output will be "2", but if we comment out the call to sdsupdatelen()
+ * the output will be "6" as the string was modified but the logical length
+ * remains 6 bytes. */
 void sdsupdatelen(sds s) {
     struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
     int reallen = strlen(s);
     sh->free += (sh->len-reallen);
     sh->len = reallen;
 }
 
+/* Modify an sds string on-place to make it empty (zero length).
+ * However all the existing buffer is not discarded but set as free space
+ * so that next append operations will not require allocations up to the
+ * number of bytes previously available. */
 void sdsclear(sds s) {
     struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
     sh->free += sh->len;
@@ -89,7 +124,7 @@ void sdsclear(sds s) {
  * is sure that after calling this function can overwrite up to addlen
  * bytes after the end of the string, plus one more byte for nul term.
  * 
- * Note: this does not change the *size* of the sds string as returned
+ * Note: this does not change the *length* of the sds string as returned
  * by sdslen(), but only the free buffer space we have. */
 sds sdsMakeRoomFor(sds s, size_t addlen) {
     struct sdshdr *sh, *newsh;
@@ -113,7 +148,10 @@ sds sdsMakeRoomFor(sds s, size_t addlen) {
 
 /* Reallocate the sds string so that it has no free space at the end. The
  * contained string remains not altered, but next concatenation operations
- * will require a reallocation. */
+ * will require a reallocation.
+ *
+ * After the call, the passed sds string is no longer valid and all the
+ * references must be substituted with the new pointer returned by the call. */
 sds sdsRemoveFreeSpace(sds s) {
     struct sdshdr *sh;
 
@@ -123,14 +161,21 @@ sds sdsRemoveFreeSpace(sds s) {
     return sh->buf;
 }
 
+/* Return the total size of the allocation of the specifed sds string,
+ * including:
+ * 1) The sds header before the pointer.
+ * 2) The string.
+ * 3) The free buffer at the end if any.
+ * 4) The implicit null term.
+ */
 size_t sdsAllocSize(sds s) {
     struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
 
     return sizeof(*sh)+sh->len+sh->free+1;
 }
 
 /* Increment the sds length and decrements the left free space at the
- * end of the string accordingly to 'incr'. Also set the null term
+ * end of the string according to 'incr'. Also set the null term
  * in the new end of the string.
  *
  * This function is used in order to fix the string length after the
@@ -140,15 +185,17 @@ size_t sdsAllocSize(sds s) {
  * Note: it is possible to use a negative increment in order to
  * right-trim the string.
  *
+ * Usage example:
+ *
  * Using sdsIncrLen() and sdsMakeRoomFor() it is possible to mount the
- * following schema to cat bytes coming from the kernel to the end of an
- * sds string new things without copying into an intermediate buffer:
+ * following schema, to cat bytes coming from the kernel to the end of an
+ * sds string without copying into an intermediate buffer:
  *
  * oldlen = sdslen(s);
  * s = sdsMakeRoomFor(s, BUFFER_SIZE);
  * nread = read(fd, s+oldlen, BUFFER_SIZE);
  * ... check for nread <= 0 and handle it ...
- * sdsIncrLen(s, nhread);
+ * sdsIncrLen(s, nread);
  */
 void sdsIncrLen(sds s, int incr) {
     struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
@@ -161,7 +208,10 @@ void sdsIncrLen(sds s, int incr) {
 }
 
 /* Grow the sds to have the specified length. Bytes that were not part of
- * the original length of the sds will be set to zero. */
+ * the original length of the sds will be set to zero.
+ *
+ * if the specified length is smaller than the current length, no operation
+ * is performed. */
 sds sdsgrowzero(sds s, size_t len) {
     struct sdshdr *sh = (void*)(s-(sizeof(struct sdshdr)));
     size_t totlen, curlen = sh->len;
@@ -179,6 +229,11 @@ sds sdsgrowzero(sds s, size_t len) {
     return s;
 }
 
+/* Append the specified binary-safe string pointed by 't' of 'len' bytes to the
+ * end of the specified sds string 's'.
+ *
+ * After the call, the passed sds string is no longer valid and all the
+ * references must be substituted with the new pointer returned by the call. */
 sds sdscatlen(sds s, const void *t, size_t len) {
     struct sdshdr *sh;
     size_t curlen = sdslen(s);
@@ -193,14 +248,24 @@ sds sdscatlen(sds s, const void *t, size_t len) {
     return s;
 }
 
+/* Append the specified null termianted C string to the sds string 's'.
+ *
+ * After the call, the passed sds string is no longer valid and all the
+ * references must be substituted with the new pointer returned by the call. */
 sds sdscat(sds s, const char *t) {
     return sdscatlen(s, t, strlen(t));
 }
 
+/* Append the specified sds 't' to the existing sds 's'.
+ *
+ * After the call, the modified sds string is no longer valid and all the
+ * references must be substituted with the new pointer returned by the call. */
 sds sdscatsds(sds s, const sds t) {
     return sdscatlen(s, t, sdslen(t));
 }
 
+/* Destructively modify the sds string 's' to hold the specified binary
+ * safe string pointed by 't' of length 'len' bytes. */
 sds sdscpylen(sds s, const char *t, size_t len) {
     struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
     size_t totlen = sh->free+sh->len;
@@ -218,10 +283,13 @@ sds sdscpylen(sds s, const char *t, size_t len) {
     return s;
 }
 
+/* Like sdscpylen() but 't' must be a null-termined string so that the length
+ * of the string is obtained with strlen(). */
 sds sdscpy(sds s, const char *t) {
     return sdscpylen(s, t, strlen(t));
 }
 
+/* Like sdscatpritf() but gets va_list instead of being variadic. */
 sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
     va_list cpy;
     char *buf, *t;
@@ -245,6 +313,22 @@ sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
     return t;
 }
 
+/* Append to the sds string 's' a string obtained using printf-alike format
+ * specifier.
+ *
+ * After the call, the modified sds string is no longer valid and all the
+ * references must be substituted with the new pointer returned by the call.
+ *
+ * Example:
+ *
+ * s = sdsempty("Sum is: ");
+ * s = sdscatprintf(s,"%d+%d = %d",a,b,a+b).
+ *
+ * Often you need to create a string from scratch with the printf-alike
+ * format. When this is the need, just use sdsempty() as the target string:
+ *
+ * s = sdscatprintf(sdsempty(), "... your format ...", args);
+ */
 sds sdscatprintf(sds s, const char *fmt, ...) {
     va_list ap;
     char *t;
@@ -254,6 +338,20 @@ sds sdscatprintf(sds s, const char *fmt, ...) {
     return t;
 }
 
+/* Remove the part of the string from left and from right composed just of
+ * contiguous characters found in 'cset', that is a null terminted C string.
+ *
+ * After the call, the modified sds string is no longer valid and all the
+ * references must be substituted with the new pointer returned by the call.
+ *
+ * Example:
+ *
+ * s = sdsnew("AA...AA.a.aa.aHelloWorld     :::");
+ * s = sdstrim(s,"A. :");
+ * printf("%s\n", s);
+ *
+ * Output will be just "Hello World".
+ */
 sds sdstrim(sds s, const char *cset) {
     struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
     char *start, *end, *sp, *ep;
@@ -271,6 +369,22 @@ sds sdstrim(sds s, const char *cset) {
     return s;
 }
 
+/* Turn the string into a smaller (or equal) string containing only the
+ * substring specified by the 'start' and 'end' indexes.
+ *
+ * start and end can be negative, where -1 means the last character of the
+ * string, -2 the penultimate character, and so forth.
+ *
+ * The interval is inclusive, so the start and end characters will be part
+ * of the resulting string.
+ *
+ * The string is modified in-place.
+ *
+ * Example:
+ *
+ * s = sdsnew("Hello World");
+ * sdstrim(s,1,-1); => "ello Worl"
+ */
 sds sdsrange(sds s, int start, int end) {
     struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
     size_t newlen, len = sdslen(s);
@@ -302,18 +416,31 @@ sds sdsrange(sds s, int start, int end) {
     return s;
 }
 
+/* Apply tolower() to every character of the sds string 's'. */
 void sdstolower(sds s) {
     int len = sdslen(s), j;
 
     for (j = 0; j < len; j++) s[j] = tolower(s[j]);
 }
 
+/* Apply toupper() to every character of the sds string 's'. */
 void sdstoupper(sds s) {
     int len = sdslen(s), j;
 
     for (j = 0; j < len; j++) s[j] = toupper(s[j]);
 }
 
+/* Compare two sds strings s1 and s2 with memcmp().
+ *
+ * Return value:
+ *
+ *     1 if s1 > s2.
+ *    -1 if s1 < s2.
+ *     0 if s1 and s2 are exactly the same binary string.
+ *
+ * If two strings share exactly the same prefix, but one of the two has
+ * additional characters, the longer string is considered to be greater than
+ * the smaller one. */
 int sdscmp(const sds s1, const sds s2) {
     size_t l1, l2, minlen;
     int cmp;
@@ -391,13 +518,18 @@ sds *sdssplitlen(const char *s, int len, const char *sep, int seplen, int *count
     }
 }
 
+/* Free the result returned by sdssplitlen(), or do nothing if 'tokens' is NULL. */
 void sdsfreesplitres(sds *tokens, int count) {
     if (!tokens) return;
     while(count--)
         sdsfree(tokens[count]);
     zfree(tokens);
 }
 
+/* Create an sds string from a long long value. It is much faster than:
+ *
+ * sdscatprintf(sdsempty(),"%lld\n", value);
+ */
 sds sdsfromlonglong(long long value) {
     char buf[32], *p;
     unsigned long long v;
@@ -413,6 +545,12 @@ sds sdsfromlonglong(long long value) {
     return sdsnewlen(p,32-(p-buf));
 }
 
+/* Append to the sds string "s" an escaped string representation where
+ * all the non-printable characters (tested with isprint()) are turned into
+ * escapes in the form "\n\r\a...." or "\x<hex-number>".
+ *
+ * After the call, the modified sds string is no longer valid and all the
+ * references must be substituted with the new pointer returned by the call. */
 sds sdscatrepr(sds s, const char *p, size_t len) {
     s = sdscatlen(s,"\"",1);
     while(len--) {