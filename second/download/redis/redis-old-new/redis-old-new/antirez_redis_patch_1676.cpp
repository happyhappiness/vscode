@@ -1,6 +1,7 @@
 #include "redis.h"
 #include <ctype.h>
 #include <limits.h>
+#include <math.h>
 
 /* Glob-style pattern matching. */
 int stringmatchlen(const char *pattern, int patternLen,
@@ -200,6 +201,102 @@ int ll2string(char *s, size_t len, long long value) {
     return l;
 }
 
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
+    if (p[0] == '-') {
+        negative = 1;
+        p++; plen++;
+
+        /* Abort on only a negative sign. */
+        if (plen == slen)
+            return 0;
+    }
+
+    /* First digit should be 1-9. */
+    if (p[0] >= '1' && p[0] <= '9') {
+        v = p[0]-'0';
+        p++; plen++;
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
+        if (v > (-(unsigned long long)LLONG_MIN)) /* Overflow. */
+            return 0;
+        if (value != NULL) *value = -v;
+    } else {
+        if (v > LLONG_MAX) /* Overflow. */
+            return 0;
+        if (value != NULL) *value = v;
+    }
+    return 1;
+}
+
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
+    } else {
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
+    }
+
+    return len;
+}
+
 /* Check if the sds string 's' can be represented by a long long
  * (that is, is a number that fits into long without any other space or
  * character before or after the digits, so that converting this number