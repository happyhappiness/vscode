   if( sqlite3MemCompare(argv[0], argv[1], pColl)!=0 ){
     sqlite3_result_value(context, argv[0]);
   }
 }
 
 /*
-** Implementation of the sqlite_version() function.  The result is the version
+** Implementation of the VERSION(*) function.  The result is the version
 ** of the SQLite library that is running.
 */
 static void versionFunc(
   sqlite3_context *context,
   int NotUsed,
   sqlite3_value **NotUsed2
 ){
   UNUSED_PARAMETER2(NotUsed, NotUsed2);
-  /* IMP: R-48699-48617 This function is an SQL wrapper around the
-  ** sqlite3_libversion() C-interface. */
-  sqlite3_result_text(context, sqlite3_libversion(), -1, SQLITE_STATIC);
+  sqlite3_result_text(context, sqlite3_version, -1, SQLITE_STATIC);
 }
 
-/*
-** Implementation of the sqlite_source_id() function. The result is a string
-** that identifies the particular version of the source code used to build
-** SQLite.
-*/
-static void sourceidFunc(
-  sqlite3_context *context,
-  int NotUsed,
-  sqlite3_value **NotUsed2
-){
-  UNUSED_PARAMETER2(NotUsed, NotUsed2);
-  /* IMP: R-24470-31136 This function is an SQL wrapper around the
-  ** sqlite3_sourceid() C interface. */
-  sqlite3_result_text(context, sqlite3_sourceid(), -1, SQLITE_STATIC);
-}
-
-/*
-** Implementation of the sqlite_log() function.  This is a wrapper around
-** sqlite3_log().  The return value is NULL.  The function exists purely for
-** its side-effects.
-*/
-static void errlogFunc(
-  sqlite3_context *context,
-  int argc,
-  sqlite3_value **argv
-){
-  UNUSED_PARAMETER(argc);
-  UNUSED_PARAMETER(context);
-  sqlite3_log(sqlite3_value_int(argv[0]), "%s", sqlite3_value_text(argv[1]));
-}
-
-/*
-** Implementation of the sqlite_compileoption_used() function.
-** The result is an integer that identifies if the compiler option
-** was used to build SQLite.
-*/
-#ifndef SQLITE_OMIT_COMPILEOPTION_DIAGS
-static void compileoptionusedFunc(
-  sqlite3_context *context,
-  int argc,
-  sqlite3_value **argv
-){
-  const char *zOptName;
-  assert( argc==1 );
-  UNUSED_PARAMETER(argc);
-  /* IMP: R-39564-36305 The sqlite_compileoption_used() SQL
-  ** function is a wrapper around the sqlite3_compileoption_used() C/C++
-  ** function.
-  */
-  if( (zOptName = (const char*)sqlite3_value_text(argv[0]))!=0 ){
-    sqlite3_result_int(context, sqlite3_compileoption_used(zOptName));
-  }
-}
-#endif /* SQLITE_OMIT_COMPILEOPTION_DIAGS */
-
-/*
-** Implementation of the sqlite_compileoption_get() function. 
-** The result is a string that identifies the compiler options 
-** used to build SQLite.
-*/
-#ifndef SQLITE_OMIT_COMPILEOPTION_DIAGS
-static void compileoptiongetFunc(
-  sqlite3_context *context,
-  int argc,
-  sqlite3_value **argv
-){
-  int n;
-  assert( argc==1 );
-  UNUSED_PARAMETER(argc);
-  /* IMP: R-04922-24076 The sqlite_compileoption_get() SQL function
-  ** is a wrapper around the sqlite3_compileoption_get() C/C++ function.
-  */
-  n = sqlite3_value_int(argv[0]);
-  sqlite3_result_text(context, sqlite3_compileoption_get(n), -1, SQLITE_STATIC);
-}
-#endif /* SQLITE_OMIT_COMPILEOPTION_DIAGS */
-
 /* Array for converting from half-bytes (nybbles) into ASCII hex
 ** digits. */
 static const char hexdigits[] = {
   '0', '1', '2', '3', '4', '5', '6', '7',
   '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' 
 };
 
 /*
+** EXPERIMENTAL - This is not an official function.  The interface may
+** change.  This function may disappear.  Do not write code that depends
+** on this function.
+**
 ** Implementation of the QUOTE() function.  This function takes a single
 ** argument.  If the argument is numeric, the return value is the same as
 ** the argument.  If the argument is NULL, the return value is the string
 ** "NULL".  Otherwise, the argument is enclosed in single quotes with
 ** single-quote escapes.
 */
 static void quoteFunc(sqlite3_context *context, int argc, sqlite3_value **argv){
   assert( argc==1 );
   UNUSED_PARAMETER(argc);
   switch( sqlite3_value_type(argv[0]) ){
+    case SQLITE_INTEGER:
     case SQLITE_FLOAT: {
-      double r1, r2;
-      char zBuf[50];
-      r1 = sqlite3_value_double(argv[0]);
-      sqlite3_snprintf(sizeof(zBuf), zBuf, "%!.15g", r1);
-      sqlite3AtoF(zBuf, &r2, 20, SQLITE_UTF8);
-      if( r1!=r2 ){
-        sqlite3_snprintf(sizeof(zBuf), zBuf, "%!.20e", r1);
-      }
-      sqlite3_result_text(context, zBuf, -1, SQLITE_TRANSIENT);
-      break;
-    }
-    case SQLITE_INTEGER: {
       sqlite3_result_value(context, argv[0]);
       break;
     }
     case SQLITE_BLOB: {
       char *zText = 0;
       char const *zBlob = sqlite3_value_blob(argv[0]);
