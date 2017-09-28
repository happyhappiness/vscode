             rdbCheckError("RDB CRC error");
         } else {
             rdbCheckInfo("Checksum OK");
         }
     }
 
-    fclose(fp);
+    if (closefile) fclose(fp);
     return 0;
 
 eoferr: /* unexpected end of file is handled here with a fatal exit */
     if (rdbstate.error_set) {
         rdbCheckError(rdbstate.error);
     } else {
         rdbCheckError("Unexpected EOF reading RDB file");
     }
     return 1;
 }
 
 /* RDB check main: called form redis.c when Redis is executed with the
- * redis-check-rdb alias.
+ * redis-check-rdb alias, on during RDB loading errors.
  *
- * The function never returns, but exits with the status code according
- * to success (RDB is sane) or error (RDB is corrupted). */
-int redis_check_rdb_main(int argc, char **argv) {
-    if (argc != 2) {
+ * The function works in two ways: can be called with argc/argv as a
+ * standalone executable, or called with a non NULL 'fp' argument if we
+ * already have an open file to check. This happens when the function
+ * is used to check an RDB preamble inside an AOF file.
+ *
+ * When called with fp = NULL, the function never returns, but exits with the
+ * status code according to success (RDB is sane) or error (RDB is corrupted).
+ * Otherwise if called with a non NULL fp, the function returns C_OK or
+ * C_ERR depending on the success or failure. */
+int redis_check_rdb_main(int argc, char **argv, FILE *fp) {
+    if (argc != 2 && fp == NULL) {
         fprintf(stderr, "Usage: %s <rdb-file-name>\n", argv[0]);
         exit(1);
     }
-    createSharedObjects(); /* Needed for loading. */
+    /* In order to call the loading functions we need to create the shared
+     * integer objects, however since this function may be called from
+     * an already initialized Redis instance, check if we really need to. */
+    if (shared.integers[0] == NULL)
+        createSharedObjects();
     server.loading_process_events_interval_bytes = 0;
     rdbCheckMode = 1;
     rdbCheckInfo("Checking RDB file %s", argv[1]);
     rdbCheckSetupSignals();
-    int retval = redis_check_rdb(argv[1]);
+    int retval = redis_check_rdb(argv[1],fp);
     if (retval == 0) {
         rdbCheckInfo("\\o/ RDB looks OK! \\o/");
         rdbShowGenericInfo();
     }
+    if (fp) return (retval == 0) ? C_OK : C_ERR;
     exit(retval);
 }
