       "unable to use function %s in the requested context", zName);
   sqlite3_result_error(context, zErr, -1);
   sqlite3_free(zErr);
 }
 
 /*
+** Create a new aggregate context for p and return a pointer to
+** its pMem->z element.
+*/
+static SQLITE_NOINLINE void *createAggContext(sqlite3_context *p, int nByte){
+  Mem *pMem = p->pMem;
+  assert( (pMem->flags & MEM_Agg)==0 );
+  if( nByte<=0 ){
+    sqlite3VdbeMemSetNull(pMem);
+    pMem->z = 0;
+  }else{
+    sqlite3VdbeMemClearAndResize(pMem, nByte);
+    pMem->flags = MEM_Agg;
+    pMem->u.pDef = p->pFunc;
+    if( pMem->z ){
+      memset(pMem->z, 0, nByte);
+    }
+  }
+  return (void*)pMem->z;
+}
+
+/*
 ** Allocate or return the aggregate context for a user function.  A new
 ** context is allocated on the first call.  Subsequent calls return the
 ** same context that was returned on prior calls.
 */
 void *sqlite3_aggregate_context(sqlite3_context *p, int nByte){
-  Mem *pMem;
-  assert( p && p->pFunc && p->pFunc->xStep );
-  assert( sqlite3_mutex_held(p->s.db->mutex) );
-  pMem = p->pMem;
-  if( (pMem->flags & MEM_Agg)==0 ){
-    if( nByte==0 ){
-      sqlite3VdbeMemReleaseExternal(pMem);
-      pMem->flags = MEM_Null;
-      pMem->z = 0;
-    }else{
-      sqlite3VdbeMemGrow(pMem, nByte, 0);
-      pMem->flags = MEM_Agg;
-      pMem->u.pDef = p->pFunc;
-      if( pMem->z ){
-        memset(pMem->z, 0, nByte);
-      }
-    }
+  assert( p && p->pFunc && p->pFunc->xFinalize );
+  assert( sqlite3_mutex_held(p->pOut->db->mutex) );
+  testcase( nByte<0 );
+  if( (p->pMem->flags & MEM_Agg)==0 ){
+    return createAggContext(p, nByte);
+  }else{
+    return (void*)p->pMem->z;
   }
-  return (void*)pMem->z;
 }
 
 /*
-** Return the auxilary data pointer, if any, for the iArg'th argument to
+** Return the auxiliary data pointer, if any, for the iArg'th argument to
 ** the user-function defined by pCtx.
+**
+** The left-most argument is 0.
+**
+** Undocumented behavior:  If iArg is negative then access a cache of
+** auxiliary data pointers that is available to all functions within a
+** single prepared statement.  The iArg values must match.
 */
 void *sqlite3_get_auxdata(sqlite3_context *pCtx, int iArg){
-  VdbeFunc *pVdbeFunc;
+  AuxData *pAuxData;
 
-  assert( sqlite3_mutex_held(pCtx->s.db->mutex) );
-  pVdbeFunc = pCtx->pVdbeFunc;
-  if( !pVdbeFunc || iArg>=pVdbeFunc->nAux || iArg<0 ){
-    return 0;
+  assert( sqlite3_mutex_held(pCtx->pOut->db->mutex) );
+#if SQLITE_ENABLE_STAT3_OR_STAT4
+  if( pCtx->pVdbe==0 ) return 0;
+#else
+  assert( pCtx->pVdbe!=0 );
+#endif
+  for(pAuxData=pCtx->pVdbe->pAuxData; pAuxData; pAuxData=pAuxData->pNextAux){
+    if(  pAuxData->iAuxArg==iArg && (pAuxData->iAuxOp==pCtx->iOp || iArg<0) ){
+      return pAuxData->pAux;
+    }
   }
-  return pVdbeFunc->apAux[iArg].pAux;
+  return 0;
 }
 
 /*
-** Set the auxilary data pointer and delete function, for the iArg'th
+** Set the auxiliary data pointer and delete function, for the iArg'th
 ** argument to the user-function defined by pCtx. Any previous value is
 ** deleted by calling the delete function specified when it was set.
+**
+** The left-most argument is 0.
+**
+** Undocumented behavior:  If iArg is negative then make the data available
+** to all functions within the current prepared statement using iArg as an
+** access code.
 */
 void sqlite3_set_auxdata(
   sqlite3_context *pCtx, 
   int iArg, 
   void *pAux, 
   void (*xDelete)(void*)
 ){
-  struct AuxData *pAuxData;
-  VdbeFunc *pVdbeFunc;
-  if( iArg<0 ) goto failed;
-
-  assert( sqlite3_mutex_held(pCtx->s.db->mutex) );
-  pVdbeFunc = pCtx->pVdbeFunc;
-  if( !pVdbeFunc || pVdbeFunc->nAux<=iArg ){
-    int nAux = (pVdbeFunc ? pVdbeFunc->nAux : 0);
-    int nMalloc = sizeof(VdbeFunc) + sizeof(struct AuxData)*iArg;
-    pVdbeFunc = sqlite3DbRealloc(pCtx->s.db, pVdbeFunc, nMalloc);
-    if( !pVdbeFunc ){
-      goto failed;
-    }
-    pCtx->pVdbeFunc = pVdbeFunc;
-    memset(&pVdbeFunc->apAux[nAux], 0, sizeof(struct AuxData)*(iArg+1-nAux));
-    pVdbeFunc->nAux = iArg+1;
-    pVdbeFunc->pFunc = pCtx->pFunc;
-  }
-
-  pAuxData = &pVdbeFunc->apAux[iArg];
-  if( pAuxData->pAux && pAuxData->xDelete ){
-    pAuxData->xDelete(pAuxData->pAux);
+  AuxData *pAuxData;
+  Vdbe *pVdbe = pCtx->pVdbe;
+
+  assert( sqlite3_mutex_held(pCtx->pOut->db->mutex) );
+#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
+  if( pVdbe==0 ) goto failed;
+#else
+  assert( pVdbe!=0 );
+#endif
+
+  for(pAuxData=pVdbe->pAuxData; pAuxData; pAuxData=pAuxData->pNextAux){
+    if( pAuxData->iAuxArg==iArg && (pAuxData->iAuxOp==pCtx->iOp || iArg<0) ){
+      break;
+    }
+  }
+  if( pAuxData==0 ){
+    pAuxData = sqlite3DbMallocZero(pVdbe->db, sizeof(AuxData));
+    if( !pAuxData ) goto failed;
+    pAuxData->iAuxOp = pCtx->iOp;
+    pAuxData->iAuxArg = iArg;
+    pAuxData->pNextAux = pVdbe->pAuxData;
+    pVdbe->pAuxData = pAuxData;
+    if( pCtx->fErrorOrAux==0 ){
+      pCtx->isError = 0;
+      pCtx->fErrorOrAux = 1;
+    }
+  }else if( pAuxData->xDeleteAux ){
+    pAuxData->xDeleteAux(pAuxData->pAux);
   }
+
   pAuxData->pAux = pAux;
-  pAuxData->xDelete = xDelete;
+  pAuxData->xDeleteAux = xDelete;
   return;
 
 failed:
   if( xDelete ){
     xDelete(pAux);
   }
 }
 
 #ifndef SQLITE_OMIT_DEPRECATED
 /*
-** Return the number of times the Step function of a aggregate has been 
+** Return the number of times the Step function of an aggregate has been 
 ** called.
 **
 ** This function is deprecated.  Do not use it for new code.  It is
 ** provide only to avoid breaking legacy code.  New aggregate function
 ** implementations should keep their own counts within their aggregate
 ** context.
 */
 int sqlite3_aggregate_count(sqlite3_context *p){
-  assert( p && p->pMem && p->pFunc && p->pFunc->xStep );
+  assert( p && p->pMem && p->pFunc && p->pFunc->xFinalize );
   return p->pMem->n;
 }
 #endif
 
 /*
 ** Return the number of columns in the result set for the statement pStmt.
