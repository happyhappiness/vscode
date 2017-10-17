 ){
   int rc;
   const sqlite3_tokenizer_module *p1;
   const sqlite3_tokenizer_module *p2;
   sqlite3 *db = (sqlite3 *)sqlite3_user_data(context);
 
-  UNUSED_PARAMETER(argc);
-  UNUSED_PARAMETER(argv);
-
   /* Test the query function */
   sqlite3Fts3SimpleTokenizerModule(&p1);
   rc = queryTokenizer(db, "simple", &p2);
   assert( rc==SQLITE_OK );
   assert( p1==p2 );
   rc = queryTokenizer(db, "nosuchtokenizer", &p2);
   assert( rc==SQLITE_ERROR );
   assert( p2==0 );
   assert( 0==strcmp(sqlite3_errmsg(db), "unknown tokenizer: nosuchtokenizer") );
 
   /* Test the storage function */
-  if( fts3TokenizerEnabled(context) ){
-    rc = registerTokenizer(db, "nosuchtokenizer", p1);
-    assert( rc==SQLITE_OK );
-    rc = queryTokenizer(db, "nosuchtokenizer", &p2);
-    assert( rc==SQLITE_OK );
-    assert( p2==p1 );
-  }
+  rc = registerTokenizer(db, "nosuchtokenizer", p1);
+  assert( rc==SQLITE_OK );
+  rc = queryTokenizer(db, "nosuchtokenizer", &p2);
+  assert( rc==SQLITE_OK );
+  assert( p2==p1 );
 
   sqlite3_result_text(context, "ok", -1, SQLITE_STATIC);
 }
 
 #endif
 
 /*
 ** Set up SQL objects in database db used to access the contents of
 ** the hash table pointed to by argument pHash. The hash table must
-** been initialized to use string keys, and to take a private copy 
+** been initialised to use string keys, and to take a private copy 
 ** of the key when a value is inserted. i.e. by a call similar to:
 **
 **    sqlite3Fts3HashInit(pHash, FTS3_HASH_STRING, 1);
 **
 ** This function adds a scalar function (see header comment above
-** fts3TokenizerFunc() in this file for details) and, if ENABLE_TABLE is
+** scalarFunc() in this file for details) and, if ENABLE_TABLE is
 ** defined at compilation time, a temporary virtual table (see header 
 ** comment above struct HashTableVtab) to the database schema. Both 
 ** provide read/write access to the contents of *pHash.
 **
 ** The third argument to this function, zName, is used as the name
 ** of both the scalar and, if created, the virtual table.
 */
 int sqlite3Fts3InitHashTable(
   sqlite3 *db, 
-  Fts3Hash *pHash, 
+  fts3Hash *pHash, 
   const char *zName
 ){
   int rc = SQLITE_OK;
   void *p = (void *)pHash;
   const int any = SQLITE_ANY;
-
-#ifdef SQLITE_TEST
   char *zTest = 0;
   char *zTest2 = 0;
+
+#ifdef SQLITE_TEST
   void *pdb = (void *)db;
   zTest = sqlite3_mprintf("%s_test", zName);
   zTest2 = sqlite3_mprintf("%s_internal_test", zName);
   if( !zTest || !zTest2 ){
     rc = SQLITE_NOMEM;
   }
 #endif
 
-  if( SQLITE_OK==rc ){
-    rc = sqlite3_create_function(db, zName, 1, any, p, fts3TokenizerFunc, 0, 0);
-  }
-  if( SQLITE_OK==rc ){
-    rc = sqlite3_create_function(db, zName, 2, any, p, fts3TokenizerFunc, 0, 0);
-  }
+  if( rc!=SQLITE_OK
+   || (rc = sqlite3_create_function(db, zName, 1, any, p, scalarFunc, 0, 0))
+   || (rc = sqlite3_create_function(db, zName, 2, any, p, scalarFunc, 0, 0))
 #ifdef SQLITE_TEST
-  if( SQLITE_OK==rc ){
-    rc = sqlite3_create_function(db, zTest, -1, any, p, testFunc, 0, 0);
-  }
-  if( SQLITE_OK==rc ){
-    rc = sqlite3_create_function(db, zTest2, 0, any, pdb, intTestFunc, 0, 0);
-  }
+   || (rc = sqlite3_create_function(db, zTest, 2, any, p, testFunc, 0, 0))
+   || (rc = sqlite3_create_function(db, zTest, 3, any, p, testFunc, 0, 0))
+   || (rc = sqlite3_create_function(db, zTest2, 0, any, pdb, intTestFunc, 0, 0))
 #endif
+  );
 
-#ifdef SQLITE_TEST
   sqlite3_free(zTest);
   sqlite3_free(zTest2);
-#endif
-
   return rc;
 }
 
 #endif /* !defined(SQLITE_CORE) || defined(SQLITE_ENABLE_FTS3) */
