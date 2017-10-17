 ** an error is returned.
 **
 ** Whether or not the <pointer> argument is specified, the value returned
 ** is a blob containing the pointer stored as the hash data corresponding
 ** to string <key-name> (after the hash-table is updated, if applicable).
 */
-static void scalarFunc(
+static void fts3TokenizerFunc(
   sqlite3_context *context,
   int argc,
   sqlite3_value **argv
 ){
-  fts3Hash *pHash;
+  Fts3Hash *pHash;
   void *pPtr = 0;
   const unsigned char *zName;
   int nName;
 
   assert( argc==1 || argc==2 );
 
-  pHash = (fts3Hash *)sqlite3_user_data(context);
+  pHash = (Fts3Hash *)sqlite3_user_data(context);
 
   zName = sqlite3_value_text(argv[0]);
   nName = sqlite3_value_bytes(argv[0])+1;
 
   if( argc==2 ){
-    void *pOld;
-    int n = sqlite3_value_bytes(argv[1]);
-    if( n!=sizeof(pPtr) ){
-      sqlite3_result_error(context, "argument type mismatch", -1);
-      return;
-    }
-    pPtr = *(void **)sqlite3_value_blob(argv[1]);
-    pOld = sqlite3Fts3HashInsert(pHash, (void *)zName, nName, pPtr);
-    if( pOld==pPtr ){
-      sqlite3_result_error(context, "out of memory", -1);
+    if( fts3TokenizerEnabled(context) ){
+      void *pOld;
+      int n = sqlite3_value_bytes(argv[1]);
+      if( zName==0 || n!=sizeof(pPtr) ){
+        sqlite3_result_error(context, "argument type mismatch", -1);
+        return;
+      }
+      pPtr = *(void **)sqlite3_value_blob(argv[1]);
+      pOld = sqlite3Fts3HashInsert(pHash, (void *)zName, nName, pPtr);
+      if( pOld==pPtr ){
+        sqlite3_result_error(context, "out of memory", -1);
+      }
+    }else{
+      sqlite3_result_error(context, "fts3tokenize disabled", -1);
       return;
     }
   }else{
-    pPtr = sqlite3Fts3HashFind(pHash, zName, nName);
+    if( zName ){
+      pPtr = sqlite3Fts3HashFind(pHash, zName, nName);
+    }
     if( !pPtr ){
       char *zErr = sqlite3_mprintf("unknown tokenizer: %s", zName);
       sqlite3_result_error(context, zErr, -1);
       sqlite3_free(zErr);
       return;
     }
