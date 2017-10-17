 */
 int sqlite3_collation_needed16(
   sqlite3 *db, 
   void *pCollNeededArg, 
   void(*xCollNeeded16)(void*,sqlite3*,int eTextRep,const void*)
 ){
-#ifdef SQLITE_ENABLE_API_ARMOR
-  if( !sqlite3SafetyCheckOk(db) ) return SQLITE_MISUSE_BKPT;
-#endif
   sqlite3_mutex_enter(db->mutex);
   db->xCollNeeded = 0;
   db->xCollNeeded16 = xCollNeeded16;
   db->pCollNeededArg = pCollNeededArg;
   sqlite3_mutex_leave(db->mutex);
   return SQLITE_OK;
 }
 #endif /* SQLITE_OMIT_UTF16 */
 
+#ifndef SQLITE_OMIT_GLOBALRECOVER
 #ifndef SQLITE_OMIT_DEPRECATED
 /*
 ** This function is now an anachronism. It used to be used to recover from a
 ** malloc() failure, but SQLite now does this automatically.
 */
 int sqlite3_global_recover(void){
   return SQLITE_OK;
 }
 #endif
+#endif
 
 /*
 ** Test to see whether or not the database connection is in autocommit
 ** mode.  Return TRUE if it is and FALSE if not.  Autocommit mode is on
 ** by default.  Autocommit is disabled by a BEGIN statement and reenabled
 ** by the next COMMIT or ROLLBACK.
+**
+******* THIS IS AN EXPERIMENTAL API AND IS SUBJECT TO CHANGE ******
 */
 int sqlite3_get_autocommit(sqlite3 *db){
-#ifdef SQLITE_ENABLE_API_ARMOR
-  if( !sqlite3SafetyCheckOk(db) ){
-    (void)SQLITE_MISUSE_BKPT;
-    return 0;
-  }
-#endif
   return db->autoCommit;
 }
 
+#ifdef SQLITE_DEBUG
 /*
-** The following routines are substitutes for constants SQLITE_CORRUPT,
-** SQLITE_MISUSE, SQLITE_CANTOPEN, SQLITE_NOMEM and possibly other error
-** constants.  They serve two purposes:
-**
-**   1.  Serve as a convenient place to set a breakpoint in a debugger
-**       to detect when version error conditions occurs.
-**
-**   2.  Invoke sqlite3_log() to provide the source code location where
-**       a low-level error is first detected.
+** The following routine is subtituted for constant SQLITE_CORRUPT in
+** debugging builds.  This provides a way to set a breakpoint for when
+** corruption is first detected.
 */
-static int reportError(int iErr, int lineno, const char *zType){
-  sqlite3_log(iErr, "%s at line %d of [%.10s]",
-              zType, lineno, 20+sqlite3_sourceid());
-  return iErr;
-}
-int sqlite3CorruptError(int lineno){
-  testcase( sqlite3GlobalConfig.xLog!=0 );
-  return reportError(SQLITE_CORRUPT, lineno, "database corruption");
-}
-int sqlite3MisuseError(int lineno){
-  testcase( sqlite3GlobalConfig.xLog!=0 );
-  return reportError(SQLITE_MISUSE, lineno, "misuse");
-}
-int sqlite3CantopenError(int lineno){
-  testcase( sqlite3GlobalConfig.xLog!=0 );
-  return reportError(SQLITE_CANTOPEN, lineno, "cannot open file");
-}
-#ifdef SQLITE_DEBUG
-int sqlite3CorruptPgnoError(int lineno, Pgno pgno){
-  char zMsg[100];
-  sqlite3_snprintf(sizeof(zMsg), zMsg, "database corruption page %d", pgno);
-  testcase( sqlite3GlobalConfig.xLog!=0 );
-  return reportError(SQLITE_CORRUPT, lineno, zMsg);
-}
-int sqlite3NomemError(int lineno){
-  testcase( sqlite3GlobalConfig.xLog!=0 );
-  return reportError(SQLITE_NOMEM, lineno, "OOM");
-}
-int sqlite3IoerrnomemError(int lineno){
-  testcase( sqlite3GlobalConfig.xLog!=0 );
-  return reportError(SQLITE_IOERR_NOMEM, lineno, "I/O OOM error");
+int sqlite3Corrupt(void){
+  return SQLITE_CORRUPT;
 }
 #endif
 
 #ifndef SQLITE_OMIT_DEPRECATED
 /*
 ** This is a convenience routine that makes sure that all thread-specific
