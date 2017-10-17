 /*
 ** Load all automatic extensions.
 **
 ** If anything goes wrong, set an error in the database connection.
 */
 void sqlite3AutoLoadExtensions(sqlite3 *db){
-  u32 i;
+  int i;
   int go = 1;
-  int rc;
-  sqlite3_loadext_entry xInit;
+  int (*xInit)(sqlite3*,char**,const sqlite3_api_routines*);
 
   wsdAutoextInit;
   if( wsdAutoext.nExt==0 ){
     /* Common case: early out without every having to acquire a mutex */
     return;
   }
   for(i=0; go; i++){
     char *zErrmsg;
 #if SQLITE_THREADSAFE
     sqlite3_mutex *mutex = sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_MASTER);
 #endif
-#ifdef SQLITE_OMIT_LOAD_EXTENSION
-    const sqlite3_api_routines *pThunk = 0;
-#else
-    const sqlite3_api_routines *pThunk = &sqlite3Apis;
-#endif
     sqlite3_mutex_enter(mutex);
     if( i>=wsdAutoext.nExt ){
       xInit = 0;
       go = 0;
     }else{
-      xInit = (sqlite3_loadext_entry)wsdAutoext.aExt[i];
+      xInit = (int(*)(sqlite3*,char**,const sqlite3_api_routines*))
+              wsdAutoext.aExt[i];
     }
     sqlite3_mutex_leave(mutex);
     zErrmsg = 0;
-    if( xInit && (rc = xInit(db, &zErrmsg, pThunk))!=0 ){
-      sqlite3ErrorWithMsg(db, rc,
+    if( xInit && xInit(db, &zErrmsg, &sqlite3Apis) ){
+      sqlite3Error(db, SQLITE_ERROR,
             "automatic extension loading failed: %s", zErrmsg);
       go = 0;
     }
     sqlite3_free(zErrmsg);
   }
 }
