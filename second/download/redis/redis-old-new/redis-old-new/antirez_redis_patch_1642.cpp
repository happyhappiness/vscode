@@ -1,6 +1,10 @@
-#include "redis.h"
+#include <stdlib.h>
+#include <stdio.h>
+#include <string.h>
 #include <ctype.h>
 #include <limits.h>
+#include <math.h>
+#include "util.h"
 
 /* Glob-style pattern matching. */
 int stringmatchlen(const char *pattern, int patternLen,
@@ -200,44 +204,237 @@ int ll2string(char *s, size_t len, long long value) {
     return l;
 }
 
-/* Check if the sds string 's' can be represented by a long long
- * (that is, is a number that fits into long without any other space or
- * character before or after the digits, so that converting this number
- * back to a string will result in the same bytes as the original string).
- *
- * If so, the function returns REDIS_OK and *llongval is set to the value
- * of the number. Otherwise REDIS_ERR is returned */
-int isStringRepresentableAsLongLong(sds s, long long *llongval) {
-    char buf[32], *endptr;
-    long long value;
-    int slen;
-
-    value = strtoll(s, &endptr, 10);
-    if (endptr[0] != '\0') return REDIS_ERR;
-    slen = ll2string(buf,32,value);
-
-    /* If the number converted back into a string is not identical
-     * then it's not possible to encode the string as integer */
-    if (sdslen(s) != (unsigned)slen || memcmp(buf,s,slen)) return REDIS_ERR;
-    if (llongval) *llongval = value;
-    return REDIS_OK;
+/* Convert a string into a long long. Returns 1 if the string could be parsed
+ * into a (non-overflowing) long long, 0 otherwise. The value will be set to
+ * the parsed value when appropriate. */
+int string2ll(char *s, size_t slen, long long *value) {
+    char *p = s;
+    size_t plen = 0;
+    int negative = 0;
+    unsigned long long v;
+
+    if (plen == slen)
+        return 0;
+
+    /* Special case: first and only digit is 0. */
+    if (slen == 1 && p[0] == '0') {
+        if (value != NULL) *value = 0;
+        return 1;
+    }
+
+    if (p[0] == '-') {
+        negative = 1;
+        p++; plen++;
+
+        /* Abort on only a negative sign. */
+        if (plen == slen)
+            return 0;
+    }
+
+    /* First digit should be 1-9, otherwise the string should just be 0. */
+    if (p[0] >= '1' && p[0] <= '9') {
+        v = p[0]-'0';
+        p++; plen++;
+    } else if (p[0] == '0' && slen == 1) {
+        *value = 0;
+        return 1;
+    } else {
+        return 0;
+    }
+
+    while (plen < slen && p[0] >= '0' && p[0] <= '9') {
+        if (v > (ULLONG_MAX / 10)) /* Overflow. */
+            return 0;
+        v *= 10;
+
+        if (v > (ULLONG_MAX - (p[0]-'0'))) /* Overflow. */
+            return 0;
+        v += p[0]-'0';
+
+        p++; plen++;
+    }
+
+    /* Return if not all bytes were used. */
+    if (plen < slen)
+        return 0;
+
+    if (negative) {
+        if (v > ((unsigned long long)(-(LLONG_MIN+1))+1)) /* Overflow. */
+            return 0;
+        if (value != NULL) *value = -v;
+    } else {
+        if (v > LLONG_MAX) /* Overflow. */
+            return 0;
+        if (value != NULL) *value = v;
+    }
+    return 1;
 }
 
-int isStringRepresentableAsLong(sds s, long *longval) {
-    long long ll;
+/* Convert a string into a long. Returns 1 if the string could be parsed into a
+ * (non-overflowing) long, 0 otherwise. The value will be set to the parsed
+ * value when appropriate. */
+int string2l(char *s, size_t slen, long *lval) {
+    long long llval;
 
-    if (isStringRepresentableAsLongLong(s,&ll) == REDIS_ERR) return REDIS_ERR;
-    if (ll < LONG_MIN || ll > LONG_MAX) return REDIS_ERR;
-    *longval = (long)ll;
-    return REDIS_OK;
+    if (!string2ll(s,slen,&llval))
+        return 0;
+
+    if (llval < LONG_MIN || llval > LONG_MAX)
+        return 0;
+
+    *lval = (long)llval;
+    return 1;
 }
 
-int isObjectRepresentableAsLongLong(robj *o, long long *llongval) {
-    redisAssert(o->type == REDIS_STRING);
-    if (o->encoding == REDIS_ENCODING_INT) {
-        if (llongval) *llongval = (long) o->ptr;
-        return REDIS_OK;
+/* Convert a double to a string representation. Returns the number of bytes
+ * required. The representation should always be parsable by stdtod(3). */
+int d2string(char *buf, size_t len, double value) {
+    if (isnan(value)) {
+        len = snprintf(buf,len,"nan");
+    } else if (isinf(value)) {
+        if (value < 0)
+            len = snprintf(buf,len,"-inf");
+        else
+            len = snprintf(buf,len,"inf");
+    } else if (value == 0) {
+        /* See: http://en.wikipedia.org/wiki/Signed_zero, "Comparisons". */
+        if (1.0/value < 0)
+            len = snprintf(buf,len,"-0");
+        else
+            len = snprintf(buf,len,"0");
     } else {
-        return isStringRepresentableAsLongLong(o->ptr,llongval);
+#if (DBL_MANT_DIG >= 52) && (LLONG_MAX == 0x7fffffffffffffffLL)
+        /* Check if the float is in a safe range to be casted into a
+         * long long. We are assuming that long long is 64 bit here.
+         * Also we are assuming that there are no implementations around where
+         * double has precision < 52 bit.
+         *
+         * Under this assumptions we test if a double is inside an interval
+         * where casting to long long is safe. Then using two castings we
+         * make sure the decimal part is zero. If all this is true we use
+         * integer printing function that is much faster. */
+        double min = -4503599627370495; /* (2^52)-1 */
+        double max = 4503599627370496; /* -(2^52) */
+        if (val > min && val < max && value == ((double)((long long)value)))
+            len = ll2string(buf,len,(long long)value);
+        else
+#endif
+            len = snprintf(buf,len,"%.17g",value);
     }
+
+    return len;
+}
+
+#ifdef UTIL_TEST_MAIN
+#include <assert.h>
+
+void test_string2ll(void) {
+    char buf[32];
+    long long v;
+
+    /* May not start with +. */
+    strcpy(buf,"+1");
+    assert(string2ll(buf,strlen(buf),&v) == 0);
+
+    /* Leading space. */
+    strcpy(buf," 1");
+    assert(string2ll(buf,strlen(buf),&v) == 0);
+
+    /* Trailing space. */
+    strcpy(buf,"1 ");
+    assert(string2ll(buf,strlen(buf),&v) == 0);
+
+    /* May not start with 0. */
+    strcpy(buf,"01");
+    assert(string2ll(buf,strlen(buf),&v) == 0);
+
+    strcpy(buf,"-1");
+    assert(string2ll(buf,strlen(buf),&v) == 1);
+    assert(v == -1);
+
+    strcpy(buf,"0");
+    assert(string2ll(buf,strlen(buf),&v) == 1);
+    assert(v == 0);
+
+    strcpy(buf,"1");
+    assert(string2ll(buf,strlen(buf),&v) == 1);
+    assert(v == 1);
+
+    strcpy(buf,"99");
+    assert(string2ll(buf,strlen(buf),&v) == 1);
+    assert(v == 99);
+
+    strcpy(buf,"-99");
+    assert(string2ll(buf,strlen(buf),&v) == 1);
+    assert(v == -99);
+
+    strcpy(buf,"-9223372036854775808");
+    assert(string2ll(buf,strlen(buf),&v) == 1);
+    assert(v == LLONG_MIN);
+
+    strcpy(buf,"-9223372036854775809"); /* overflow */
+    assert(string2ll(buf,strlen(buf),&v) == 0);
+
+    strcpy(buf,"9223372036854775807");
+    assert(string2ll(buf,strlen(buf),&v) == 1);
+    assert(v == LLONG_MAX);
+
+    strcpy(buf,"9223372036854775808"); /* overflow */
+    assert(string2ll(buf,strlen(buf),&v) == 0);
+}
+
+void test_string2l(void) {
+    char buf[32];
+    long v;
+
+    /* May not start with +. */
+    strcpy(buf,"+1");
+    assert(string2l(buf,strlen(buf),&v) == 0);
+
+    /* May not start with 0. */
+    strcpy(buf,"01");
+    assert(string2l(buf,strlen(buf),&v) == 0);
+
+    strcpy(buf,"-1");
+    assert(string2l(buf,strlen(buf),&v) == 1);
+    assert(v == -1);
+
+    strcpy(buf,"0");
+    assert(string2l(buf,strlen(buf),&v) == 1);
+    assert(v == 0);
+
+    strcpy(buf,"1");
+    assert(string2l(buf,strlen(buf),&v) == 1);
+    assert(v == 1);
+
+    strcpy(buf,"99");
+    assert(string2l(buf,strlen(buf),&v) == 1);
+    assert(v == 99);
+
+    strcpy(buf,"-99");
+    assert(string2l(buf,strlen(buf),&v) == 1);
+    assert(v == -99);
+
+#if LONG_MAX != LLONG_MAX
+    strcpy(buf,"-2147483648");
+    assert(string2l(buf,strlen(buf),&v) == 1);
+    assert(v == LONG_MIN);
+
+    strcpy(buf,"-2147483649"); /* overflow */
+    assert(string2l(buf,strlen(buf),&v) == 0);
+
+    strcpy(buf,"2147483647");
+    assert(string2l(buf,strlen(buf),&v) == 1);
+    assert(v == LONG_MAX);
+
+    strcpy(buf,"2147483648"); /* overflow */
+    assert(string2l(buf,strlen(buf),&v) == 0);
+#endif
+}
+
+int main(int argc, char **argv) {
+    test_string2ll();
+    test_string2l();
+    return 0;
 }
+#endif