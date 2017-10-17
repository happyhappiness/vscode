 **      %s      Insert a string
 **      %z      A string that should be freed after use
 **      %d      Insert an integer
 **      %T      Insert a token
 **      %S      Insert the first element of a SrcList
 **
-** This function should be used to report any error that occurs whilst
+** This function should be used to report any error that occurs while
 ** compiling an SQL statement (i.e. within sqlite3_prepare()). The
 ** last thing the sqlite3_prepare() function does is copy the error
 ** stored by this function into the database handle using sqlite3Error().
-** Function sqlite3Error() should be used during statement execution
-** (sqlite3_step() etc.).
+** Functions sqlite3Error() or sqlite3ErrorWithMsg() should be used
+** during statement execution (sqlite3_step() etc.).
 */
 void sqlite3ErrorMsg(Parse *pParse, const char *zFormat, ...){
+  char *zMsg;
   va_list ap;
   sqlite3 *db = pParse->db;
-  pParse->nErr++;
-  sqlite3DbFree(db, pParse->zErrMsg);
   va_start(ap, zFormat);
-  pParse->zErrMsg = sqlite3VMPrintf(db, zFormat, ap);
+  zMsg = sqlite3VMPrintf(db, zFormat, ap);
   va_end(ap);
-  pParse->rc = SQLITE_ERROR;
-}
-
-/*
-** Clear the error message in pParse, if any
-*/
-void sqlite3ErrorClear(Parse *pParse){
-  sqlite3DbFree(pParse->db, pParse->zErrMsg);
-  pParse->zErrMsg = 0;
-  pParse->nErr = 0;
+  if( db->suppressErr ){
+    sqlite3DbFree(db, zMsg);
+  }else{
+    pParse->nErr++;
+    sqlite3DbFree(db, pParse->zErrMsg);
+    pParse->zErrMsg = zMsg;
+    pParse->rc = SQLITE_ERROR;
+  }
 }
 
 /*
 ** Convert an SQL-style quoted string into a normal string by removing
 ** the quote characters.  The conversion is done in-place.  If the
 ** input does not begin with a quote character, then this routine
