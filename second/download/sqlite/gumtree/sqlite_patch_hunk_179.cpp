     while( j<4 ){
       zResult[j++] = '0';
     }
     zResult[j] = 0;
     sqlite3_result_text(context, zResult, 4, SQLITE_TRANSIENT);
   }else{
+    /* IMP: R-64894-50321 The string "?000" is returned if the argument
+    ** is NULL or contains no ASCII alphabetic characters. */
     sqlite3_result_text(context, "?000", 4, SQLITE_STATIC);
   }
 }
-#endif
+#endif /* SQLITE_SOUNDEX */
 
 #ifndef SQLITE_OMIT_LOAD_EXTENSION
 /*
 ** A function that loads a shared-library extension then returns NULL.
 */
 static void loadExt(sqlite3_context *context, int argc, sqlite3_value **argv){
   const char *zFile = (const char *)sqlite3_value_text(argv[0]);
   const char *zProc;
   sqlite3 *db = sqlite3_context_db_handle(context);
   char *zErrMsg = 0;
 
+  /* Disallow the load_extension() SQL function unless the SQLITE_LoadExtFunc
+  ** flag is set.  See the sqlite3_enable_load_extension() API.
+  */
+  if( (db->flags & SQLITE_LoadExtFunc)==0 ){
+    sqlite3_result_error(context, "not authorized", -1);
+    return;
+  }
+
   if( argc==2 ){
     zProc = (const char *)sqlite3_value_text(argv[1]);
   }else{
     zProc = 0;
   }
   if( zFile && sqlite3_load_extension(db, zFile, zProc, &zErrMsg) ){
