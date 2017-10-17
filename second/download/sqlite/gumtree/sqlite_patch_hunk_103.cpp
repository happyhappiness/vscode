   return sqlite3ValueText(pVal, SQLITE_UTF16BE);
 }
 const void *sqlite3_value_text16le(sqlite3_value *pVal){
   return sqlite3ValueText(pVal, SQLITE_UTF16LE);
 }
 #endif /* SQLITE_OMIT_UTF16 */
-/* EVIDENCE-OF: R-12793-43283 Every value in SQLite has one of five
-** fundamental datatypes: 64-bit signed integer 64-bit IEEE floating
-** point number string BLOB NULL
-*/
 int sqlite3_value_type(sqlite3_value* pVal){
-  static const u8 aType[] = {
-     SQLITE_BLOB,     /* 0x00 */
-     SQLITE_NULL,     /* 0x01 */
-     SQLITE_TEXT,     /* 0x02 */
-     SQLITE_NULL,     /* 0x03 */
-     SQLITE_INTEGER,  /* 0x04 */
-     SQLITE_NULL,     /* 0x05 */
-     SQLITE_INTEGER,  /* 0x06 */
-     SQLITE_NULL,     /* 0x07 */
-     SQLITE_FLOAT,    /* 0x08 */
-     SQLITE_NULL,     /* 0x09 */
-     SQLITE_FLOAT,    /* 0x0a */
-     SQLITE_NULL,     /* 0x0b */
-     SQLITE_INTEGER,  /* 0x0c */
-     SQLITE_NULL,     /* 0x0d */
-     SQLITE_INTEGER,  /* 0x0e */
-     SQLITE_NULL,     /* 0x0f */
-     SQLITE_BLOB,     /* 0x10 */
-     SQLITE_NULL,     /* 0x11 */
-     SQLITE_TEXT,     /* 0x12 */
-     SQLITE_NULL,     /* 0x13 */
-     SQLITE_INTEGER,  /* 0x14 */
-     SQLITE_NULL,     /* 0x15 */
-     SQLITE_INTEGER,  /* 0x16 */
-     SQLITE_NULL,     /* 0x17 */
-     SQLITE_FLOAT,    /* 0x18 */
-     SQLITE_NULL,     /* 0x19 */
-     SQLITE_FLOAT,    /* 0x1a */
-     SQLITE_NULL,     /* 0x1b */
-     SQLITE_INTEGER,  /* 0x1c */
-     SQLITE_NULL,     /* 0x1d */
-     SQLITE_INTEGER,  /* 0x1e */
-     SQLITE_NULL,     /* 0x1f */
-  };
-  return aType[pVal->flags&MEM_AffMask];
-}
-
-/* Make a copy of an sqlite3_value object
-*/
-sqlite3_value *sqlite3_value_dup(const sqlite3_value *pOrig){
-  sqlite3_value *pNew;
-  if( pOrig==0 ) return 0;
-  pNew = sqlite3_malloc( sizeof(*pNew) );
-  if( pNew==0 ) return 0;
-  memset(pNew, 0, sizeof(*pNew));
-  memcpy(pNew, pOrig, MEMCELLSIZE);
-  pNew->flags &= ~MEM_Dyn;
-  pNew->db = 0;
-  if( pNew->flags&(MEM_Str|MEM_Blob) ){
-    pNew->flags &= ~(MEM_Static|MEM_Dyn);
-    pNew->flags |= MEM_Ephem;
-    if( sqlite3VdbeMemMakeWriteable(pNew)!=SQLITE_OK ){
-      sqlite3ValueFree(pNew);
-      pNew = 0;
-    }
-  }
-  return pNew;
+  return pVal->type;
 }
 
-/* Destroy an sqlite3_value object previously obtained from
-** sqlite3_value_dup().
-*/
-void sqlite3_value_free(sqlite3_value *pOld){
-  sqlite3ValueFree(pOld);
-}
-  
-
 /**************************** sqlite3_result_  *******************************
 ** The following routines are used by user-defined functions to specify
 ** the function result.
-**
-** The setStrOrError() function calls sqlite3VdbeMemSetStr() to store the
-** result as a string or blob but if the string or blob is too large, it
-** then sets the error code to SQLITE_TOOBIG
-**
-** The invokeValueDestructor(P,X) routine invokes destructor function X()
-** on value P is not going to be used and need to be destroyed.
-*/
-static void setResultStrOrError(
-  sqlite3_context *pCtx,  /* Function context */
-  const char *z,          /* String pointer */
-  int n,                  /* Bytes in string, or negative */
-  u8 enc,                 /* Encoding of z.  0 for BLOBs */
-  void (*xDel)(void*)     /* Destructor function */
-){
-  if( sqlite3VdbeMemSetStr(pCtx->pOut, z, n, enc, xDel)==SQLITE_TOOBIG ){
-    sqlite3_result_error_toobig(pCtx);
-  }
-}
-static int invokeValueDestructor(
-  const void *p,             /* Value to destroy */
-  void (*xDel)(void*),       /* The destructor */
-  sqlite3_context *pCtx      /* Set a SQLITE_TOOBIG error if no NULL */
-){
-  assert( xDel!=SQLITE_DYNAMIC );
-  if( xDel==0 ){
-    /* noop */
-  }else if( xDel==SQLITE_TRANSIENT ){
-    /* noop */
-  }else{
-    xDel((void*)p);
-  }
-  if( pCtx ) sqlite3_result_error_toobig(pCtx);
-  return SQLITE_TOOBIG;
-}
+*/
 void sqlite3_result_blob(
   sqlite3_context *pCtx, 
   const void *z, 
   int n, 
   void (*xDel)(void *)
 ){
   assert( n>=0 );
-  assert( sqlite3_mutex_held(pCtx->pOut->db->mutex) );
-  setResultStrOrError(pCtx, z, n, 0, xDel);
-}
-void sqlite3_result_blob64(
-  sqlite3_context *pCtx, 
-  const void *z, 
-  sqlite3_uint64 n,
-  void (*xDel)(void *)
-){
-  assert( sqlite3_mutex_held(pCtx->pOut->db->mutex) );
-  assert( xDel!=SQLITE_DYNAMIC );
-  if( n>0x7fffffff ){
-    (void)invokeValueDestructor(z, xDel, pCtx);
-  }else{
-    setResultStrOrError(pCtx, z, (int)n, 0, xDel);
-  }
+  assert( sqlite3_mutex_held(pCtx->s.db->mutex) );
+  sqlite3VdbeMemSetStr(&pCtx->s, z, n, 0, xDel);
 }
 void sqlite3_result_double(sqlite3_context *pCtx, double rVal){
-  assert( sqlite3_mutex_held(pCtx->pOut->db->mutex) );
-  sqlite3VdbeMemSetDouble(pCtx->pOut, rVal);
+  assert( sqlite3_mutex_held(pCtx->s.db->mutex) );
+  sqlite3VdbeMemSetDouble(&pCtx->s, rVal);
 }
 void sqlite3_result_error(sqlite3_context *pCtx, const char *z, int n){
-  assert( sqlite3_mutex_held(pCtx->pOut->db->mutex) );
+  assert( sqlite3_mutex_held(pCtx->s.db->mutex) );
   pCtx->isError = SQLITE_ERROR;
-  pCtx->fErrorOrAux = 1;
-  sqlite3VdbeMemSetStr(pCtx->pOut, z, n, SQLITE_UTF8, SQLITE_TRANSIENT);
+  sqlite3VdbeMemSetStr(&pCtx->s, z, n, SQLITE_UTF8, SQLITE_TRANSIENT);
 }
 #ifndef SQLITE_OMIT_UTF16
 void sqlite3_result_error16(sqlite3_context *pCtx, const void *z, int n){
-  assert( sqlite3_mutex_held(pCtx->pOut->db->mutex) );
+  assert( sqlite3_mutex_held(pCtx->s.db->mutex) );
   pCtx->isError = SQLITE_ERROR;
-  pCtx->fErrorOrAux = 1;
-  sqlite3VdbeMemSetStr(pCtx->pOut, z, n, SQLITE_UTF16NATIVE, SQLITE_TRANSIENT);
+  sqlite3VdbeMemSetStr(&pCtx->s, z, n, SQLITE_UTF16NATIVE, SQLITE_TRANSIENT);
 }
 #endif
 void sqlite3_result_int(sqlite3_context *pCtx, int iVal){
-  assert( sqlite3_mutex_held(pCtx->pOut->db->mutex) );
-  sqlite3VdbeMemSetInt64(pCtx->pOut, (i64)iVal);
+  assert( sqlite3_mutex_held(pCtx->s.db->mutex) );
+  sqlite3VdbeMemSetInt64(&pCtx->s, (i64)iVal);
 }
 void sqlite3_result_int64(sqlite3_context *pCtx, i64 iVal){
-  assert( sqlite3_mutex_held(pCtx->pOut->db->mutex) );
-  sqlite3VdbeMemSetInt64(pCtx->pOut, iVal);
+  assert( sqlite3_mutex_held(pCtx->s.db->mutex) );
+  sqlite3VdbeMemSetInt64(&pCtx->s, iVal);
 }
 void sqlite3_result_null(sqlite3_context *pCtx){
-  assert( sqlite3_mutex_held(pCtx->pOut->db->mutex) );
-  sqlite3VdbeMemSetNull(pCtx->pOut);
-}
-void sqlite3_result_pointer(
-  sqlite3_context *pCtx,
-  void *pPtr,
-  const char *zPType,
-  void (*xDestructor)(void*)
-){
-  Mem *pOut = pCtx->pOut;
-  assert( sqlite3_mutex_held(pOut->db->mutex) );
-  sqlite3VdbeMemRelease(pOut);
-  pOut->flags = MEM_Null;
-  sqlite3VdbeMemSetPointer(pOut, pPtr, zPType, xDestructor);
-}
-void sqlite3_result_subtype(sqlite3_context *pCtx, unsigned int eSubtype){
-  Mem *pOut = pCtx->pOut;
-  assert( sqlite3_mutex_held(pOut->db->mutex) );
-  pOut->eSubtype = eSubtype & 0xff;
-  pOut->flags |= MEM_Subtype;
+  assert( sqlite3_mutex_held(pCtx->s.db->mutex) );
+  sqlite3VdbeMemSetNull(&pCtx->s);
 }
 void sqlite3_result_text(
   sqlite3_context *pCtx, 
   const char *z, 
   int n,
   void (*xDel)(void *)
 ){
-  assert( sqlite3_mutex_held(pCtx->pOut->db->mutex) );
-  setResultStrOrError(pCtx, z, n, SQLITE_UTF8, xDel);
-}
-void sqlite3_result_text64(
-  sqlite3_context *pCtx, 
-  const char *z, 
-  sqlite3_uint64 n,
-  void (*xDel)(void *),
-  unsigned char enc
-){
-  assert( sqlite3_mutex_held(pCtx->pOut->db->mutex) );
-  assert( xDel!=SQLITE_DYNAMIC );
-  if( enc==SQLITE_UTF16 ) enc = SQLITE_UTF16NATIVE;
-  if( n>0x7fffffff ){
-    (void)invokeValueDestructor(z, xDel, pCtx);
-  }else{
-    setResultStrOrError(pCtx, z, (int)n, enc, xDel);
-  }
+  assert( sqlite3_mutex_held(pCtx->s.db->mutex) );
+  sqlite3VdbeMemSetStr(&pCtx->s, z, n, SQLITE_UTF8, xDel);
 }
 #ifndef SQLITE_OMIT_UTF16
 void sqlite3_result_text16(
   sqlite3_context *pCtx, 
   const void *z, 
   int n, 
   void (*xDel)(void *)
 ){
-  assert( sqlite3_mutex_held(pCtx->pOut->db->mutex) );
-  setResultStrOrError(pCtx, z, n, SQLITE_UTF16NATIVE, xDel);
+  assert( sqlite3_mutex_held(pCtx->s.db->mutex) );
+  sqlite3VdbeMemSetStr(&pCtx->s, z, n, SQLITE_UTF16NATIVE, xDel);
 }
 void sqlite3_result_text16be(
   sqlite3_context *pCtx, 
   const void *z, 
   int n, 
   void (*xDel)(void *)
 ){
-  assert( sqlite3_mutex_held(pCtx->pOut->db->mutex) );
-  setResultStrOrError(pCtx, z, n, SQLITE_UTF16BE, xDel);
+  assert( sqlite3_mutex_held(pCtx->s.db->mutex) );
+  sqlite3VdbeMemSetStr(&pCtx->s, z, n, SQLITE_UTF16BE, xDel);
 }
 void sqlite3_result_text16le(
   sqlite3_context *pCtx, 
   const void *z, 
   int n, 
   void (*xDel)(void *)
 ){
-  assert( sqlite3_mutex_held(pCtx->pOut->db->mutex) );
-  setResultStrOrError(pCtx, z, n, SQLITE_UTF16LE, xDel);
+  assert( sqlite3_mutex_held(pCtx->s.db->mutex) );
+  sqlite3VdbeMemSetStr(&pCtx->s, z, n, SQLITE_UTF16LE, xDel);
 }
 #endif /* SQLITE_OMIT_UTF16 */
 void sqlite3_result_value(sqlite3_context *pCtx, sqlite3_value *pValue){
-  assert( sqlite3_mutex_held(pCtx->pOut->db->mutex) );
-  sqlite3VdbeMemCopy(pCtx->pOut, pValue);
+  assert( sqlite3_mutex_held(pCtx->s.db->mutex) );
+  sqlite3VdbeMemCopy(&pCtx->s, pValue);
 }
 void sqlite3_result_zeroblob(sqlite3_context *pCtx, int n){
-  assert( sqlite3_mutex_held(pCtx->pOut->db->mutex) );
-  sqlite3VdbeMemSetZeroBlob(pCtx->pOut, n);
-}
-int sqlite3_result_zeroblob64(sqlite3_context *pCtx, u64 n){
-  Mem *pOut = pCtx->pOut;
-  assert( sqlite3_mutex_held(pOut->db->mutex) );
-  if( n>(u64)pOut->db->aLimit[SQLITE_LIMIT_LENGTH] ){
-    return SQLITE_TOOBIG;
-  }
-  sqlite3VdbeMemSetZeroBlob(pCtx->pOut, (int)n);
-  return SQLITE_OK;
+  assert( sqlite3_mutex_held(pCtx->s.db->mutex) );
+  sqlite3VdbeMemSetZeroBlob(&pCtx->s, n);
 }
 void sqlite3_result_error_code(sqlite3_context *pCtx, int errCode){
   pCtx->isError = errCode;
-  pCtx->fErrorOrAux = 1;
-#ifdef SQLITE_DEBUG
-  if( pCtx->pVdbe ) pCtx->pVdbe->rcApp = errCode;
-#endif
-  if( pCtx->pOut->flags & MEM_Null ){
-    sqlite3VdbeMemSetStr(pCtx->pOut, sqlite3ErrStr(errCode), -1, 
+  if( pCtx->s.flags & MEM_Null ){
+    sqlite3VdbeMemSetStr(&pCtx->s, sqlite3ErrStr(errCode), -1, 
                          SQLITE_UTF8, SQLITE_STATIC);
   }
 }
 
 /* Force an SQLITE_TOOBIG error. */
 void sqlite3_result_error_toobig(sqlite3_context *pCtx){
-  assert( sqlite3_mutex_held(pCtx->pOut->db->mutex) );
+  assert( sqlite3_mutex_held(pCtx->s.db->mutex) );
   pCtx->isError = SQLITE_TOOBIG;
-  pCtx->fErrorOrAux = 1;
-  sqlite3VdbeMemSetStr(pCtx->pOut, "string or blob too big", -1, 
+  sqlite3VdbeMemSetStr(&pCtx->s, "string or blob too big", -1, 
                        SQLITE_UTF8, SQLITE_STATIC);
 }
 
 /* An SQLITE_NOMEM error. */
 void sqlite3_result_error_nomem(sqlite3_context *pCtx){
-  assert( sqlite3_mutex_held(pCtx->pOut->db->mutex) );
-  sqlite3VdbeMemSetNull(pCtx->pOut);
-  pCtx->isError = SQLITE_NOMEM_BKPT;
-  pCtx->fErrorOrAux = 1;
-  sqlite3OomFault(pCtx->pOut->db);
-}
-
-/*
-** This function is called after a transaction has been committed. It 
-** invokes callbacks registered with sqlite3_wal_hook() as required.
-*/
-static int doWalCallbacks(sqlite3 *db){
-  int rc = SQLITE_OK;
-#ifndef SQLITE_OMIT_WAL
-  int i;
-  for(i=0; i<db->nDb; i++){
-    Btree *pBt = db->aDb[i].pBt;
-    if( pBt ){
-      int nEntry;
-      sqlite3BtreeEnter(pBt);
-      nEntry = sqlite3PagerWalCallback(sqlite3BtreePager(pBt));
-      sqlite3BtreeLeave(pBt);
-      if( nEntry>0 && db->xWalCallback && rc==SQLITE_OK ){
-        rc = db->xWalCallback(db->pWalArg, db, db->aDb[i].zDbSName, nEntry);
-      }
-    }
-  }
-#endif
-  return rc;
+  assert( sqlite3_mutex_held(pCtx->s.db->mutex) );
+  sqlite3VdbeMemSetNull(&pCtx->s);
+  pCtx->isError = SQLITE_NOMEM;
+  pCtx->s.db->mallocFailed = 1;
 }
 
-
 /*
 ** Execute the statement pStmt, either until a row of data is ready, the
 ** statement is completely executed or an error occurs.
 **
 ** This routine implements the bulk of the logic behind the sqlite_step()
 ** API.  The only thing omitted is the automatic recompile if a 
