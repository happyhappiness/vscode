 ** encoded in UTF-8.
 **
 ** To clear the most recent error for sqlite handle "db", sqlite3Error
 ** should be called with err_code set to SQLITE_OK and zFormat set
 ** to NULL.
 */
-void sqlite3Error(sqlite3 *db, int err_code, const char *zFormat, ...){
-  if( db && (db->pErr || (db->pErr = sqlite3ValueNew(db))!=0) ){
-    db->errCode = err_code;
-    if( zFormat ){
-      char *z;
-      va_list ap;
-      va_start(ap, zFormat);
-      z = sqlite3VMPrintf(db, zFormat, ap);
-      va_end(ap);
-      sqlite3ValueSetStr(db->pErr, -1, z, SQLITE_UTF8, SQLITE_DYNAMIC);
-    }else{
-      sqlite3ValueSetStr(db->pErr, 0, 0, SQLITE_UTF8, SQLITE_STATIC);
-    }
+void sqlite3ErrorWithMsg(sqlite3 *db, int err_code, const char *zFormat, ...){
+  assert( db!=0 );
+  db->errCode = err_code;
+  sqlite3SystemError(db, err_code);
+  if( zFormat==0 ){
+    sqlite3Error(db, err_code);
+  }else if( db->pErr || (db->pErr = sqlite3ValueNew(db))!=0 ){
+    char *z;
+    va_list ap;
+    va_start(ap, zFormat);
+    z = sqlite3VMPrintf(db, zFormat, ap);
+    va_end(ap);
+    sqlite3ValueSetStr(db->pErr, -1, z, SQLITE_UTF8, SQLITE_DYNAMIC);
   }
 }
 
 /*
 ** Add an error message to pParse->zErrMsg and increment pParse->nErr.
 ** The following formatting characters are allowed:
