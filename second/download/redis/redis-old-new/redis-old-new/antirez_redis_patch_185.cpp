@@ -40,6 +40,7 @@ int rdbCheckMode = 0;
 struct {
     rio *rio;
     robj *key;                      /* Current key we are reading. */
+    int key_type;                   /* Current key type if != -1. */
     unsigned long keys;             /* Number of keys processed. */
     unsigned long expires;          /* Number of keys with an expire. */
     unsigned long already_expired;  /* Number of keys already expired. */
@@ -68,6 +69,23 @@ char *rdb_check_doing_string[] = {
     "read-aux"
 };
 
+char *rdb_type_string[] = {
+    "string",
+    "list-linked",
+    "set-hashtable",
+    "zset-v1",
+    "hash-hashtable",
+    "zset-v2",
+    "module-value",
+    "","",
+    "hash-zipmap",
+    "list-ziplist",
+    "set-intset",
+    "zset-ziplist",
+    "hash-ziplist",
+    "quicklist"
+};
+
 /* Show a few stats collected into 'rdbstate' */
 void rdbShowGenericInfo(void) {
     printf("[info] %lu keys read\n", rdbstate.keys);
@@ -94,6 +112,12 @@ void rdbCheckError(const char *fmt, ...) {
     if (rdbstate.key)
         printf("[additional info] Reading key '%s'\n",
             (char*)rdbstate.key->ptr);
+    if (rdbstate.key_type != -1)
+        printf("[additional info] Reading type %d (%s)\n",
+            rdbstate.key_type,
+            ((unsigned)rdbstate.key_type <
+             sizeof(rdb_type_string)/sizeof(char*)) ?
+                rdb_type_string[rdbstate.key_type] : "unknown");
     rdbShowGenericInfo();
 }
 
@@ -128,8 +152,7 @@ void rdbCheckSetupSignals(void) {
 
     sigemptyset(&act.sa_mask);
     act.sa_flags = SA_NODEFER | SA_RESETHAND | SA_SIGINFO;
-#warning "Uncomment here"
-//    act.sa_sigaction = rdbCheckHandleCrash;
+    act.sa_sigaction = rdbCheckHandleCrash;
     sigaction(SIGSEGV, &act, NULL);
     sigaction(SIGBUS, &act, NULL);
     sigaction(SIGFPE, &act, NULL);
@@ -233,6 +256,7 @@ int redis_check_rdb(char *rdbfilename) {
                 rdbCheckError("Invalid object type: %d", type);
                 return 1;
             }
+            rdbstate.key_type = type;
         }
 
         /* Read key */
@@ -254,6 +278,7 @@ int redis_check_rdb(char *rdbfilename) {
         rdbstate.key = NULL;
         decrRefCount(key);
         decrRefCount(val);
+        rdbstate.key_type = -1;
     }
     /* Verify the checksum if RDB version is >= 5 */
     if (rdbver >= 5 && server.rdb_checksum) {