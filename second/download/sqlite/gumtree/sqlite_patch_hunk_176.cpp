     n = sqlite3_value_int(argv[1]);
     if( n>30 ) n = 30;
     if( n<0 ) n = 0;
   }
   if( sqlite3_value_type(argv[0])==SQLITE_NULL ) return;
   r = sqlite3_value_double(argv[0]);
-  zBuf = sqlite3_mprintf("%.*f",n,r);
-  if( zBuf==0 ){
-    sqlite3_result_error_nomem(context);
+  /* If Y==0 and X will fit in a 64-bit int,
+  ** handle the rounding directly,
+  ** otherwise use printf.
+  */
+  if( n==0 && r>=0 && r<LARGEST_INT64-1 ){
+    r = (double)((sqlite_int64)(r+0.5));
+  }else if( n==0 && r<0 && (-r)<LARGEST_INT64-1 ){
+    r = -(double)((sqlite_int64)((-r)+0.5));
   }else{
-    sqlite3AtoF(zBuf, &r);
+    zBuf = sqlite3_mprintf("%.*f",n,r);
+    if( zBuf==0 ){
+      sqlite3_result_error_nomem(context);
+      return;
+    }
+    sqlite3AtoF(zBuf, &r, sqlite3Strlen30(zBuf), SQLITE_UTF8);
     sqlite3_free(zBuf);
-    sqlite3_result_double(context, r);
   }
+  sqlite3_result_double(context, r);
 }
 #endif
 
 /*
-** Allocate nByte bytes of space using sqlite3_malloc(). If the
+** Allocate nByte bytes of space using sqlite3Malloc(). If the
 ** allocation fails, call sqlite3_result_error_nomem() to notify
 ** the database handle that malloc() has failed and return NULL.
 ** If nByte is larger than the maximum string or blob length, then
 ** raise an SQLITE_TOOBIG exception and return NULL.
 */
 static void *contextMalloc(sqlite3_context *context, i64 nByte){
