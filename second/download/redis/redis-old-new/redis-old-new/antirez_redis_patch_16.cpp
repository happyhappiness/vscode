@@ -173,16 +173,18 @@ void rdbCheckSetupSignals(void) {
 }
 
 /* Check the specified RDB file. Return 0 if the RDB looks sane, otherwise
- * 1 is returned. */
-int redis_check_rdb(char *rdbfilename) {
+ * 1 is returned.
+ * The file is specified as a filename in 'rdbfilename' if 'fp' is not NULL,
+ * otherwise the already open file 'fp' is checked. */
+int redis_check_rdb(char *rdbfilename, FILE *fp) {
     uint64_t dbid;
     int type, rdbver;
     char buf[1024];
     long long expiretime, now = mstime();
-    FILE *fp;
     static rio rdb; /* Pointed by global struct riostate. */
 
-    if ((fp = fopen(rdbfilename,"r")) == NULL) return 1;
+    int closefile = (fp == NULL);
+    if (fp == NULL && (fp = fopen(rdbfilename,"r")) == NULL) return 1;
 
     rioInitWithFile(&rdb,fp);
     rdbstate.rio = &rdb;
@@ -310,7 +312,7 @@ int redis_check_rdb(char *rdbfilename) {
         }
     }
 
-    fclose(fp);
+    if (closefile) fclose(fp);
     return 0;
 
 eoferr: /* unexpected end of file is handled here with a fatal exit */
@@ -323,12 +325,19 @@ int redis_check_rdb(char *rdbfilename) {
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
@@ -341,10 +350,11 @@ int redis_check_rdb_main(int argc, char **argv) {
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