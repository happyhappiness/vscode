@@ -45,6 +45,8 @@ struct {
     unsigned long expires;          /* Number of keys with an expire. */
     unsigned long already_expired;  /* Number of keys already expired. */
     int doing;                      /* The state while reading the RDB. */
+    int error_set;                  /* True if error is populated. */
+    char error[1024];
 } rdbstate;
 
 /* At every loading step try to remember what we were about to do, so that
@@ -135,6 +137,17 @@ void rdbCheckInfo(const char *fmt, ...) {
             rdbstate.rio->processed_bytes : 0), msg);
 }
 
+/* Used inside rdb.c in order to log specific errors happening inside
+ * the RDB loading internals. */
+void rdbCheckSetError(const char *fmt, ...) {
+    va_list ap;
+
+    va_start(ap, fmt);
+    vsnprintf(rdbstate.error, sizeof(rdbstate.error), fmt, ap);
+    va_end(ap);
+    rdbstate.error_set = 1;
+}
+
 /* During RDB check we setup a special signal handler for memory violations
  * and similar conditions, so that we can log the offending part of the RDB
  * if the crash is due to broken content. */
@@ -300,7 +313,11 @@ int redis_check_rdb(char *rdbfilename) {
     return 0;
 
 eoferr: /* unexpected end of file is handled here with a fatal exit */
-    rdbCheckError("Unexpected EOF reading RDB file");
+    if (rdbstate.error_set) {
+        rdbCheckError(rdbstate.error);
+    } else {
+        rdbCheckError("Unexpected EOF reading RDB file");
+    }
     return 1;
 }
 