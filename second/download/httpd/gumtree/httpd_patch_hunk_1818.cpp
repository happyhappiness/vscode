     while (--n >= 0) {
         *s++ = itoa64[v&0x3f];
         v >>= 6;
     }
 }
 
+static void generate_salt(char *s, size_t size)
+{
+    static unsigned char tbl[] = 
+        "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
+    size_t i;
+    for (i = 0; i < size; ++i) {
+        int idx = (int) (64.0 * rand() / (RAND_MAX + 1.0));
+        s[i] = tbl[idx];
+    }
+}
+
+static apr_status_t seed_rand(void)
+{
+    int seed = 0;
+    apr_status_t rv;
+    rv = apr_generate_random_bytes((unsigned char*) &seed, sizeof(seed));
+    if (rv) {
+        apr_file_printf(errfile, "Unable to generate random bytes: %pm" NL, &rv);
+        return rv;
+    }
+    srand(seed);
+    return rv;
+}
+
 static void putline(apr_file_t *f, const char *l)
 {
     apr_file_puts(l, f);
 }
 
 /*
