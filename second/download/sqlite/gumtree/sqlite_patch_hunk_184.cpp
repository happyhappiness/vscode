   
   /* Check if an existing function is being overridden or deleted. If so,
   ** and there are active VMs, then return SQLITE_BUSY. If a function
   ** is being overridden/deleted but there are no active VMs, allow the
   ** operation to continue but invalidate all precompiled statements.
   */
-  p = sqlite3FindFunction(db, zFunctionName, nName, nArg, (u8)enc, 0);
-  if( p && p->iPrefEnc==enc && p->nArg==nArg ){
-    if( db->activeVdbeCnt ){
-      sqlite3Error(db, SQLITE_BUSY, 
+  p = sqlite3FindFunction(db, zFunctionName, nArg, (u8)enc, 0);
+  if( p && (p->funcFlags & SQLITE_FUNC_ENCMASK)==enc && p->nArg==nArg ){
+    if( db->nVdbeActive ){
+      sqlite3ErrorWithMsg(db, SQLITE_BUSY, 
         "unable to delete/modify user-function due to active statements");
       assert( !db->mallocFailed );
       return SQLITE_BUSY;
     }else{
       sqlite3ExpirePreparedStatements(db);
     }
   }
 
-  p = sqlite3FindFunction(db, zFunctionName, nName, nArg, (u8)enc, 1);
+  p = sqlite3FindFunction(db, zFunctionName, nArg, (u8)enc, 1);
   assert(p || db->mallocFailed);
   if( !p ){
-    return SQLITE_NOMEM;
+    return SQLITE_NOMEM_BKPT;
+  }
+
+  /* If an older version of the function with a configured destructor is
+  ** being replaced invoke the destructor function here. */
+  functionDestroy(db, p);
+
+  if( pDestructor ){
+    pDestructor->nRef++;
   }
-  p->flags = 0;
-  p->xFunc = xFunc;
-  p->xStep = xStep;
+  p->u.pDestructor = pDestructor;
+  p->funcFlags = (p->funcFlags & SQLITE_FUNC_ENCMASK) | extraFlags;
+  testcase( p->funcFlags & SQLITE_DETERMINISTIC );
+  p->xSFunc = xSFunc ? xSFunc : xStep;
   p->xFinalize = xFinal;
   p->pUserData = pUserData;
   p->nArg = (u16)nArg;
   return SQLITE_OK;
 }
 
 /*
 ** Create new user functions.
 */
 int sqlite3_create_function(
   sqlite3 *db,
-  const char *zFunctionName,
+  const char *zFunc,
   int nArg,
   int enc,
   void *p,
-  void (*xFunc)(sqlite3_context*,int,sqlite3_value **),
+  void (*xSFunc)(sqlite3_context*,int,sqlite3_value **),
   void (*xStep)(sqlite3_context*,int,sqlite3_value **),
   void (*xFinal)(sqlite3_context*)
 ){
-  int rc;
+  return sqlite3_create_function_v2(db, zFunc, nArg, enc, p, xSFunc, xStep,
+                                    xFinal, 0);
+}
+
+int sqlite3_create_function_v2(
+  sqlite3 *db,
+  const char *zFunc,
+  int nArg,
+  int enc,
+  void *p,
+  void (*xSFunc)(sqlite3_context*,int,sqlite3_value **),
+  void (*xStep)(sqlite3_context*,int,sqlite3_value **),
+  void (*xFinal)(sqlite3_context*),
+  void (*xDestroy)(void *)
+){
+  int rc = SQLITE_ERROR;
+  FuncDestructor *pArg = 0;
+
+#ifdef SQLITE_ENABLE_API_ARMOR
+  if( !sqlite3SafetyCheckOk(db) ){
+    return SQLITE_MISUSE_BKPT;
+  }
+#endif
   sqlite3_mutex_enter(db->mutex);
-  rc = sqlite3CreateFunc(db, zFunctionName, nArg, enc, p, xFunc, xStep, xFinal);
+  if( xDestroy ){
+    pArg = (FuncDestructor *)sqlite3DbMallocZero(db, sizeof(FuncDestructor));
+    if( !pArg ){
+      xDestroy(p);
+      goto out;
+    }
+    pArg->xDestroy = xDestroy;
+    pArg->pUserData = p;
+  }
+  rc = sqlite3CreateFunc(db, zFunc, nArg, enc, p, xSFunc, xStep, xFinal, pArg);
+  if( pArg && pArg->nRef==0 ){
+    assert( rc!=SQLITE_OK );
+    xDestroy(p);
+    sqlite3DbFree(db, pArg);
+  }
+
+ out:
   rc = sqlite3ApiExit(db, rc);
   sqlite3_mutex_leave(db->mutex);
   return rc;
 }
 
 #ifndef SQLITE_OMIT_UTF16
 int sqlite3_create_function16(
   sqlite3 *db,
   const void *zFunctionName,
   int nArg,
   int eTextRep,
   void *p,
-  void (*xFunc)(sqlite3_context*,int,sqlite3_value**),
+  void (*xSFunc)(sqlite3_context*,int,sqlite3_value**),
   void (*xStep)(sqlite3_context*,int,sqlite3_value**),
   void (*xFinal)(sqlite3_context*)
 ){
   int rc;
   char *zFunc8;
+
+#ifdef SQLITE_ENABLE_API_ARMOR
+  if( !sqlite3SafetyCheckOk(db) || zFunctionName==0 ) return SQLITE_MISUSE_BKPT;
+#endif
   sqlite3_mutex_enter(db->mutex);
   assert( !db->mallocFailed );
-  zFunc8 = sqlite3Utf16to8(db, zFunctionName, -1);
-  rc = sqlite3CreateFunc(db, zFunc8, nArg, eTextRep, p, xFunc, xStep, xFinal);
+  zFunc8 = sqlite3Utf16to8(db, zFunctionName, -1, SQLITE_UTF16NATIVE);
+  rc = sqlite3CreateFunc(db, zFunc8, nArg, eTextRep, p, xSFunc,xStep,xFinal,0);
   sqlite3DbFree(db, zFunc8);
   rc = sqlite3ApiExit(db, rc);
   sqlite3_mutex_leave(db->mutex);
   return rc;
 }
 #endif
