@@ -32,8 +32,10 @@
 
 #include <stdarg.h>
 
+void createSharedObjects(void);
 void rdbLoadProgressCallback(rio *r, const void *buf, size_t len);
 long long rdbLoadMillisecondTime(rio *rdb);
+int rdbCheckMode = 0;
 
 struct {
     rio *rio;
@@ -44,10 +46,34 @@ struct {
     int doing;                      /* The state while reading the RDB. */
 } rdbstate;
 
+/* At every loading step try to remember what we were about to do, so that
+ * we can log this information when an error is encountered. */
 #define RDB_CHECK_DOING_START 0
-#define RDB_CHECK_DOING_READ_EXPIRE 1
-#define RDB_CHECK_DOING_READ_KEY 2
-#define RDB_CHECK_DOING_READ_VALUE 3
+#define RDB_CHECK_DOING_READ_TYPE 1
+#define RDB_CHECK_DOING_READ_EXPIRE 2
+#define RDB_CHECK_DOING_READ_KEY 3
+#define RDB_CHECK_DOING_READ_OBJECT_VALUE 4
+#define RDB_CHECK_DOING_CHECK_SUM 5
+#define RDB_CHECK_DOING_READ_LEN 6
+#define RDB_CHECK_DOING_READ_AUX 7
+
+char *rdb_check_doing_string[] = {
+    "start",
+    "read-type",
+    "read-expire",
+    "read-key",
+    "read-object-value",
+    "check-sum",
+    "read-len",
+    "read-aux"
+};
+
+/* Show a few stats collected into 'rdbstate' */
+void rdbShowGenericInfo(void) {
+    printf("[info] %lu keys read\n", rdbstate.keys);
+    printf("[info] %lu expires\n", rdbstate.expires);
+    printf("[info] %lu already expired\n", rdbstate.already_expired);
+}
 
 /* Called on RDB errors. Provides details about the RDB and the offset
  * we were when the error was detected. */
@@ -59,12 +85,16 @@ void rdbCheckError(const char *fmt, ...) {
     vsnprintf(msg, sizeof(msg), fmt, ap);
     va_end(ap);
 
-    printf("*** RDB CHECK FAILED: %s ***\n", msg);
-    printf("AT RDB OFFSET: %llu\n",
+    printf("--- RDB ERROR DETECTED ---\n");
+    printf("[offset %llu] %s\n",
         (unsigned long long) (rdbstate.rio ?
-            rdbstate.rio->processed_bytes : 0));
+            rdbstate.rio->processed_bytes : 0), msg);
+    printf("[additional info] While doing: %s\n",
+        rdb_check_doing_string[rdbstate.doing]);
     if (rdbstate.key)
-        printf("READING KEY: %s\n", (char*)rdbstate.key->ptr);
+        printf("[additional info] Reading key '%s'\n",
+            (char*)rdbstate.key->ptr);
+    rdbShowGenericInfo();
 }
 
 /* Print informations during RDB checking. */
@@ -138,30 +168,36 @@ int redis_check_rdb(char *rdbfilename) {
         expiretime = -1;
 
         /* Read type. */
+        rdbstate.doing = RDB_CHECK_DOING_READ_TYPE;
         if ((type = rdbLoadType(&rdb)) == -1) goto eoferr;
 
         /* Handle special types. */
         if (type == RDB_OPCODE_EXPIRETIME) {
+            rdbstate.doing = RDB_CHECK_DOING_READ_EXPIRE;
             /* EXPIRETIME: load an expire associated with the next key
              * to load. Note that after loading an expire we need to
              * load the actual type, and continue. */
             if ((expiretime = rdbLoadTime(&rdb)) == -1) goto eoferr;
             /* We read the time so we need to read the object type again. */
+            rdbstate.doing = RDB_CHECK_DOING_READ_TYPE;
             if ((type = rdbLoadType(&rdb)) == -1) goto eoferr;
             /* the EXPIRETIME opcode specifies time in seconds, so convert
              * into milliseconds. */
             expiretime *= 1000;
         } else if (type == RDB_OPCODE_EXPIRETIME_MS) {
             /* EXPIRETIME_MS: milliseconds precision expire times introduced
              * with RDB v3. Like EXPIRETIME but no with more precision. */
+            rdbstate.doing = RDB_CHECK_DOING_READ_EXPIRE;
             if ((expiretime = rdbLoadMillisecondTime(&rdb)) == -1) goto eoferr;
             /* We read the time so we need to read the object type again. */
+            rdbstate.doing = RDB_CHECK_DOING_READ_TYPE;
             if ((type = rdbLoadType(&rdb)) == -1) goto eoferr;
         } else if (type == RDB_OPCODE_EOF) {
             /* EOF: End of file, exit the main loop. */
             break;
         } else if (type == RDB_OPCODE_SELECTDB) {
             /* SELECTDB: Select the specified database. */
+            rdbstate.doing = RDB_CHECK_DOING_READ_LEN;
             if ((dbid = rdbLoadLen(&rdb,NULL)) == RDB_LENERR)
                 goto eoferr;
             rdbCheckInfo("Selecting DB ID %d", dbid);
@@ -170,6 +206,7 @@ int redis_check_rdb(char *rdbfilename) {
             /* RESIZEDB: Hint about the size of the keys in the currently
              * selected data base, in order to avoid useless rehashing. */
             uint64_t db_size, expires_size;
+            rdbstate.doing = RDB_CHECK_DOING_READ_LEN;
             if ((db_size = rdbLoadLen(&rdb,NULL)) == RDB_LENERR)
                 goto eoferr;
             if ((expires_size = rdbLoadLen(&rdb,NULL)) == RDB_LENERR)
@@ -182,20 +219,28 @@ int redis_check_rdb(char *rdbfilename) {
              *
              * An AUX field is composed of two strings: key and value. */
             robj *auxkey, *auxval;
+            rdbstate.doing = RDB_CHECK_DOING_READ_AUX;
             if ((auxkey = rdbLoadStringObject(&rdb)) == NULL) goto eoferr;
             if ((auxval = rdbLoadStringObject(&rdb)) == NULL) goto eoferr;
 
             rdbCheckInfo("%s = '%s'", (char*)auxkey->ptr, (char*)auxval->ptr);
             decrRefCount(auxkey);
             decrRefCount(auxval);
             continue; /* Read type again. */
+        } else {
+            if (!rdbIsObjectType(type)) {
+                rdbCheckError("Invalid object type: %d", type);
+                return 1;
+            }
         }
 
         /* Read key */
+        rdbstate.doing = RDB_CHECK_DOING_READ_KEY;
         if ((key = rdbLoadStringObject(&rdb)) == NULL) goto eoferr;
         rdbstate.key = key;
         rdbstate.keys++;
         /* Read value */
+        rdbstate.doing = RDB_CHECK_DOING_READ_OBJECT_VALUE;
         if ((val = rdbLoadObject(type,&rdb)) == NULL) goto eoferr;
         /* Check if the key already expired. This function is used when loading
          * an RDB file from disk, either at startup, or when an RDB was
@@ -213,6 +258,7 @@ int redis_check_rdb(char *rdbfilename) {
     if (rdbver >= 5 && server.rdb_checksum) {
         uint64_t cksum, expected = rdb.cksum;
 
+        rdbstate.doing = RDB_CHECK_DOING_CHECK_SUM;
         if (rioRead(&rdb,&cksum,8) == 0) goto eoferr;
         memrev64ifbe(&cksum);
         if (cksum == 0) {
@@ -235,18 +281,20 @@ int redis_check_rdb(char *rdbfilename) {
  *
  * The function never returns, but exits with the status code according
  * to success (RDB is sane) or error (RDB is corrupted). */
-int redis_check_rdb_main(char **argv, int argc) {
+int redis_check_rdb_main(int argc, char **argv) {
     if (argc != 2) {
         fprintf(stderr, "Usage: %s <rdb-file-name>\n", argv[0]);
         exit(1);
     }
     createSharedObjects(); /* Needed for loading. */
     server.loading_process_events_interval_bytes = 0;
+    rdbCheckMode = 1;
     rdbCheckInfo("Checking RDB file %s", argv[1]);
     rdbCheckSetupSignals();
     int retval = redis_check_rdb(argv[1]);
     if (retval == 0) {
         rdbCheckInfo("\\o/ RDB looks OK! \\o/");
+        rdbShowGenericInfo();
     }
     exit(retval);
 }