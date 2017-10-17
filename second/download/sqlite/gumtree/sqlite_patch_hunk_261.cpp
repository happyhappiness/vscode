     if( flags&MEM_Term ){
       nAlloc += (enc==SQLITE_UTF8?1:2);
     }
     if( nByte>iLimit ){
       return SQLITE_TOOBIG;
     }
-    if( sqlite3VdbeMemGrow(pMem, nAlloc, 0) ){
-      return SQLITE_NOMEM;
+    testcase( nAlloc==0 );
+    testcase( nAlloc==31 );
+    testcase( nAlloc==32 );
+    if( sqlite3VdbeMemClearAndResize(pMem, MAX(nAlloc,32)) ){
+      return SQLITE_NOMEM_BKPT;
     }
     memcpy(pMem->z, z, nAlloc);
   }else if( xDel==SQLITE_DYNAMIC ){
     sqlite3VdbeMemRelease(pMem);
     pMem->zMalloc = pMem->z = (char *)z;
-    pMem->xDel = 0;
+    pMem->szMalloc = sqlite3DbMallocSize(pMem->db, pMem->zMalloc);
   }else{
     sqlite3VdbeMemRelease(pMem);
     pMem->z = (char *)z;
     pMem->xDel = xDel;
     flags |= ((xDel==SQLITE_STATIC)?MEM_Static:MEM_Dyn);
   }
-  if( nByte>iLimit ){
-    return SQLITE_TOOBIG;
-  }
 
   pMem->n = nByte;
   pMem->flags = flags;
   pMem->enc = (enc==0 ? SQLITE_UTF8 : enc);
-  pMem->type = (enc==0 ? SQLITE_BLOB : SQLITE_TEXT);
 
 #ifndef SQLITE_OMIT_UTF16
   if( pMem->enc!=SQLITE_UTF8 && sqlite3VdbeMemHandleBom(pMem) ){
-    return SQLITE_NOMEM;
+    return SQLITE_NOMEM_BKPT;
   }
 #endif
 
-  return SQLITE_OK;
-}
-
-/*
-** Compare the values contained by the two memory cells, returning
-** negative, zero or positive if pMem1 is less than, equal to, or greater
-** than pMem2. Sorting order is NULL's first, followed by numbers (integers
-** and reals) sorted numerically, followed by text ordered by the collating
-** sequence pColl and finally blob's ordered by memcmp().
-**
-** Two NULL values are considered equal by this function.
-*/
-int sqlite3MemCompare(const Mem *pMem1, const Mem *pMem2, const CollSeq *pColl){
-  int rc;
-  int f1, f2;
-  int combined_flags;
-
-  /* Interchange pMem1 and pMem2 if the collating sequence specifies
-  ** DESC order.
-  */
-  f1 = pMem1->flags;
-  f2 = pMem2->flags;
-  combined_flags = f1|f2;
-  assert( (combined_flags & MEM_RowSet)==0 );
- 
-  /* If one value is NULL, it is less than the other. If both values
-  ** are NULL, return 0.
-  */
-  if( combined_flags&MEM_Null ){
-    return (f2&MEM_Null) - (f1&MEM_Null);
-  }
-
-  /* If one value is a number and the other is not, the number is less.
-  ** If both are numbers, compare as reals if one is a real, or as integers
-  ** if both values are integers.
-  */
-  if( combined_flags&(MEM_Int|MEM_Real) ){
-    if( !(f1&(MEM_Int|MEM_Real)) ){
-      return 1;
-    }
-    if( !(f2&(MEM_Int|MEM_Real)) ){
-      return -1;
-    }
-    if( (f1 & f2 & MEM_Int)==0 ){
-      double r1, r2;
-      if( (f1&MEM_Real)==0 ){
-        r1 = (double)pMem1->u.i;
-      }else{
-        r1 = pMem1->r;
-      }
-      if( (f2&MEM_Real)==0 ){
-        r2 = (double)pMem2->u.i;
-      }else{
-        r2 = pMem2->r;
-      }
-      if( r1<r2 ) return -1;
-      if( r1>r2 ) return 1;
-      return 0;
-    }else{
-      assert( f1&MEM_Int );
-      assert( f2&MEM_Int );
-      if( pMem1->u.i < pMem2->u.i ) return -1;
-      if( pMem1->u.i > pMem2->u.i ) return 1;
-      return 0;
-    }
+  if( nByte>iLimit ){
+    return SQLITE_TOOBIG;
   }
 
-  /* If one value is a string and the other is a blob, the string is less.
-  ** If both are strings, compare using the collating functions.
-  */
-  if( combined_flags&MEM_Str ){
-    if( (f1 & MEM_Str)==0 ){
-      return 1;
-    }
-    if( (f2 & MEM_Str)==0 ){
-      return -1;
-    }
-
-    assert( pMem1->enc==pMem2->enc );
-    assert( pMem1->enc==SQLITE_UTF8 || 
-            pMem1->enc==SQLITE_UTF16LE || pMem1->enc==SQLITE_UTF16BE );
-
-    /* The collation sequence must be defined at this point, even if
-    ** the user deletes the collation sequence after the vdbe program is
-    ** compiled (this was not always the case).
-    */
-    assert( !pColl || pColl->xCmp );
-
-    if( pColl ){
-      if( pMem1->enc==pColl->enc ){
-        /* The strings are already in the correct encoding.  Call the
-        ** comparison function directly */
-        return pColl->xCmp(pColl->pUser,pMem1->n,pMem1->z,pMem2->n,pMem2->z);
-      }else{
-        const void *v1, *v2;
-        int n1, n2;
-        Mem c1;
-        Mem c2;
-        memset(&c1, 0, sizeof(c1));
-        memset(&c2, 0, sizeof(c2));
-        sqlite3VdbeMemShallowCopy(&c1, pMem1, MEM_Ephem);
-        sqlite3VdbeMemShallowCopy(&c2, pMem2, MEM_Ephem);
-        v1 = sqlite3ValueText((sqlite3_value*)&c1, pColl->enc);
-        n1 = v1==0 ? 0 : c1.n;
-        v2 = sqlite3ValueText((sqlite3_value*)&c2, pColl->enc);
-        n2 = v2==0 ? 0 : c2.n;
-        rc = pColl->xCmp(pColl->pUser, n1, v1, n2, v2);
-        sqlite3VdbeMemRelease(&c1);
-        sqlite3VdbeMemRelease(&c2);
-        return rc;
-      }
-    }
-    /* If a NULL pointer was passed as the collate function, fall through
-    ** to the blob case and use memcmp().  */
-  }
- 
-  /* Both values must be blobs.  Compare using memcmp().  */
-  rc = memcmp(pMem1->z, pMem2->z, (pMem1->n>pMem2->n)?pMem2->n:pMem1->n);
-  if( rc==0 ){
-    rc = pMem1->n - pMem2->n;
-  }
-  return rc;
+  return SQLITE_OK;
 }
 
 /*
 ** Move data out of a btree key or data field and into a Mem structure.
-** The data or key is taken from the entry that pCur is currently pointing
+** The data is payload from the entry that pCur is currently pointing
 ** to.  offset and amt determine what portion of the data or key to retrieve.
-** key is true to get the key or false to get data.  The result is written
-** into the pMem element.
+** The result is written into the pMem element.
 **
-** The pMem structure is assumed to be uninitialized.  Any prior content
-** is overwritten without being freed.
+** The pMem object must have been initialized.  This routine will use
+** pMem->zMalloc to hold the content from the btree, if possible.  New
+** pMem->zMalloc space will be allocated if necessary.  The calling routine
+** is responsible for making sure that the pMem object is eventually
+** destroyed.
 **
 ** If this routine fails for any reason (malloc returns NULL or unable
 ** to read from the disk) then the pMem is left in an inconsistent state.
 */
+static SQLITE_NOINLINE int vdbeMemFromBtreeResize(
+  BtCursor *pCur,   /* Cursor pointing at record to retrieve. */
+  u32 offset,       /* Offset from the start of data to return bytes from. */
+  u32 amt,          /* Number of bytes to return. */
+  Mem *pMem         /* OUT: Return data in this Mem structure. */
+){
+  int rc;
+  pMem->flags = MEM_Null;
+  if( SQLITE_OK==(rc = sqlite3VdbeMemClearAndResize(pMem, amt+1)) ){
+    rc = sqlite3BtreePayload(pCur, offset, amt, pMem->z);
+    if( rc==SQLITE_OK ){
+      pMem->z[amt] = 0;   /* Overrun area used when reading malformed records */
+      pMem->flags = MEM_Blob;
+      pMem->n = (int)amt;
+    }else{
+      sqlite3VdbeMemRelease(pMem);
+    }
+  }
+  return rc;
+}
 int sqlite3VdbeMemFromBtree(
   BtCursor *pCur,   /* Cursor pointing at record to retrieve. */
-  int offset,       /* Offset from the start of data to return bytes from. */
-  int amt,          /* Number of bytes to return. */
-  int key,          /* If true, retrieve from the btree key, not data. */
+  u32 offset,       /* Offset from the start of data to return bytes from. */
+  u32 amt,          /* Number of bytes to return. */
   Mem *pMem         /* OUT: Return data in this Mem structure. */
 ){
   char *zData;        /* Data from the btree layer */
-  int available = 0;  /* Number of bytes available on the local btree page */
+  u32 available = 0;  /* Number of bytes available on the local btree page */
   int rc = SQLITE_OK; /* Return code */
 
+  assert( sqlite3BtreeCursorIsValid(pCur) );
+  assert( !VdbeMemDynamic(pMem) );
+
   /* Note: the calls to BtreeKeyFetch() and DataFetch() below assert() 
   ** that both the BtShared and database handle mutexes are held. */
   assert( (pMem->flags & MEM_RowSet)==0 );
-  if( key ){
-    zData = (char *)sqlite3BtreeKeyFetch(pCur, &available);
-  }else{
-    zData = (char *)sqlite3BtreeDataFetch(pCur, &available);
-  }
+  zData = (char *)sqlite3BtreePayloadFetch(pCur, &available);
   assert( zData!=0 );
 
-  if( offset+amt<=available && ((pMem->flags&MEM_Dyn)==0 || pMem->xDel) ){
-    sqlite3VdbeMemRelease(pMem);
+  if( offset+amt<=available ){
     pMem->z = &zData[offset];
     pMem->flags = MEM_Blob|MEM_Ephem;
-  }else if( SQLITE_OK==(rc = sqlite3VdbeMemGrow(pMem, amt+2, 0)) ){
-    pMem->flags = MEM_Blob|MEM_Dyn|MEM_Term;
-    pMem->enc = 0;
-    pMem->type = SQLITE_BLOB;
-    if( key ){
-      rc = sqlite3BtreeKey(pCur, offset, amt, pMem->z);
-    }else{
-      rc = sqlite3BtreeData(pCur, offset, amt, pMem->z);
-    }
-    pMem->z[amt] = 0;
-    pMem->z[amt+1] = 0;
-    if( rc!=SQLITE_OK ){
-      sqlite3VdbeMemRelease(pMem);
-    }
+    pMem->n = (int)amt;
+  }else{
+    rc = vdbeMemFromBtreeResize(pCur, offset, amt, pMem);
   }
-  pMem->n = amt;
 
   return rc;
 }
 
-/* This function is only available internally, it is not part of the
-** external API. It works in a similar way to sqlite3_value_text(),
-** except the data returned is in the encoding specified by the second
-** parameter, which must be one of SQLITE_UTF16BE, SQLITE_UTF16LE or
-** SQLITE_UTF8.
-**
-** (2006-02-16:)  The enc value can be or-ed with SQLITE_UTF16_ALIGNED.
-** If that is the case, then the result must be aligned on an even byte
-** boundary.
+/*
+** The pVal argument is known to be a value other than NULL.
+** Convert it into a string with encoding enc and return a pointer
+** to a zero-terminated version of that string.
 */
-const void *sqlite3ValueText(sqlite3_value* pVal, u8 enc){
-  if( !pVal ) return 0;
-
+static SQLITE_NOINLINE const void *valueToText(sqlite3_value* pVal, u8 enc){
+  assert( pVal!=0 );
   assert( pVal->db==0 || sqlite3_mutex_held(pVal->db->mutex) );
   assert( (enc&3)==(enc&~SQLITE_UTF16_ALIGNED) );
   assert( (pVal->flags & MEM_RowSet)==0 );
-
-  if( pVal->flags&MEM_Null ){
-    return 0;
-  }
-  assert( (MEM_Blob>>3) == MEM_Str );
-  pVal->flags |= (pVal->flags & MEM_Blob)>>3;
-  expandBlob(pVal);
-  if( pVal->flags&MEM_Str ){
-    sqlite3VdbeChangeEncoding(pVal, enc & ~SQLITE_UTF16_ALIGNED);
+  assert( (pVal->flags & (MEM_Null))==0 );
+  if( pVal->flags & (MEM_Blob|MEM_Str) ){
+    if( ExpandBlob(pVal) ) return 0;
+    pVal->flags |= MEM_Str;
+    if( pVal->enc != (enc & ~SQLITE_UTF16_ALIGNED) ){
+      sqlite3VdbeChangeEncoding(pVal, enc & ~SQLITE_UTF16_ALIGNED);
+    }
     if( (enc & SQLITE_UTF16_ALIGNED)!=0 && 1==(1&SQLITE_PTR_TO_INT(pVal->z)) ){
       assert( (pVal->flags & (MEM_Ephem|MEM_Static))!=0 );
       if( sqlite3VdbeMemMakeWriteable(pVal)!=SQLITE_OK ){
         return 0;
       }
     }
-    sqlite3VdbeMemNulTerminate(pVal);
+    sqlite3VdbeMemNulTerminate(pVal); /* IMP: R-31275-44060 */
   }else{
-    assert( (pVal->flags&MEM_Blob)==0 );
-    sqlite3VdbeMemStringify(pVal, enc);
+    sqlite3VdbeMemStringify(pVal, enc, 0);
     assert( 0==(1&SQLITE_PTR_TO_INT(pVal->z)) );
   }
   assert(pVal->enc==(enc & ~SQLITE_UTF16_ALIGNED) || pVal->db==0
               || pVal->db->mallocFailed );
   if( pVal->enc==(enc & ~SQLITE_UTF16_ALIGNED) ){
     return pVal->z;
   }else{
     return 0;
   }
 }
 
+/* This function is only available internally, it is not part of the
+** external API. It works in a similar way to sqlite3_value_text(),
+** except the data returned is in the encoding specified by the second
+** parameter, which must be one of SQLITE_UTF16BE, SQLITE_UTF16LE or
+** SQLITE_UTF8.
+**
+** (2006-02-16:)  The enc value can be or-ed with SQLITE_UTF16_ALIGNED.
+** If that is the case, then the result must be aligned on an even byte
+** boundary.
+*/
+const void *sqlite3ValueText(sqlite3_value* pVal, u8 enc){
+  if( !pVal ) return 0;
+  assert( pVal->db==0 || sqlite3_mutex_held(pVal->db->mutex) );
+  assert( (enc&3)==(enc&~SQLITE_UTF16_ALIGNED) );
+  assert( (pVal->flags & MEM_RowSet)==0 );
+  if( (pVal->flags&(MEM_Str|MEM_Term))==(MEM_Str|MEM_Term) && pVal->enc==enc ){
+    return pVal->z;
+  }
+  if( pVal->flags&MEM_Null ){
+    return 0;
+  }
+  return valueToText(pVal, enc);
+}
+
 /*
 ** Create a new sqlite3_value object.
 */
 sqlite3_value *sqlite3ValueNew(sqlite3 *db){
   Mem *p = sqlite3DbMallocZero(db, sizeof(*p));
   if( p ){
     p->flags = MEM_Null;
-    p->type = SQLITE_NULL;
     p->db = db;
   }
   return p;
 }
 
 /*
-** Create a new sqlite3_value object, containing the value of pExpr.
+** Context object passed by sqlite3Stat4ProbeSetValue() through to 
+** valueNew(). See comments above valueNew() for details.
+*/
+struct ValueNewStat4Ctx {
+  Parse *pParse;
+  Index *pIdx;
+  UnpackedRecord **ppRec;
+  int iVal;
+};
+
+/*
+** Allocate and return a pointer to a new sqlite3_value object. If
+** the second argument to this function is NULL, the object is allocated
+** by calling sqlite3ValueNew().
 **
-** This only works for very simple expressions that consist of one constant
-** token (i.e. "5", "5.1", "'a string'"). If the expression can
-** be converted directly into a value, then the value is allocated and
-** a pointer written to *ppVal. The caller is responsible for deallocating
-** the value by passing it to sqlite3ValueFree() later on. If the expression
-** cannot be converted to a value, then *ppVal is set to NULL.
+** Otherwise, if the second argument is non-zero, then this function is 
+** being called indirectly by sqlite3Stat4ProbeSetValue(). If it has not
+** already been allocated, allocate the UnpackedRecord structure that 
+** that function will return to its caller here. Then return a pointer to
+** an sqlite3_value within the UnpackedRecord.a[] array.
 */
-int sqlite3ValueFromExpr(
-  sqlite3 *db,              /* The database connection */
-  Expr *pExpr,              /* The expression to evaluate */
-  u8 enc,                   /* Encoding to use */
-  u8 affinity,              /* Affinity to use */
-  sqlite3_value **ppVal     /* Write the new value here */
+static sqlite3_value *valueNew(sqlite3 *db, struct ValueNewStat4Ctx *p){
+#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
+  if( p ){
+    UnpackedRecord *pRec = p->ppRec[0];
+
+    if( pRec==0 ){
+      Index *pIdx = p->pIdx;      /* Index being probed */
+      int nByte;                  /* Bytes of space to allocate */
+      int i;                      /* Counter variable */
+      int nCol = pIdx->nColumn;   /* Number of index columns including rowid */
+  
+      nByte = sizeof(Mem) * nCol + ROUND8(sizeof(UnpackedRecord));
+      pRec = (UnpackedRecord*)sqlite3DbMallocZero(db, nByte);
+      if( pRec ){
+        pRec->pKeyInfo = sqlite3KeyInfoOfIndex(p->pParse, pIdx);
+        if( pRec->pKeyInfo ){
+          assert( pRec->pKeyInfo->nAllField==nCol );
+          assert( pRec->pKeyInfo->enc==ENC(db) );
+          pRec->aMem = (Mem *)((u8*)pRec + ROUND8(sizeof(UnpackedRecord)));
+          for(i=0; i<nCol; i++){
+            pRec->aMem[i].flags = MEM_Null;
+            pRec->aMem[i].db = db;
+          }
+        }else{
+          sqlite3DbFreeNN(db, pRec);
+          pRec = 0;
+        }
+      }
+      if( pRec==0 ) return 0;
+      p->ppRec[0] = pRec;
+    }
+  
+    pRec->nField = p->iVal+1;
+    return &pRec->aMem[p->iVal];
+  }
+#else
+  UNUSED_PARAMETER(p);
+#endif /* defined(SQLITE_ENABLE_STAT3_OR_STAT4) */
+  return sqlite3ValueNew(db);
+}
+
+/*
+** The expression object indicated by the second argument is guaranteed
+** to be a scalar SQL function. If
+**
+**   * all function arguments are SQL literals,
+**   * one of the SQLITE_FUNC_CONSTANT or _SLOCHNG function flags is set, and
+**   * the SQLITE_FUNC_NEEDCOLL function flag is not set,
+**
+** then this routine attempts to invoke the SQL function. Assuming no
+** error occurs, output parameter (*ppVal) is set to point to a value 
+** object containing the result before returning SQLITE_OK.
+**
+** Affinity aff is applied to the result of the function before returning.
+** If the result is a text value, the sqlite3_value object uses encoding 
+** enc.
+**
+** If the conditions above are not met, this function returns SQLITE_OK
+** and sets (*ppVal) to NULL. Or, if an error occurs, (*ppVal) is set to
+** NULL and an SQLite error code returned.
+*/
+#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
+static int valueFromFunction(
+  sqlite3 *db,                    /* The database connection */
+  Expr *p,                        /* The expression to evaluate */
+  u8 enc,                         /* Encoding to use */
+  u8 aff,                         /* Affinity to use */
+  sqlite3_value **ppVal,          /* Write the new value here */
+  struct ValueNewStat4Ctx *pCtx   /* Second argument for valueNew() */
+){
+  sqlite3_context ctx;            /* Context object for function invocation */
+  sqlite3_value **apVal = 0;      /* Function arguments */
+  int nVal = 0;                   /* Size of apVal[] array */
+  FuncDef *pFunc = 0;             /* Function definition */
+  sqlite3_value *pVal = 0;        /* New value */
+  int rc = SQLITE_OK;             /* Return code */
+  ExprList *pList = 0;            /* Function arguments */
+  int i;                          /* Iterator variable */
+
+  assert( pCtx!=0 );
+  assert( (p->flags & EP_TokenOnly)==0 );
+  pList = p->x.pList;
+  if( pList ) nVal = pList->nExpr;
+  pFunc = sqlite3FindFunction(db, p->u.zToken, nVal, enc, 0);
+  assert( pFunc );
+  if( (pFunc->funcFlags & (SQLITE_FUNC_CONSTANT|SQLITE_FUNC_SLOCHNG))==0 
+   || (pFunc->funcFlags & SQLITE_FUNC_NEEDCOLL)
+  ){
+    return SQLITE_OK;
+  }
+
+  if( pList ){
+    apVal = (sqlite3_value**)sqlite3DbMallocZero(db, sizeof(apVal[0]) * nVal);
+    if( apVal==0 ){
+      rc = SQLITE_NOMEM_BKPT;
+      goto value_from_function_out;
+    }
+    for(i=0; i<nVal; i++){
+      rc = sqlite3ValueFromExpr(db, pList->a[i].pExpr, enc, aff, &apVal[i]);
+      if( apVal[i]==0 || rc!=SQLITE_OK ) goto value_from_function_out;
+    }
+  }
+
+  pVal = valueNew(db, pCtx);
+  if( pVal==0 ){
+    rc = SQLITE_NOMEM_BKPT;
+    goto value_from_function_out;
+  }
+
+  assert( pCtx->pParse->rc==SQLITE_OK );
+  memset(&ctx, 0, sizeof(ctx));
+  ctx.pOut = pVal;
+  ctx.pFunc = pFunc;
+  pFunc->xSFunc(&ctx, nVal, apVal);
+  if( ctx.isError ){
+    rc = ctx.isError;
+    sqlite3ErrorMsg(pCtx->pParse, "%s", sqlite3_value_text(pVal));
+  }else{
+    sqlite3ValueApplyAffinity(pVal, aff, SQLITE_UTF8);
+    assert( rc==SQLITE_OK );
+    rc = sqlite3VdbeChangeEncoding(pVal, enc);
+    if( rc==SQLITE_OK && sqlite3VdbeMemTooBig(pVal) ){
+      rc = SQLITE_TOOBIG;
+      pCtx->pParse->nErr++;
+    }
+  }
+  pCtx->pParse->rc = rc;
+
+ value_from_function_out:
+  if( rc!=SQLITE_OK ){
+    pVal = 0;
+  }
+  if( apVal ){
+    for(i=0; i<nVal; i++){
+      sqlite3ValueFree(apVal[i]);
+    }
+    sqlite3DbFreeNN(db, apVal);
+  }
+
+  *ppVal = pVal;
+  return rc;
+}
+#else
+# define valueFromFunction(a,b,c,d,e,f) SQLITE_OK
+#endif /* defined(SQLITE_ENABLE_STAT3_OR_STAT4) */
+
+/*
+** Extract a value from the supplied expression in the manner described
+** above sqlite3ValueFromExpr(). Allocate the sqlite3_value object
+** using valueNew().
+**
+** If pCtx is NULL and an error occurs after the sqlite3_value object
+** has been allocated, it is freed before returning. Or, if pCtx is not
+** NULL, it is assumed that the caller will free any allocated object
+** in all cases.
+*/
+static int valueFromExpr(
+  sqlite3 *db,                    /* The database connection */
+  Expr *pExpr,                    /* The expression to evaluate */
+  u8 enc,                         /* Encoding to use */
+  u8 affinity,                    /* Affinity to use */
+  sqlite3_value **ppVal,          /* Write the new value here */
+  struct ValueNewStat4Ctx *pCtx   /* Second argument for valueNew() */
 ){
   int op;
   char *zVal = 0;
   sqlite3_value *pVal = 0;
+  int negInt = 1;
+  const char *zNeg = "";
+  int rc = SQLITE_OK;
 
-  if( !pExpr ){
-    *ppVal = 0;
-    return SQLITE_OK;
+  assert( pExpr!=0 );
+  while( (op = pExpr->op)==TK_UPLUS || op==TK_SPAN ) pExpr = pExpr->pLeft;
+  if( NEVER(op==TK_REGISTER) ) op = pExpr->op2;
+
+  /* Compressed expressions only appear when parsing the DEFAULT clause
+  ** on a table column definition, and hence only when pCtx==0.  This
+  ** check ensures that an EP_TokenOnly expression is never passed down
+  ** into valueFromFunction(). */
+  assert( (pExpr->flags & EP_TokenOnly)==0 || pCtx==0 );
+
+  if( op==TK_CAST ){
+    u8 aff = sqlite3AffinityType(pExpr->u.zToken,0);
+    rc = valueFromExpr(db, pExpr->pLeft, enc, aff, ppVal, pCtx);
+    testcase( rc!=SQLITE_OK );
+    if( *ppVal ){
+      sqlite3VdbeMemCast(*ppVal, aff, SQLITE_UTF8);
+      sqlite3ValueApplyAffinity(*ppVal, affinity, SQLITE_UTF8);
+    }
+    return rc;
+  }
+
+  /* Handle negative integers in a single step.  This is needed in the
+  ** case when the value is -9223372036854775808.
+  */
+  if( op==TK_UMINUS
+   && (pExpr->pLeft->op==TK_INTEGER || pExpr->pLeft->op==TK_FLOAT) ){
+    pExpr = pExpr->pLeft;
+    op = pExpr->op;
+    negInt = -1;
+    zNeg = "-";
   }
-  op = pExpr->op;
 
   if( op==TK_STRING || op==TK_FLOAT || op==TK_INTEGER ){
-    pVal = sqlite3ValueNew(db);
+    pVal = valueNew(db, pCtx);
     if( pVal==0 ) goto no_mem;
     if( ExprHasProperty(pExpr, EP_IntValue) ){
-      sqlite3VdbeMemSetInt64(pVal, (i64)pExpr->u.iValue);
+      sqlite3VdbeMemSetInt64(pVal, (i64)pExpr->u.iValue*negInt);
     }else{
-      zVal = sqlite3DbStrDup(db, pExpr->u.zToken);
+      zVal = sqlite3MPrintf(db, "%s%s", zNeg, pExpr->u.zToken);
       if( zVal==0 ) goto no_mem;
       sqlite3ValueSetStr(pVal, -1, zVal, SQLITE_UTF8, SQLITE_DYNAMIC);
     }
-    if( (op==TK_INTEGER || op==TK_FLOAT ) && affinity==SQLITE_AFF_NONE ){
+    if( (op==TK_INTEGER || op==TK_FLOAT ) && affinity==SQLITE_AFF_BLOB ){
       sqlite3ValueApplyAffinity(pVal, SQLITE_AFF_NUMERIC, SQLITE_UTF8);
     }else{
       sqlite3ValueApplyAffinity(pVal, affinity, SQLITE_UTF8);
     }
+    if( pVal->flags & (MEM_Int|MEM_Real) ) pVal->flags &= ~MEM_Str;
     if( enc!=SQLITE_UTF8 ){
-      sqlite3VdbeChangeEncoding(pVal, enc);
+      rc = sqlite3VdbeChangeEncoding(pVal, enc);
     }
   }else if( op==TK_UMINUS ) {
-    if( SQLITE_OK==sqlite3ValueFromExpr(db,pExpr->pLeft,enc,affinity,&pVal) ){
-      pVal->u.i = -1 * pVal->u.i;
-      /* (double)-1 In case of SQLITE_OMIT_FLOATING_POINT... */
-      pVal->r = (double)-1 * pVal->r;
+    /* This branch happens for multiple negative signs.  Ex: -(-5) */
+    if( SQLITE_OK==valueFromExpr(db,pExpr->pLeft,enc,affinity,&pVal,pCtx) 
+     && pVal!=0
+    ){
+      sqlite3VdbeMemNumerify(pVal);
+      if( pVal->flags & MEM_Real ){
+        pVal->u.r = -pVal->u.r;
+      }else if( pVal->u.i==SMALLEST_INT64 ){
+        pVal->u.r = -(double)SMALLEST_INT64;
+        MemSetTypeFlag(pVal, MEM_Real);
+      }else{
+        pVal->u.i = -pVal->u.i;
+      }
+      sqlite3ValueApplyAffinity(pVal, affinity, enc);
     }
+  }else if( op==TK_NULL ){
+    pVal = valueNew(db, pCtx);
+    if( pVal==0 ) goto no_mem;
+    sqlite3VdbeMemNumerify(pVal);
   }
 #ifndef SQLITE_OMIT_BLOB_LITERAL
   else if( op==TK_BLOB ){
     int nVal;
     assert( pExpr->u.zToken[0]=='x' || pExpr->u.zToken[0]=='X' );
     assert( pExpr->u.zToken[1]=='\'' );
-    pVal = sqlite3ValueNew(db);
+    pVal = valueNew(db, pCtx);
     if( !pVal ) goto no_mem;
     zVal = &pExpr->u.zToken[2];
     nVal = sqlite3Strlen30(zVal)-1;
     assert( zVal[nVal]=='\'' );
     sqlite3VdbeMemSetStr(pVal, sqlite3HexToBlob(db, zVal, nVal), nVal/2,
                          0, SQLITE_DYNAMIC);
   }
 #endif
 
+#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
+  else if( op==TK_FUNCTION && pCtx!=0 ){
+    rc = valueFromFunction(db, pExpr, enc, affinity, &pVal, pCtx);
+  }
+#endif
+
   *ppVal = pVal;
-  return SQLITE_OK;
+  return rc;
 
 no_mem:
-  db->mallocFailed = 1;
+  sqlite3OomFault(db);
   sqlite3DbFree(db, zVal);
-  sqlite3ValueFree(pVal);
-  *ppVal = 0;
-  return SQLITE_NOMEM;
+  assert( *ppVal==0 );
+#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
+  if( pCtx==0 ) sqlite3ValueFree(pVal);
+#else
+  assert( pCtx==0 ); sqlite3ValueFree(pVal);
+#endif
+  return SQLITE_NOMEM_BKPT;
+}
+
+/*
+** Create a new sqlite3_value object, containing the value of pExpr.
+**
+** This only works for very simple expressions that consist of one constant
+** token (i.e. "5", "5.1", "'a string'"). If the expression can
+** be converted directly into a value, then the value is allocated and
+** a pointer written to *ppVal. The caller is responsible for deallocating
+** the value by passing it to sqlite3ValueFree() later on. If the expression
+** cannot be converted to a value, then *ppVal is set to NULL.
+*/
+int sqlite3ValueFromExpr(
+  sqlite3 *db,              /* The database connection */
+  Expr *pExpr,              /* The expression to evaluate */
+  u8 enc,                   /* Encoding to use */
+  u8 affinity,              /* Affinity to use */
+  sqlite3_value **ppVal     /* Write the new value here */
+){
+  return pExpr ? valueFromExpr(db, pExpr, enc, affinity, ppVal, 0) : 0;
+}
+
+#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
+/*
+** The implementation of the sqlite_record() function. This function accepts
+** a single argument of any type. The return value is a formatted database 
+** record (a blob) containing the argument value.
+**
+** This is used to convert the value stored in the 'sample' column of the
+** sqlite_stat3 table to the record format SQLite uses internally.
+*/
+static void recordFunc(
+  sqlite3_context *context,
+  int argc,
+  sqlite3_value **argv
+){
+  const int file_format = 1;
+  u32 iSerial;                    /* Serial type */
+  int nSerial;                    /* Bytes of space for iSerial as varint */
+  u32 nVal;                       /* Bytes of space required for argv[0] */
+  int nRet;
+  sqlite3 *db;
+  u8 *aRet;
+
+  UNUSED_PARAMETER( argc );
+  iSerial = sqlite3VdbeSerialType(argv[0], file_format, &nVal);
+  nSerial = sqlite3VarintLen(iSerial);
+  db = sqlite3_context_db_handle(context);
+
+  nRet = 1 + nSerial + nVal;
+  aRet = sqlite3DbMallocRawNN(db, nRet);
+  if( aRet==0 ){
+    sqlite3_result_error_nomem(context);
+  }else{
+    aRet[0] = nSerial+1;
+    putVarint32(&aRet[1], iSerial);
+    sqlite3VdbeSerialPut(&aRet[1+nSerial], argv[0], iSerial);
+    sqlite3_result_blob(context, aRet, nRet, SQLITE_TRANSIENT);
+    sqlite3DbFreeNN(db, aRet);
+  }
+}
+
+/*
+** Register built-in functions used to help read ANALYZE data.
+*/
+void sqlite3AnalyzeFunctions(void){
+  static FuncDef aAnalyzeTableFuncs[] = {
+    FUNCTION(sqlite_record,   1, 0, 0, recordFunc),
+  };
+  sqlite3InsertBuiltinFuncs(aAnalyzeTableFuncs, ArraySize(aAnalyzeTableFuncs));
 }
 
 /*
+** Attempt to extract a value from pExpr and use it to construct *ppVal.
+**
+** If pAlloc is not NULL, then an UnpackedRecord object is created for
+** pAlloc if one does not exist and the new value is added to the
+** UnpackedRecord object.
+**
+** A value is extracted in the following cases:
+**
+**  * (pExpr==0). In this case the value is assumed to be an SQL NULL,
+**
+**  * The expression is a bound variable, and this is a reprepare, or
+**
+**  * The expression is a literal value.
+**
+** On success, *ppVal is made to point to the extracted value.  The caller
+** is responsible for ensuring that the value is eventually freed.
+*/
+static int stat4ValueFromExpr(
+  Parse *pParse,                  /* Parse context */
+  Expr *pExpr,                    /* The expression to extract a value from */
+  u8 affinity,                    /* Affinity to use */
+  struct ValueNewStat4Ctx *pAlloc,/* How to allocate space.  Or NULL */
+  sqlite3_value **ppVal           /* OUT: New value object (or NULL) */
+){
+  int rc = SQLITE_OK;
+  sqlite3_value *pVal = 0;
+  sqlite3 *db = pParse->db;
+
+  /* Skip over any TK_COLLATE nodes */
+  pExpr = sqlite3ExprSkipCollate(pExpr);
+
+  assert( pExpr==0 || pExpr->op!=TK_REGISTER || pExpr->op2!=TK_VARIABLE );
+  if( !pExpr ){
+    pVal = valueNew(db, pAlloc);
+    if( pVal ){
+      sqlite3VdbeMemSetNull((Mem*)pVal);
+    }
+  }else if( pExpr->op==TK_VARIABLE && (db->flags & SQLITE_EnableQPSG)==0 ){
+    Vdbe *v;
+    int iBindVar = pExpr->iColumn;
+    sqlite3VdbeSetVarmask(pParse->pVdbe, iBindVar);
+    if( (v = pParse->pReprepare)!=0 ){
+      pVal = valueNew(db, pAlloc);
+      if( pVal ){
+        rc = sqlite3VdbeMemCopy((Mem*)pVal, &v->aVar[iBindVar-1]);
+        sqlite3ValueApplyAffinity(pVal, affinity, ENC(db));
+        pVal->db = pParse->db;
+      }
+    }
+  }else{
+    rc = valueFromExpr(db, pExpr, ENC(db), affinity, &pVal, pAlloc);
+  }
+
+  assert( pVal==0 || pVal->db==db );
+  *ppVal = pVal;
+  return rc;
+}
+
+/*
+** This function is used to allocate and populate UnpackedRecord 
+** structures intended to be compared against sample index keys stored 
+** in the sqlite_stat4 table.
+**
+** A single call to this function populates zero or more fields of the
+** record starting with field iVal (fields are numbered from left to
+** right starting with 0). A single field is populated if:
+**
+**  * (pExpr==0). In this case the value is assumed to be an SQL NULL,
+**
+**  * The expression is a bound variable, and this is a reprepare, or
+**
+**  * The sqlite3ValueFromExpr() function is able to extract a value 
+**    from the expression (i.e. the expression is a literal value).
+**
+** Or, if pExpr is a TK_VECTOR, one field is populated for each of the
+** vector components that match either of the two latter criteria listed
+** above.
+**
+** Before any value is appended to the record, the affinity of the 
+** corresponding column within index pIdx is applied to it. Before
+** this function returns, output parameter *pnExtract is set to the
+** number of values appended to the record.
+**
+** When this function is called, *ppRec must either point to an object
+** allocated by an earlier call to this function, or must be NULL. If it
+** is NULL and a value can be successfully extracted, a new UnpackedRecord
+** is allocated (and *ppRec set to point to it) before returning.
+**
+** Unless an error is encountered, SQLITE_OK is returned. It is not an
+** error if a value cannot be extracted from pExpr. If an error does
+** occur, an SQLite error code is returned.
+*/
+int sqlite3Stat4ProbeSetValue(
+  Parse *pParse,                  /* Parse context */
+  Index *pIdx,                    /* Index being probed */
+  UnpackedRecord **ppRec,         /* IN/OUT: Probe record */
+  Expr *pExpr,                    /* The expression to extract a value from */
+  int nElem,                      /* Maximum number of values to append */
+  int iVal,                       /* Array element to populate */
+  int *pnExtract                  /* OUT: Values appended to the record */
+){
+  int rc = SQLITE_OK;
+  int nExtract = 0;
+
+  if( pExpr==0 || pExpr->op!=TK_SELECT ){
+    int i;
+    struct ValueNewStat4Ctx alloc;
+
+    alloc.pParse = pParse;
+    alloc.pIdx = pIdx;
+    alloc.ppRec = ppRec;
+
+    for(i=0; i<nElem; i++){
+      sqlite3_value *pVal = 0;
+      Expr *pElem = (pExpr ? sqlite3VectorFieldSubexpr(pExpr, i) : 0);
+      u8 aff = sqlite3IndexColumnAffinity(pParse->db, pIdx, iVal+i);
+      alloc.iVal = iVal+i;
+      rc = stat4ValueFromExpr(pParse, pElem, aff, &alloc, &pVal);
+      if( !pVal ) break;
+      nExtract++;
+    }
+  }
+
+  *pnExtract = nExtract;
+  return rc;
+}
+
+/*
+** Attempt to extract a value from expression pExpr using the methods
+** as described for sqlite3Stat4ProbeSetValue() above. 
+**
+** If successful, set *ppVal to point to a new value object and return 
+** SQLITE_OK. If no value can be extracted, but no other error occurs
+** (e.g. OOM), return SQLITE_OK and set *ppVal to NULL. Or, if an error
+** does occur, return an SQLite error code. The final value of *ppVal
+** is undefined in this case.
+*/
+int sqlite3Stat4ValueFromExpr(
+  Parse *pParse,                  /* Parse context */
+  Expr *pExpr,                    /* The expression to extract a value from */
+  u8 affinity,                    /* Affinity to use */
+  sqlite3_value **ppVal           /* OUT: New value object (or NULL) */
+){
+  return stat4ValueFromExpr(pParse, pExpr, affinity, 0, ppVal);
+}
+
+/*
+** Extract the iCol-th column from the nRec-byte record in pRec.  Write
+** the column value into *ppVal.  If *ppVal is initially NULL then a new
+** sqlite3_value object is allocated.
+**
+** If *ppVal is initially NULL then the caller is responsible for 
+** ensuring that the value written into *ppVal is eventually freed.
+*/
+int sqlite3Stat4Column(
+  sqlite3 *db,                    /* Database handle */
+  const void *pRec,               /* Pointer to buffer containing record */
+  int nRec,                       /* Size of buffer pRec in bytes */
+  int iCol,                       /* Column to extract */
+  sqlite3_value **ppVal           /* OUT: Extracted value */
+){
+  u32 t;                          /* a column type code */
+  int nHdr;                       /* Size of the header in the record */
+  int iHdr;                       /* Next unread header byte */
+  int iField;                     /* Next unread data byte */
+  int szField;                    /* Size of the current data field */
+  int i;                          /* Column index */
+  u8 *a = (u8*)pRec;              /* Typecast byte array */
+  Mem *pMem = *ppVal;             /* Write result into this Mem object */
+
+  assert( iCol>0 );
+  iHdr = getVarint32(a, nHdr);
+  if( nHdr>nRec || iHdr>=nHdr ) return SQLITE_CORRUPT_BKPT;
+  iField = nHdr;
+  for(i=0; i<=iCol; i++){
+    iHdr += getVarint32(&a[iHdr], t);
+    testcase( iHdr==nHdr );
+    testcase( iHdr==nHdr+1 );
+    if( iHdr>nHdr ) return SQLITE_CORRUPT_BKPT;
+    szField = sqlite3VdbeSerialTypeLen(t);
+    iField += szField;
+  }
+  testcase( iField==nRec );
+  testcase( iField==nRec+1 );
+  if( iField>nRec ) return SQLITE_CORRUPT_BKPT;
+  if( pMem==0 ){
+    pMem = *ppVal = sqlite3ValueNew(db);
+    if( pMem==0 ) return SQLITE_NOMEM_BKPT;
+  }
+  sqlite3VdbeSerialGet(&a[iField-szField], t, pMem);
+  pMem->enc = ENC(db);
+  return SQLITE_OK;
+}
+
+/*
+** Unless it is NULL, the argument must be an UnpackedRecord object returned
+** by an earlier call to sqlite3Stat4ProbeSetValue(). This call deletes
+** the object.
+*/
+void sqlite3Stat4ProbeFree(UnpackedRecord *pRec){
+  if( pRec ){
+    int i;
+    int nCol = pRec->pKeyInfo->nAllField;
+    Mem *aMem = pRec->aMem;
+    sqlite3 *db = aMem[0].db;
+    for(i=0; i<nCol; i++){
+      sqlite3VdbeMemRelease(&aMem[i]);
+    }
+    sqlite3KeyInfoUnref(pRec->pKeyInfo);
+    sqlite3DbFreeNN(db, pRec);
+  }
+}
+#endif /* ifdef SQLITE_ENABLE_STAT4 */
+
+/*
 ** Change the string value of an sqlite3_value object
 */
 void sqlite3ValueSetStr(
   sqlite3_value *v,     /* Value to be set */
   int n,                /* Length of string z */
   const void *z,        /* Text of the new string */
