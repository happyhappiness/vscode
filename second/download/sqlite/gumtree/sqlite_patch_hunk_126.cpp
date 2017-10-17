   return rc;
 #endif
 }
 
 /*
 ** Make sure pMem->z points to a writable allocation of at least 
-** min(n,32) bytes.
+** n bytes.
 **
-** If the bPreserve argument is true, then copy of the content of
-** pMem->z into the new allocation.  pMem must be either a string or
-** blob if bPreserve is true.  If bPreserve is false, any prior content
-** in pMem->z is discarded.
-*/
-SQLITE_NOINLINE int sqlite3VdbeMemGrow(Mem *pMem, int n, int bPreserve){
-  assert( sqlite3VdbeCheckMemInvariants(pMem) );
+** If the memory cell currently contains string or blob data
+** and the third argument passed to this function is true, the 
+** current content of the cell is preserved. Otherwise, it may
+** be discarded.  
+**
+** This function sets the MEM_Dyn flag and clears any xDel callback.
+** It also clears MEM_Ephem and MEM_Static. If the preserve flag is 
+** not set, Mem.n is zeroed.
+*/
+int sqlite3VdbeMemGrow(Mem *pMem, int n, int preserve){
+  assert( 1 >=
+    ((pMem->zMalloc && pMem->zMalloc==pMem->z) ? 1 : 0) +
+    (((pMem->flags&MEM_Dyn)&&pMem->xDel) ? 1 : 0) + 
+    ((pMem->flags&MEM_Ephem) ? 1 : 0) + 
+    ((pMem->flags&MEM_Static) ? 1 : 0)
+  );
   assert( (pMem->flags&MEM_RowSet)==0 );
-  testcase( pMem->db==0 );
-
-  /* If the bPreserve flag is set to true, then the memory cell must already
-  ** contain a valid string or blob value.  */
-  assert( bPreserve==0 || pMem->flags&(MEM_Blob|MEM_Str) );
-  testcase( bPreserve && pMem->z==0 );
 
-  assert( pMem->szMalloc==0
-       || pMem->szMalloc==sqlite3DbMallocSize(pMem->db, pMem->zMalloc) );
   if( n<32 ) n = 32;
-  if( pMem->szMalloc>0 && bPreserve && pMem->z==pMem->zMalloc ){
-    pMem->z = pMem->zMalloc = sqlite3DbReallocOrFree(pMem->db, pMem->z, n);
-    bPreserve = 0;
-  }else{
-    if( pMem->szMalloc>0 ) sqlite3DbFreeNN(pMem->db, pMem->zMalloc);
-    pMem->zMalloc = sqlite3DbMallocRaw(pMem->db, n);
-  }
-  if( pMem->zMalloc==0 ){
-    sqlite3VdbeMemSetNull(pMem);
-    pMem->z = 0;
-    pMem->szMalloc = 0;
-    return SQLITE_NOMEM_BKPT;
-  }else{
-    pMem->szMalloc = sqlite3DbMallocSize(pMem->db, pMem->zMalloc);
+  if( sqlite3DbMallocSize(pMem->db, pMem->zMalloc)<n ){
+    if( preserve && pMem->z==pMem->zMalloc ){
+      pMem->z = pMem->zMalloc = sqlite3DbReallocOrFree(pMem->db, pMem->z, n);
+      preserve = 0;
+    }else{
+      sqlite3DbFree(pMem->db, pMem->zMalloc);
+      pMem->zMalloc = sqlite3DbMallocRaw(pMem->db, n);
+    }
   }
 
-  if( bPreserve && pMem->z ){
-    assert( pMem->z!=pMem->zMalloc );
+  if( preserve && pMem->z && pMem->zMalloc && pMem->z!=pMem->zMalloc ){
     memcpy(pMem->zMalloc, pMem->z, pMem->n);
   }
-  if( (pMem->flags&MEM_Dyn)!=0 ){
-    assert( pMem->xDel!=0 && pMem->xDel!=SQLITE_DYNAMIC );
+  if( pMem->flags&MEM_Dyn && pMem->xDel ){
     pMem->xDel((void *)(pMem->z));
   }
 
   pMem->z = pMem->zMalloc;
-  pMem->flags &= ~(MEM_Dyn|MEM_Ephem|MEM_Static);
-  return SQLITE_OK;
-}
-
-/*
-** Change the pMem->zMalloc allocation to be at least szNew bytes.
-** If pMem->zMalloc already meets or exceeds the requested size, this
-** routine is a no-op.
-**
-** Any prior string or blob content in the pMem object may be discarded.
-** The pMem->xDel destructor is called, if it exists.  Though MEM_Str
-** and MEM_Blob values may be discarded, MEM_Int, MEM_Real, and MEM_Null
-** values are preserved.
-**
-** Return SQLITE_OK on success or an error code (probably SQLITE_NOMEM)
-** if unable to complete the resizing.
-*/
-int sqlite3VdbeMemClearAndResize(Mem *pMem, int szNew){
-  assert( szNew>0 );
-  assert( (pMem->flags & MEM_Dyn)==0 || pMem->szMalloc==0 );
-  if( pMem->szMalloc<szNew ){
-    return sqlite3VdbeMemGrow(pMem, szNew, 0);
-  }
-  assert( (pMem->flags & MEM_Dyn)==0 );
-  pMem->z = pMem->zMalloc;
-  pMem->flags &= (MEM_Null|MEM_Int|MEM_Real);
-  return SQLITE_OK;
-}
-
-/*
-** It is already known that pMem contains an unterminated string.
-** Add the zero terminator.
-*/
-static SQLITE_NOINLINE int vdbeMemAddTerminator(Mem *pMem){
-  if( sqlite3VdbeMemGrow(pMem, pMem->n+2, 1) ){
-    return SQLITE_NOMEM_BKPT;
+  if( pMem->z==0 ){
+    pMem->flags = MEM_Null;
+  }else{
+    pMem->flags &= ~(MEM_Ephem|MEM_Static);
   }
-  pMem->z[pMem->n] = 0;
-  pMem->z[pMem->n+1] = 0;
-  pMem->flags |= MEM_Term;
-  return SQLITE_OK;
+  pMem->xDel = 0;
+  return (pMem->z ? SQLITE_OK : SQLITE_NOMEM);
 }
 
 /*
-** Change pMem so that its MEM_Str or MEM_Blob value is stored in
-** MEM.zMalloc, where it can be safely written.
+** Make the given Mem object MEM_Dyn.  In other words, make it so
+** that any TEXT or BLOB content is stored in memory obtained from
+** malloc().  In this way, we know that the memory is safe to be
+** overwritten or altered.
 **
 ** Return SQLITE_OK on success or SQLITE_NOMEM if malloc fails.
 */
 int sqlite3VdbeMemMakeWriteable(Mem *pMem){
+  int f;
   assert( pMem->db==0 || sqlite3_mutex_held(pMem->db->mutex) );
   assert( (pMem->flags&MEM_RowSet)==0 );
-  if( (pMem->flags & (MEM_Str|MEM_Blob))!=0 ){
-    if( ExpandBlob(pMem) ) return SQLITE_NOMEM;
-    if( pMem->szMalloc==0 || pMem->z!=pMem->zMalloc ){
-      int rc = vdbeMemAddTerminator(pMem);
-      if( rc ) return rc;
-    }
+  expandBlob(pMem);
+  f = pMem->flags;
+  if( (f&(MEM_Str|MEM_Blob)) && pMem->z!=pMem->zMalloc ){
+    if( sqlite3VdbeMemGrow(pMem, pMem->n + 2, 1) ){
+      return SQLITE_NOMEM;
+    }
+    pMem->z[pMem->n] = 0;
+    pMem->z[pMem->n+1] = 0;
+    pMem->flags |= MEM_Term;
   }
-  pMem->flags &= ~MEM_Ephem;
-#ifdef SQLITE_DEBUG
-  pMem->pScopyFrom = 0;
-#endif
 
   return SQLITE_OK;
 }
 
 /*
 ** If the given Mem* has a zero-filled tail, turn it into an ordinary
 ** blob stored in dynamically allocated space.
 */
 #ifndef SQLITE_OMIT_INCRBLOB
 int sqlite3VdbeMemExpandBlob(Mem *pMem){
-  int nByte;
-  assert( pMem->flags & MEM_Zero );
-  assert( pMem->flags&MEM_Blob );
-  assert( (pMem->flags&MEM_RowSet)==0 );
-  assert( pMem->db==0 || sqlite3_mutex_held(pMem->db->mutex) );
+  if( pMem->flags & MEM_Zero ){
+    int nByte;
+    assert( pMem->flags&MEM_Blob );
+    assert( (pMem->flags&MEM_RowSet)==0 );
+    assert( pMem->db==0 || sqlite3_mutex_held(pMem->db->mutex) );
 
-  /* Set nByte to the number of bytes required to store the expanded blob. */
-  nByte = pMem->n + pMem->u.nZero;
-  if( nByte<=0 ){
-    nByte = 1;
-  }
-  if( sqlite3VdbeMemGrow(pMem, nByte, 1) ){
-    return SQLITE_NOMEM_BKPT;
-  }
+    /* Set nByte to the number of bytes required to store the expanded blob. */
+    nByte = pMem->n + pMem->u.nZero;
+    if( nByte<=0 ){
+      nByte = 1;
+    }
+    if( sqlite3VdbeMemGrow(pMem, nByte, 1) ){
+      return SQLITE_NOMEM;
+    }
 
-  memset(&pMem->z[pMem->n], 0, pMem->u.nZero);
-  pMem->n += pMem->u.nZero;
-  pMem->flags &= ~(MEM_Zero|MEM_Term);
+    memset(&pMem->z[pMem->n], 0, pMem->u.nZero);
+    pMem->n += pMem->u.nZero;
+    pMem->flags &= ~(MEM_Zero|MEM_Term);
+  }
   return SQLITE_OK;
 }
 #endif
 
+
 /*
 ** Make sure the given Mem is \u0000 terminated.
 */
 int sqlite3VdbeMemNulTerminate(Mem *pMem){
   assert( pMem->db==0 || sqlite3_mutex_held(pMem->db->mutex) );
-  testcase( (pMem->flags & (MEM_Term|MEM_Str))==(MEM_Term|MEM_Str) );
-  testcase( (pMem->flags & (MEM_Term|MEM_Str))==0 );
-  if( (pMem->flags & (MEM_Term|MEM_Str))!=MEM_Str ){
+  if( (pMem->flags & MEM_Term)!=0 || (pMem->flags & MEM_Str)==0 ){
     return SQLITE_OK;   /* Nothing to do */
-  }else{
-    return vdbeMemAddTerminator(pMem);
   }
+  if( sqlite3VdbeMemGrow(pMem, pMem->n+2, 1) ){
+    return SQLITE_NOMEM;
+  }
+  pMem->z[pMem->n] = 0;
+  pMem->z[pMem->n+1] = 0;
+  pMem->flags |= MEM_Term;
+  return SQLITE_OK;
 }
 
 /*
 ** Add MEM_Str to the set of representations for the given Mem.  Numbers
 ** are converted using sqlite3_snprintf().  Converting a BLOB to a string
 ** is a no-op.
 **
-** Existing representations MEM_Int and MEM_Real are invalidated if
-** bForce is true but are retained if bForce is false.
+** Existing representations MEM_Int and MEM_Real are *not* invalidated.
 **
 ** A MEM_Null value will never be passed to this function. This function is
 ** used for converting values to text for returning to the user (i.e. via
 ** sqlite3_value_text()), or for ensuring that values to be used as btree
 ** keys are strings. In the former case a NULL pointer is returned the
-** user and the latter is an internal programming error.
+** user and the later is an internal programming error.
 */
-int sqlite3VdbeMemStringify(Mem *pMem, u8 enc, u8 bForce){
+int sqlite3VdbeMemStringify(Mem *pMem, int enc){
+  int rc = SQLITE_OK;
   int fg = pMem->flags;
   const int nByte = 32;
 
   assert( pMem->db==0 || sqlite3_mutex_held(pMem->db->mutex) );
   assert( !(fg&MEM_Zero) );
   assert( !(fg&(MEM_Str|MEM_Blob)) );
   assert( fg&(MEM_Int|MEM_Real) );
   assert( (pMem->flags&MEM_RowSet)==0 );
   assert( EIGHT_BYTE_ALIGNMENT(pMem) );
 
 
-  if( sqlite3VdbeMemClearAndResize(pMem, nByte) ){
-    pMem->enc = 0;
-    return SQLITE_NOMEM_BKPT;
+  if( sqlite3VdbeMemGrow(pMem, nByte, 0) ){
+    return SQLITE_NOMEM;
   }
 
-  /* For a Real or Integer, use sqlite3_snprintf() to produce the UTF-8
+  /* For a Real or Integer, use sqlite3_mprintf() to produce the UTF-8
   ** string representation of the value. Then, if the required encoding
   ** is UTF-16le or UTF-16be do a translation.
   ** 
   ** FIX ME: It would be better if sqlite3_snprintf() could do UTF-16.
   */
   if( fg & MEM_Int ){
     sqlite3_snprintf(nByte, pMem->z, "%lld", pMem->u.i);
   }else{
     assert( fg & MEM_Real );
-    sqlite3_snprintf(nByte, pMem->z, "%!.15g", pMem->u.r);
+    sqlite3_snprintf(nByte, pMem->z, "%!.15g", pMem->r);
   }
   pMem->n = sqlite3Strlen30(pMem->z);
   pMem->enc = SQLITE_UTF8;
   pMem->flags |= MEM_Str|MEM_Term;
-  if( bForce ) pMem->flags &= ~(MEM_Int|MEM_Real);
   sqlite3VdbeChangeEncoding(pMem, enc);
-  return SQLITE_OK;
+  return rc;
 }
 
 /*
 ** Memory cell pMem contains the context of an aggregate function.
 ** This routine calls the finalize method for that function.  The
 ** result of the aggregate is stored back into pMem.
 **
 ** Return SQLITE_ERROR if the finalizer reports an error.  SQLITE_OK
 ** otherwise.
 */
 int sqlite3VdbeMemFinalize(Mem *pMem, FuncDef *pFunc){
   int rc = SQLITE_OK;
-  if( ALWAYS(pFunc && pFunc->xFinalize) ){
+  if( pFunc && pFunc->xFinalize ){
     sqlite3_context ctx;
-    Mem t;
     assert( (pMem->flags & MEM_Null)!=0 || pFunc==pMem->u.pDef );
     assert( pMem->db==0 || sqlite3_mutex_held(pMem->db->mutex) );
     memset(&ctx, 0, sizeof(ctx));
-    memset(&t, 0, sizeof(t));
-    t.flags = MEM_Null;
-    t.db = pMem->db;
-    ctx.pOut = &t;
+    ctx.s.flags = MEM_Null;
+    ctx.s.db = pMem->db;
     ctx.pMem = pMem;
     ctx.pFunc = pFunc;
-    pFunc->xFinalize(&ctx); /* IMP: R-24505-23230 */
-    assert( (pMem->flags & MEM_Dyn)==0 );
-    if( pMem->szMalloc>0 ) sqlite3DbFreeNN(pMem->db, pMem->zMalloc);
-    memcpy(pMem, &t, sizeof(t));
-    rc = ctx.isError;
+    pFunc->xFinalize(&ctx);
+    assert( 0==(pMem->flags&MEM_Dyn) && !pMem->xDel );
+    sqlite3DbFree(pMem->db, pMem->zMalloc);
+    memcpy(pMem, &ctx.s, sizeof(ctx.s));
+    rc = (ctx.isError?SQLITE_ERROR:SQLITE_OK);
   }
   return rc;
 }
 
 /*
-** If the memory cell contains a value that must be freed by
-** invoking the external callback in Mem.xDel, then this routine
-** will free that value.  It also sets Mem.flags to MEM_Null.
-**
-** This is a helper routine for sqlite3VdbeMemSetNull() and
-** for sqlite3VdbeMemRelease().  Use those other routines as the
-** entry point for releasing Mem resources.
+** If the memory cell contains a string value that must be freed by
+** invoking an external callback, free it now. Calling this function
+** does not free any Mem.zMalloc buffer.
 */
-static SQLITE_NOINLINE void vdbeMemClearExternAndSetNull(Mem *p){
+void sqlite3VdbeMemReleaseExternal(Mem *p){
   assert( p->db==0 || sqlite3_mutex_held(p->db->mutex) );
-  assert( VdbeMemDynamic(p) );
-  if( p->flags&MEM_Agg ){
-    sqlite3VdbeMemFinalize(p, p->u.pDef);
-    assert( (p->flags & MEM_Agg)==0 );
-    testcase( p->flags & MEM_Dyn );
-  }
-  if( p->flags&MEM_Dyn ){
-    assert( (p->flags&MEM_RowSet)==0 );
-    assert( p->xDel!=SQLITE_DYNAMIC && p->xDel!=0 );
-    p->xDel((void *)p->z);
-  }else if( p->flags&MEM_RowSet ){
-    sqlite3RowSetClear(p->u.pRowSet);
-  }else if( p->flags&MEM_Frame ){
-    VdbeFrame *pFrame = p->u.pFrame;
-    pFrame->pParent = pFrame->v->pDelFrame;
-    pFrame->v->pDelFrame = pFrame;
-  }
-  p->flags = MEM_Null;
-}
-
-/*
-** Release memory held by the Mem p, both external memory cleared
-** by p->xDel and memory in p->zMalloc.
-**
-** This is a helper routine invoked by sqlite3VdbeMemRelease() in
-** the unusual case where there really is memory in p that needs
-** to be freed.
-*/
-static SQLITE_NOINLINE void vdbeMemClear(Mem *p){
-  if( VdbeMemDynamic(p) ){
-    vdbeMemClearExternAndSetNull(p);
-  }
-  if( p->szMalloc ){
-    sqlite3DbFreeNN(p->db, p->zMalloc);
-    p->szMalloc = 0;
+  if( p->flags&(MEM_Agg|MEM_Dyn|MEM_RowSet) ){
+    if( p->flags&MEM_Agg ){
+      sqlite3VdbeMemFinalize(p, p->u.pDef);
+      assert( (p->flags & MEM_Agg)==0 );
+      sqlite3VdbeMemRelease(p);
+    }else if( p->flags&MEM_Dyn && p->xDel ){
+      assert( (p->flags&MEM_RowSet)==0 );
+      p->xDel((void *)p->z);
+      p->xDel = 0;
+    }else if( p->flags&MEM_RowSet ){
+      sqlite3RowSetClear(p->u.pRowSet);
+    }
   }
-  p->z = 0;
 }
 
 /*
-** Release any memory resources held by the Mem.  Both the memory that is
-** free by Mem.xDel and the Mem.zMalloc allocation are freed.
-**
-** Use this routine prior to clean up prior to abandoning a Mem, or to
-** reset a Mem back to its minimum memory utilization.
-**
-** Use sqlite3VdbeMemSetNull() to release just the Mem.xDel space
-** prior to inserting new content into the Mem.
+** Release any memory held by the Mem. This may leave the Mem in an
+** inconsistent state, for example with (Mem.z==0) and
+** (Mem.type==SQLITE_TEXT).
 */
 void sqlite3VdbeMemRelease(Mem *p){
-  assert( sqlite3VdbeCheckMemInvariants(p) );
-  if( VdbeMemDynamic(p) || p->szMalloc ){
-    vdbeMemClear(p);
-  }
+  sqlite3VdbeMemReleaseExternal(p);
+  sqlite3DbFree(p->db, p->zMalloc);
+  p->z = 0;
+  p->zMalloc = 0;
+  p->xDel = 0;
 }
 
 /*
 ** Convert a 64-bit IEEE double into a 64-bit signed integer.
-** If the double is out of range of a 64-bit signed integer then
-** return the closest available 64-bit signed integer.
+** If the double is too large, return 0x8000000000000000.
+**
+** Most systems appear to do this simply by assigning
+** variables and without the extra range tests.  But
+** there are reports that windows throws an expection
+** if the floating point value is out of range. (See ticket #2880.)
+** Because we do not completely understand the problem, we will
+** take the conservative approach and always do range tests
+** before attempting the conversion.
 */
-static SQLITE_NOINLINE i64 doubleToInt64(double r){
-#ifdef SQLITE_OMIT_FLOATING_POINT
-  /* When floating-point is omitted, double and int64 are the same thing */
-  return r;
-#else
+static i64 doubleToInt64(double r){
   /*
   ** Many compilers we encounter do not define constants for the
   ** minimum and maximum 64-bit integers, or they define them
   ** inconsistently.  And many do not understand the "LL" notation.
   ** So we define our own static constants here using nothing
   ** larger than a 32-bit integer constant.
   */
   static const i64 maxInt = LARGEST_INT64;
   static const i64 minInt = SMALLEST_INT64;
 
-  if( r<=(double)minInt ){
+  if( r<(double)minInt ){
+    return minInt;
+  }else if( r>(double)maxInt ){
+    /* minInt is correct here - not maxInt.  It turns out that assigning
+    ** a very large positive number to an integer results in a very large
+    ** negative integer.  This makes no sense, but it is what x86 hardware
+    ** does so for compatibility we will do the same in software. */
     return minInt;
-  }else if( r>=(double)maxInt ){
-    return maxInt;
   }else{
     return (i64)r;
   }
-#endif
 }
 
 /*
 ** Return some kind of integer value which is the best we can do
 ** at representing the value that *pMem describes as an integer.
 ** If pMem is an integer, then the value is exact.  If pMem is
 ** a floating-point then the value returned is the integer part.
 ** If pMem is a string or blob, then we make an attempt to convert
-** it into an integer and return that.  If pMem represents an
+** it into a integer and return that.  If pMem represents an
 ** an SQL-NULL value, return 0.
 **
 ** If pMem represents a string value, its encoding might be changed.
 */
-static SQLITE_NOINLINE i64 memIntValue(Mem *pMem){
-  i64 value = 0;
-  sqlite3Atoi64(pMem->z, &value, pMem->n, pMem->enc);
-  return value;
-}
 i64 sqlite3VdbeIntValue(Mem *pMem){
   int flags;
   assert( pMem->db==0 || sqlite3_mutex_held(pMem->db->mutex) );
   assert( EIGHT_BYTE_ALIGNMENT(pMem) );
   flags = pMem->flags;
   if( flags & MEM_Int ){
     return pMem->u.i;
   }else if( flags & MEM_Real ){
-    return doubleToInt64(pMem->u.r);
+    return doubleToInt64(pMem->r);
   }else if( flags & (MEM_Str|MEM_Blob) ){
-    assert( pMem->z || pMem->n==0 );
-    return memIntValue(pMem);
+    i64 value;
+    pMem->flags |= MEM_Str;
+    if( sqlite3VdbeChangeEncoding(pMem, SQLITE_UTF8)
+       || sqlite3VdbeMemNulTerminate(pMem) ){
+      return 0;
+    }
+    assert( pMem->z );
+    sqlite3Atoi64(pMem->z, &value);
+    return value;
   }else{
     return 0;
   }
 }
 
 /*
 ** Return the best representation of pMem that we can get into a
 ** double.  If pMem is already a double or an integer, return its
 ** value.  If it is a string or blob, try to convert it to a double.
 ** If it is a NULL, return 0.0.
 */
-static SQLITE_NOINLINE double memRealValue(Mem *pMem){
-  /* (double)0 In case of SQLITE_OMIT_FLOATING_POINT... */
-  double val = (double)0;
-  sqlite3AtoF(pMem->z, &val, pMem->n, pMem->enc);
-  return val;
-}
 double sqlite3VdbeRealValue(Mem *pMem){
   assert( pMem->db==0 || sqlite3_mutex_held(pMem->db->mutex) );
   assert( EIGHT_BYTE_ALIGNMENT(pMem) );
   if( pMem->flags & MEM_Real ){
-    return pMem->u.r;
+    return pMem->r;
   }else if( pMem->flags & MEM_Int ){
     return (double)pMem->u.i;
   }else if( pMem->flags & (MEM_Str|MEM_Blob) ){
-    return memRealValue(pMem);
+    /* (double)0 In case of SQLITE_OMIT_FLOATING_POINT... */
+    double val = (double)0;
+    pMem->flags |= MEM_Str;
+    if( sqlite3VdbeChangeEncoding(pMem, SQLITE_UTF8)
+       || sqlite3VdbeMemNulTerminate(pMem) ){
+      /* (double)0 In case of SQLITE_OMIT_FLOATING_POINT... */
+      return (double)0;
+    }
+    assert( pMem->z );
+    sqlite3AtoF(pMem->z, &val);
+    return val;
   }else{
     /* (double)0 In case of SQLITE_OMIT_FLOATING_POINT... */
     return (double)0;
   }
 }
 
 /*
 ** The MEM structure is already a MEM_Real.  Try to also make it a
 ** MEM_Int if we can.
 */
 void sqlite3VdbeIntegerAffinity(Mem *pMem){
-  i64 ix;
   assert( pMem->flags & MEM_Real );
   assert( (pMem->flags & MEM_RowSet)==0 );
   assert( pMem->db==0 || sqlite3_mutex_held(pMem->db->mutex) );
   assert( EIGHT_BYTE_ALIGNMENT(pMem) );
 
-  ix = doubleToInt64(pMem->u.r);
-
-  /* Only mark the value as an integer if
-  **
-  **    (1) the round-trip conversion real->int->real is a no-op, and
-  **    (2) The integer is neither the largest nor the smallest
-  **        possible integer (ticket #3922)
-  **
-  ** The second and third terms in the following conditional enforces
-  ** the second condition under the assumption that addition overflow causes
-  ** values to wrap around.
-  */
-  if( pMem->u.r==ix && ix>SMALLEST_INT64 && ix<LARGEST_INT64 ){
-    pMem->u.i = ix;
-    MemSetTypeFlag(pMem, MEM_Int);
+  pMem->u.i = doubleToInt64(pMem->r);
+  if( pMem->r==(double)pMem->u.i ){
+    pMem->flags |= MEM_Int;
   }
 }
 
 /*
 ** Convert pMem to type integer.  Invalidate any prior representations.
 */
