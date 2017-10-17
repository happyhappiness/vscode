   *(struct sqlite3_index_constraint**)&pIdxInfo->aConstraint = pIdxCons;
   *(struct sqlite3_index_orderby**)&pIdxInfo->aOrderBy = pIdxOrderBy;
   *(struct sqlite3_index_constraint_usage**)&pIdxInfo->aConstraintUsage =
                                                                    pUsage;
 
   for(i=j=0, pTerm=pWC->a; i<pWC->nTerm; i++, pTerm++){
-    u16 op;
     if( pTerm->leftCursor != pSrc->iCursor ) continue;
-    if( pTerm->prereqRight & mUnusable ) continue;
-    assert( IsPowerOfTwo(pTerm->eOperator & ~WO_EQUIV) );
-    testcase( pTerm->eOperator & WO_IN );
-    testcase( pTerm->eOperator & WO_IS );
-    testcase( pTerm->eOperator & WO_ISNULL );
-    testcase( pTerm->eOperator & WO_ALL );
-    if( (pTerm->eOperator & ~(WO_EQUIV))==0 ) continue;
-    if( pTerm->wtFlags & TERM_VNULL ) continue;
-    assert( pTerm->u.leftColumn>=(-1) );
+    assert( (pTerm->eOperator&(pTerm->eOperator-1))==0 );
+    testcase( pTerm->eOperator==WO_IN );
+    testcase( pTerm->eOperator==WO_ISNULL );
+    if( pTerm->eOperator & (WO_IN|WO_ISNULL) ) continue;
     pIdxCons[j].iColumn = pTerm->u.leftColumn;
     pIdxCons[j].iTermOffset = i;
-    op = pTerm->eOperator & WO_ALL;
-    if( op==WO_IN ) op = WO_EQ;
-    if( op==WO_AUX ){
-      pIdxCons[j].op = pTerm->eMatchOp;
-    }else if( op & (WO_ISNULL|WO_IS) ){
-      if( op==WO_ISNULL ){
-        pIdxCons[j].op = SQLITE_INDEX_CONSTRAINT_ISNULL;
-      }else{
-        pIdxCons[j].op = SQLITE_INDEX_CONSTRAINT_IS;
-      }
-    }else{
-      pIdxCons[j].op = (u8)op;
-      /* The direct assignment in the previous line is possible only because
-      ** the WO_ and SQLITE_INDEX_CONSTRAINT_ codes are identical.  The
-      ** following asserts verify this fact. */
-      assert( WO_EQ==SQLITE_INDEX_CONSTRAINT_EQ );
-      assert( WO_LT==SQLITE_INDEX_CONSTRAINT_LT );
-      assert( WO_LE==SQLITE_INDEX_CONSTRAINT_LE );
-      assert( WO_GT==SQLITE_INDEX_CONSTRAINT_GT );
-      assert( WO_GE==SQLITE_INDEX_CONSTRAINT_GE );
-      assert( pTerm->eOperator&(WO_IN|WO_EQ|WO_LT|WO_LE|WO_GT|WO_GE|WO_AUX) );
-
-      if( op & (WO_LT|WO_LE|WO_GT|WO_GE)
-       && sqlite3ExprIsVector(pTerm->pExpr->pRight) 
-      ){
-        if( i<16 ) mNoOmit |= (1 << i);
-        if( op==WO_LT ) pIdxCons[j].op = WO_LE;
-        if( op==WO_GT ) pIdxCons[j].op = WO_GE;
-      }
-    }
-
+    pIdxCons[j].op = (u8)pTerm->eOperator;
+    /* The direct assignment in the previous line is possible only because
+    ** the WO_ and SQLITE_INDEX_CONSTRAINT_ codes are identical.  The
+    ** following asserts verify this fact. */
+    assert( WO_EQ==SQLITE_INDEX_CONSTRAINT_EQ );
+    assert( WO_LT==SQLITE_INDEX_CONSTRAINT_LT );
+    assert( WO_LE==SQLITE_INDEX_CONSTRAINT_LE );
+    assert( WO_GT==SQLITE_INDEX_CONSTRAINT_GT );
+    assert( WO_GE==SQLITE_INDEX_CONSTRAINT_GE );
+    assert( WO_MATCH==SQLITE_INDEX_CONSTRAINT_MATCH );
+    assert( pTerm->eOperator & (WO_EQ|WO_LT|WO_LE|WO_GT|WO_GE|WO_MATCH) );
     j++;
   }
   for(i=0; i<nOrderBy; i++){
     Expr *pExpr = pOrderBy->a[i].pExpr;
     pIdxOrderBy[i].iColumn = pExpr->iColumn;
     pIdxOrderBy[i].desc = pOrderBy->a[i].sortOrder;
   }
 
-  *pmNoOmit = mNoOmit;
   return pIdxInfo;
 }
 
 /*
 ** The table object reference passed as the second argument to this function
 ** must represent a virtual table. This function invokes the xBestIndex()
-** method of the virtual table with the sqlite3_index_info object that
-** comes in as the 3rd argument to this function.
+** method of the virtual table with the sqlite3_index_info pointer passed
+** as the argument.
 **
 ** If an error occurs, pParse is populated with an error message and a
 ** non-zero value is returned. Otherwise, 0 is returned and the output
 ** part of the sqlite3_index_info structure is left populated.
 **
 ** Whether or not an error is returned, it is the responsibility of the
 ** caller to eventually free p->idxStr if p->needToFreeIdxStr indicates
 ** that this is required.
 */
 static int vtabBestIndex(Parse *pParse, Table *pTab, sqlite3_index_info *p){
-  sqlite3_vtab *pVtab = sqlite3GetVTable(pParse->db, pTab)->pVtab;
+  sqlite3_vtab *pVtab = pTab->pVtab;
+  int i;
   int rc;
 
+  (void)sqlite3SafetyOff(pParse->db);
+  WHERETRACE(("xBestIndex for %s\n", pTab->zName));
   TRACE_IDX_INPUTS(p);
   rc = pVtab->pModule->xBestIndex(pVtab, p);
   TRACE_IDX_OUTPUTS(p);
+  (void)sqlite3SafetyOn(pParse->db);
 
   if( rc!=SQLITE_OK ){
     if( rc==SQLITE_NOMEM ){
-      sqlite3OomFault(pParse->db);
+      pParse->db->mallocFailed = 1;
     }else if( !pVtab->zErrMsg ){
       sqlite3ErrorMsg(pParse, "%s", sqlite3ErrStr(rc));
     }else{
       sqlite3ErrorMsg(pParse, "%s", pVtab->zErrMsg);
     }
   }
-  sqlite3_free(pVtab->zErrMsg);
+  sqlite3DbFree(pParse->db, pVtab->zErrMsg);
   pVtab->zErrMsg = 0;
 
-#if 0
-  /* This error is now caught by the caller.
-  ** Search for "xBestIndex malfunction" below */
   for(i=0; i<p->nConstraint; i++){
     if( !p->aConstraint[i].usable && p->aConstraintUsage[i].argvIndex>0 ){
       sqlite3ErrorMsg(pParse, 
           "table %s: xBestIndex returned an invalid plan", pTab->zName);
     }
   }
-#endif
 
   return pParse->nErr;
 }
-#endif /* !defined(SQLITE_OMIT_VIRTUALTABLE) */
 
-#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
+
 /*
-** Estimate the location of a particular key among all keys in an
-** index.  Store the results in aStat as follows:
+** Compute the best index for a virtual table.
 **
-**    aStat[0]      Est. number of rows less than pRec
-**    aStat[1]      Est. number of rows equal to pRec
-**
-** Return the index of the sample that is the smallest sample that
-** is greater than or equal to pRec. Note that this index is not an index
-** into the aSample[] array - it is an index into a virtual set of samples
-** based on the contents of aSample[] and the number of fields in record 
-** pRec. 
-*/
-static int whereKeyStats(
-  Parse *pParse,              /* Database connection */
-  Index *pIdx,                /* Index to consider domain of */
-  UnpackedRecord *pRec,       /* Vector of values to consider */
-  int roundUp,                /* Round up if true.  Round down if false */
-  tRowcnt *aStat              /* OUT: stats written here */
+** The best index is computed by the xBestIndex method of the virtual
+** table module.  This routine is really just a wrapper that sets up
+** the sqlite3_index_info structure that is used to communicate with
+** xBestIndex.
+**
+** In a join, this routine might be called multiple times for the
+** same virtual table.  The sqlite3_index_info structure is created
+** and initialized on the first invocation and reused on all subsequent
+** invocations.  The sqlite3_index_info structure is also used when
+** code is generated to access the virtual table.  The whereInfoDelete() 
+** routine takes care of freeing the sqlite3_index_info structure after
+** everybody has finished with it.
+*/
+static void bestVirtualIndex(
+  Parse *pParse,                  /* The parsing context */
+  WhereClause *pWC,               /* The WHERE clause */
+  struct SrcList_item *pSrc,      /* The FROM clause term to search */
+  Bitmask notReady,               /* Mask of cursors that are not available */
+  ExprList *pOrderBy,             /* The order by clause */
+  WhereCost *pCost,               /* Lowest cost query plan */
+  sqlite3_index_info **ppIdxInfo  /* Index information passed to xBestIndex */
 ){
-  IndexSample *aSample = pIdx->aSample;
-  int iCol;                   /* Index of required stats in anEq[] etc. */
-  int i;                      /* Index of first sample >= pRec */
-  int iSample;                /* Smallest sample larger than or equal to pRec */
-  int iMin = 0;               /* Smallest sample not yet tested */
-  int iTest;                  /* Next sample to test */
-  int res;                    /* Result of comparison operation */
-  int nField;                 /* Number of fields in pRec */
-  tRowcnt iLower = 0;         /* anLt[] + anEq[] of largest sample pRec is > */
+  Table *pTab = pSrc->pTab;
+  sqlite3_index_info *pIdxInfo;
+  struct sqlite3_index_constraint *pIdxCons;
+  struct sqlite3_index_constraint_usage *pUsage;
+  WhereTerm *pTerm;
+  int i, j;
+  int nOrderBy;
 
-#ifndef SQLITE_DEBUG
-  UNUSED_PARAMETER( pParse );
-#endif
-  assert( pRec!=0 );
-  assert( pIdx->nSample>0 );
-  assert( pRec->nField>0 && pRec->nField<=pIdx->nSampleCol );
-
-  /* Do a binary search to find the first sample greater than or equal
-  ** to pRec. If pRec contains a single field, the set of samples to search
-  ** is simply the aSample[] array. If the samples in aSample[] contain more
-  ** than one fields, all fields following the first are ignored.
-  **
-  ** If pRec contains N fields, where N is more than one, then as well as the
-  ** samples in aSample[] (truncated to N fields), the search also has to
-  ** consider prefixes of those samples. For example, if the set of samples
-  ** in aSample is:
-  **
-  **     aSample[0] = (a, 5) 
-  **     aSample[1] = (a, 10) 
-  **     aSample[2] = (b, 5) 
-  **     aSample[3] = (c, 100) 
-  **     aSample[4] = (c, 105)
+  /* Make sure wsFlags is initialized to some sane value. Otherwise, if the 
+  ** malloc in allocateIndexInfo() fails and this function returns leaving
+  ** wsFlags in an uninitialized state, the caller may behave unpredictably.
+  */
+  memset(pCost, 0, sizeof(*pCost));
+  pCost->plan.wsFlags = WHERE_VIRTUALTABLE;
+
+  /* If the sqlite3_index_info structure has not been previously
+  ** allocated and initialized, then allocate and initialize it now.
+  */
+  pIdxInfo = *ppIdxInfo;
+  if( pIdxInfo==0 ){
+    *ppIdxInfo = pIdxInfo = allocateIndexInfo(pParse, pWC, pSrc, pOrderBy);
+  }
+  if( pIdxInfo==0 ){
+    return;
+  }
+
+  /* At this point, the sqlite3_index_info structure that pIdxInfo points
+  ** to will have been initialized, either during the current invocation or
+  ** during some prior invocation.  Now we just have to customize the
+  ** details of pIdxInfo for the current invocation and pass it to
+  ** xBestIndex.
+  */
+
+  /* The module name must be defined. Also, by this point there must
+  ** be a pointer to an sqlite3_vtab structure. Otherwise
+  ** sqlite3ViewGetColumnNames() would have picked up the error. 
+  */
+  assert( pTab->azModuleArg && pTab->azModuleArg[0] );
+  assert( pTab->pVtab );
+
+  /* Set the aConstraint[].usable fields and initialize all 
+  ** output variables to zero.
   **
-  ** Then the search space should ideally be the samples above and the 
-  ** unique prefixes [a], [b] and [c]. But since that is hard to organize, 
-  ** the code actually searches this set:
+  ** aConstraint[].usable is true for constraints where the right-hand
+  ** side contains only references to tables to the left of the current
+  ** table.  In other words, if the constraint is of the form:
   **
-  **     0: (a) 
-  **     1: (a, 5) 
-  **     2: (a, 10) 
-  **     3: (a, 10) 
-  **     4: (b) 
-  **     5: (b, 5) 
-  **     6: (c) 
-  **     7: (c, 100) 
-  **     8: (c, 105)
-  **     9: (c, 105)
+  **           column = expr
   **
-  ** For each sample in the aSample[] array, N samples are present in the
-  ** effective sample array. In the above, samples 0 and 1 are based on 
-  ** sample aSample[0]. Samples 2 and 3 on aSample[1] etc.
+  ** and we are evaluating a join, then the constraint on column is 
+  ** only valid if all tables referenced in expr occur to the left
+  ** of the table containing column.
   **
-  ** Often, sample i of each block of N effective samples has (i+1) fields.
-  ** Except, each sample may be extended to ensure that it is greater than or
-  ** equal to the previous sample in the array. For example, in the above, 
-  ** sample 2 is the first sample of a block of N samples, so at first it 
-  ** appears that it should be 1 field in size. However, that would make it 
-  ** smaller than sample 1, so the binary search would not work. As a result, 
-  ** it is extended to two fields. The duplicates that this creates do not 
-  ** cause any problems.
-  */
-  nField = pRec->nField;
-  iCol = 0;
-  iSample = pIdx->nSample * nField;
-  do{
-    int iSamp;                    /* Index in aSample[] of test sample */
-    int n;                        /* Number of fields in test sample */
-
-    iTest = (iMin+iSample)/2;
-    iSamp = iTest / nField;
-    if( iSamp>0 ){
-      /* The proposed effective sample is a prefix of sample aSample[iSamp].
-      ** Specifically, the shortest prefix of at least (1 + iTest%nField) 
-      ** fields that is greater than the previous effective sample.  */
-      for(n=(iTest % nField) + 1; n<nField; n++){
-        if( aSample[iSamp-1].anLt[n-1]!=aSample[iSamp].anLt[n-1] ) break;
-      }
-    }else{
-      n = iTest + 1;
-    }
-
-    pRec->nField = n;
-    res = sqlite3VdbeRecordCompare(aSample[iSamp].n, aSample[iSamp].p, pRec);
-    if( res<0 ){
-      iLower = aSample[iSamp].anLt[n-1] + aSample[iSamp].anEq[n-1];
-      iMin = iTest+1;
-    }else if( res==0 && n<nField ){
-      iLower = aSample[iSamp].anLt[n-1];
-      iMin = iTest+1;
-      res = -1;
-    }else{
-      iSample = iTest;
-      iCol = n-1;
-    }
-  }while( res && iMin<iSample );
-  i = iSample / nField;
-
-#ifdef SQLITE_DEBUG
-  /* The following assert statements check that the binary search code
-  ** above found the right answer. This block serves no purpose other
-  ** than to invoke the asserts.  */
-  if( pParse->db->mallocFailed==0 ){
-    if( res==0 ){
-      /* If (res==0) is true, then pRec must be equal to sample i. */
-      assert( i<pIdx->nSample );
-      assert( iCol==nField-1 );
-      pRec->nField = nField;
-      assert( 0==sqlite3VdbeRecordCompare(aSample[i].n, aSample[i].p, pRec) 
-           || pParse->db->mallocFailed 
-      );
-    }else{
-      /* Unless i==pIdx->nSample, indicating that pRec is larger than
-      ** all samples in the aSample[] array, pRec must be smaller than the
-      ** (iCol+1) field prefix of sample i.  */
-      assert( i<=pIdx->nSample && i>=0 );
-      pRec->nField = iCol+1;
-      assert( i==pIdx->nSample 
-           || sqlite3VdbeRecordCompare(aSample[i].n, aSample[i].p, pRec)>0
-           || pParse->db->mallocFailed );
-
-      /* if i==0 and iCol==0, then record pRec is smaller than all samples
-      ** in the aSample[] array. Otherwise, if (iCol>0) then pRec must
-      ** be greater than or equal to the (iCol) field prefix of sample i.
-      ** If (i>0), then pRec must also be greater than sample (i-1).  */
-      if( iCol>0 ){
-        pRec->nField = iCol;
-        assert( sqlite3VdbeRecordCompare(aSample[i].n, aSample[i].p, pRec)<=0
-             || pParse->db->mallocFailed );
-      }
-      if( i>0 ){
-        pRec->nField = nField;
-        assert( sqlite3VdbeRecordCompare(aSample[i-1].n, aSample[i-1].p, pRec)<0
-             || pParse->db->mallocFailed );
-      }
-    }
+  ** The aConstraints[] array contains entries for all constraints
+  ** on the current table.  That way we only have to compute it once
+  ** even though we might try to pick the best index multiple times.
+  ** For each attempt at picking an index, the order of tables in the
+  ** join might be different so we have to recompute the usable flag
+  ** each time.
+  */
+  pIdxCons = *(struct sqlite3_index_constraint**)&pIdxInfo->aConstraint;
+  pUsage = pIdxInfo->aConstraintUsage;
+  for(i=0; i<pIdxInfo->nConstraint; i++, pIdxCons++){
+    j = pIdxCons->iTermOffset;
+    pTerm = &pWC->a[j];
+    pIdxCons->usable =  (pTerm->prereqRight & notReady)==0 ?1:0;
+  }
+  memset(pUsage, 0, sizeof(pUsage[0])*pIdxInfo->nConstraint);
+  if( pIdxInfo->needToFreeIdxStr ){
+    sqlite3_free(pIdxInfo->idxStr);
   }
-#endif /* ifdef SQLITE_DEBUG */
-
-  if( res==0 ){
-    /* Record pRec is equal to sample i */
-    assert( iCol==nField-1 );
-    aStat[0] = aSample[i].anLt[iCol];
-    aStat[1] = aSample[i].anEq[iCol];
-  }else{
-    /* At this point, the (iCol+1) field prefix of aSample[i] is the first 
-    ** sample that is greater than pRec. Or, if i==pIdx->nSample then pRec
-    ** is larger than all samples in the array. */
-    tRowcnt iUpper, iGap;
-    if( i>=pIdx->nSample ){
-      iUpper = sqlite3LogEstToInt(pIdx->aiRowLogEst[0]);
-    }else{
-      iUpper = aSample[i].anLt[iCol];
-    }
-
-    if( iLower>=iUpper ){
-      iGap = 0;
-    }else{
-      iGap = iUpper - iLower;
-    }
-    if( roundUp ){
-      iGap = (iGap*2)/3;
-    }else{
-      iGap = iGap/3;
-    }
-    aStat[0] = iLower + iGap;
-    aStat[1] = pIdx->aAvgEq[nField-1];
+  pIdxInfo->idxStr = 0;
+  pIdxInfo->idxNum = 0;
+  pIdxInfo->needToFreeIdxStr = 0;
+  pIdxInfo->orderByConsumed = 0;
+  /* ((double)2) In case of SQLITE_OMIT_FLOATING_POINT... */
+  pIdxInfo->estimatedCost = SQLITE_BIG_DBL / ((double)2);
+  nOrderBy = pIdxInfo->nOrderBy;
+  if( !pOrderBy ){
+    pIdxInfo->nOrderBy = 0;
   }
 
-  /* Restore the pRec->nField value before returning.  */
-  pRec->nField = nField;
-  return i;
-}
-#endif /* SQLITE_ENABLE_STAT3_OR_STAT4 */
+  if( vtabBestIndex(pParse, pTab, pIdxInfo) ){
+    return;
+  }
 
-/*
-** If it is not NULL, pTerm is a term that provides an upper or lower
-** bound on a range scan. Without considering pTerm, it is estimated 
-** that the scan will visit nNew rows. This function returns the number
-** estimated to be visited after taking pTerm into account.
-**
-** If the user explicitly specified a likelihood() value for this term,
-** then the return value is the likelihood multiplied by the number of
-** input rows. Otherwise, this function assumes that an "IS NOT NULL" term
-** has a likelihood of 0.50, and any other term a likelihood of 0.25.
-*/
-static LogEst whereRangeAdjust(WhereTerm *pTerm, LogEst nNew){
-  LogEst nRet = nNew;
-  if( pTerm ){
-    if( pTerm->truthProb<=0 ){
-      nRet += pTerm->truthProb;
-    }else if( (pTerm->wtFlags & TERM_VNULL)==0 ){
-      nRet -= 20;        assert( 20==sqlite3LogEst(4) );
-    }
+  /* The cost is not allowed to be larger than SQLITE_BIG_DBL (the
+  ** inital value of lowestCost in this loop. If it is, then the
+  ** (cost<lowestCost) test below will never be true.
+  ** 
+  ** Use "(double)2" instead of "2.0" in case OMIT_FLOATING_POINT 
+  ** is defined.
+  */
+  if( (SQLITE_BIG_DBL/((double)2))<pIdxInfo->estimatedCost ){
+    pCost->rCost = (SQLITE_BIG_DBL/((double)2));
+  }else{
+    pCost->rCost = pIdxInfo->estimatedCost;
   }
-  return nRet;
-}
+  pCost->plan.u.pVtabIdx = pIdxInfo;
+  if( pIdxInfo->orderByConsumed ){
+    pCost->plan.wsFlags |= WHERE_ORDERBY;
+  }
+  pCost->plan.nEq = 0;
+  pIdxInfo->nOrderBy = nOrderBy;
 
+  /* Try to find a more efficient access pattern by using multiple indexes
+  ** to optimize an OR expression within the WHERE clause. 
+  */
+  bestOrClauseIndex(pParse, pWC, pSrc, notReady, pOrderBy, pCost);
+}
+#endif /* SQLITE_OMIT_VIRTUALTABLE */
 
-#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
 /*
-** Return the affinity for a single column of an index.
+** Find the query plan for accessing a particular table.  Write the
+** best query plan and its cost into the WhereCost object supplied as the
+** last parameter.
+**
+** The lowest cost plan wins.  The cost is an estimate of the amount of
+** CPU and disk I/O need to process the request using the selected plan.
+** Factors that influence cost include:
+**
+**    *  The estimated number of rows that will be retrieved.  (The
+**       fewer the better.)
+**
+**    *  Whether or not sorting must occur.
+**
+**    *  Whether or not there must be separate lookups in the
+**       index and in the main table.
+**
+** If there was an INDEXED BY clause (pSrc->pIndex) attached to the table in
+** the SQL statement, then this function only considers plans using the 
+** named index. If no such plan is found, then the returned cost is
+** SQLITE_BIG_DBL. If a plan is found that uses the named index, 
+** then the cost is calculated in the usual way.
+**
+** If a NOT INDEXED clause (pSrc->notIndexed!=0) was attached to the table 
+** in the SELECT statement, then no indexes are considered. However, the 
+** selected plan may still take advantage of the tables built-in rowid
+** index.
 */
-char sqlite3IndexColumnAffinity(sqlite3 *db, Index *pIdx, int iCol){
-  assert( iCol>=0 && iCol<pIdx->nColumn );
-  if( !pIdx->zColAff ){
-    if( sqlite3IndexAffinityStr(db, pIdx)==0 ) return SQLITE_AFF_BLOB;
-  }
-  return pIdx->zColAff[iCol];
-}
-#endif
-
-
-#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
-/* 
-** This function is called to estimate the number of rows visited by a
-** range-scan on a skip-scan index. For example:
-**
-**   CREATE INDEX i1 ON t1(a, b, c);
-**   SELECT * FROM t1 WHERE a=? AND c BETWEEN ? AND ?;
-**
-** Value pLoop->nOut is currently set to the estimated number of rows 
-** visited for scanning (a=? AND b=?). This function reduces that estimate 
-** by some factor to account for the (c BETWEEN ? AND ?) expression based
-** on the stat4 data for the index. this scan will be peformed multiple 
-** times (once for each (a,b) combination that matches a=?) is dealt with 
-** by the caller.
-**
-** It does this by scanning through all stat4 samples, comparing values
-** extracted from pLower and pUpper with the corresponding column in each
-** sample. If L and U are the number of samples found to be less than or
-** equal to the values extracted from pLower and pUpper respectively, and
-** N is the total number of samples, the pLoop->nOut value is adjusted
-** as follows:
-**
-**   nOut = nOut * ( min(U - L, 1) / N )
-**
-** If pLower is NULL, or a value cannot be extracted from the term, L is
-** set to zero. If pUpper is NULL, or a value cannot be extracted from it,
-** U is set to N.
-**
-** Normally, this function sets *pbDone to 1 before returning. However,
-** if no value can be extracted from either pLower or pUpper (and so the
-** estimate of the number of rows delivered remains unchanged), *pbDone
-** is left as is.
-**
-** If an error occurs, an SQLite error code is returned. Otherwise, 
-** SQLITE_OK.
-*/
-static int whereRangeSkipScanEst(
-  Parse *pParse,       /* Parsing & code generating context */
-  WhereTerm *pLower,   /* Lower bound on the range. ex: "x>123" Might be NULL */
-  WhereTerm *pUpper,   /* Upper bound on the range. ex: "x<455" Might be NULL */
-  WhereLoop *pLoop,    /* Update the .nOut value of this loop */
-  int *pbDone          /* Set to true if at least one expr. value extracted */
+static void bestBtreeIndex(
+  Parse *pParse,              /* The parsing context */
+  WhereClause *pWC,           /* The WHERE clause */
+  struct SrcList_item *pSrc,  /* The FROM clause term to search */
+  Bitmask notReady,           /* Mask of cursors that are not available */
+  ExprList *pOrderBy,         /* The ORDER BY clause */
+  WhereCost *pCost            /* Lowest cost query plan */
 ){
-  Index *p = pLoop->u.btree.pIndex;
-  int nEq = pLoop->u.btree.nEq;
-  sqlite3 *db = pParse->db;
-  int nLower = -1;
-  int nUpper = p->nSample+1;
-  int rc = SQLITE_OK;
-  u8 aff = sqlite3IndexColumnAffinity(db, p, nEq);
-  CollSeq *pColl;
-  
-  sqlite3_value *p1 = 0;          /* Value extracted from pLower */
-  sqlite3_value *p2 = 0;          /* Value extracted from pUpper */
-  sqlite3_value *pVal = 0;        /* Value extracted from record */
-
-  pColl = sqlite3LocateCollSeq(pParse, p->azColl[nEq]);
-  if( pLower ){
-    rc = sqlite3Stat4ValueFromExpr(pParse, pLower->pExpr->pRight, aff, &p1);
-    nLower = 0;
-  }
-  if( pUpper && rc==SQLITE_OK ){
-    rc = sqlite3Stat4ValueFromExpr(pParse, pUpper->pExpr->pRight, aff, &p2);
-    nUpper = p2 ? 0 : p->nSample;
-  }
+  WhereTerm *pTerm;           /* A single term of the WHERE clause */
+  int iCur = pSrc->iCursor;   /* The cursor of the table to be accessed */
+  Index *pProbe;              /* An index we are evaluating */
+  int rev;                    /* True to scan in reverse order */
+  int wsFlags;                /* Flags associated with pProbe */
+  int nEq;                    /* Number of == or IN constraints */
+  int eqTermMask;             /* Mask of valid equality operators */
+  double cost;                /* Cost of using pProbe */
+  double nRow;                /* Estimated number of rows in result set */
+  int i;                      /* Loop counter */
 
-  if( p1 || p2 ){
-    int i;
-    int nDiff;
-    for(i=0; rc==SQLITE_OK && i<p->nSample; i++){
-      rc = sqlite3Stat4Column(db, p->aSample[i].p, p->aSample[i].n, nEq, &pVal);
-      if( rc==SQLITE_OK && p1 ){
-        int res = sqlite3MemCompare(p1, pVal, pColl);
-        if( res>=0 ) nLower++;
-      }
-      if( rc==SQLITE_OK && p2 ){
-        int res = sqlite3MemCompare(p2, pVal, pColl);
-        if( res>=0 ) nUpper++;
-      }
-    }
-    nDiff = (nUpper - nLower);
-    if( nDiff<=0 ) nDiff = 1;
-
-    /* If there is both an upper and lower bound specified, and the 
-    ** comparisons indicate that they are close together, use the fallback
-    ** method (assume that the scan visits 1/64 of the rows) for estimating
-    ** the number of rows visited. Otherwise, estimate the number of rows
-    ** using the method described in the header comment for this function. */
-    if( nDiff!=1 || pUpper==0 || pLower==0 ){
-      int nAdjust = (sqlite3LogEst(p->nSample) - sqlite3LogEst(nDiff));
-      pLoop->nOut -= nAdjust;
-      *pbDone = 1;
-      WHERETRACE(0x10, ("range skip-scan regions: %u..%u  adjust=%d est=%d\n",
-                           nLower, nUpper, nAdjust*-1, pLoop->nOut));
+  WHERETRACE(("bestIndex: tbl=%s notReady=%llx\n", pSrc->pTab->zName,notReady));
+  pProbe = pSrc->pTab->pIndex;
+  if( pSrc->notIndexed ){
+    pProbe = 0;
+  }
+
+  /* If the table has no indices and there are no terms in the where
+  ** clause that refer to the ROWID, then we will never be able to do
+  ** anything other than a full table scan on this table.  We might as
+  ** well put it first in the join order.  That way, perhaps it can be
+  ** referenced by other tables in the join.
+  */
+  memset(pCost, 0, sizeof(*pCost));
+  if( pProbe==0 &&
+     findTerm(pWC, iCur, -1, 0, WO_EQ|WO_IN|WO_LT|WO_LE|WO_GT|WO_GE,0)==0 &&
+     (pOrderBy==0 || !sortableByRowid(iCur, pOrderBy, pWC->pMaskSet, &rev)) ){
+     if( pParse->db->flags & SQLITE_ReverseOrder ){
+      /* For application testing, randomly reverse the output order for
+      ** SELECT statements that omit the ORDER BY clause.  This will help
+      ** to find cases where
+      */
+      pCost->plan.wsFlags |= WHERE_REVERSE;
     }
-
-  }else{
-    assert( *pbDone==0 );
+    return;
   }
+  pCost->rCost = SQLITE_BIG_DBL;
 
-  sqlite3ValueFree(p1);
-  sqlite3ValueFree(p2);
-  sqlite3ValueFree(pVal);
-
-  return rc;
-}
-#endif /* SQLITE_ENABLE_STAT3_OR_STAT4 */
-
-/*
-** This function is used to estimate the number of rows that will be visited
-** by scanning an index for a range of values. The range may have an upper
-** bound, a lower bound, or both. The WHERE clause terms that set the upper
-** and lower bounds are represented by pLower and pUpper respectively. For
-** example, assuming that index p is on t1(a):
-**
-**   ... FROM t1 WHERE a > ? AND a < ? ...
-**                    |_____|   |_____|
-**                       |         |
-**                     pLower    pUpper
-**
-** If either of the upper or lower bound is not present, then NULL is passed in
-** place of the corresponding WhereTerm.
-**
-** The value in (pBuilder->pNew->u.btree.nEq) is the number of the index
-** column subject to the range constraint. Or, equivalently, the number of
-** equality constraints optimized by the proposed index scan. For example,
-** assuming index p is on t1(a, b), and the SQL query is:
-**
-**   ... FROM t1 WHERE a = ? AND b > ? AND b < ? ...
-**
-** then nEq is set to 1 (as the range restricted column, b, is the second 
-** left-most column of the index). Or, if the query is:
-**
-**   ... FROM t1 WHERE a > ? AND a < ? ...
-**
-** then nEq is set to 0.
-**
-** When this function is called, *pnOut is set to the sqlite3LogEst() of the
-** number of rows that the index scan is expected to visit without 
-** considering the range constraints. If nEq is 0, then *pnOut is the number of 
-** rows in the index. Assuming no error occurs, *pnOut is adjusted (reduced)
-** to account for the range constraints pLower and pUpper.
-** 
-** In the absence of sqlite_stat4 ANALYZE data, or if such data cannot be
-** used, a single range inequality reduces the search space by a factor of 4. 
-** and a pair of constraints (x>? AND x<?) reduces the expected number of
-** rows visited by a factor of 64.
-*/
-static int whereRangeScanEst(
-  Parse *pParse,       /* Parsing & code generating context */
-  WhereLoopBuilder *pBuilder,
-  WhereTerm *pLower,   /* Lower bound on the range. ex: "x>123" Might be NULL */
-  WhereTerm *pUpper,   /* Upper bound on the range. ex: "x<455" Might be NULL */
-  WhereLoop *pLoop     /* Modify the .nOut and maybe .rRun fields */
-){
-  int rc = SQLITE_OK;
-  int nOut = pLoop->nOut;
-  LogEst nNew;
-
-#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
-  Index *p = pLoop->u.btree.pIndex;
-  int nEq = pLoop->u.btree.nEq;
-
-  if( p->nSample>0 && nEq<p->nSampleCol ){
-    if( nEq==pBuilder->nRecValid ){
-      UnpackedRecord *pRec = pBuilder->pRec;
-      tRowcnt a[2];
-      int nBtm = pLoop->u.btree.nBtm;
-      int nTop = pLoop->u.btree.nTop;
-
-      /* Variable iLower will be set to the estimate of the number of rows in 
-      ** the index that are less than the lower bound of the range query. The
-      ** lower bound being the concatenation of $P and $L, where $P is the
-      ** key-prefix formed by the nEq values matched against the nEq left-most
-      ** columns of the index, and $L is the value in pLower.
-      **
-      ** Or, if pLower is NULL or $L cannot be extracted from it (because it
-      ** is not a simple variable or literal value), the lower bound of the
-      ** range is $P. Due to a quirk in the way whereKeyStats() works, even
-      ** if $L is available, whereKeyStats() is called for both ($P) and 
-      ** ($P:$L) and the larger of the two returned values is used.
-      **
-      ** Similarly, iUpper is to be set to the estimate of the number of rows
-      ** less than the upper bound of the range query. Where the upper bound
-      ** is either ($P) or ($P:$U). Again, even if $U is available, both values
-      ** of iUpper are requested of whereKeyStats() and the smaller used.
-      **
-      ** The number of rows between the two bounds is then just iUpper-iLower.
-      */
-      tRowcnt iLower;     /* Rows less than the lower bound */
-      tRowcnt iUpper;     /* Rows less than the upper bound */
-      int iLwrIdx = -2;   /* aSample[] for the lower bound */
-      int iUprIdx = -1;   /* aSample[] for the upper bound */
-
-      if( pRec ){
-        testcase( pRec->nField!=pBuilder->nRecValid );
-        pRec->nField = pBuilder->nRecValid;
-      }
-      /* Determine iLower and iUpper using ($P) only. */
-      if( nEq==0 ){
-        iLower = 0;
-        iUpper = p->nRowEst0;
+  /* Check for a rowid=EXPR or rowid IN (...) constraints. If there was
+  ** an INDEXED BY clause attached to this table, skip this step.
+  */
+  if( !pSrc->pIndex ){
+    pTerm = findTerm(pWC, iCur, -1, notReady, WO_EQ|WO_IN, 0);
+    if( pTerm ){
+      Expr *pExpr;
+      pCost->plan.wsFlags = WHERE_ROWID_EQ;
+      if( pTerm->eOperator & WO_EQ ){
+        /* Rowid== is always the best pick.  Look no further.  Because only
+        ** a single row is generated, output is always in sorted order */
+        pCost->plan.wsFlags = WHERE_ROWID_EQ | WHERE_UNIQUE;
+        pCost->plan.nEq = 1;
+        WHERETRACE(("... best is rowid\n"));
+        pCost->rCost = 0;
+        pCost->nRow = 1;
+        return;
+      }else if( !ExprHasProperty((pExpr = pTerm->pExpr), EP_xIsSelect) 
+             && pExpr->x.pList 
+      ){
+        /* Rowid IN (LIST): cost is NlogN where N is the number of list
+        ** elements.  */
+        pCost->rCost = pCost->nRow = pExpr->x.pList->nExpr;
+        pCost->rCost *= estLog(pCost->rCost);
       }else{
-        /* Note: this call could be optimized away - since the same values must 
-        ** have been requested when testing key $P in whereEqualScanEst().  */
-        whereKeyStats(pParse, p, pRec, 0, a);
-        iLower = a[0];
-        iUpper = a[0] + a[1];
-      }
-
-      assert( pLower==0 || (pLower->eOperator & (WO_GT|WO_GE))!=0 );
-      assert( pUpper==0 || (pUpper->eOperator & (WO_LT|WO_LE))!=0 );
-      assert( p->aSortOrder!=0 );
-      if( p->aSortOrder[nEq] ){
-        /* The roles of pLower and pUpper are swapped for a DESC index */
-        SWAP(WhereTerm*, pLower, pUpper);
-        SWAP(int, nBtm, nTop);
-      }
-
-      /* If possible, improve on the iLower estimate using ($P:$L). */
-      if( pLower ){
-        int n;                    /* Values extracted from pExpr */
-        Expr *pExpr = pLower->pExpr->pRight;
-        rc = sqlite3Stat4ProbeSetValue(pParse, p, &pRec, pExpr, nBtm, nEq, &n);
-        if( rc==SQLITE_OK && n ){
-          tRowcnt iNew;
-          u16 mask = WO_GT|WO_LE;
-          if( sqlite3ExprVectorSize(pExpr)>n ) mask = (WO_LE|WO_LT);
-          iLwrIdx = whereKeyStats(pParse, p, pRec, 0, a);
-          iNew = a[0] + ((pLower->eOperator & mask) ? a[1] : 0);
-          if( iNew>iLower ) iLower = iNew;
-          nOut--;
-          pLower = 0;
-        }
+        /* Rowid IN (SELECT): cost is NlogN where N is the number of rows
+        ** in the result of the inner select.  We have no way to estimate
+        ** that value so make a wild guess. */
+        pCost->nRow = 100;
+        pCost->rCost = 200;
       }
-
-      /* If possible, improve on the iUpper estimate using ($P:$U). */
-      if( pUpper ){
-        int n;                    /* Values extracted from pExpr */
-        Expr *pExpr = pUpper->pExpr->pRight;
-        rc = sqlite3Stat4ProbeSetValue(pParse, p, &pRec, pExpr, nTop, nEq, &n);
-        if( rc==SQLITE_OK && n ){
-          tRowcnt iNew;
-          u16 mask = WO_GT|WO_LE;
-          if( sqlite3ExprVectorSize(pExpr)>n ) mask = (WO_LE|WO_LT);
-          iUprIdx = whereKeyStats(pParse, p, pRec, 1, a);
-          iNew = a[0] + ((pUpper->eOperator & mask) ? a[1] : 0);
-          if( iNew<iUpper ) iUpper = iNew;
-          nOut--;
-          pUpper = 0;
-        }
+      WHERETRACE(("... rowid IN cost: %.9g\n", pCost->rCost));
+    }
+  
+    /* Estimate the cost of a table scan.  If we do not know how many
+    ** entries are in the table, use 1 million as a guess.
+    */
+    cost = pProbe ? pProbe->aiRowEst[0] : 1000000;
+    WHERETRACE(("... table scan base cost: %.9g\n", cost));
+    wsFlags = WHERE_ROWID_RANGE;
+  
+    /* Check for constraints on a range of rowids in a table scan.
+    */
+    pTerm = findTerm(pWC, iCur, -1, notReady, WO_LT|WO_LE|WO_GT|WO_GE, 0);
+    if( pTerm ){
+      if( findTerm(pWC, iCur, -1, notReady, WO_LT|WO_LE, 0) ){
+        wsFlags |= WHERE_TOP_LIMIT;
+        cost /= 3;  /* Guess that rowid<EXPR eliminates two-thirds of rows */
       }
-
-      pBuilder->pRec = pRec;
-      if( rc==SQLITE_OK ){
-        if( iUpper>iLower ){
-          nNew = sqlite3LogEst(iUpper - iLower);
-          /* TUNING:  If both iUpper and iLower are derived from the same
-          ** sample, then assume they are 4x more selective.  This brings
-          ** the estimated selectivity more in line with what it would be
-          ** if estimated without the use of STAT3/4 tables. */
-          if( iLwrIdx==iUprIdx ) nNew -= 20;  assert( 20==sqlite3LogEst(4) );
-        }else{
-          nNew = 10;        assert( 10==sqlite3LogEst(2) );
-        }
-        if( nNew<nOut ){
-          nOut = nNew;
-        }
-        WHERETRACE(0x10, ("STAT4 range scan: %u..%u  est=%d\n",
-                           (u32)iLower, (u32)iUpper, nOut));
+      if( findTerm(pWC, iCur, -1, notReady, WO_GT|WO_GE, 0) ){
+        wsFlags |= WHERE_BTM_LIMIT;
+        cost /= 3;  /* Guess that rowid>EXPR eliminates two-thirds of rows */
       }
+      WHERETRACE(("... rowid range reduces cost to %.9g\n", cost));
     }else{
-      int bDone = 0;
-      rc = whereRangeSkipScanEst(pParse, pLower, pUpper, pLoop, &bDone);
-      if( bDone ) return rc;
+      wsFlags = 0;
     }
-  }
-#else
-  UNUSED_PARAMETER(pParse);
-  UNUSED_PARAMETER(pBuilder);
-  assert( pLower || pUpper );
-#endif
-  assert( pUpper==0 || (pUpper->wtFlags & TERM_VNULL)==0 );
-  nNew = whereRangeAdjust(pLower, nOut);
-  nNew = whereRangeAdjust(pUpper, nNew);
-
-  /* TUNING: If there is both an upper and lower limit and neither limit
-  ** has an application-defined likelihood(), assume the range is
-  ** reduced by an additional 75%. This means that, by default, an open-ended
-  ** range query (e.g. col > ?) is assumed to match 1/4 of the rows in the
-  ** index. While a closed range (e.g. col BETWEEN ? AND ?) is estimated to
-  ** match 1/64 of the index. */ 
-  if( pLower && pLower->truthProb>0 && pUpper && pUpper->truthProb>0 ){
-    nNew -= 20;
-  }
-
-  nOut -= (pLower!=0) + (pUpper!=0);
-  if( nNew<10 ) nNew = 10;
-  if( nNew<nOut ) nOut = nNew;
-#if defined(WHERETRACE_ENABLED)
-  if( pLoop->nOut>nOut ){
-    WHERETRACE(0x10,("Range scan lowers nOut from %d to %d\n",
-                    pLoop->nOut, nOut));
-  }
-#endif
-  pLoop->nOut = (LogEst)nOut;
-  return rc;
-}
-
-#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
-/*
-** Estimate the number of rows that will be returned based on
-** an equality constraint x=VALUE and where that VALUE occurs in
-** the histogram data.  This only works when x is the left-most
-** column of an index and sqlite_stat3 histogram data is available
-** for that index.  When pExpr==NULL that means the constraint is
-** "x IS NULL" instead of "x=VALUE".
-**
-** Write the estimated row count into *pnRow and return SQLITE_OK. 
-** If unable to make an estimate, leave *pnRow unchanged and return
-** non-zero.
-**
-** This routine can fail if it is unable to load a collating sequence
-** required for string comparison, or if unable to allocate memory
-** for a UTF conversion required for comparison.  The error is stored
-** in the pParse structure.
-*/
-static int whereEqualScanEst(
-  Parse *pParse,       /* Parsing & code generating context */
-  WhereLoopBuilder *pBuilder,
-  Expr *pExpr,         /* Expression for VALUE in the x=VALUE constraint */
-  tRowcnt *pnRow       /* Write the revised row estimate here */
-){
-  Index *p = pBuilder->pNew->u.btree.pIndex;
-  int nEq = pBuilder->pNew->u.btree.nEq;
-  UnpackedRecord *pRec = pBuilder->pRec;
-  int rc;                   /* Subfunction return code */
-  tRowcnt a[2];             /* Statistics */
-  int bOk;
-
-  assert( nEq>=1 );
-  assert( nEq<=p->nColumn );
-  assert( p->aSample!=0 );
-  assert( p->nSample>0 );
-  assert( pBuilder->nRecValid<nEq );
-
-  /* If values are not available for all fields of the index to the left
-  ** of this one, no estimate can be made. Return SQLITE_NOTFOUND. */
-  if( pBuilder->nRecValid<(nEq-1) ){
-    return SQLITE_NOTFOUND;
-  }
-
-  /* This is an optimization only. The call to sqlite3Stat4ProbeSetValue()
-  ** below would return the same value.  */
-  if( nEq>=p->nColumn ){
-    *pnRow = 1;
-    return SQLITE_OK;
-  }
-
-  rc = sqlite3Stat4ProbeSetValue(pParse, p, &pRec, pExpr, 1, nEq-1, &bOk);
-  pBuilder->pRec = pRec;
-  if( rc!=SQLITE_OK ) return rc;
-  if( bOk==0 ) return SQLITE_NOTFOUND;
-  pBuilder->nRecValid = nEq;
-
-  whereKeyStats(pParse, p, pRec, 0, a);
-  WHERETRACE(0x10,("equality scan regions %s(%d): %d\n",
-                   p->zName, nEq-1, (int)a[1]));
-  *pnRow = a[1];
+    nRow = cost;
   
-  return rc;
-}
-#endif /* SQLITE_ENABLE_STAT3_OR_STAT4 */
-
-#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
-/*
-** Estimate the number of rows that will be returned based on
-** an IN constraint where the right-hand side of the IN operator
-** is a list of values.  Example:
-**
-**        WHERE x IN (1,2,3,4)
-**
-** Write the estimated row count into *pnRow and return SQLITE_OK. 
-** If unable to make an estimate, leave *pnRow unchanged and return
-** non-zero.
-**
-** This routine can fail if it is unable to load a collating sequence
-** required for string comparison, or if unable to allocate memory
-** for a UTF conversion required for comparison.  The error is stored
-** in the pParse structure.
-*/
-static int whereInScanEst(
-  Parse *pParse,       /* Parsing & code generating context */
-  WhereLoopBuilder *pBuilder,
-  ExprList *pList,     /* The value list on the RHS of "x IN (v1,v2,v3,...)" */
-  tRowcnt *pnRow       /* Write the revised row estimate here */
-){
-  Index *p = pBuilder->pNew->u.btree.pIndex;
-  i64 nRow0 = sqlite3LogEstToInt(p->aiRowLogEst[0]);
-  int nRecValid = pBuilder->nRecValid;
-  int rc = SQLITE_OK;     /* Subfunction return code */
-  tRowcnt nEst;           /* Number of rows for a single term */
-  tRowcnt nRowEst = 0;    /* New estimate of the number of rows */
-  int i;                  /* Loop counter */
-
-  assert( p->aSample!=0 );
-  for(i=0; rc==SQLITE_OK && i<pList->nExpr; i++){
-    nEst = nRow0;
-    rc = whereEqualScanEst(pParse, pBuilder, pList->a[i].pExpr, &nEst);
-    nRowEst += nEst;
-    pBuilder->nRecValid = nRecValid;
-  }
+    /* If the table scan does not satisfy the ORDER BY clause, increase
+    ** the cost by NlogN to cover the expense of sorting. */
+    if( pOrderBy ){
+      if( sortableByRowid(iCur, pOrderBy, pWC->pMaskSet, &rev) ){
+        wsFlags |= WHERE_ORDERBY|WHERE_ROWID_RANGE;
+        if( rev ){
+          wsFlags |= WHERE_REVERSE;
+        }
+      }else{
+        cost += cost*estLog(cost);
+        WHERETRACE(("... sorting increases cost to %.9g\n", cost));
+      }
+    }else if( pParse->db->flags & SQLITE_ReverseOrder ){
+      /* For application testing, randomly reverse the output order for
+      ** SELECT statements that omit the ORDER BY clause.  This will help
+      ** to find cases where
+      */
+      wsFlags |= WHERE_REVERSE;
+    }
 
-  if( rc==SQLITE_OK ){
-    if( nRowEst > nRow0 ) nRowEst = nRow0;
-    *pnRow = nRowEst;
-    WHERETRACE(0x10,("IN row estimate: est=%d\n", nRowEst));
+    /* Remember this case if it is the best so far */
+    if( cost<pCost->rCost ){
+      pCost->rCost = cost;
+      pCost->nRow = nRow;
+      pCost->plan.wsFlags = wsFlags;
+    }
   }
-  assert( pBuilder->nRecValid==nRecValid );
-  return rc;
-}
-#endif /* SQLITE_ENABLE_STAT3_OR_STAT4 */
 
+  bestOrClauseIndex(pParse, pWC, pSrc, notReady, pOrderBy, pCost);
 
-#ifdef WHERETRACE_ENABLED
-/*
-** Print the content of a WhereTerm object
-*/
-static void whereTermPrint(WhereTerm *pTerm, int iTerm){
-  if( pTerm==0 ){
-    sqlite3DebugPrintf("TERM-%-3d NULL\n", iTerm);
+  /* If the pSrc table is the right table of a LEFT JOIN then we may not
+  ** use an index to satisfy IS NULL constraints on that table.  This is
+  ** because columns might end up being NULL if the table does not match -
+  ** a circumstance which the index cannot help us discover.  Ticket #2177.
+  */
+  if( (pSrc->jointype & JT_LEFT)!=0 ){
+    eqTermMask = WO_EQ|WO_IN;
   }else{
-    char zType[4];
-    char zLeft[50];
-    memcpy(zType, "...", 4);
-    if( pTerm->wtFlags & TERM_VIRTUAL ) zType[0] = 'V';
-    if( pTerm->eOperator & WO_EQUIV  ) zType[1] = 'E';
-    if( ExprHasProperty(pTerm->pExpr, EP_FromJoin) ) zType[2] = 'L';
-    if( pTerm->eOperator & WO_SINGLE ){
-      sqlite3_snprintf(sizeof(zLeft),zLeft,"left={%d:%d}",
-                       pTerm->leftCursor, pTerm->u.leftColumn);
-    }else if( (pTerm->eOperator & WO_OR)!=0 && pTerm->u.pOrInfo!=0 ){
-      sqlite3_snprintf(sizeof(zLeft),zLeft,"indexable=0x%lld", 
-                       pTerm->u.pOrInfo->indexable);
-    }else{
-      sqlite3_snprintf(sizeof(zLeft),zLeft,"left=%d", pTerm->leftCursor);
-    }
-    sqlite3DebugPrintf(
-       "TERM-%-3d %p %s %-12s prob=%-3d op=0x%03x wtFlags=0x%04x",
-       iTerm, pTerm, zType, zLeft, pTerm->truthProb,
-       pTerm->eOperator, pTerm->wtFlags);
-    if( pTerm->iField ){
-      sqlite3DebugPrintf(" iField=%d\n", pTerm->iField);
-    }else{
-      sqlite3DebugPrintf("\n");
-    }
-    sqlite3TreeViewExpr(0, pTerm->pExpr, 0);
+    eqTermMask = WO_EQ|WO_IN|WO_ISNULL;
   }
-}
-#endif
 
-#ifdef WHERETRACE_ENABLED
-/*
-** Show the complete content of a WhereClause
-*/
-void sqlite3WhereClausePrint(WhereClause *pWC){
-  int i;
-  for(i=0; i<pWC->nTerm; i++){
-    whereTermPrint(&pWC->a[i], i);
+  /* Look at each index.
+  */
+  if( pSrc->pIndex ){
+    pProbe = pSrc->pIndex;
   }
-}
-#endif
+  for(; pProbe; pProbe=(pSrc->pIndex ? 0 : pProbe->pNext)){
+    double inMultiplier = 1;  /* Number of equality look-ups needed */
+    int inMultIsEst = 0;      /* True if inMultiplier is an estimate */
 
-#ifdef WHERETRACE_ENABLED
-/*
-** Print a WhereLoop object for debugging purposes
-*/
-static void whereLoopPrint(WhereLoop *p, WhereClause *pWC){
-  WhereInfo *pWInfo = pWC->pWInfo;
-  int nb = 1+(pWInfo->pTabList->nSrc+3)/4;
-  struct SrcList_item *pItem = pWInfo->pTabList->a + p->iTab;
-  Table *pTab = pItem->pTab;
-  Bitmask mAll = (((Bitmask)1)<<(nb*4)) - 1;
-  sqlite3DebugPrintf("%c%2d.%0*llx.%0*llx", p->cId,
-                     p->iTab, nb, p->maskSelf, nb, p->prereq & mAll);
-  sqlite3DebugPrintf(" %12s",
-                     pItem->zAlias ? pItem->zAlias : pTab->zName);
-  if( (p->wsFlags & WHERE_VIRTUALTABLE)==0 ){
-    const char *zName;
-    if( p->u.btree.pIndex && (zName = p->u.btree.pIndex->zName)!=0 ){
-      if( strncmp(zName, "sqlite_autoindex_", 17)==0 ){
-        int i = sqlite3Strlen30(zName) - 1;
-        while( zName[i]!='_' ) i--;
-        zName += i;
+    WHERETRACE(("... index %s:\n", pProbe->zName));
+
+    /* Count the number of columns in the index that are satisfied
+    ** by x=EXPR or x IS NULL constraints or x IN (...) constraints.
+    ** For a term of the form x=EXPR or x IS NULL we only have to do 
+    ** a single binary search.  But for x IN (...) we have to do a
+    ** number of binary searched
+    ** equal to the number of entries on the RHS of the IN operator.
+    ** The inMultipler variable with try to estimate the number of
+    ** binary searches needed.
+    */
+    wsFlags = 0;
+    for(i=0; i<pProbe->nColumn; i++){
+      int j = pProbe->aiColumn[i];
+      pTerm = findTerm(pWC, iCur, j, notReady, eqTermMask, pProbe);
+      if( pTerm==0 ) break;
+      wsFlags |= WHERE_COLUMN_EQ;
+      if( pTerm->eOperator & WO_IN ){
+        Expr *pExpr = pTerm->pExpr;
+        wsFlags |= WHERE_COLUMN_IN;
+        if( ExprHasProperty(pExpr, EP_xIsSelect) ){
+          inMultiplier *= 25;
+          inMultIsEst = 1;
+        }else if( pExpr->x.pList ){
+          inMultiplier *= pExpr->x.pList->nExpr + 1;
+        }
+      }else if( pTerm->eOperator & WO_ISNULL ){
+        wsFlags |= WHERE_COLUMN_NULL;
+      }
+    }
+    nRow = pProbe->aiRowEst[i] * inMultiplier;
+    /* If inMultiplier is an estimate and that estimate results in an
+    ** nRow it that is more than half number of rows in the table,
+    ** then reduce inMultipler */
+    if( inMultIsEst && nRow*2 > pProbe->aiRowEst[0] ){
+      nRow = pProbe->aiRowEst[0]/2;
+      inMultiplier = nRow/pProbe->aiRowEst[i];
+    }
+    cost = nRow + inMultiplier*estLog(pProbe->aiRowEst[0]);
+    nEq = i;
+    if( pProbe->onError!=OE_None && nEq==pProbe->nColumn ){
+      testcase( wsFlags & WHERE_COLUMN_IN );
+      testcase( wsFlags & WHERE_COLUMN_NULL );
+      if( (wsFlags & (WHERE_COLUMN_IN|WHERE_COLUMN_NULL))==0 ){
+        wsFlags |= WHERE_UNIQUE;
       }
-      sqlite3DebugPrintf(".%-16s %2d", zName, p->u.btree.nEq);
-    }else{
-      sqlite3DebugPrintf("%20s","");
-    }
-  }else{
-    char *z;
-    if( p->u.vtab.idxStr ){
-      z = sqlite3_mprintf("(%d,\"%s\",%x)",
-                p->u.vtab.idxNum, p->u.vtab.idxStr, p->u.vtab.omitMask);
-    }else{
-      z = sqlite3_mprintf("(%d,%x)", p->u.vtab.idxNum, p->u.vtab.omitMask);
-    }
-    sqlite3DebugPrintf(" %-19s", z);
-    sqlite3_free(z);
-  }
-  if( p->wsFlags & WHERE_SKIPSCAN ){
-    sqlite3DebugPrintf(" f %05x %d-%d", p->wsFlags, p->nLTerm,p->nSkip);
-  }else{
-    sqlite3DebugPrintf(" f %05x N %d", p->wsFlags, p->nLTerm);
-  }
-  sqlite3DebugPrintf(" cost %d,%d,%d\n", p->rSetup, p->rRun, p->nOut);
-  if( p->nLTerm && (sqlite3WhereTrace & 0x100)!=0 ){
-    int i;
-    for(i=0; i<p->nLTerm; i++){
-      whereTermPrint(p->aLTerm[i], i);
     }
-  }
-}
-#endif
-
-/*
-** Convert bulk memory into a valid WhereLoop that can be passed
-** to whereLoopClear harmlessly.
-*/
-static void whereLoopInit(WhereLoop *p){
-  p->aLTerm = p->aLTermSpace;
-  p->nLTerm = 0;
-  p->nLSlot = ArraySize(p->aLTermSpace);
-  p->wsFlags = 0;
-}
+    WHERETRACE(("...... nEq=%d inMult=%.9g nRow=%.9g cost=%.9g\n",
+                nEq, inMultiplier, nRow, cost));
 
-/*
-** Clear the WhereLoop.u union.  Leave WhereLoop.pLTerm intact.
-*/
-static void whereLoopClearUnion(sqlite3 *db, WhereLoop *p){
-  if( p->wsFlags & (WHERE_VIRTUALTABLE|WHERE_AUTO_INDEX) ){
-    if( (p->wsFlags & WHERE_VIRTUALTABLE)!=0 && p->u.vtab.needFree ){
-      sqlite3_free(p->u.vtab.idxStr);
-      p->u.vtab.needFree = 0;
-      p->u.vtab.idxStr = 0;
-    }else if( (p->wsFlags & WHERE_AUTO_INDEX)!=0 && p->u.btree.pIndex!=0 ){
-      sqlite3DbFree(db, p->u.btree.pIndex->zColAff);
-      sqlite3DbFreeNN(db, p->u.btree.pIndex);
-      p->u.btree.pIndex = 0;
+    /* Look for range constraints.  Assume that each range constraint
+    ** makes the search space 1/3rd smaller.
+    */
+    if( nEq<pProbe->nColumn ){
+      int j = pProbe->aiColumn[nEq];
+      pTerm = findTerm(pWC, iCur, j, notReady, WO_LT|WO_LE|WO_GT|WO_GE, pProbe);
+      if( pTerm ){
+        wsFlags |= WHERE_COLUMN_RANGE;
+        if( findTerm(pWC, iCur, j, notReady, WO_LT|WO_LE, pProbe) ){
+          wsFlags |= WHERE_TOP_LIMIT;
+          cost /= 3;
+          nRow /= 3;
+        }
+        if( findTerm(pWC, iCur, j, notReady, WO_GT|WO_GE, pProbe) ){
+          wsFlags |= WHERE_BTM_LIMIT;
+          cost /= 3;
+          nRow /= 3;
+        }
+        WHERETRACE(("...... range reduces nRow to %.9g and cost to %.9g\n",
+                    nRow, cost));
+      }
     }
-  }
-}
-
-/*
-** Deallocate internal memory used by a WhereLoop object
-*/
-static void whereLoopClear(sqlite3 *db, WhereLoop *p){
-  if( p->aLTerm!=p->aLTermSpace ) sqlite3DbFreeNN(db, p->aLTerm);
-  whereLoopClearUnion(db, p);
-  whereLoopInit(p);
-}
-
-/*
-** Increase the memory allocation for pLoop->aLTerm[] to be at least n.
-*/
-static int whereLoopResize(sqlite3 *db, WhereLoop *p, int n){
-  WhereTerm **paNew;
-  if( p->nLSlot>=n ) return SQLITE_OK;
-  n = (n+7)&~7;
-  paNew = sqlite3DbMallocRawNN(db, sizeof(p->aLTerm[0])*n);
-  if( paNew==0 ) return SQLITE_NOMEM_BKPT;
-  memcpy(paNew, p->aLTerm, sizeof(p->aLTerm[0])*p->nLSlot);
-  if( p->aLTerm!=p->aLTermSpace ) sqlite3DbFreeNN(db, p->aLTerm);
-  p->aLTerm = paNew;
-  p->nLSlot = n;
-  return SQLITE_OK;
-}
-
-/*
-** Transfer content from the second pLoop into the first.
-*/
-static int whereLoopXfer(sqlite3 *db, WhereLoop *pTo, WhereLoop *pFrom){
-  whereLoopClearUnion(db, pTo);
-  if( whereLoopResize(db, pTo, pFrom->nLTerm) ){
-    memset(&pTo->u, 0, sizeof(pTo->u));
-    return SQLITE_NOMEM_BKPT;
-  }
-  memcpy(pTo, pFrom, WHERE_LOOP_XFER_SZ);
-  memcpy(pTo->aLTerm, pFrom->aLTerm, pTo->nLTerm*sizeof(pTo->aLTerm[0]));
-  if( pFrom->wsFlags & WHERE_VIRTUALTABLE ){
-    pFrom->u.vtab.needFree = 0;
-  }else if( (pFrom->wsFlags & WHERE_AUTO_INDEX)!=0 ){
-    pFrom->u.btree.pIndex = 0;
-  }
-  return SQLITE_OK;
-}
 
-/*
-** Delete a WhereLoop object
-*/
-static void whereLoopDelete(sqlite3 *db, WhereLoop *p){
-  whereLoopClear(db, p);
-  sqlite3DbFreeNN(db, p);
-}
+    /* Add the additional cost of sorting if that is a factor.
+    */
+    if( pOrderBy ){
+      if( (wsFlags & (WHERE_COLUMN_IN|WHERE_COLUMN_NULL))==0
+       && isSortingIndex(pParse,pWC->pMaskSet,pProbe,iCur,pOrderBy,nEq,&rev)
+      ){
+        if( wsFlags==0 ){
+          wsFlags = WHERE_COLUMN_RANGE;
+        }
+        wsFlags |= WHERE_ORDERBY;
+        if( rev ){
+          wsFlags |= WHERE_REVERSE;
+        }
+      }else{
+        cost += cost*estLog(cost);
+        WHERETRACE(("...... orderby increases cost to %.9g\n", cost));
+      }
+    }else if( wsFlags!=0 && (pParse->db->flags & SQLITE_ReverseOrder)!=0 ){
+      /* For application testing, randomly reverse the output order for
+      ** SELECT statements that omit the ORDER BY clause.  This will help
+      ** to find cases where
+      */
+      wsFlags |= WHERE_REVERSE;
+    }
 
-/*
-** Free a WhereInfo structure
-*/
-static void whereInfoFree(sqlite3 *db, WhereInfo *pWInfo){
-  if( ALWAYS(pWInfo) ){
-    int i;
-    for(i=0; i<pWInfo->nLevel; i++){
-      WhereLevel *pLevel = &pWInfo->a[i];
-      if( pLevel->pWLoop && (pLevel->pWLoop->wsFlags & WHERE_IN_ABLE) ){
-        sqlite3DbFree(db, pLevel->u.in.aInLoop);
+    /* Check to see if we can get away with using just the index without
+    ** ever reading the table.  If that is the case, then halve the
+    ** cost of this index.
+    */
+    if( wsFlags && pSrc->colUsed < (((Bitmask)1)<<(BMS-1)) ){
+      Bitmask m = pSrc->colUsed;
+      int j;
+      for(j=0; j<pProbe->nColumn; j++){
+        int x = pProbe->aiColumn[j];
+        if( x<BMS-1 ){
+          m &= ~(((Bitmask)1)<<x);
+        }
+      }
+      if( m==0 ){
+        wsFlags |= WHERE_IDX_ONLY;
+        cost /= 2;
+        WHERETRACE(("...... idx-only reduces cost to %.9g\n", cost));
       }
     }
-    sqlite3WhereClauseClear(&pWInfo->sWC);
-    while( pWInfo->pLoops ){
-      WhereLoop *p = pWInfo->pLoops;
-      pWInfo->pLoops = p->pNextLoop;
-      whereLoopDelete(db, p);
+
+    /* If this index has achieved the lowest cost so far, then use it.
+    */
+    if( wsFlags!=0 && cost < pCost->rCost ){
+      pCost->rCost = cost;
+      pCost->nRow = nRow;
+      pCost->plan.wsFlags = wsFlags;
+      pCost->plan.nEq = nEq;
+      assert( pCost->plan.wsFlags & WHERE_INDEXED );
+      pCost->plan.u.pIdx = pProbe;
     }
-    sqlite3DbFreeNN(db, pWInfo);
   }
+
+  /* Report the best result
+  */
+  pCost->plan.wsFlags |= eqTermMask;
+  WHERETRACE(("best index is %s, cost=%.9g, nrow=%.9g, wsFlags=%x, nEq=%d\n",
+        (pCost->plan.wsFlags & WHERE_INDEXED)!=0 ?
+             pCost->plan.u.pIdx->zName : "(none)", pCost->nRow,
+        pCost->rCost, pCost->plan.wsFlags, pCost->plan.nEq));
 }
 
 /*
-** Return TRUE if all of the following are true:
-**
-**   (1)  X has the same or lower cost that Y
-**   (2)  X users fewer WHERE clause terms than Y
-**   (3)  Every WHERE clause term used by X is also used by Y
-**   (4)  X skips at least as many columns as Y
-**   (5)  If X is a covering index, than Y is too
-**
-** Conditions (2) and (3) mean that X is a "proper subset" of Y.
-** If X is a proper subset of Y then Y is a better choice and ought
-** to have a lower cost.  This routine returns TRUE when that cost 
-** relationship is inverted and needs to be adjusted.  Constraint (4)
-** was added because if X uses skip-scan less than Y it still might
-** deserve a lower cost even if it is a proper subset of Y.
+** Find the query plan for accessing table pSrc->pTab. Write the
+** best query plan and its cost into the WhereCost object supplied 
+** as the last parameter. This function may calculate the cost of
+** both real and virtual table scans.
 */
-static int whereLoopCheaperProperSubset(
-  const WhereLoop *pX,       /* First WhereLoop to compare */
-  const WhereLoop *pY        /* Compare against this WhereLoop */
+static void bestIndex(
+  Parse *pParse,              /* The parsing context */
+  WhereClause *pWC,           /* The WHERE clause */
+  struct SrcList_item *pSrc,  /* The FROM clause term to search */
+  Bitmask notReady,           /* Mask of cursors that are not available */
+  ExprList *pOrderBy,         /* The ORDER BY clause */
+  WhereCost *pCost            /* Lowest cost query plan */
 ){
-  int i, j;
-  if( pX->nLTerm-pX->nSkip >= pY->nLTerm-pY->nSkip ){
-    return 0; /* X is not a subset of Y */
-  }
-  if( pY->nSkip > pX->nSkip ) return 0;
-  if( pX->rRun >= pY->rRun ){
-    if( pX->rRun > pY->rRun ) return 0;    /* X costs more than Y */
-    if( pX->nOut > pY->nOut ) return 0;    /* X costs more than Y */
-  }
-  for(i=pX->nLTerm-1; i>=0; i--){
-    if( pX->aLTerm[i]==0 ) continue;
-    for(j=pY->nLTerm-1; j>=0; j--){
-      if( pY->aLTerm[j]==pX->aLTerm[i] ) break;
+  if( IsVirtual(pSrc->pTab) ){
+    sqlite3_index_info *p = 0;
+    bestVirtualIndex(pParse, pWC, pSrc, notReady, pOrderBy, pCost, &p);
+    if( p->needToFreeIdxStr ){
+      sqlite3_free(p->idxStr);
     }
-    if( j<0 ) return 0;  /* X not a subset of Y since term X[i] not used by Y */
-  }
-  if( (pX->wsFlags&WHERE_IDX_ONLY)!=0 
-   && (pY->wsFlags&WHERE_IDX_ONLY)==0 ){
-    return 0;  /* Constraint (5) */
+    sqlite3DbFree(pParse->db, p);
+  }else{
+    bestBtreeIndex(pParse, pWC, pSrc, notReady, pOrderBy, pCost);
   }
-  return 1;  /* All conditions meet */
 }
 
 /*
-** Try to adjust the cost of WhereLoop pTemplate upwards or downwards so
-** that:
+** Disable a term in the WHERE clause.  Except, do not disable the term
+** if it controls a LEFT OUTER JOIN and it did not originate in the ON
+** or USING clause of that join.
+**
+** Consider the term t2.z='ok' in the following queries:
 **
-**   (1) pTemplate costs less than any other WhereLoops that are a proper
-**       subset of pTemplate
+**   (1)  SELECT * FROM t1 LEFT JOIN t2 ON t1.a=t2.x WHERE t2.z='ok'
+**   (2)  SELECT * FROM t1 LEFT JOIN t2 ON t1.a=t2.x AND t2.z='ok'
+**   (3)  SELECT * FROM t1, t2 WHERE t1.a=t2.x AND t2.z='ok'
 **
-**   (2) pTemplate costs more than any other WhereLoops for which pTemplate
-**       is a proper subset.
+** The t2.z='ok' is disabled in the in (2) because it originates
+** in the ON clause.  The term is disabled in (3) because it is not part
+** of a LEFT OUTER JOIN.  In (1), the term is not disabled.
 **
-** To say "WhereLoop X is a proper subset of Y" means that X uses fewer
-** WHERE clause terms than Y and that every WHERE clause term used by X is
-** also used by Y.
+** Disabling a term causes that term to not be tested in the inner loop
+** of the join.  Disabling is an optimization.  When terms are satisfied
+** by indices, we disable them to prevent redundant tests in the inner
+** loop.  We would get the correct results if nothing were ever disabled,
+** but joins might run a little slower.  The trick is to disable as much
+** as we can without disabling too much.  If we disabled in (1), we'd get
+** the wrong answer.  See ticket #813.
 */
-static void whereLoopAdjustCost(const WhereLoop *p, WhereLoop *pTemplate){
-  if( (pTemplate->wsFlags & WHERE_INDEXED)==0 ) return;
-  for(; p; p=p->pNextLoop){
-    if( p->iTab!=pTemplate->iTab ) continue;
-    if( (p->wsFlags & WHERE_INDEXED)==0 ) continue;
-    if( whereLoopCheaperProperSubset(p, pTemplate) ){
-      /* Adjust pTemplate cost downward so that it is cheaper than its 
-      ** subset p. */
-      WHERETRACE(0x80,("subset cost adjustment %d,%d to %d,%d\n",
-                       pTemplate->rRun, pTemplate->nOut, p->rRun, p->nOut-1));
-      pTemplate->rRun = p->rRun;
-      pTemplate->nOut = p->nOut - 1;
-    }else if( whereLoopCheaperProperSubset(pTemplate, p) ){
-      /* Adjust pTemplate cost upward so that it is costlier than p since
-      ** pTemplate is a proper subset of p */
-      WHERETRACE(0x80,("subset cost adjustment %d,%d to %d,%d\n",
-                       pTemplate->rRun, pTemplate->nOut, p->rRun, p->nOut+1));
-      pTemplate->rRun = p->rRun;
-      pTemplate->nOut = p->nOut + 1;
+static void disableTerm(WhereLevel *pLevel, WhereTerm *pTerm){
+  if( pTerm
+      && ALWAYS((pTerm->wtFlags & TERM_CODED)==0)
+      && (pLevel->iLeftJoin==0 || ExprHasProperty(pTerm->pExpr, EP_FromJoin))
+  ){
+    pTerm->wtFlags |= TERM_CODED;
+    if( pTerm->iParent>=0 ){
+      WhereTerm *pOther = &pTerm->pWC->a[pTerm->iParent];
+      if( (--pOther->nChild)==0 ){
+        disableTerm(pLevel, pOther);
+      }
     }
   }
 }
 
 /*
-** Search the list of WhereLoops in *ppPrev looking for one that can be
-** replaced by pTemplate.
-**
-** Return NULL if pTemplate does not belong on the WhereLoop list.
-** In other words if pTemplate ought to be dropped from further consideration.
-**
-** If pX is a WhereLoop that pTemplate can replace, then return the
-** link that points to pX.
-**
-** If pTemplate cannot replace any existing element of the list but needs
-** to be added to the list as a new entry, then return a pointer to the
-** tail of the list.
+** Apply the affinities associated with the first n columns of index
+** pIdx to the values in the n registers starting at base.
 */
-static WhereLoop **whereLoopFindLesser(
-  WhereLoop **ppPrev,
-  const WhereLoop *pTemplate
-){
-  WhereLoop *p;
-  for(p=(*ppPrev); p; ppPrev=&p->pNextLoop, p=*ppPrev){
-    if( p->iTab!=pTemplate->iTab || p->iSortIdx!=pTemplate->iSortIdx ){
-      /* If either the iTab or iSortIdx values for two WhereLoop are different
-      ** then those WhereLoops need to be considered separately.  Neither is
-      ** a candidate to replace the other. */
-      continue;
-    }
-    /* In the current implementation, the rSetup value is either zero
-    ** or the cost of building an automatic index (NlogN) and the NlogN
-    ** is the same for compatible WhereLoops. */
-    assert( p->rSetup==0 || pTemplate->rSetup==0 
-                 || p->rSetup==pTemplate->rSetup );
-
-    /* whereLoopAddBtree() always generates and inserts the automatic index
-    ** case first.  Hence compatible candidate WhereLoops never have a larger
-    ** rSetup. Call this SETUP-INVARIANT */
-    assert( p->rSetup>=pTemplate->rSetup );
-
-    /* Any loop using an appliation-defined index (or PRIMARY KEY or
-    ** UNIQUE constraint) with one or more == constraints is better
-    ** than an automatic index. Unless it is a skip-scan. */
-    if( (p->wsFlags & WHERE_AUTO_INDEX)!=0
-     && (pTemplate->nSkip)==0
-     && (pTemplate->wsFlags & WHERE_INDEXED)!=0
-     && (pTemplate->wsFlags & WHERE_COLUMN_EQ)!=0
-     && (p->prereq & pTemplate->prereq)==pTemplate->prereq
-    ){
-      break;
-    }
-
-    /* If existing WhereLoop p is better than pTemplate, pTemplate can be
-    ** discarded.  WhereLoop p is better if:
-    **   (1)  p has no more dependencies than pTemplate, and
-    **   (2)  p has an equal or lower cost than pTemplate
-    */
-    if( (p->prereq & pTemplate->prereq)==p->prereq    /* (1)  */
-     && p->rSetup<=pTemplate->rSetup                  /* (2a) */
-     && p->rRun<=pTemplate->rRun                      /* (2b) */
-     && p->nOut<=pTemplate->nOut                      /* (2c) */
-    ){
-      return 0;  /* Discard pTemplate */
-    }
-
-    /* If pTemplate is always better than p, then cause p to be overwritten
-    ** with pTemplate.  pTemplate is better than p if:
-    **   (1)  pTemplate has no more dependences than p, and
-    **   (2)  pTemplate has an equal or lower cost than p.
-    */
-    if( (p->prereq & pTemplate->prereq)==pTemplate->prereq   /* (1)  */
-     && p->rRun>=pTemplate->rRun                             /* (2a) */
-     && p->nOut>=pTemplate->nOut                             /* (2b) */
-    ){
-      assert( p->rSetup>=pTemplate->rSetup ); /* SETUP-INVARIANT above */
-      break;   /* Cause p to be overwritten by pTemplate */
-    }
+static void codeApplyAffinity(Parse *pParse, int base, int n, Index *pIdx){
+  if( n>0 ){
+    Vdbe *v = pParse->pVdbe;
+    assert( v!=0 );
+    sqlite3VdbeAddOp2(v, OP_Affinity, base, n);
+    sqlite3IndexAffinityStr(v, pIdx);
+    sqlite3ExprCacheAffinityChange(pParse, base, n);
   }
-  return ppPrev;
 }
 
+
 /*
-** Insert or replace a WhereLoop entry using the template supplied.
+** Generate code for a single equality term of the WHERE clause.  An equality
+** term can be either X=expr or X IN (...).   pTerm is the term to be 
+** coded.
 **
-** An existing WhereLoop entry might be overwritten if the new template
-** is better and has fewer dependencies.  Or the template will be ignored
-** and no insert will occur if an existing WhereLoop is faster and has
-** fewer dependencies than the template.  Otherwise a new WhereLoop is
-** added based on the template.
+** The current value for the constraint is left in register iReg.
 **
-** If pBuilder->pOrSet is not NULL then we care about only the
-** prerequisites and rRun and nOut costs of the N best loops.  That
-** information is gathered in the pBuilder->pOrSet object.  This special
-** processing mode is used only for OR clause processing.
-**
-** When accumulating multiple loops (when pBuilder->pOrSet is NULL) we
-** still might overwrite similar loops with the new template if the
-** new template is better.  Loops may be overwritten if the following 
-** conditions are met:
-**
-**    (1)  They have the same iTab.
-**    (2)  They have the same iSortIdx.
-**    (3)  The template has same or fewer dependencies than the current loop
-**    (4)  The template has the same or lower cost than the current loop
+** For a constraint of the form X=expr, the expression is evaluated and its
+** result is left on the stack.  For constraints of the form X IN (...)
+** this routine sets up a loop that will iterate over all values of X.
 */
-static int whereLoopInsert(WhereLoopBuilder *pBuilder, WhereLoop *pTemplate){
-  WhereLoop **ppPrev, *p;
-  WhereInfo *pWInfo = pBuilder->pWInfo;
-  sqlite3 *db = pWInfo->pParse->db;
-  int rc;
-
-  /* If pBuilder->pOrSet is defined, then only keep track of the costs
-  ** and prereqs.
-  */
-  if( pBuilder->pOrSet!=0 ){
-    if( pTemplate->nLTerm ){
-#if WHERETRACE_ENABLED
-      u16 n = pBuilder->pOrSet->n;
-      int x =
-#endif
-      whereOrInsert(pBuilder->pOrSet, pTemplate->prereq, pTemplate->rRun,
-                                    pTemplate->nOut);
-#if WHERETRACE_ENABLED /* 0x8 */
-      if( sqlite3WhereTrace & 0x8 ){
-        sqlite3DebugPrintf(x?"   or-%d:  ":"   or-X:  ", n);
-        whereLoopPrint(pTemplate, pBuilder->pWC);
-      }
-#endif
-    }
-    return SQLITE_OK;
-  }
-
-  /* Look for an existing WhereLoop to replace with pTemplate
-  */
-  whereLoopAdjustCost(pWInfo->pLoops, pTemplate);
-  ppPrev = whereLoopFindLesser(&pWInfo->pLoops, pTemplate);
+static int codeEqualityTerm(
+  Parse *pParse,      /* The parsing context */
+  WhereTerm *pTerm,   /* The term of the WHERE clause to be coded */
+  WhereLevel *pLevel, /* When level of the FROM clause we are working on */
+  int iTarget         /* Attempt to leave results in this register */
+){
+  Expr *pX = pTerm->pExpr;
+  Vdbe *v = pParse->pVdbe;
+  int iReg;                  /* Register holding results */
 
-  if( ppPrev==0 ){
-    /* There already exists a WhereLoop on the list that is better
-    ** than pTemplate, so just ignore pTemplate */
-#if WHERETRACE_ENABLED /* 0x8 */
-    if( sqlite3WhereTrace & 0x8 ){
-      sqlite3DebugPrintf("   skip: ");
-      whereLoopPrint(pTemplate, pBuilder->pWC);
-    }
-#endif
-    return SQLITE_OK;  
+  assert( iTarget>0 );
+  if( pX->op==TK_EQ ){
+    iReg = sqlite3ExprCodeTarget(pParse, pX->pRight, iTarget);
+  }else if( pX->op==TK_ISNULL ){
+    iReg = iTarget;
+    sqlite3VdbeAddOp2(v, OP_Null, 0, iReg);
+#ifndef SQLITE_OMIT_SUBQUERY
   }else{
-    p = *ppPrev;
-  }
-
-  /* If we reach this point it means that either p[] should be overwritten
-  ** with pTemplate[] if p[] exists, or if p==NULL then allocate a new
-  ** WhereLoop and insert it.
-  */
-#if WHERETRACE_ENABLED /* 0x8 */
-  if( sqlite3WhereTrace & 0x8 ){
-    if( p!=0 ){
-      sqlite3DebugPrintf("replace: ");
-      whereLoopPrint(p, pBuilder->pWC);
-      sqlite3DebugPrintf("   with: ");
+    int eType;
+    int iTab;
+    struct InLoop *pIn;
+
+    assert( pX->op==TK_IN );
+    iReg = iTarget;
+    eType = sqlite3FindInIndex(pParse, pX, 0);
+    iTab = pX->iTable;
+    sqlite3VdbeAddOp2(v, OP_Rewind, iTab, 0);
+    assert( pLevel->plan.wsFlags & WHERE_IN_ABLE );
+    if( pLevel->u.in.nIn==0 ){
+      pLevel->addrNxt = sqlite3VdbeMakeLabel(v);
+    }
+    pLevel->u.in.nIn++;
+    pLevel->u.in.aInLoop =
+       sqlite3DbReallocOrFree(pParse->db, pLevel->u.in.aInLoop,
+                              sizeof(pLevel->u.in.aInLoop[0])*pLevel->u.in.nIn);
+    pIn = pLevel->u.in.aInLoop;
+    if( pIn ){
+      pIn += pLevel->u.in.nIn - 1;
+      pIn->iCur = iTab;
+      if( eType==IN_INDEX_ROWID ){
+        pIn->addrInTop = sqlite3VdbeAddOp2(v, OP_Rowid, iTab, iReg);
+      }else{
+        pIn->addrInTop = sqlite3VdbeAddOp3(v, OP_Column, iTab, 0, iReg);
+      }
+      sqlite3VdbeAddOp1(v, OP_IsNull, iReg);
     }else{
-      sqlite3DebugPrintf("    add: ");
+      pLevel->u.in.nIn = 0;
     }
-    whereLoopPrint(pTemplate, pBuilder->pWC);
-  }
-#endif
-  if( p==0 ){
-    /* Allocate a new WhereLoop to add to the end of the list */
-    *ppPrev = p = sqlite3DbMallocRawNN(db, sizeof(WhereLoop));
-    if( p==0 ) return SQLITE_NOMEM_BKPT;
-    whereLoopInit(p);
-    p->pNextLoop = 0;
-  }else{
-    /* We will be overwriting WhereLoop p[].  But before we do, first
-    ** go through the rest of the list and delete any other entries besides
-    ** p[] that are also supplated by pTemplate */
-    WhereLoop **ppTail = &p->pNextLoop;
-    WhereLoop *pToDel;
-    while( *ppTail ){
-      ppTail = whereLoopFindLesser(ppTail, pTemplate);
-      if( ppTail==0 ) break;
-      pToDel = *ppTail;
-      if( pToDel==0 ) break;
-      *ppTail = pToDel->pNextLoop;
-#if WHERETRACE_ENABLED /* 0x8 */
-      if( sqlite3WhereTrace & 0x8 ){
-        sqlite3DebugPrintf(" delete: ");
-        whereLoopPrint(pToDel, pBuilder->pWC);
-      }
 #endif
-      whereLoopDelete(db, pToDel);
-    }
-  }
-  rc = whereLoopXfer(db, p, pTemplate);
-  if( (p->wsFlags & WHERE_VIRTUALTABLE)==0 ){
-    Index *pIndex = p->u.btree.pIndex;
-    if( pIndex && pIndex->tnum==0 ){
-      p->u.btree.pIndex = 0;
-    }
   }
-  return rc;
-}
-
-/*
-** Adjust the WhereLoop.nOut value downward to account for terms of the
-** WHERE clause that reference the loop but which are not used by an
-** index.
-*
-** For every WHERE clause term that is not used by the index
-** and which has a truth probability assigned by one of the likelihood(),
-** likely(), or unlikely() SQL functions, reduce the estimated number
-** of output rows by the probability specified.
-**
-** TUNING:  For every WHERE clause term that is not used by the index
-** and which does not have an assigned truth probability, heuristics
-** described below are used to try to estimate the truth probability.
-** TODO --> Perhaps this is something that could be improved by better
-** table statistics.
-**
-** Heuristic 1:  Estimate the truth probability as 93.75%.  The 93.75%
-** value corresponds to -1 in LogEst notation, so this means decrement
-** the WhereLoop.nOut field for every such WHERE clause term.
-**
-** Heuristic 2:  If there exists one or more WHERE clause terms of the
-** form "x==EXPR" and EXPR is not a constant 0 or 1, then make sure the
-** final output row estimate is no greater than 1/4 of the total number
-** of rows in the table.  In other words, assume that x==EXPR will filter
-** out at least 3 out of 4 rows.  If EXPR is -1 or 0 or 1, then maybe the
-** "x" column is boolean or else -1 or 0 or 1 is a common default value
-** on the "x" column and so in that case only cap the output row estimate
-** at 1/2 instead of 1/4.
-*/
-static void whereLoopOutputAdjust(
-  WhereClause *pWC,      /* The WHERE clause */
-  WhereLoop *pLoop,      /* The loop to adjust downward */
-  LogEst nRow            /* Number of rows in the entire table */
-){
-  WhereTerm *pTerm, *pX;
-  Bitmask notAllowed = ~(pLoop->prereq|pLoop->maskSelf);
-  int i, j, k;
-  LogEst iReduce = 0;    /* pLoop->nOut should not exceed nRow-iReduce */
-
-  assert( (pLoop->wsFlags & WHERE_AUTO_INDEX)==0 );
-  for(i=pWC->nTerm, pTerm=pWC->a; i>0; i--, pTerm++){
-    if( (pTerm->wtFlags & TERM_VIRTUAL)!=0 ) break;
-    if( (pTerm->prereqAll & pLoop->maskSelf)==0 ) continue;
-    if( (pTerm->prereqAll & notAllowed)!=0 ) continue;
-    for(j=pLoop->nLTerm-1; j>=0; j--){
-      pX = pLoop->aLTerm[j];
-      if( pX==0 ) continue;
-      if( pX==pTerm ) break;
-      if( pX->iParent>=0 && (&pWC->a[pX->iParent])==pTerm ) break;
-    }
-    if( j<0 ){
-      if( pTerm->truthProb<=0 ){
-        /* If a truth probability is specified using the likelihood() hints,
-        ** then use the probability provided by the application. */
-        pLoop->nOut += pTerm->truthProb;
+  disableTerm(pLevel, pTerm);
+  return iReg;
+}
+
+/*
+** Generate code that will evaluate all == and IN constraints for an
+** index.  The values for all constraints are left on the stack.
+**
+** For example, consider table t1(a,b,c,d,e,f) with index i1(a,b,c).
+** Suppose the WHERE clause is this:  a==5 AND b IN (1,2,3) AND c>5 AND c<10
+** The index has as many as three equality constraints, but in this
+** example, the third "c" value is an inequality.  So only two 
+** constraints are coded.  This routine will generate code to evaluate
+** a==5 and b IN (1,2,3).  The current values for a and b will be stored
+** in consecutive registers and the index of the first register is returned.
+**
+** In the example above nEq==2.  But this subroutine works for any value
+** of nEq including 0.  If nEq==0, this routine is nearly a no-op.
+** The only thing it does is allocate the pLevel->iMem memory cell.
+**
+** This routine always allocates at least one memory cell and returns
+** the index of that memory cell. The code that
+** calls this routine will use that memory cell to store the termination
+** key value of the loop.  If one or more IN operators appear, then
+** this routine allocates an additional nEq memory cells for internal
+** use.
+*/
+static int codeAllEqualityTerms(
+  Parse *pParse,        /* Parsing context */
+  WhereLevel *pLevel,   /* Which nested loop of the FROM we are coding */
+  WhereClause *pWC,     /* The WHERE clause */
+  Bitmask notReady,     /* Which parts of FROM have not yet been coded */
+  int nExtraReg         /* Number of extra registers to allocate */
+){
+  int nEq = pLevel->plan.nEq;   /* The number of == or IN constraints to code */
+  Vdbe *v = pParse->pVdbe;      /* The vm under construction */
+  Index *pIdx;                  /* The index being used for this loop */
+  int iCur = pLevel->iTabCur;   /* The cursor of the table */
+  WhereTerm *pTerm;             /* A single constraint term */
+  int j;                        /* Loop counter */
+  int regBase;                  /* Base register */
+  int nReg;                     /* Number of registers to allocate */
+
+  /* This module is only called on query plans that use an index. */
+  assert( pLevel->plan.wsFlags & WHERE_INDEXED );
+  pIdx = pLevel->plan.u.pIdx;
+
+  /* Figure out how many memory cells we will need then allocate them.
+  */
+  regBase = pParse->nMem + 1;
+  nReg = pLevel->plan.nEq + nExtraReg;
+  pParse->nMem += nReg;
+
+  /* Evaluate the equality constraints
+  */
+  assert( pIdx->nColumn>=nEq );
+  for(j=0; j<nEq; j++){
+    int r1;
+    int k = pIdx->aiColumn[j];
+    pTerm = findTerm(pWC, iCur, k, notReady, pLevel->plan.wsFlags, pIdx);
+    if( NEVER(pTerm==0) ) break;
+    assert( (pTerm->wtFlags & TERM_CODED)==0 );
+    r1 = codeEqualityTerm(pParse, pTerm, pLevel, regBase+j);
+    if( r1!=regBase+j ){
+      if( nReg==1 ){
+        sqlite3ReleaseTempReg(pParse, regBase);
+        regBase = r1;
       }else{
-        /* In the absence of explicit truth probabilities, use heuristics to
-        ** guess a reasonable truth probability. */
-        pLoop->nOut--;
-        if( pTerm->eOperator&(WO_EQ|WO_IS) ){
-          Expr *pRight = pTerm->pExpr->pRight;
-          testcase( pTerm->pExpr->op==TK_IS );
-          if( sqlite3ExprIsInteger(pRight, &k) && k>=(-1) && k<=1 ){
-            k = 10;
-          }else{
-            k = 20;
-          }
-          if( iReduce<k ) iReduce = k;
-        }
+        sqlite3VdbeAddOp2(v, OP_SCopy, r1, regBase+j);
       }
     }
-  }
-  if( pLoop->nOut > nRow-iReduce )  pLoop->nOut = nRow - iReduce;
-}
-
-/* 
-** Term pTerm is a vector range comparison operation. The first comparison
-** in the vector can be optimized using column nEq of the index. This
-** function returns the total number of vector elements that can be used
-** as part of the range comparison.
-**
-** For example, if the query is:
-**
-**   WHERE a = ? AND (b, c, d) > (?, ?, ?)
-**
-** and the index:
-**
-**   CREATE INDEX ... ON (a, b, c, d, e)
-**
-** then this function would be invoked with nEq=1. The value returned in
-** this case is 3.
-*/
-static int whereRangeVectorLen(
-  Parse *pParse,       /* Parsing context */
-  int iCur,            /* Cursor open on pIdx */
-  Index *pIdx,         /* The index to be used for a inequality constraint */
-  int nEq,             /* Number of prior equality constraints on same index */
-  WhereTerm *pTerm     /* The vector inequality constraint */
-){
-  int nCmp = sqlite3ExprVectorSize(pTerm->pExpr->pLeft);
-  int i;
-
-  nCmp = MIN(nCmp, (pIdx->nColumn - nEq));
-  for(i=1; i<nCmp; i++){
-    /* Test if comparison i of pTerm is compatible with column (i+nEq) 
-    ** of the index. If not, exit the loop.  */
-    char aff;                     /* Comparison affinity */
-    char idxaff = 0;              /* Indexed columns affinity */
-    CollSeq *pColl;               /* Comparison collation sequence */
-    Expr *pLhs = pTerm->pExpr->pLeft->x.pList->a[i].pExpr;
-    Expr *pRhs = pTerm->pExpr->pRight;
-    if( pRhs->flags & EP_xIsSelect ){
-      pRhs = pRhs->x.pSelect->pEList->a[i].pExpr;
-    }else{
-      pRhs = pRhs->x.pList->a[i].pExpr;
-    }
-
-    /* Check that the LHS of the comparison is a column reference to
-    ** the right column of the right source table. And that the sort
-    ** order of the index column is the same as the sort order of the
-    ** leftmost index column.  */
-    if( pLhs->op!=TK_COLUMN 
-     || pLhs->iTable!=iCur 
-     || pLhs->iColumn!=pIdx->aiColumn[i+nEq] 
-     || pIdx->aSortOrder[i+nEq]!=pIdx->aSortOrder[nEq]
-    ){
-      break;
-    }
-
-    testcase( pLhs->iColumn==XN_ROWID );
-    aff = sqlite3CompareAffinity(pRhs, sqlite3ExprAffinity(pLhs));
-    idxaff = sqlite3TableColumnAffinity(pIdx->pTable, pLhs->iColumn);
-    if( aff!=idxaff ) break;
-
-    pColl = sqlite3BinaryCompareCollSeq(pParse, pLhs, pRhs);
-    if( pColl==0 ) break;
-    if( sqlite3StrICmp(pColl->zName, pIdx->azColl[i+nEq]) ) break;
-  }
-  return i;
-}
-
-/*
-** Adjust the cost C by the costMult facter T.  This only occurs if
-** compiled with -DSQLITE_ENABLE_COSTMULT
-*/
-#ifdef SQLITE_ENABLE_COSTMULT
-# define ApplyCostMultiplier(C,T)  C += T
-#else
-# define ApplyCostMultiplier(C,T)
-#endif
-
-/*
-** We have so far matched pBuilder->pNew->u.btree.nEq terms of the 
-** index pIndex. Try to match one more.
-**
-** When this function is called, pBuilder->pNew->nOut contains the 
-** number of rows expected to be visited by filtering using the nEq 
-** terms only. If it is modified, this value is restored before this 
-** function returns.
-**
-** If pProbe->tnum==0, that means pIndex is a fake index used for the
-** INTEGER PRIMARY KEY.
-*/
-static int whereLoopAddBtreeIndex(
-  WhereLoopBuilder *pBuilder,     /* The WhereLoop factory */
-  struct SrcList_item *pSrc,      /* FROM clause term being analyzed */
-  Index *pProbe,                  /* An index on pSrc */
-  LogEst nInMul                   /* log(Number of iterations due to IN) */
-){
-  WhereInfo *pWInfo = pBuilder->pWInfo;  /* WHERE analyse context */
-  Parse *pParse = pWInfo->pParse;        /* Parsing context */
-  sqlite3 *db = pParse->db;       /* Database connection malloc context */
-  WhereLoop *pNew;                /* Template WhereLoop under construction */
-  WhereTerm *pTerm;               /* A WhereTerm under consideration */
-  int opMask;                     /* Valid operators for constraints */
-  WhereScan scan;                 /* Iterator for WHERE terms */
-  Bitmask saved_prereq;           /* Original value of pNew->prereq */
-  u16 saved_nLTerm;               /* Original value of pNew->nLTerm */
-  u16 saved_nEq;                  /* Original value of pNew->u.btree.nEq */
-  u16 saved_nBtm;                 /* Original value of pNew->u.btree.nBtm */
-  u16 saved_nTop;                 /* Original value of pNew->u.btree.nTop */
-  u16 saved_nSkip;                /* Original value of pNew->nSkip */
-  u32 saved_wsFlags;              /* Original value of pNew->wsFlags */
-  LogEst saved_nOut;              /* Original value of pNew->nOut */
-  int rc = SQLITE_OK;             /* Return code */
-  LogEst rSize;                   /* Number of rows in the table */
-  LogEst rLogSize;                /* Logarithm of table size */
-  WhereTerm *pTop = 0, *pBtm = 0; /* Top and bottom range constraints */
-
-  pNew = pBuilder->pNew;
-  if( db->mallocFailed ) return SQLITE_NOMEM_BKPT;
-  WHERETRACE(0x800, ("BEGIN addBtreeIdx(%s), nEq=%d\n",
-                     pProbe->zName, pNew->u.btree.nEq));
-
-  assert( (pNew->wsFlags & WHERE_VIRTUALTABLE)==0 );
-  assert( (pNew->wsFlags & WHERE_TOP_LIMIT)==0 );
-  if( pNew->wsFlags & WHERE_BTM_LIMIT ){
-    opMask = WO_LT|WO_LE;
-  }else{
-    assert( pNew->u.btree.nBtm==0 );
-    opMask = WO_EQ|WO_IN|WO_GT|WO_GE|WO_LT|WO_LE|WO_ISNULL|WO_IS;
-  }
-  if( pProbe->bUnordered ) opMask &= ~(WO_GT|WO_GE|WO_LT|WO_LE);
-
-  assert( pNew->u.btree.nEq<pProbe->nColumn );
-
-  saved_nEq = pNew->u.btree.nEq;
-  saved_nBtm = pNew->u.btree.nBtm;
-  saved_nTop = pNew->u.btree.nTop;
-  saved_nSkip = pNew->nSkip;
-  saved_nLTerm = pNew->nLTerm;
-  saved_wsFlags = pNew->wsFlags;
-  saved_prereq = pNew->prereq;
-  saved_nOut = pNew->nOut;
-  pTerm = whereScanInit(&scan, pBuilder->pWC, pSrc->iCursor, saved_nEq,
-                        opMask, pProbe);
-  pNew->rSetup = 0;
-  rSize = pProbe->aiRowLogEst[0];
-  rLogSize = estLog(rSize);
-  for(; rc==SQLITE_OK && pTerm!=0; pTerm = whereScanNext(&scan)){
-    u16 eOp = pTerm->eOperator;   /* Shorthand for pTerm->eOperator */
-    LogEst rCostIdx;
-    LogEst nOutUnadjusted;        /* nOut before IN() and WHERE adjustments */
-    int nIn = 0;
-#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
-    int nRecValid = pBuilder->nRecValid;
-#endif
-    if( (eOp==WO_ISNULL || (pTerm->wtFlags&TERM_VNULL)!=0)
-     && indexColumnNotNull(pProbe, saved_nEq)
-    ){
-      continue; /* ignore IS [NOT] NULL constraints on NOT NULL columns */
-    }
-    if( pTerm->prereqRight & pNew->maskSelf ) continue;
-
-    /* Do not allow the upper bound of a LIKE optimization range constraint
-    ** to mix with a lower range bound from some other source */
-    if( pTerm->wtFlags & TERM_LIKEOPT && pTerm->eOperator==WO_LT ) continue;
-
-    /* Do not allow IS constraints from the WHERE clause to be used by the
-    ** right table of a LEFT JOIN.  Only constraints in the ON clause are
-    ** allowed */
-    if( (pSrc->fg.jointype & JT_LEFT)!=0
-     && !ExprHasProperty(pTerm->pExpr, EP_FromJoin)
-     && (eOp & (WO_IS|WO_ISNULL))!=0
-    ){
-      testcase( eOp & WO_IS );
-      testcase( eOp & WO_ISNULL );
-      continue;
-    }
-
-    if( IsUniqueIndex(pProbe) && saved_nEq==pProbe->nKeyCol-1 ){
-      pBuilder->bldFlags |= SQLITE_BLDF_UNIQUE;
-    }else{
-      pBuilder->bldFlags |= SQLITE_BLDF_INDEXED;
-    }
-    pNew->wsFlags = saved_wsFlags;
-    pNew->u.btree.nEq = saved_nEq;
-    pNew->u.btree.nBtm = saved_nBtm;
-    pNew->u.btree.nTop = saved_nTop;
-    pNew->nLTerm = saved_nLTerm;
-    if( whereLoopResize(db, pNew, pNew->nLTerm+1) ) break; /* OOM */
-    pNew->aLTerm[pNew->nLTerm++] = pTerm;
-    pNew->prereq = (saved_prereq | pTerm->prereqRight) & ~pNew->maskSelf;
-
-    assert( nInMul==0
-        || (pNew->wsFlags & WHERE_COLUMN_NULL)!=0 
-        || (pNew->wsFlags & WHERE_COLUMN_IN)!=0 
-        || (pNew->wsFlags & WHERE_SKIPSCAN)!=0 
-    );
-
-    if( eOp & WO_IN ){
-      Expr *pExpr = pTerm->pExpr;
-      pNew->wsFlags |= WHERE_COLUMN_IN;
-      if( ExprHasProperty(pExpr, EP_xIsSelect) ){
-        /* "x IN (SELECT ...)":  TUNING: the SELECT returns 25 rows */
-        int i;
-        nIn = 46;  assert( 46==sqlite3LogEst(25) );
-
-        /* The expression may actually be of the form (x, y) IN (SELECT...).
-        ** In this case there is a separate term for each of (x) and (y).
-        ** However, the nIn multiplier should only be applied once, not once
-        ** for each such term. The following loop checks that pTerm is the
-        ** first such term in use, and sets nIn back to 0 if it is not. */
-        for(i=0; i<pNew->nLTerm-1; i++){
-          if( pNew->aLTerm[i] && pNew->aLTerm[i]->pExpr==pExpr ) nIn = 0;
-        }
-      }else if( ALWAYS(pExpr->x.pList && pExpr->x.pList->nExpr) ){
-        /* "x IN (value, value, ...)" */
-        nIn = sqlite3LogEst(pExpr->x.pList->nExpr);
-        assert( nIn>0 );  /* RHS always has 2 or more terms...  The parser
-                          ** changes "x IN (?)" into "x=?". */
-      }
-    }else if( eOp & (WO_EQ|WO_IS) ){
-      int iCol = pProbe->aiColumn[saved_nEq];
-      pNew->wsFlags |= WHERE_COLUMN_EQ;
-      assert( saved_nEq==pNew->u.btree.nEq );
-      if( iCol==XN_ROWID 
-       || (iCol>0 && nInMul==0 && saved_nEq==pProbe->nKeyCol-1)
-      ){
-        if( iCol>=0 && pProbe->uniqNotNull==0 ){
-          pNew->wsFlags |= WHERE_UNQ_WANTED;
-        }else{
-          pNew->wsFlags |= WHERE_ONEROW;
-        }
-      }
-    }else if( eOp & WO_ISNULL ){
-      pNew->wsFlags |= WHERE_COLUMN_NULL;
-    }else if( eOp & (WO_GT|WO_GE) ){
-      testcase( eOp & WO_GT );
-      testcase( eOp & WO_GE );
-      pNew->wsFlags |= WHERE_COLUMN_RANGE|WHERE_BTM_LIMIT;
-      pNew->u.btree.nBtm = whereRangeVectorLen(
-          pParse, pSrc->iCursor, pProbe, saved_nEq, pTerm
-      );
-      pBtm = pTerm;
-      pTop = 0;
-      if( pTerm->wtFlags & TERM_LIKEOPT ){
-        /* Range contraints that come from the LIKE optimization are
-        ** always used in pairs. */
-        pTop = &pTerm[1];
-        assert( (pTop-(pTerm->pWC->a))<pTerm->pWC->nTerm );
-        assert( pTop->wtFlags & TERM_LIKEOPT );
-        assert( pTop->eOperator==WO_LT );
-        if( whereLoopResize(db, pNew, pNew->nLTerm+1) ) break; /* OOM */
-        pNew->aLTerm[pNew->nLTerm++] = pTop;
-        pNew->wsFlags |= WHERE_TOP_LIMIT;
-        pNew->u.btree.nTop = 1;
-      }
-    }else{
-      assert( eOp & (WO_LT|WO_LE) );
-      testcase( eOp & WO_LT );
-      testcase( eOp & WO_LE );
-      pNew->wsFlags |= WHERE_COLUMN_RANGE|WHERE_TOP_LIMIT;
-      pNew->u.btree.nTop = whereRangeVectorLen(
-          pParse, pSrc->iCursor, pProbe, saved_nEq, pTerm
-      );
-      pTop = pTerm;
-      pBtm = (pNew->wsFlags & WHERE_BTM_LIMIT)!=0 ?
-                     pNew->aLTerm[pNew->nLTerm-2] : 0;
-    }
-
-    /* At this point pNew->nOut is set to the number of rows expected to
-    ** be visited by the index scan before considering term pTerm, or the
-    ** values of nIn and nInMul. In other words, assuming that all 
-    ** "x IN(...)" terms are replaced with "x = ?". This block updates
-    ** the value of pNew->nOut to account for pTerm (but not nIn/nInMul).  */
-    assert( pNew->nOut==saved_nOut );
-    if( pNew->wsFlags & WHERE_COLUMN_RANGE ){
-      /* Adjust nOut using stat3/stat4 data. Or, if there is no stat3/stat4
-      ** data, using some other estimate.  */
-      whereRangeScanEst(pParse, pBuilder, pBtm, pTop, pNew);
-    }else{
-      int nEq = ++pNew->u.btree.nEq;
-      assert( eOp & (WO_ISNULL|WO_EQ|WO_IN|WO_IS) );
-
-      assert( pNew->nOut==saved_nOut );
-      if( pTerm->truthProb<=0 && pProbe->aiColumn[saved_nEq]>=0 ){
-        assert( (eOp & WO_IN) || nIn==0 );
-        testcase( eOp & WO_IN );
-        pNew->nOut += pTerm->truthProb;
-        pNew->nOut -= nIn;
-      }else{
-#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
-        tRowcnt nOut = 0;
-        if( nInMul==0 
-         && pProbe->nSample 
-         && pNew->u.btree.nEq<=pProbe->nSampleCol
-         && ((eOp & WO_IN)==0 || !ExprHasProperty(pTerm->pExpr, EP_xIsSelect))
-        ){
-          Expr *pExpr = pTerm->pExpr;
-          if( (eOp & (WO_EQ|WO_ISNULL|WO_IS))!=0 ){
-            testcase( eOp & WO_EQ );
-            testcase( eOp & WO_IS );
-            testcase( eOp & WO_ISNULL );
-            rc = whereEqualScanEst(pParse, pBuilder, pExpr->pRight, &nOut);
-          }else{
-            rc = whereInScanEst(pParse, pBuilder, pExpr->x.pList, &nOut);
-          }
-          if( rc==SQLITE_NOTFOUND ) rc = SQLITE_OK;
-          if( rc!=SQLITE_OK ) break;          /* Jump out of the pTerm loop */
-          if( nOut ){
-            pNew->nOut = sqlite3LogEst(nOut);
-            if( pNew->nOut>saved_nOut ) pNew->nOut = saved_nOut;
-            pNew->nOut -= nIn;
-          }
-        }
-        if( nOut==0 )
-#endif
-        {
-          pNew->nOut += (pProbe->aiRowLogEst[nEq] - pProbe->aiRowLogEst[nEq-1]);
-          if( eOp & WO_ISNULL ){
-            /* TUNING: If there is no likelihood() value, assume that a 
-            ** "col IS NULL" expression matches twice as many rows 
-            ** as (col=?). */
-            pNew->nOut += 10;
-          }
-        }
-      }
-    }
-
-    /* Set rCostIdx to the cost of visiting selected rows in index. Add
-    ** it to pNew->rRun, which is currently set to the cost of the index
-    ** seek only. Then, if this is a non-covering index, add the cost of
-    ** visiting the rows in the main table.  */
-    rCostIdx = pNew->nOut + 1 + (15*pProbe->szIdxRow)/pSrc->pTab->szTabRow;
-    pNew->rRun = sqlite3LogEstAdd(rLogSize, rCostIdx);
-    if( (pNew->wsFlags & (WHERE_IDX_ONLY|WHERE_IPK))==0 ){
-      pNew->rRun = sqlite3LogEstAdd(pNew->rRun, pNew->nOut + 16);
-    }
-    ApplyCostMultiplier(pNew->rRun, pProbe->pTable->costMult);
-
-    nOutUnadjusted = pNew->nOut;
-    pNew->rRun += nInMul + nIn;
-    pNew->nOut += nInMul + nIn;
-    whereLoopOutputAdjust(pBuilder->pWC, pNew, rSize);
-    rc = whereLoopInsert(pBuilder, pNew);
-
-    if( pNew->wsFlags & WHERE_COLUMN_RANGE ){
-      pNew->nOut = saved_nOut;
-    }else{
-      pNew->nOut = nOutUnadjusted;
-    }
-
-    if( (pNew->wsFlags & WHERE_TOP_LIMIT)==0
-     && pNew->u.btree.nEq<pProbe->nColumn
-    ){
-      whereLoopAddBtreeIndex(pBuilder, pSrc, pProbe, nInMul+nIn);
-    }
-    pNew->nOut = saved_nOut;
-#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
-    pBuilder->nRecValid = nRecValid;
-#endif
-  }
-  pNew->prereq = saved_prereq;
-  pNew->u.btree.nEq = saved_nEq;
-  pNew->u.btree.nBtm = saved_nBtm;
-  pNew->u.btree.nTop = saved_nTop;
-  pNew->nSkip = saved_nSkip;
-  pNew->wsFlags = saved_wsFlags;
-  pNew->nOut = saved_nOut;
-  pNew->nLTerm = saved_nLTerm;
-
-  /* Consider using a skip-scan if there are no WHERE clause constraints
-  ** available for the left-most terms of the index, and if the average
-  ** number of repeats in the left-most terms is at least 18. 
-  **
-  ** The magic number 18 is selected on the basis that scanning 17 rows
-  ** is almost always quicker than an index seek (even though if the index
-  ** contains fewer than 2^17 rows we assume otherwise in other parts of
-  ** the code). And, even if it is not, it should not be too much slower. 
-  ** On the other hand, the extra seeks could end up being significantly
-  ** more expensive.  */
-  assert( 42==sqlite3LogEst(18) );
-  if( saved_nEq==saved_nSkip
-   && saved_nEq+1<pProbe->nKeyCol
-   && pProbe->noSkipScan==0
-   && pProbe->aiRowLogEst[saved_nEq+1]>=42  /* TUNING: Minimum for skip-scan */
-   && (rc = whereLoopResize(db, pNew, pNew->nLTerm+1))==SQLITE_OK
-  ){
-    LogEst nIter;
-    pNew->u.btree.nEq++;
-    pNew->nSkip++;
-    pNew->aLTerm[pNew->nLTerm++] = 0;
-    pNew->wsFlags |= WHERE_SKIPSCAN;
-    nIter = pProbe->aiRowLogEst[saved_nEq] - pProbe->aiRowLogEst[saved_nEq+1];
-    pNew->nOut -= nIter;
-    /* TUNING:  Because uncertainties in the estimates for skip-scan queries,
-    ** add a 1.375 fudge factor to make skip-scan slightly less likely. */
-    nIter += 5;
-    whereLoopAddBtreeIndex(pBuilder, pSrc, pProbe, nIter + nInMul);
-    pNew->nOut = saved_nOut;
-    pNew->u.btree.nEq = saved_nEq;
-    pNew->nSkip = saved_nSkip;
-    pNew->wsFlags = saved_wsFlags;
-  }
-
-  WHERETRACE(0x800, ("END addBtreeIdx(%s), nEq=%d, rc=%d\n",
-                      pProbe->zName, saved_nEq, rc));
-  return rc;
-}
-
-/*
-** Return True if it is possible that pIndex might be useful in
-** implementing the ORDER BY clause in pBuilder.
-**
-** Return False if pBuilder does not contain an ORDER BY clause or
-** if there is no way for pIndex to be useful in implementing that
-** ORDER BY clause.
-*/
-static int indexMightHelpWithOrderBy(
-  WhereLoopBuilder *pBuilder,
-  Index *pIndex,
-  int iCursor
-){
-  ExprList *pOB;
-  ExprList *aColExpr;
-  int ii, jj;
-
-  if( pIndex->bUnordered ) return 0;
-  if( (pOB = pBuilder->pWInfo->pOrderBy)==0 ) return 0;
-  for(ii=0; ii<pOB->nExpr; ii++){
-    Expr *pExpr = sqlite3ExprSkipCollate(pOB->a[ii].pExpr);
-    if( pExpr->op==TK_COLUMN && pExpr->iTable==iCursor ){
-      if( pExpr->iColumn<0 ) return 1;
-      for(jj=0; jj<pIndex->nKeyCol; jj++){
-        if( pExpr->iColumn==pIndex->aiColumn[jj] ) return 1;
-      }
-    }else if( (aColExpr = pIndex->aColExpr)!=0 ){
-      for(jj=0; jj<pIndex->nKeyCol; jj++){
-        if( pIndex->aiColumn[jj]!=XN_EXPR ) continue;
-        if( sqlite3ExprCompareSkip(pExpr,aColExpr->a[jj].pExpr,iCursor)==0 ){
-          return 1;
-        }
-      }
-    }
-  }
-  return 0;
-}
-
-/*
-** Return a bitmask where 1s indicate that the corresponding column of
-** the table is used by an index.  Only the first 63 columns are considered.
-*/
-static Bitmask columnsInIndex(Index *pIdx){
-  Bitmask m = 0;
-  int j;
-  for(j=pIdx->nColumn-1; j>=0; j--){
-    int x = pIdx->aiColumn[j];
-    if( x>=0 ){
-      testcase( x==BMS-1 );
-      testcase( x==BMS-2 );
-      if( x<BMS-1 ) m |= MASKBIT(x);
-    }
-  }
-  return m;
-}
-
-/* Check to see if a partial index with pPartIndexWhere can be used
-** in the current query.  Return true if it can be and false if not.
-*/
-static int whereUsablePartialIndex(int iTab, WhereClause *pWC, Expr *pWhere){
-  int i;
-  WhereTerm *pTerm;
-  Parse *pParse = pWC->pWInfo->pParse;
-  while( pWhere->op==TK_AND ){
-    if( !whereUsablePartialIndex(iTab,pWC,pWhere->pLeft) ) return 0;
-    pWhere = pWhere->pRight;
-  }
-  if( pParse->db->flags & SQLITE_EnableQPSG ) pParse = 0;
-  for(i=0, pTerm=pWC->a; i<pWC->nTerm; i++, pTerm++){
-    Expr *pExpr = pTerm->pExpr;
-    if( (!ExprHasProperty(pExpr, EP_FromJoin) || pExpr->iRightJoinTable==iTab)
-     && sqlite3ExprImpliesExpr(pParse, pExpr, pWhere, iTab) 
-    ){
-      return 1;
-    }
-  }
-  return 0;
-}
-
-/*
-** Add all WhereLoop objects for a single table of the join where the table
-** is identified by pBuilder->pNew->iTab.  That table is guaranteed to be
-** a b-tree table, not a virtual table.
-**
-** The costs (WhereLoop.rRun) of the b-tree loops added by this function
-** are calculated as follows:
-**
-** For a full scan, assuming the table (or index) contains nRow rows:
-**
-**     cost = nRow * 3.0                    // full-table scan
-**     cost = nRow * K                      // scan of covering index
-**     cost = nRow * (K+3.0)                // scan of non-covering index
-**
-** where K is a value between 1.1 and 3.0 set based on the relative 
-** estimated average size of the index and table records.
-**
-** For an index scan, where nVisit is the number of index rows visited
-** by the scan, and nSeek is the number of seek operations required on 
-** the index b-tree:
-**
-**     cost = nSeek * (log(nRow) + K * nVisit)          // covering index
-**     cost = nSeek * (log(nRow) + (K+3.0) * nVisit)    // non-covering index
-**
-** Normally, nSeek is 1. nSeek values greater than 1 come about if the 
-** WHERE clause includes "x IN (....)" terms used in place of "x=?". Or when 
-** implicit "x IN (SELECT x FROM tbl)" terms are added for skip-scans.
-**
-** The estimated values (nRow, nVisit, nSeek) often contain a large amount
-** of uncertainty.  For this reason, scoring is designed to pick plans that
-** "do the least harm" if the estimates are inaccurate.  For example, a
-** log(nRow) factor is omitted from a non-covering index scan in order to
-** bias the scoring in favor of using an index, since the worst-case
-** performance of using an index is far better than the worst-case performance
-** of a full table scan.
-*/
-static int whereLoopAddBtree(
-  WhereLoopBuilder *pBuilder, /* WHERE clause information */
-  Bitmask mPrereq             /* Extra prerequesites for using this table */
-){
-  WhereInfo *pWInfo;          /* WHERE analysis context */
-  Index *pProbe;              /* An index we are evaluating */
-  Index sPk;                  /* A fake index object for the primary key */
-  LogEst aiRowEstPk[2];       /* The aiRowLogEst[] value for the sPk index */
-  i16 aiColumnPk = -1;        /* The aColumn[] value for the sPk index */
-  SrcList *pTabList;          /* The FROM clause */
-  struct SrcList_item *pSrc;  /* The FROM clause btree term to add */
-  WhereLoop *pNew;            /* Template WhereLoop object */
-  int rc = SQLITE_OK;         /* Return code */
-  int iSortIdx = 1;           /* Index number */
-  int b;                      /* A boolean value */
-  LogEst rSize;               /* number of rows in the table */
-  LogEst rLogSize;            /* Logarithm of the number of rows in the table */
-  WhereClause *pWC;           /* The parsed WHERE clause */
-  Table *pTab;                /* Table being queried */
-  
-  pNew = pBuilder->pNew;
-  pWInfo = pBuilder->pWInfo;
-  pTabList = pWInfo->pTabList;
-  pSrc = pTabList->a + pNew->iTab;
-  pTab = pSrc->pTab;
-  pWC = pBuilder->pWC;
-  assert( !IsVirtual(pSrc->pTab) );
-
-  if( pSrc->pIBIndex ){
-    /* An INDEXED BY clause specifies a particular index to use */
-    pProbe = pSrc->pIBIndex;
-  }else if( !HasRowid(pTab) ){
-    pProbe = pTab->pIndex;
-  }else{
-    /* There is no INDEXED BY clause.  Create a fake Index object in local
-    ** variable sPk to represent the rowid primary key index.  Make this
-    ** fake index the first in a chain of Index objects with all of the real
-    ** indices to follow */
-    Index *pFirst;                  /* First of real indices on the table */
-    memset(&sPk, 0, sizeof(Index));
-    sPk.nKeyCol = 1;
-    sPk.nColumn = 1;
-    sPk.aiColumn = &aiColumnPk;
-    sPk.aiRowLogEst = aiRowEstPk;
-    sPk.onError = OE_Replace;
-    sPk.pTable = pTab;
-    sPk.szIdxRow = pTab->szTabRow;
-    aiRowEstPk[0] = pTab->nRowLogEst;
-    aiRowEstPk[1] = 0;
-    pFirst = pSrc->pTab->pIndex;
-    if( pSrc->fg.notIndexed==0 ){
-      /* The real indices of the table are only considered if the
-      ** NOT INDEXED qualifier is omitted from the FROM clause */
-      sPk.pNext = pFirst;
-    }
-    pProbe = &sPk;
-  }
-  rSize = pTab->nRowLogEst;
-  rLogSize = estLog(rSize);
-
-#ifndef SQLITE_OMIT_AUTOMATIC_INDEX
-  /* Automatic indexes */
-  if( !pBuilder->pOrSet      /* Not part of an OR optimization */
-   && (pWInfo->wctrlFlags & WHERE_OR_SUBCLAUSE)==0
-   && (pWInfo->pParse->db->flags & SQLITE_AutoIndex)!=0
-   && pSrc->pIBIndex==0      /* Has no INDEXED BY clause */
-   && !pSrc->fg.notIndexed   /* Has no NOT INDEXED clause */
-   && HasRowid(pTab)         /* Not WITHOUT ROWID table. (FIXME: Why not?) */
-   && !pSrc->fg.isCorrelated /* Not a correlated subquery */
-   && !pSrc->fg.isRecursive  /* Not a recursive common table expression. */
-  ){
-    /* Generate auto-index WhereLoops */
-    WhereTerm *pTerm;
-    WhereTerm *pWCEnd = pWC->a + pWC->nTerm;
-    for(pTerm=pWC->a; rc==SQLITE_OK && pTerm<pWCEnd; pTerm++){
-      if( pTerm->prereqRight & pNew->maskSelf ) continue;
-      if( termCanDriveIndex(pTerm, pSrc, 0) ){
-        pNew->u.btree.nEq = 1;
-        pNew->nSkip = 0;
-        pNew->u.btree.pIndex = 0;
-        pNew->nLTerm = 1;
-        pNew->aLTerm[0] = pTerm;
-        /* TUNING: One-time cost for computing the automatic index is
-        ** estimated to be X*N*log2(N) where N is the number of rows in
-        ** the table being indexed and where X is 7 (LogEst=28) for normal
-        ** tables or 1.375 (LogEst=4) for views and subqueries.  The value
-        ** of X is smaller for views and subqueries so that the query planner
-        ** will be more aggressive about generating automatic indexes for
-        ** those objects, since there is no opportunity to add schema
-        ** indexes on subqueries and views. */
-        pNew->rSetup = rLogSize + rSize + 4;
-        if( pTab->pSelect==0 && (pTab->tabFlags & TF_Ephemeral)==0 ){
-          pNew->rSetup += 24;
-        }
-        ApplyCostMultiplier(pNew->rSetup, pTab->costMult);
-        if( pNew->rSetup<0 ) pNew->rSetup = 0;
-        /* TUNING: Each index lookup yields 20 rows in the table.  This
-        ** is more than the usual guess of 10 rows, since we have no way
-        ** of knowing how selective the index will ultimately be.  It would
-        ** not be unreasonable to make this value much larger. */
-        pNew->nOut = 43;  assert( 43==sqlite3LogEst(20) );
-        pNew->rRun = sqlite3LogEstAdd(rLogSize,pNew->nOut);
-        pNew->wsFlags = WHERE_AUTO_INDEX;
-        pNew->prereq = mPrereq | pTerm->prereqRight;
-        rc = whereLoopInsert(pBuilder, pNew);
-      }
-    }
-  }
-#endif /* SQLITE_OMIT_AUTOMATIC_INDEX */
-
-  /* Loop over all indices
-  */
-  for(; rc==SQLITE_OK && pProbe; pProbe=pProbe->pNext, iSortIdx++){
-    if( pProbe->pPartIdxWhere!=0
-     && !whereUsablePartialIndex(pSrc->iCursor, pWC, pProbe->pPartIdxWhere) ){
-      testcase( pNew->iTab!=pSrc->iCursor );  /* See ticket [98d973b8f5] */
-      continue;  /* Partial index inappropriate for this query */
-    }
-    rSize = pProbe->aiRowLogEst[0];
-    pNew->u.btree.nEq = 0;
-    pNew->u.btree.nBtm = 0;
-    pNew->u.btree.nTop = 0;
-    pNew->nSkip = 0;
-    pNew->nLTerm = 0;
-    pNew->iSortIdx = 0;
-    pNew->rSetup = 0;
-    pNew->prereq = mPrereq;
-    pNew->nOut = rSize;
-    pNew->u.btree.pIndex = pProbe;
-    b = indexMightHelpWithOrderBy(pBuilder, pProbe, pSrc->iCursor);
-    /* The ONEPASS_DESIRED flags never occurs together with ORDER BY */
-    assert( (pWInfo->wctrlFlags & WHERE_ONEPASS_DESIRED)==0 || b==0 );
-    if( pProbe->tnum<=0 ){
-      /* Integer primary key index */
-      pNew->wsFlags = WHERE_IPK;
-
-      /* Full table scan */
-      pNew->iSortIdx = b ? iSortIdx : 0;
-      /* TUNING: Cost of full table scan is (N*3.0). */
-      pNew->rRun = rSize + 16;
-      ApplyCostMultiplier(pNew->rRun, pTab->costMult);
-      whereLoopOutputAdjust(pWC, pNew, rSize);
-      rc = whereLoopInsert(pBuilder, pNew);
-      pNew->nOut = rSize;
-      if( rc ) break;
-    }else{
-      Bitmask m;
-      if( pProbe->isCovering ){
-        pNew->wsFlags = WHERE_IDX_ONLY | WHERE_INDEXED;
-        m = 0;
-      }else{
-        m = pSrc->colUsed & ~columnsInIndex(pProbe);
-        pNew->wsFlags = (m==0) ? (WHERE_IDX_ONLY|WHERE_INDEXED) : WHERE_INDEXED;
-      }
-
-      /* Full scan via index */
-      if( b
-       || !HasRowid(pTab)
-       || pProbe->pPartIdxWhere!=0
-       || ( m==0
-         && pProbe->bUnordered==0
-         && (pProbe->szIdxRow<pTab->szTabRow)
-         && (pWInfo->wctrlFlags & WHERE_ONEPASS_DESIRED)==0
-         && sqlite3GlobalConfig.bUseCis
-         && OptimizationEnabled(pWInfo->pParse->db, SQLITE_CoverIdxScan)
-          )
-      ){
-        pNew->iSortIdx = b ? iSortIdx : 0;
-
-        /* The cost of visiting the index rows is N*K, where K is
-        ** between 1.1 and 3.0, depending on the relative sizes of the
-        ** index and table rows. */
-        pNew->rRun = rSize + 1 + (15*pProbe->szIdxRow)/pTab->szTabRow;
-        if( m!=0 ){
-          /* If this is a non-covering index scan, add in the cost of
-          ** doing table lookups.  The cost will be 3x the number of
-          ** lookups.  Take into account WHERE clause terms that can be
-          ** satisfied using just the index, and that do not require a
-          ** table lookup. */
-          LogEst nLookup = rSize + 16;  /* Base cost:  N*3 */
-          int ii;
-          int iCur = pSrc->iCursor;
-          WhereClause *pWC2 = &pWInfo->sWC;
-          for(ii=0; ii<pWC2->nTerm; ii++){
-            WhereTerm *pTerm = &pWC2->a[ii];
-            if( !sqlite3ExprCoveredByIndex(pTerm->pExpr, iCur, pProbe) ){
-              break;
-            }
-            /* pTerm can be evaluated using just the index.  So reduce
-            ** the expected number of table lookups accordingly */
-            if( pTerm->truthProb<=0 ){
-              nLookup += pTerm->truthProb;
-            }else{
-              nLookup--;
-              if( pTerm->eOperator & (WO_EQ|WO_IS) ) nLookup -= 19;
-            }
-          }
-          
-          pNew->rRun = sqlite3LogEstAdd(pNew->rRun, nLookup);
-        }
-        ApplyCostMultiplier(pNew->rRun, pTab->costMult);
-        whereLoopOutputAdjust(pWC, pNew, rSize);
-        rc = whereLoopInsert(pBuilder, pNew);
-        pNew->nOut = rSize;
-        if( rc ) break;
-      }
-    }
-
-    pBuilder->bldFlags = 0;
-    rc = whereLoopAddBtreeIndex(pBuilder, pSrc, pProbe, 0);
-    if( pBuilder->bldFlags==SQLITE_BLDF_INDEXED ){
-      /* If a non-unique index is used, or if a prefix of the key for
-      ** unique index is used (making the index functionally non-unique)
-      ** then the sqlite_stat1 data becomes important for scoring the
-      ** plan */
-      pTab->tabFlags |= TF_StatsUsed;
-    }
-#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
-    sqlite3Stat4ProbeFree(pBuilder->pRec);
-    pBuilder->nRecValid = 0;
-    pBuilder->pRec = 0;
-#endif
-
-    /* If there was an INDEXED BY clause, then only that one index is
-    ** considered. */
-    if( pSrc->pIBIndex ) break;
-  }
-  return rc;
-}
-
-#ifndef SQLITE_OMIT_VIRTUALTABLE
-
-/*
-** Argument pIdxInfo is already populated with all constraints that may
-** be used by the virtual table identified by pBuilder->pNew->iTab. This
-** function marks a subset of those constraints usable, invokes the
-** xBestIndex method and adds the returned plan to pBuilder.
-**
-** A constraint is marked usable if:
-**
-**   * Argument mUsable indicates that its prerequisites are available, and
-**
-**   * It is not one of the operators specified in the mExclude mask passed
-**     as the fourth argument (which in practice is either WO_IN or 0).
-**
-** Argument mPrereq is a mask of tables that must be scanned before the
-** virtual table in question. These are added to the plans prerequisites
-** before it is added to pBuilder.
-**
-** Output parameter *pbIn is set to true if the plan added to pBuilder
-** uses one or more WO_IN terms, or false otherwise.
-*/
-static int whereLoopAddVirtualOne(
-  WhereLoopBuilder *pBuilder,
-  Bitmask mPrereq,                /* Mask of tables that must be used. */
-  Bitmask mUsable,                /* Mask of usable tables */
-  u16 mExclude,                   /* Exclude terms using these operators */
-  sqlite3_index_info *pIdxInfo,   /* Populated object for xBestIndex */
-  u16 mNoOmit,                    /* Do not omit these constraints */
-  int *pbIn                       /* OUT: True if plan uses an IN(...) op */
-){
-  WhereClause *pWC = pBuilder->pWC;
-  struct sqlite3_index_constraint *pIdxCons;
-  struct sqlite3_index_constraint_usage *pUsage = pIdxInfo->aConstraintUsage;
-  int i;
-  int mxTerm;
-  int rc = SQLITE_OK;
-  WhereLoop *pNew = pBuilder->pNew;
-  Parse *pParse = pBuilder->pWInfo->pParse;
-  struct SrcList_item *pSrc = &pBuilder->pWInfo->pTabList->a[pNew->iTab];
-  int nConstraint = pIdxInfo->nConstraint;
-
-  assert( (mUsable & mPrereq)==mPrereq );
-  *pbIn = 0;
-  pNew->prereq = mPrereq;
-
-  /* Set the usable flag on the subset of constraints identified by 
-  ** arguments mUsable and mExclude. */
-  pIdxCons = *(struct sqlite3_index_constraint**)&pIdxInfo->aConstraint;
-  for(i=0; i<nConstraint; i++, pIdxCons++){
-    WhereTerm *pTerm = &pWC->a[pIdxCons->iTermOffset];
-    pIdxCons->usable = 0;
-    if( (pTerm->prereqRight & mUsable)==pTerm->prereqRight 
-     && (pTerm->eOperator & mExclude)==0
-    ){
-      pIdxCons->usable = 1;
+    testcase( pTerm->eOperator & WO_ISNULL );
+    testcase( pTerm->eOperator & WO_IN );
+    if( (pTerm->eOperator & (WO_ISNULL|WO_IN))==0 ){
+      sqlite3VdbeAddOp2(v, OP_IsNull, regBase+j, pLevel->addrBrk);
     }
   }
-
-  /* Initialize the output fields of the sqlite3_index_info structure */
-  memset(pUsage, 0, sizeof(pUsage[0])*nConstraint);
-  assert( pIdxInfo->needToFreeIdxStr==0 );
-  pIdxInfo->idxStr = 0;
-  pIdxInfo->idxNum = 0;
-  pIdxInfo->orderByConsumed = 0;
-  pIdxInfo->estimatedCost = SQLITE_BIG_DBL / (double)2;
-  pIdxInfo->estimatedRows = 25;
-  pIdxInfo->idxFlags = 0;
-  pIdxInfo->colUsed = (sqlite3_int64)pSrc->colUsed;
-
-  /* Invoke the virtual table xBestIndex() method */
-  rc = vtabBestIndex(pParse, pSrc->pTab, pIdxInfo);
-  if( rc ) return rc;
-
-  mxTerm = -1;
-  assert( pNew->nLSlot>=nConstraint );
-  for(i=0; i<nConstraint; i++) pNew->aLTerm[i] = 0;
-  pNew->u.vtab.omitMask = 0;
-  pIdxCons = *(struct sqlite3_index_constraint**)&pIdxInfo->aConstraint;
-  for(i=0; i<nConstraint; i++, pIdxCons++){
-    int iTerm;
-    if( (iTerm = pUsage[i].argvIndex - 1)>=0 ){
-      WhereTerm *pTerm;
-      int j = pIdxCons->iTermOffset;
-      if( iTerm>=nConstraint
-       || j<0
-       || j>=pWC->nTerm
-       || pNew->aLTerm[iTerm]!=0
-       || pIdxCons->usable==0
-      ){
-        rc = SQLITE_ERROR;
-        sqlite3ErrorMsg(pParse,"%s.xBestIndex malfunction",pSrc->pTab->zName);
-        return rc;
-      }
-      testcase( iTerm==nConstraint-1 );
-      testcase( j==0 );
-      testcase( j==pWC->nTerm-1 );
-      pTerm = &pWC->a[j];
-      pNew->prereq |= pTerm->prereqRight;
-      assert( iTerm<pNew->nLSlot );
-      pNew->aLTerm[iTerm] = pTerm;
-      if( iTerm>mxTerm ) mxTerm = iTerm;
-      testcase( iTerm==15 );
-      testcase( iTerm==16 );
-      if( iTerm<16 && pUsage[i].omit ) pNew->u.vtab.omitMask |= 1<<iTerm;
-      if( (pTerm->eOperator & WO_IN)!=0 ){
-        /* A virtual table that is constrained by an IN clause may not
-        ** consume the ORDER BY clause because (1) the order of IN terms
-        ** is not necessarily related to the order of output terms and
-        ** (2) Multiple outputs from a single IN value will not merge
-        ** together.  */
-        pIdxInfo->orderByConsumed = 0;
-        pIdxInfo->idxFlags &= ~SQLITE_INDEX_SCAN_UNIQUE;
-        *pbIn = 1; assert( (mExclude & WO_IN)==0 );
-      }
-    }
-  }
-  pNew->u.vtab.omitMask &= ~mNoOmit;
-
-  pNew->nLTerm = mxTerm+1;
-  assert( pNew->nLTerm<=pNew->nLSlot );
-  pNew->u.vtab.idxNum = pIdxInfo->idxNum;
-  pNew->u.vtab.needFree = pIdxInfo->needToFreeIdxStr;
-  pIdxInfo->needToFreeIdxStr = 0;
-  pNew->u.vtab.idxStr = pIdxInfo->idxStr;
-  pNew->u.vtab.isOrdered = (i8)(pIdxInfo->orderByConsumed ?
-      pIdxInfo->nOrderBy : 0);
-  pNew->rSetup = 0;
-  pNew->rRun = sqlite3LogEstFromDouble(pIdxInfo->estimatedCost);
-  pNew->nOut = sqlite3LogEst(pIdxInfo->estimatedRows);
-
-  /* Set the WHERE_ONEROW flag if the xBestIndex() method indicated
-  ** that the scan will visit at most one row. Clear it otherwise. */
-  if( pIdxInfo->idxFlags & SQLITE_INDEX_SCAN_UNIQUE ){
-    pNew->wsFlags |= WHERE_ONEROW;
-  }else{
-    pNew->wsFlags &= ~WHERE_ONEROW;
-  }
-  rc = whereLoopInsert(pBuilder, pNew);
-  if( pNew->u.vtab.needFree ){
-    sqlite3_free(pNew->u.vtab.idxStr);
-    pNew->u.vtab.needFree = 0;
-  }
-  WHERETRACE(0xffff, ("  bIn=%d prereqIn=%04llx prereqOut=%04llx\n",
-                      *pbIn, (sqlite3_uint64)mPrereq,
-                      (sqlite3_uint64)(pNew->prereq & ~mPrereq)));
-
-  return rc;
-}
-
-
-/*
-** Add all WhereLoop objects for a table of the join identified by
-** pBuilder->pNew->iTab.  That table is guaranteed to be a virtual table.
-**
-** If there are no LEFT or CROSS JOIN joins in the query, both mPrereq and
-** mUnusable are set to 0. Otherwise, mPrereq is a mask of all FROM clause
-** entries that occur before the virtual table in the FROM clause and are
-** separated from it by at least one LEFT or CROSS JOIN. Similarly, the
-** mUnusable mask contains all FROM clause entries that occur after the
-** virtual table and are separated from it by at least one LEFT or 
-** CROSS JOIN. 
-**
-** For example, if the query were:
-**
-**   ... FROM t1, t2 LEFT JOIN t3, t4, vt CROSS JOIN t5, t6;
-**
-** then mPrereq corresponds to (t1, t2) and mUnusable to (t5, t6).
-**
-** All the tables in mPrereq must be scanned before the current virtual 
-** table. So any terms for which all prerequisites are satisfied by 
-** mPrereq may be specified as "usable" in all calls to xBestIndex. 
-** Conversely, all tables in mUnusable must be scanned after the current
-** virtual table, so any terms for which the prerequisites overlap with
-** mUnusable should always be configured as "not-usable" for xBestIndex.
-*/
-static int whereLoopAddVirtual(
-  WhereLoopBuilder *pBuilder,  /* WHERE clause information */
-  Bitmask mPrereq,             /* Tables that must be scanned before this one */
-  Bitmask mUnusable            /* Tables that must be scanned after this one */
-){
-  int rc = SQLITE_OK;          /* Return code */
-  WhereInfo *pWInfo;           /* WHERE analysis context */
-  Parse *pParse;               /* The parsing context */
-  WhereClause *pWC;            /* The WHERE clause */
-  struct SrcList_item *pSrc;   /* The FROM clause term to search */
-  sqlite3_index_info *p;       /* Object to pass to xBestIndex() */
-  int nConstraint;             /* Number of constraints in p */
-  int bIn;                     /* True if plan uses IN(...) operator */
-  WhereLoop *pNew;
-  Bitmask mBest;               /* Tables used by best possible plan */
-  u16 mNoOmit;
-
-  assert( (mPrereq & mUnusable)==0 );
-  pWInfo = pBuilder->pWInfo;
-  pParse = pWInfo->pParse;
-  pWC = pBuilder->pWC;
-  pNew = pBuilder->pNew;
-  pSrc = &pWInfo->pTabList->a[pNew->iTab];
-  assert( IsVirtual(pSrc->pTab) );
-  p = allocateIndexInfo(pParse, pWC, mUnusable, pSrc, pBuilder->pOrderBy, 
-      &mNoOmit);
-  if( p==0 ) return SQLITE_NOMEM_BKPT;
-  pNew->rSetup = 0;
-  pNew->wsFlags = WHERE_VIRTUALTABLE;
-  pNew->nLTerm = 0;
-  pNew->u.vtab.needFree = 0;
-  nConstraint = p->nConstraint;
-  if( whereLoopResize(pParse->db, pNew, nConstraint) ){
-    sqlite3DbFree(pParse->db, p);
-    return SQLITE_NOMEM_BKPT;
-  }
-
-  /* First call xBestIndex() with all constraints usable. */
-  WHERETRACE(0x40, ("  VirtualOne: all usable\n"));
-  rc = whereLoopAddVirtualOne(pBuilder, mPrereq, ALLBITS, 0, p, mNoOmit, &bIn);
-
-  /* If the call to xBestIndex() with all terms enabled produced a plan
-  ** that does not require any source tables (IOW: a plan with mBest==0),
-  ** then there is no point in making any further calls to xBestIndex() 
-  ** since they will all return the same result (if the xBestIndex()
-  ** implementation is sane). */
-  if( rc==SQLITE_OK && (mBest = (pNew->prereq & ~mPrereq))!=0 ){
-    int seenZero = 0;             /* True if a plan with no prereqs seen */
-    int seenZeroNoIN = 0;         /* Plan with no prereqs and no IN(...) seen */
-    Bitmask mPrev = 0;
-    Bitmask mBestNoIn = 0;
-
-    /* If the plan produced by the earlier call uses an IN(...) term, call
-    ** xBestIndex again, this time with IN(...) terms disabled. */
-    if( bIn ){
-      WHERETRACE(0x40, ("  VirtualOne: all usable w/o IN\n"));
-      rc = whereLoopAddVirtualOne(
-          pBuilder, mPrereq, ALLBITS, WO_IN, p, mNoOmit, &bIn);
-      assert( bIn==0 );
-      mBestNoIn = pNew->prereq & ~mPrereq;
-      if( mBestNoIn==0 ){
-        seenZero = 1;
-        seenZeroNoIN = 1;
-      }
-    }
-
-    /* Call xBestIndex once for each distinct value of (prereqRight & ~mPrereq) 
-    ** in the set of terms that apply to the current virtual table.  */
-    while( rc==SQLITE_OK ){
-      int i;
-      Bitmask mNext = ALLBITS;
-      assert( mNext>0 );
-      for(i=0; i<nConstraint; i++){
-        Bitmask mThis = (
-            pWC->a[p->aConstraint[i].iTermOffset].prereqRight & ~mPrereq
-        );
-        if( mThis>mPrev && mThis<mNext ) mNext = mThis;
-      }
-      mPrev = mNext;
-      if( mNext==ALLBITS ) break;
-      if( mNext==mBest || mNext==mBestNoIn ) continue;
-      WHERETRACE(0x40, ("  VirtualOne: mPrev=%04llx mNext=%04llx\n",
-                       (sqlite3_uint64)mPrev, (sqlite3_uint64)mNext));
-      rc = whereLoopAddVirtualOne(
-          pBuilder, mPrereq, mNext|mPrereq, 0, p, mNoOmit, &bIn);
-      if( pNew->prereq==mPrereq ){
-        seenZero = 1;
-        if( bIn==0 ) seenZeroNoIN = 1;
-      }
-    }
-
-    /* If the calls to xBestIndex() in the above loop did not find a plan
-    ** that requires no source tables at all (i.e. one guaranteed to be
-    ** usable), make a call here with all source tables disabled */
-    if( rc==SQLITE_OK && seenZero==0 ){
-      WHERETRACE(0x40, ("  VirtualOne: all disabled\n"));
-      rc = whereLoopAddVirtualOne(
-          pBuilder, mPrereq, mPrereq, 0, p, mNoOmit, &bIn);
-      if( bIn==0 ) seenZeroNoIN = 1;
-    }
-
-    /* If the calls to xBestIndex() have so far failed to find a plan
-    ** that requires no source tables at all and does not use an IN(...)
-    ** operator, make a final call to obtain one here.  */
-    if( rc==SQLITE_OK && seenZeroNoIN==0 ){
-      WHERETRACE(0x40, ("  VirtualOne: all disabled and w/o IN\n"));
-      rc = whereLoopAddVirtualOne(
-          pBuilder, mPrereq, mPrereq, WO_IN, p, mNoOmit, &bIn);
-    }
-  }
-
-  if( p->needToFreeIdxStr ) sqlite3_free(p->idxStr);
-  sqlite3DbFreeNN(pParse->db, p);
-  return rc;
-}
-#endif /* SQLITE_OMIT_VIRTUALTABLE */
-
-/*
-** Add WhereLoop entries to handle OR terms.  This works for either
-** btrees or virtual tables.
-*/
-static int whereLoopAddOr(
-  WhereLoopBuilder *pBuilder, 
-  Bitmask mPrereq, 
-  Bitmask mUnusable
-){
-  WhereInfo *pWInfo = pBuilder->pWInfo;
-  WhereClause *pWC;
-  WhereLoop *pNew;
-  WhereTerm *pTerm, *pWCEnd;
-  int rc = SQLITE_OK;
-  int iCur;
-  WhereClause tempWC;
-  WhereLoopBuilder sSubBuild;
-  WhereOrSet sSum, sCur;
-  struct SrcList_item *pItem;
-  
-  pWC = pBuilder->pWC;
-  pWCEnd = pWC->a + pWC->nTerm;
-  pNew = pBuilder->pNew;
-  memset(&sSum, 0, sizeof(sSum));
-  pItem = pWInfo->pTabList->a + pNew->iTab;
-  iCur = pItem->iCursor;
-
-  for(pTerm=pWC->a; pTerm<pWCEnd && rc==SQLITE_OK; pTerm++){
-    if( (pTerm->eOperator & WO_OR)!=0
-     && (pTerm->u.pOrInfo->indexable & pNew->maskSelf)!=0 
-    ){
-      WhereClause * const pOrWC = &pTerm->u.pOrInfo->wc;
-      WhereTerm * const pOrWCEnd = &pOrWC->a[pOrWC->nTerm];
-      WhereTerm *pOrTerm;
-      int once = 1;
-      int i, j;
-    
-      sSubBuild = *pBuilder;
-      sSubBuild.pOrderBy = 0;
-      sSubBuild.pOrSet = &sCur;
-
-      WHERETRACE(0x200, ("Begin processing OR-clause %p\n", pTerm));
-      for(pOrTerm=pOrWC->a; pOrTerm<pOrWCEnd; pOrTerm++){
-        if( (pOrTerm->eOperator & WO_AND)!=0 ){
-          sSubBuild.pWC = &pOrTerm->u.pAndInfo->wc;
-        }else if( pOrTerm->leftCursor==iCur ){
-          tempWC.pWInfo = pWC->pWInfo;
-          tempWC.pOuter = pWC;
-          tempWC.op = TK_AND;
-          tempWC.nTerm = 1;
-          tempWC.a = pOrTerm;
-          sSubBuild.pWC = &tempWC;
-        }else{
-          continue;
-        }
-        sCur.n = 0;
-#ifdef WHERETRACE_ENABLED
-        WHERETRACE(0x200, ("OR-term %d of %p has %d subterms:\n", 
-                   (int)(pOrTerm-pOrWC->a), pTerm, sSubBuild.pWC->nTerm));
-        if( sqlite3WhereTrace & 0x400 ){
-          sqlite3WhereClausePrint(sSubBuild.pWC);
-        }
-#endif
-#ifndef SQLITE_OMIT_VIRTUALTABLE
-        if( IsVirtual(pItem->pTab) ){
-          rc = whereLoopAddVirtual(&sSubBuild, mPrereq, mUnusable);
-        }else
-#endif
-        {
-          rc = whereLoopAddBtree(&sSubBuild, mPrereq);
-        }
-        if( rc==SQLITE_OK ){
-          rc = whereLoopAddOr(&sSubBuild, mPrereq, mUnusable);
-        }
-        assert( rc==SQLITE_OK || sCur.n==0 );
-        if( sCur.n==0 ){
-          sSum.n = 0;
-          break;
-        }else if( once ){
-          whereOrMove(&sSum, &sCur);
-          once = 0;
-        }else{
-          WhereOrSet sPrev;
-          whereOrMove(&sPrev, &sSum);
-          sSum.n = 0;
-          for(i=0; i<sPrev.n; i++){
-            for(j=0; j<sCur.n; j++){
-              whereOrInsert(&sSum, sPrev.a[i].prereq | sCur.a[j].prereq,
-                            sqlite3LogEstAdd(sPrev.a[i].rRun, sCur.a[j].rRun),
-                            sqlite3LogEstAdd(sPrev.a[i].nOut, sCur.a[j].nOut));
-            }
-          }
-        }
-      }
-      pNew->nLTerm = 1;
-      pNew->aLTerm[0] = pTerm;
-      pNew->wsFlags = WHERE_MULTI_OR;
-      pNew->rSetup = 0;
-      pNew->iSortIdx = 0;
-      memset(&pNew->u, 0, sizeof(pNew->u));
-      for(i=0; rc==SQLITE_OK && i<sSum.n; i++){
-        /* TUNING: Currently sSum.a[i].rRun is set to the sum of the costs
-        ** of all sub-scans required by the OR-scan. However, due to rounding
-        ** errors, it may be that the cost of the OR-scan is equal to its
-        ** most expensive sub-scan. Add the smallest possible penalty 
-        ** (equivalent to multiplying the cost by 1.07) to ensure that 
-        ** this does not happen. Otherwise, for WHERE clauses such as the
-        ** following where there is an index on "y":
-        **
-        **     WHERE likelihood(x=?, 0.99) OR y=?
-        **
-        ** the planner may elect to "OR" together a full-table scan and an
-        ** index lookup. And other similarly odd results.  */
-        pNew->rRun = sSum.a[i].rRun + 1;
-        pNew->nOut = sSum.a[i].nOut;
-        pNew->prereq = sSum.a[i].prereq;
-        rc = whereLoopInsert(pBuilder, pNew);
-      }
-      WHERETRACE(0x200, ("End processing OR-clause %p\n", pTerm));
-    }
-  }
-  return rc;
-}
-
-/*
-** Add all WhereLoop objects for all tables 
-*/
-static int whereLoopAddAll(WhereLoopBuilder *pBuilder){
-  WhereInfo *pWInfo = pBuilder->pWInfo;
-  Bitmask mPrereq = 0;
-  Bitmask mPrior = 0;
-  int iTab;
-  SrcList *pTabList = pWInfo->pTabList;
-  struct SrcList_item *pItem;
-  struct SrcList_item *pEnd = &pTabList->a[pWInfo->nLevel];
-  sqlite3 *db = pWInfo->pParse->db;
-  int rc = SQLITE_OK;
-  WhereLoop *pNew;
-  u8 priorJointype = 0;
-
-  /* Loop over the tables in the join, from left to right */
-  pNew = pBuilder->pNew;
-  whereLoopInit(pNew);
-  for(iTab=0, pItem=pTabList->a; pItem<pEnd; iTab++, pItem++){
-    Bitmask mUnusable = 0;
-    pNew->iTab = iTab;
-    pNew->maskSelf = sqlite3WhereGetMask(&pWInfo->sMaskSet, pItem->iCursor);
-    if( ((pItem->fg.jointype|priorJointype) & (JT_LEFT|JT_CROSS))!=0 ){
-      /* This condition is true when pItem is the FROM clause term on the
-      ** right-hand-side of a LEFT or CROSS JOIN.  */
-      mPrereq = mPrior;
-    }
-    priorJointype = pItem->fg.jointype;
-#ifndef SQLITE_OMIT_VIRTUALTABLE
-    if( IsVirtual(pItem->pTab) ){
-      struct SrcList_item *p;
-      for(p=&pItem[1]; p<pEnd; p++){
-        if( mUnusable || (p->fg.jointype & (JT_LEFT|JT_CROSS)) ){
-          mUnusable |= sqlite3WhereGetMask(&pWInfo->sMaskSet, p->iCursor);
-        }
-      }
-      rc = whereLoopAddVirtual(pBuilder, mPrereq, mUnusable);
-    }else
-#endif /* SQLITE_OMIT_VIRTUALTABLE */
-    {
-      rc = whereLoopAddBtree(pBuilder, mPrereq);
-    }
-    if( rc==SQLITE_OK ){
-      rc = whereLoopAddOr(pBuilder, mPrereq, mUnusable);
-    }
-    mPrior |= pNew->maskSelf;
-    if( rc || db->mallocFailed ) break;
-  }
-
-  whereLoopClear(db, pNew);
-  return rc;
-}
-
-/*
-** Examine a WherePath (with the addition of the extra WhereLoop of the 6th
-** parameters) to see if it outputs rows in the requested ORDER BY
-** (or GROUP BY) without requiring a separate sort operation.  Return N:
-** 
-**   N>0:   N terms of the ORDER BY clause are satisfied
-**   N==0:  No terms of the ORDER BY clause are satisfied
-**   N<0:   Unknown yet how many terms of ORDER BY might be satisfied.   
-**
-** Note that processing for WHERE_GROUPBY and WHERE_DISTINCTBY is not as
-** strict.  With GROUP BY and DISTINCT the only requirement is that
-** equivalent rows appear immediately adjacent to one another.  GROUP BY
-** and DISTINCT do not require rows to appear in any particular order as long
-** as equivalent rows are grouped together.  Thus for GROUP BY and DISTINCT
-** the pOrderBy terms can be matched in any order.  With ORDER BY, the 
-** pOrderBy terms must be matched in strict left-to-right order.
-*/
-static i8 wherePathSatisfiesOrderBy(
-  WhereInfo *pWInfo,    /* The WHERE clause */
-  ExprList *pOrderBy,   /* ORDER BY or GROUP BY or DISTINCT clause to check */
-  WherePath *pPath,     /* The WherePath to check */
-  u16 wctrlFlags,       /* WHERE_GROUPBY or _DISTINCTBY or _ORDERBY_LIMIT */
-  u16 nLoop,            /* Number of entries in pPath->aLoop[] */
-  WhereLoop *pLast,     /* Add this WhereLoop to the end of pPath->aLoop[] */
-  Bitmask *pRevMask     /* OUT: Mask of WhereLoops to run in reverse order */
-){
-  u8 revSet;            /* True if rev is known */
-  u8 rev;               /* Composite sort order */
-  u8 revIdx;            /* Index sort order */
-  u8 isOrderDistinct;   /* All prior WhereLoops are order-distinct */
-  u8 distinctColumns;   /* True if the loop has UNIQUE NOT NULL columns */
-  u8 isMatch;           /* iColumn matches a term of the ORDER BY clause */
-  u16 eqOpMask;         /* Allowed equality operators */
-  u16 nKeyCol;          /* Number of key columns in pIndex */
-  u16 nColumn;          /* Total number of ordered columns in the index */
-  u16 nOrderBy;         /* Number terms in the ORDER BY clause */
-  int iLoop;            /* Index of WhereLoop in pPath being processed */
-  int i, j;             /* Loop counters */
-  int iCur;             /* Cursor number for current WhereLoop */
-  int iColumn;          /* A column number within table iCur */
-  WhereLoop *pLoop = 0; /* Current WhereLoop being processed. */
-  WhereTerm *pTerm;     /* A single term of the WHERE clause */
-  Expr *pOBExpr;        /* An expression from the ORDER BY clause */
-  CollSeq *pColl;       /* COLLATE function from an ORDER BY clause term */
-  Index *pIndex;        /* The index associated with pLoop */
-  sqlite3 *db = pWInfo->pParse->db;  /* Database connection */
-  Bitmask obSat = 0;    /* Mask of ORDER BY terms satisfied so far */
-  Bitmask obDone;       /* Mask of all ORDER BY terms */
-  Bitmask orderDistinctMask;  /* Mask of all well-ordered loops */
-  Bitmask ready;              /* Mask of inner loops */
-
-  /*
-  ** We say the WhereLoop is "one-row" if it generates no more than one
-  ** row of output.  A WhereLoop is one-row if all of the following are true:
-  **  (a) All index columns match with WHERE_COLUMN_EQ.
-  **  (b) The index is unique
-  ** Any WhereLoop with an WHERE_COLUMN_EQ constraint on the rowid is one-row.
-  ** Every one-row WhereLoop will have the WHERE_ONEROW bit set in wsFlags.
-  **
-  ** We say the WhereLoop is "order-distinct" if the set of columns from
-  ** that WhereLoop that are in the ORDER BY clause are different for every
-  ** row of the WhereLoop.  Every one-row WhereLoop is automatically
-  ** order-distinct.   A WhereLoop that has no columns in the ORDER BY clause
-  ** is not order-distinct. To be order-distinct is not quite the same as being
-  ** UNIQUE since a UNIQUE column or index can have multiple rows that 
-  ** are NULL and NULL values are equivalent for the purpose of order-distinct.
-  ** To be order-distinct, the columns must be UNIQUE and NOT NULL.
-  **
-  ** The rowid for a table is always UNIQUE and NOT NULL so whenever the
-  ** rowid appears in the ORDER BY clause, the corresponding WhereLoop is
-  ** automatically order-distinct.
-  */
-
-  assert( pOrderBy!=0 );
-  if( nLoop && OptimizationDisabled(db, SQLITE_OrderByIdxJoin) ) return 0;
-
-  nOrderBy = pOrderBy->nExpr;
-  testcase( nOrderBy==BMS-1 );
-  if( nOrderBy>BMS-1 ) return 0;  /* Cannot optimize overly large ORDER BYs */
-  isOrderDistinct = 1;
-  obDone = MASKBIT(nOrderBy)-1;
-  orderDistinctMask = 0;
-  ready = 0;
-  eqOpMask = WO_EQ | WO_IS | WO_ISNULL;
-  if( wctrlFlags & WHERE_ORDERBY_LIMIT ) eqOpMask |= WO_IN;
-  for(iLoop=0; isOrderDistinct && obSat<obDone && iLoop<=nLoop; iLoop++){
-    if( iLoop>0 ) ready |= pLoop->maskSelf;
-    if( iLoop<nLoop ){
-      pLoop = pPath->aLoop[iLoop];
-      if( wctrlFlags & WHERE_ORDERBY_LIMIT ) continue;
-    }else{
-      pLoop = pLast;
-    }
-    if( pLoop->wsFlags & WHERE_VIRTUALTABLE ){
-      if( pLoop->u.vtab.isOrdered ) obSat = obDone;
-      break;
-    }else{
-      pLoop->u.btree.nIdxCol = 0;
-    }
-    iCur = pWInfo->pTabList->a[pLoop->iTab].iCursor;
-
-    /* Mark off any ORDER BY term X that is a column in the table of
-    ** the current loop for which there is term in the WHERE
-    ** clause of the form X IS NULL or X=? that reference only outer
-    ** loops.
-    */
-    for(i=0; i<nOrderBy; i++){
-      if( MASKBIT(i) & obSat ) continue;
-      pOBExpr = sqlite3ExprSkipCollate(pOrderBy->a[i].pExpr);
-      if( pOBExpr->op!=TK_COLUMN ) continue;
-      if( pOBExpr->iTable!=iCur ) continue;
-      pTerm = sqlite3WhereFindTerm(&pWInfo->sWC, iCur, pOBExpr->iColumn,
-                       ~ready, eqOpMask, 0);
-      if( pTerm==0 ) continue;
-      if( pTerm->eOperator==WO_IN ){
-        /* IN terms are only valid for sorting in the ORDER BY LIMIT 
-        ** optimization, and then only if they are actually used
-        ** by the query plan */
-        assert( wctrlFlags & WHERE_ORDERBY_LIMIT );
-        for(j=0; j<pLoop->nLTerm && pTerm!=pLoop->aLTerm[j]; j++){}
-        if( j>=pLoop->nLTerm ) continue;
-      }
-      if( (pTerm->eOperator&(WO_EQ|WO_IS))!=0 && pOBExpr->iColumn>=0 ){
-        if( sqlite3ExprCollSeqMatch(pWInfo->pParse, 
-                  pOrderBy->a[i].pExpr, pTerm->pExpr)==0 ){
-          continue;
-        }
-        testcase( pTerm->pExpr->op==TK_IS );
-      }
-      obSat |= MASKBIT(i);
-    }
-
-    if( (pLoop->wsFlags & WHERE_ONEROW)==0 ){
-      if( pLoop->wsFlags & WHERE_IPK ){
-        pIndex = 0;
-        nKeyCol = 0;
-        nColumn = 1;
-      }else if( (pIndex = pLoop->u.btree.pIndex)==0 || pIndex->bUnordered ){
-        return 0;
-      }else{
-        nKeyCol = pIndex->nKeyCol;
-        nColumn = pIndex->nColumn;
-        assert( nColumn==nKeyCol+1 || !HasRowid(pIndex->pTable) );
-        assert( pIndex->aiColumn[nColumn-1]==XN_ROWID
-                          || !HasRowid(pIndex->pTable));
-        isOrderDistinct = IsUniqueIndex(pIndex);
-      }
-
-      /* Loop through all columns of the index and deal with the ones
-      ** that are not constrained by == or IN.
-      */
-      rev = revSet = 0;
-      distinctColumns = 0;
-      for(j=0; j<nColumn; j++){
-        u8 bOnce = 1; /* True to run the ORDER BY search loop */
-
-        assert( j>=pLoop->u.btree.nEq 
-            || (pLoop->aLTerm[j]==0)==(j<pLoop->nSkip)
-        );
-        if( j<pLoop->u.btree.nEq && j>=pLoop->nSkip ){
-          u16 eOp = pLoop->aLTerm[j]->eOperator;
-
-          /* Skip over == and IS and ISNULL terms.  (Also skip IN terms when
-          ** doing WHERE_ORDERBY_LIMIT processing). 
-          **
-          ** If the current term is a column of an ((?,?) IN (SELECT...)) 
-          ** expression for which the SELECT returns more than one column,
-          ** check that it is the only column used by this loop. Otherwise,
-          ** if it is one of two or more, none of the columns can be
-          ** considered to match an ORDER BY term.  */
-          if( (eOp & eqOpMask)!=0 ){
-            if( eOp & WO_ISNULL ){
-              testcase( isOrderDistinct );
-              isOrderDistinct = 0;
-            }
-            continue;  
-          }else if( ALWAYS(eOp & WO_IN) ){
-            /* ALWAYS() justification: eOp is an equality operator due to the
-            ** j<pLoop->u.btree.nEq constraint above.  Any equality other
-            ** than WO_IN is captured by the previous "if".  So this one
-            ** always has to be WO_IN. */
-            Expr *pX = pLoop->aLTerm[j]->pExpr;
-            for(i=j+1; i<pLoop->u.btree.nEq; i++){
-              if( pLoop->aLTerm[i]->pExpr==pX ){
-                assert( (pLoop->aLTerm[i]->eOperator & WO_IN) );
-                bOnce = 0;
-                break;
-              }
-            }
-          }
-        }
-
-        /* Get the column number in the table (iColumn) and sort order
-        ** (revIdx) for the j-th column of the index.
-        */
-        if( pIndex ){
-          iColumn = pIndex->aiColumn[j];
-          revIdx = pIndex->aSortOrder[j];
-          if( iColumn==pIndex->pTable->iPKey ) iColumn = XN_ROWID;
-        }else{
-          iColumn = XN_ROWID;
-          revIdx = 0;
-        }
-
-        /* An unconstrained column that might be NULL means that this
-        ** WhereLoop is not well-ordered
-        */
-        if( isOrderDistinct
-         && iColumn>=0
-         && j>=pLoop->u.btree.nEq
-         && pIndex->pTable->aCol[iColumn].notNull==0
-        ){
-          isOrderDistinct = 0;
-        }
-
-        /* Find the ORDER BY term that corresponds to the j-th column
-        ** of the index and mark that ORDER BY term off 
-        */
-        isMatch = 0;
-        for(i=0; bOnce && i<nOrderBy; i++){
-          if( MASKBIT(i) & obSat ) continue;
-          pOBExpr = sqlite3ExprSkipCollate(pOrderBy->a[i].pExpr);
-          testcase( wctrlFlags & WHERE_GROUPBY );
-          testcase( wctrlFlags & WHERE_DISTINCTBY );
-          if( (wctrlFlags & (WHERE_GROUPBY|WHERE_DISTINCTBY))==0 ) bOnce = 0;
-          if( iColumn>=XN_ROWID ){
-            if( pOBExpr->op!=TK_COLUMN ) continue;
-            if( pOBExpr->iTable!=iCur ) continue;
-            if( pOBExpr->iColumn!=iColumn ) continue;
-          }else{
-            Expr *pIdxExpr = pIndex->aColExpr->a[j].pExpr;
-            if( sqlite3ExprCompareSkip(pOBExpr, pIdxExpr, iCur) ){
-              continue;
-            }
-          }
-          if( iColumn!=XN_ROWID ){
-            pColl = sqlite3ExprNNCollSeq(pWInfo->pParse, pOrderBy->a[i].pExpr);
-            if( sqlite3StrICmp(pColl->zName, pIndex->azColl[j])!=0 ) continue;
-          }
-          pLoop->u.btree.nIdxCol = j+1;
-          isMatch = 1;
-          break;
-        }
-        if( isMatch && (wctrlFlags & WHERE_GROUPBY)==0 ){
-          /* Make sure the sort order is compatible in an ORDER BY clause.
-          ** Sort order is irrelevant for a GROUP BY clause. */
-          if( revSet ){
-            if( (rev ^ revIdx)!=pOrderBy->a[i].sortOrder ) isMatch = 0;
-          }else{
-            rev = revIdx ^ pOrderBy->a[i].sortOrder;
-            if( rev ) *pRevMask |= MASKBIT(iLoop);
-            revSet = 1;
-          }
-        }
-        if( isMatch ){
-          if( iColumn==XN_ROWID ){
-            testcase( distinctColumns==0 );
-            distinctColumns = 1;
-          }
-          obSat |= MASKBIT(i);
-        }else{
-          /* No match found */
-          if( j==0 || j<nKeyCol ){
-            testcase( isOrderDistinct!=0 );
-            isOrderDistinct = 0;
-          }
-          break;
-        }
-      } /* end Loop over all index columns */
-      if( distinctColumns ){
-        testcase( isOrderDistinct==0 );
-        isOrderDistinct = 1;
-      }
-    } /* end-if not one-row */
-
-    /* Mark off any other ORDER BY terms that reference pLoop */
-    if( isOrderDistinct ){
-      orderDistinctMask |= pLoop->maskSelf;
-      for(i=0; i<nOrderBy; i++){
-        Expr *p;
-        Bitmask mTerm;
-        if( MASKBIT(i) & obSat ) continue;
-        p = pOrderBy->a[i].pExpr;
-        mTerm = sqlite3WhereExprUsage(&pWInfo->sMaskSet,p);
-        if( mTerm==0 && !sqlite3ExprIsConstant(p) ) continue;
-        if( (mTerm&~orderDistinctMask)==0 ){
-          obSat |= MASKBIT(i);
-        }
-      }
-    }
-  } /* End the loop over all WhereLoops from outer-most down to inner-most */
-  if( obSat==obDone ) return (i8)nOrderBy;
-  if( !isOrderDistinct ){
-    for(i=nOrderBy-1; i>0; i--){
-      Bitmask m = MASKBIT(i) - 1;
-      if( (obSat&m)==m ) return i;
-    }
-    return 0;
-  }
-  return -1;
-}
-
-
-/*
-** If the WHERE_GROUPBY flag is set in the mask passed to sqlite3WhereBegin(),
-** the planner assumes that the specified pOrderBy list is actually a GROUP
-** BY clause - and so any order that groups rows as required satisfies the
-** request.
-**
-** Normally, in this case it is not possible for the caller to determine
-** whether or not the rows are really being delivered in sorted order, or
-** just in some other order that provides the required grouping. However,
-** if the WHERE_SORTBYGROUP flag is also passed to sqlite3WhereBegin(), then
-** this function may be called on the returned WhereInfo object. It returns
-** true if the rows really will be sorted in the specified order, or false
-** otherwise.
-**
-** For example, assuming:
-**
-**   CREATE INDEX i1 ON t1(x, Y);
-**
-** then
-**
-**   SELECT * FROM t1 GROUP BY x,y ORDER BY x,y;   -- IsSorted()==1
-**   SELECT * FROM t1 GROUP BY y,x ORDER BY y,x;   -- IsSorted()==0
-*/
-int sqlite3WhereIsSorted(WhereInfo *pWInfo){
-  assert( pWInfo->wctrlFlags & WHERE_GROUPBY );
-  assert( pWInfo->wctrlFlags & WHERE_SORTBYGROUP );
-  return pWInfo->sorted;
-}
-
-#ifdef WHERETRACE_ENABLED
-/* For debugging use only: */
-static const char *wherePathName(WherePath *pPath, int nLoop, WhereLoop *pLast){
-  static char zName[65];
-  int i;
-  for(i=0; i<nLoop; i++){ zName[i] = pPath->aLoop[i]->cId; }
-  if( pLast ) zName[i++] = pLast->cId;
-  zName[i] = 0;
-  return zName;
-}
-#endif
-
-/*
-** Return the cost of sorting nRow rows, assuming that the keys have 
-** nOrderby columns and that the first nSorted columns are already in
-** order.
-*/
-static LogEst whereSortingCost(
-  WhereInfo *pWInfo,
-  LogEst nRow,
-  int nOrderBy,
-  int nSorted
-){
-  /* TUNING: Estimated cost of a full external sort, where N is 
-  ** the number of rows to sort is:
-  **
-  **   cost = (3.0 * N * log(N)).
-  ** 
-  ** Or, if the order-by clause has X terms but only the last Y 
-  ** terms are out of order, then block-sorting will reduce the 
-  ** sorting cost to:
-  **
-  **   cost = (3.0 * N * log(N)) * (Y/X)
-  **
-  ** The (Y/X) term is implemented using stack variable rScale
-  ** below.  */
-  LogEst rScale, rSortCost;
-  assert( nOrderBy>0 && 66==sqlite3LogEst(100) );
-  rScale = sqlite3LogEst((nOrderBy-nSorted)*100/nOrderBy) - 66;
-  rSortCost = nRow + rScale + 16;
-
-  /* Multiple by log(M) where M is the number of output rows.
-  ** Use the LIMIT for M if it is smaller */
-  if( (pWInfo->wctrlFlags & WHERE_USE_LIMIT)!=0 && pWInfo->iLimit<nRow ){
-    nRow = pWInfo->iLimit;
-  }
-  rSortCost += estLog(nRow);
-  return rSortCost;
+  return regBase;
 }
 
 /*
-** Given the list of WhereLoop objects at pWInfo->pLoops, this routine
-** attempts to find the lowest cost path that visits each WhereLoop
-** once.  This path is then loaded into the pWInfo->a[].pWLoop fields.
-**
-** Assume that the total number of output rows that will need to be sorted
-** will be nRowEst (in the 10*log2 representation).  Or, ignore sorting
-** costs if nRowEst==0.
-**
-** Return SQLITE_OK on success or SQLITE_NOMEM of a memory allocation
-** error occurs.
-*/
-static int wherePathSolver(WhereInfo *pWInfo, LogEst nRowEst){
-  int mxChoice;             /* Maximum number of simultaneous paths tracked */
-  int nLoop;                /* Number of terms in the join */
-  Parse *pParse;            /* Parsing context */
-  sqlite3 *db;              /* The database connection */
-  int iLoop;                /* Loop counter over the terms of the join */
-  int ii, jj;               /* Loop counters */
-  int mxI = 0;              /* Index of next entry to replace */
-  int nOrderBy;             /* Number of ORDER BY clause terms */
-  LogEst mxCost = 0;        /* Maximum cost of a set of paths */
-  LogEst mxUnsorted = 0;    /* Maximum unsorted cost of a set of path */
-  int nTo, nFrom;           /* Number of valid entries in aTo[] and aFrom[] */
-  WherePath *aFrom;         /* All nFrom paths at the previous level */
-  WherePath *aTo;           /* The nTo best paths at the current level */
-  WherePath *pFrom;         /* An element of aFrom[] that we are working on */
-  WherePath *pTo;           /* An element of aTo[] that we are working on */
-  WhereLoop *pWLoop;        /* One of the WhereLoop objects */
-  WhereLoop **pX;           /* Used to divy up the pSpace memory */
-  LogEst *aSortCost = 0;    /* Sorting and partial sorting costs */
-  char *pSpace;             /* Temporary memory used by this routine */
-  int nSpace;               /* Bytes of space allocated at pSpace */
+** Generate code for the start of the iLevel-th loop in the WHERE clause
+** implementation described by pWInfo.
+*/
+static Bitmask codeOneLoopStart(
+  WhereInfo *pWInfo,   /* Complete information about the WHERE clause */
+  int iLevel,          /* Which level of pWInfo->a[] should be coded */
+  u16 wctrlFlags,      /* One of the WHERE_* flags defined in sqliteInt.h */
+  Bitmask notReady     /* Which tables are currently available */
+){
+  int j, k;            /* Loop counters */
+  int iCur;            /* The VDBE cursor for the table */
+  int addrNxt;         /* Where to jump to continue with the next IN case */
+  int omitTable;       /* True if we use the index only */
+  int bRev;            /* True if we need to scan in reverse order */
+  WhereLevel *pLevel;  /* The where level to be coded */
+  WhereClause *pWC;    /* Decomposition of the entire WHERE clause */
+  WhereTerm *pTerm;               /* A WHERE clause term */
+  Parse *pParse;                  /* Parsing context */
+  Vdbe *v;                        /* The prepared stmt under constructions */
+  struct SrcList_item *pTabItem;  /* FROM clause term being coded */
+  int addrBrk;                    /* Jump here to break out of the loop */
+  int addrCont;                   /* Jump here to continue with next cycle */
+  int iRowidReg = 0;        /* Rowid is stored in this register, if not zero */
+  int iReleaseReg = 0;      /* Temp register to free before returning */
 
   pParse = pWInfo->pParse;
-  db = pParse->db;
-  nLoop = pWInfo->nLevel;
-  /* TUNING: For simple queries, only the best path is tracked.
-  ** For 2-way joins, the 5 best paths are followed.
-  ** For joins of 3 or more tables, track the 10 best paths */
-  mxChoice = (nLoop<=1) ? 1 : (nLoop==2 ? 5 : 10);
-  assert( nLoop<=pWInfo->pTabList->nSrc );
-  WHERETRACE(0x002, ("---- begin solver.  (nRowEst=%d)\n", nRowEst));
-
-  /* If nRowEst is zero and there is an ORDER BY clause, ignore it. In this
-  ** case the purpose of this call is to estimate the number of rows returned
-  ** by the overall query. Once this estimate has been obtained, the caller
-  ** will invoke this function a second time, passing the estimate as the
-  ** nRowEst parameter.  */
-  if( pWInfo->pOrderBy==0 || nRowEst==0 ){
-    nOrderBy = 0;
-  }else{
-    nOrderBy = pWInfo->pOrderBy->nExpr;
-  }
-
-  /* Allocate and initialize space for aTo, aFrom and aSortCost[] */
-  nSpace = (sizeof(WherePath)+sizeof(WhereLoop*)*nLoop)*mxChoice*2;
-  nSpace += sizeof(LogEst) * nOrderBy;
-  pSpace = sqlite3DbMallocRawNN(db, nSpace);
-  if( pSpace==0 ) return SQLITE_NOMEM_BKPT;
-  aTo = (WherePath*)pSpace;
-  aFrom = aTo+mxChoice;
-  memset(aFrom, 0, sizeof(aFrom[0]));
-  pX = (WhereLoop**)(aFrom+mxChoice);
-  for(ii=mxChoice*2, pFrom=aTo; ii>0; ii--, pFrom++, pX += nLoop){
-    pFrom->aLoop = pX;
-  }
-  if( nOrderBy ){
-    /* If there is an ORDER BY clause and it is not being ignored, set up
-    ** space for the aSortCost[] array. Each element of the aSortCost array
-    ** is either zero - meaning it has not yet been initialized - or the
-    ** cost of sorting nRowEst rows of data where the first X terms of
-    ** the ORDER BY clause are already in order, where X is the array 
-    ** index.  */
-    aSortCost = (LogEst*)pX;
-    memset(aSortCost, 0, sizeof(LogEst) * nOrderBy);
+  v = pParse->pVdbe;
+  pWC = pWInfo->pWC;
+  pLevel = &pWInfo->a[iLevel];
+  pTabItem = &pWInfo->pTabList->a[pLevel->iFrom];
+  iCur = pTabItem->iCursor;
+  bRev = (pLevel->plan.wsFlags & WHERE_REVERSE)!=0;
+  omitTable = (pLevel->plan.wsFlags & WHERE_IDX_ONLY)!=0 
+           && (wctrlFlags & WHERE_FORCE_TABLE)==0;
+
+  /* Create labels for the "break" and "continue" instructions
+  ** for the current loop.  Jump to addrBrk to break out of a loop.
+  ** Jump to cont to go immediately to the next iteration of the
+  ** loop.
+  **
+  ** When there is an IN operator, we also have a "addrNxt" label that
+  ** means to continue with the next IN value combination.  When
+  ** there are no IN operators in the constraints, the "addrNxt" label
+  ** is the same as "addrBrk".
+  */
+  addrBrk = pLevel->addrBrk = pLevel->addrNxt = sqlite3VdbeMakeLabel(v);
+  addrCont = pLevel->addrCont = sqlite3VdbeMakeLabel(v);
+
+  /* If this is the right table of a LEFT OUTER JOIN, allocate and
+  ** initialize a memory cell that records if this table matches any
+  ** row of the left table of the join.
+  */
+  if( pLevel->iFrom>0 && (pTabItem[0].jointype & JT_LEFT)!=0 ){
+    pLevel->iLeftJoin = ++pParse->nMem;
+    sqlite3VdbeAddOp2(v, OP_Integer, 0, pLevel->iLeftJoin);
+    VdbeComment((v, "init LEFT JOIN no-match flag"));
   }
-  assert( aSortCost==0 || &pSpace[nSpace]==(char*)&aSortCost[nOrderBy] );
-  assert( aSortCost!=0 || &pSpace[nSpace]==(char*)pX );
 
-  /* Seed the search with a single WherePath containing zero WhereLoops.
-  **
-  ** TUNING: Do not let the number of iterations go above 28.  If the cost
-  ** of computing an automatic index is not paid back within the first 28
-  ** rows, then do not use the automatic index. */
-  aFrom[0].nRow = MIN(pParse->nQueryLoop, 48);  assert( 48==sqlite3LogEst(28) );
-  nFrom = 1;
-  assert( aFrom[0].isOrdered==0 );
-  if( nOrderBy ){
-    /* If nLoop is zero, then there are no FROM terms in the query. Since
-    ** in this case the query may return a maximum of one row, the results
-    ** are already in the requested order. Set isOrdered to nOrderBy to
-    ** indicate this. Or, if nLoop is greater than zero, set isOrdered to
-    ** -1, indicating that the result set may or may not be ordered, 
-    ** depending on the loops added to the current plan.  */
-    aFrom[0].isOrdered = nLoop>0 ? -1 : nOrderBy;
-  }
-
-  /* Compute successively longer WherePaths using the previous generation
-  ** of WherePaths as the basis for the next.  Keep track of the mxChoice
-  ** best paths at each generation */
-  for(iLoop=0; iLoop<nLoop; iLoop++){
-    nTo = 0;
-    for(ii=0, pFrom=aFrom; ii<nFrom; ii++, pFrom++){
-      for(pWLoop=pWInfo->pLoops; pWLoop; pWLoop=pWLoop->pNextLoop){
-        LogEst nOut;                      /* Rows visited by (pFrom+pWLoop) */
-        LogEst rCost;                     /* Cost of path (pFrom+pWLoop) */
-        LogEst rUnsorted;                 /* Unsorted cost of (pFrom+pWLoop) */
-        i8 isOrdered = pFrom->isOrdered;  /* isOrdered for (pFrom+pWLoop) */
-        Bitmask maskNew;                  /* Mask of src visited by (..) */
-        Bitmask revMask = 0;              /* Mask of rev-order loops for (..) */
-
-        if( (pWLoop->prereq & ~pFrom->maskLoop)!=0 ) continue;
-        if( (pWLoop->maskSelf & pFrom->maskLoop)!=0 ) continue;
-        if( (pWLoop->wsFlags & WHERE_AUTO_INDEX)!=0 && pFrom->nRow<10 ){
-          /* Do not use an automatic index if the this loop is expected
-          ** to run less than 2 times. */
-          assert( 10==sqlite3LogEst(2) );
-          continue;
-        }
-        /* At this point, pWLoop is a candidate to be the next loop. 
-        ** Compute its cost */
-        rUnsorted = sqlite3LogEstAdd(pWLoop->rSetup,pWLoop->rRun + pFrom->nRow);
-        rUnsorted = sqlite3LogEstAdd(rUnsorted, pFrom->rUnsorted);
-        nOut = pFrom->nRow + pWLoop->nOut;
-        maskNew = pFrom->maskLoop | pWLoop->maskSelf;
-        if( isOrdered<0 ){
-          isOrdered = wherePathSatisfiesOrderBy(pWInfo,
-                       pWInfo->pOrderBy, pFrom, pWInfo->wctrlFlags,
-                       iLoop, pWLoop, &revMask);
-        }else{
-          revMask = pFrom->revLoop;
+#ifndef SQLITE_OMIT_VIRTUALTABLE
+  if(  (pLevel->plan.wsFlags & WHERE_VIRTUALTABLE)!=0 ){
+    /* Case 0:  The table is a virtual-table.  Use the VFilter and VNext
+    **          to access the data.
+    */
+    int iReg;   /* P3 Value for OP_VFilter */
+    sqlite3_index_info *pVtabIdx = pLevel->plan.u.pVtabIdx;
+    int nConstraint = pVtabIdx->nConstraint;
+    struct sqlite3_index_constraint_usage *aUsage =
+                                                pVtabIdx->aConstraintUsage;
+    const struct sqlite3_index_constraint *aConstraint =
+                                                pVtabIdx->aConstraint;
+
+    iReg = sqlite3GetTempRange(pParse, nConstraint+2);
+    for(j=1; j<=nConstraint; j++){
+      for(k=0; k<nConstraint; k++){
+        if( aUsage[k].argvIndex==j ){
+          int iTerm = aConstraint[k].iTermOffset;
+          sqlite3ExprCode(pParse, pWC->a[iTerm].pExpr->pRight, iReg+j+1);
+          break;
         }
-        if( isOrdered>=0 && isOrdered<nOrderBy ){
-          if( aSortCost[isOrdered]==0 ){
-            aSortCost[isOrdered] = whereSortingCost(
-                pWInfo, nRowEst, nOrderBy, isOrdered
-            );
-          }
-          rCost = sqlite3LogEstAdd(rUnsorted, aSortCost[isOrdered]);
+      }
+      if( k==nConstraint ) break;
+    }
+    sqlite3VdbeAddOp2(v, OP_Integer, pVtabIdx->idxNum, iReg);
+    sqlite3VdbeAddOp2(v, OP_Integer, j-1, iReg+1);
+    sqlite3VdbeAddOp4(v, OP_VFilter, iCur, addrBrk, iReg, pVtabIdx->idxStr,
+                      pVtabIdx->needToFreeIdxStr ? P4_MPRINTF : P4_STATIC);
+    pVtabIdx->needToFreeIdxStr = 0;
+    for(j=0; j<nConstraint; j++){
+      if( aUsage[j].omit ){
+        int iTerm = aConstraint[j].iTermOffset;
+        disableTerm(pLevel, &pWC->a[iTerm]);
+      }
+    }
+    pLevel->op = OP_VNext;
+    pLevel->p1 = iCur;
+    pLevel->p2 = sqlite3VdbeCurrentAddr(v);
+    sqlite3ReleaseTempRange(pParse, iReg, nConstraint+2);
+  }else
+#endif /* SQLITE_OMIT_VIRTUALTABLE */
 
-          WHERETRACE(0x002,
-              ("---- sort cost=%-3d (%d/%d) increases cost %3d to %-3d\n",
-               aSortCost[isOrdered], (nOrderBy-isOrdered), nOrderBy, 
-               rUnsorted, rCost));
-        }else{
-          rCost = rUnsorted;
-          rUnsorted -= 2;  /* TUNING:  Slight bias in favor of no-sort plans */
-        }
+  if( pLevel->plan.wsFlags & WHERE_ROWID_EQ ){
+    /* Case 1:  We can directly reference a single row using an
+    **          equality comparison against the ROWID field.  Or
+    **          we reference multiple rows using a "rowid IN (...)"
+    **          construct.
+    */
+    iReleaseReg = sqlite3GetTempReg(pParse);
+    pTerm = findTerm(pWC, iCur, -1, notReady, WO_EQ|WO_IN, 0);
+    assert( pTerm!=0 );
+    assert( pTerm->pExpr!=0 );
+    assert( pTerm->leftCursor==iCur );
+    assert( omitTable==0 );
+    iRowidReg = codeEqualityTerm(pParse, pTerm, pLevel, iReleaseReg);
+    addrNxt = pLevel->addrNxt;
+    sqlite3VdbeAddOp2(v, OP_MustBeInt, iRowidReg, addrNxt);
+    sqlite3VdbeAddOp3(v, OP_NotExists, iCur, addrNxt, iRowidReg);
+    sqlite3ExprCacheStore(pParse, iCur, -1, iRowidReg);
+    VdbeComment((v, "pk"));
+    pLevel->op = OP_Noop;
+  }else if( pLevel->plan.wsFlags & WHERE_ROWID_RANGE ){
+    /* Case 2:  We have an inequality comparison against the ROWID field.
+    */
+    int testOp = OP_Noop;
+    int start;
+    int memEndValue = 0;
+    WhereTerm *pStart, *pEnd;
+
+    assert( omitTable==0 );
+    pStart = findTerm(pWC, iCur, -1, notReady, WO_GT|WO_GE, 0);
+    pEnd = findTerm(pWC, iCur, -1, notReady, WO_LT|WO_LE, 0);
+    if( bRev ){
+      pTerm = pStart;
+      pStart = pEnd;
+      pEnd = pTerm;
+    }
+    if( pStart ){
+      Expr *pX;             /* The expression that defines the start bound */
+      int r1, rTemp;        /* Registers for holding the start boundary */
 
-        /* Check to see if pWLoop should be added to the set of
-        ** mxChoice best-so-far paths.
-        **
-        ** First look for an existing path among best-so-far paths
-        ** that covers the same set of loops and has the same isOrdered
-        ** setting as the current path candidate.
-        **
-        ** The term "((pTo->isOrdered^isOrdered)&0x80)==0" is equivalent
-        ** to (pTo->isOrdered==(-1))==(isOrdered==(-1))" for the range
-        ** of legal values for isOrdered, -1..64.
-        */
-        for(jj=0, pTo=aTo; jj<nTo; jj++, pTo++){
-          if( pTo->maskLoop==maskNew
-           && ((pTo->isOrdered^isOrdered)&0x80)==0
-          ){
-            testcase( jj==nTo-1 );
-            break;
-          }
-        }
-        if( jj>=nTo ){
-          /* None of the existing best-so-far paths match the candidate. */
-          if( nTo>=mxChoice
-           && (rCost>mxCost || (rCost==mxCost && rUnsorted>=mxUnsorted))
-          ){
-            /* The current candidate is no better than any of the mxChoice
-            ** paths currently in the best-so-far buffer.  So discard
-            ** this candidate as not viable. */
-#ifdef WHERETRACE_ENABLED /* 0x4 */
-            if( sqlite3WhereTrace&0x4 ){
-              sqlite3DebugPrintf("Skip   %s cost=%-3d,%3d,%3d order=%c\n",
-                  wherePathName(pFrom, iLoop, pWLoop), rCost, nOut, rUnsorted,
-                  isOrdered>=0 ? isOrdered+'0' : '?');
-            }
-#endif
-            continue;
-          }
-          /* If we reach this points it means that the new candidate path
-          ** needs to be added to the set of best-so-far paths. */
-          if( nTo<mxChoice ){
-            /* Increase the size of the aTo set by one */
-            jj = nTo++;
-          }else{
-            /* New path replaces the prior worst to keep count below mxChoice */
-            jj = mxI;
-          }
-          pTo = &aTo[jj];
-#ifdef WHERETRACE_ENABLED /* 0x4 */
-          if( sqlite3WhereTrace&0x4 ){
-            sqlite3DebugPrintf("New    %s cost=%-3d,%3d,%3d order=%c\n",
-                wherePathName(pFrom, iLoop, pWLoop), rCost, nOut, rUnsorted,
-                isOrdered>=0 ? isOrdered+'0' : '?');
-          }
-#endif
-        }else{
-          /* Control reaches here if best-so-far path pTo=aTo[jj] covers the
-          ** same set of loops and has the same isOrdered setting as the
-          ** candidate path.  Check to see if the candidate should replace
-          ** pTo or if the candidate should be skipped.
-          ** 
-          ** The conditional is an expanded vector comparison equivalent to:
-          **   (pTo->rCost,pTo->nRow,pTo->rUnsorted) <= (rCost,nOut,rUnsorted)
-          */
-          if( pTo->rCost<rCost 
-           || (pTo->rCost==rCost
-               && (pTo->nRow<nOut
-                   || (pTo->nRow==nOut && pTo->rUnsorted<=rUnsorted)
-                  )
-              )
-          ){
-#ifdef WHERETRACE_ENABLED /* 0x4 */
-            if( sqlite3WhereTrace&0x4 ){
-              sqlite3DebugPrintf(
-                  "Skip   %s cost=%-3d,%3d,%3d order=%c",
-                  wherePathName(pFrom, iLoop, pWLoop), rCost, nOut, rUnsorted,
-                  isOrdered>=0 ? isOrdered+'0' : '?');
-              sqlite3DebugPrintf("   vs %s cost=%-3d,%3d,%3d order=%c\n",
-                  wherePathName(pTo, iLoop+1, 0), pTo->rCost, pTo->nRow,
-                  pTo->rUnsorted, pTo->isOrdered>=0 ? pTo->isOrdered+'0' : '?');
-            }
-#endif
-            /* Discard the candidate path from further consideration */
-            testcase( pTo->rCost==rCost );
-            continue;
-          }
-          testcase( pTo->rCost==rCost+1 );
-          /* Control reaches here if the candidate path is better than the
-          ** pTo path.  Replace pTo with the candidate. */
-#ifdef WHERETRACE_ENABLED /* 0x4 */
-          if( sqlite3WhereTrace&0x4 ){
-            sqlite3DebugPrintf(
-                "Update %s cost=%-3d,%3d,%3d order=%c",
-                wherePathName(pFrom, iLoop, pWLoop), rCost, nOut, rUnsorted,
-                isOrdered>=0 ? isOrdered+'0' : '?');
-            sqlite3DebugPrintf("  was %s cost=%-3d,%3d,%3d order=%c\n",
-                wherePathName(pTo, iLoop+1, 0), pTo->rCost, pTo->nRow,
-                pTo->rUnsorted, pTo->isOrdered>=0 ? pTo->isOrdered+'0' : '?');
-          }
-#endif
-        }
-        /* pWLoop is a winner.  Add it to the set of best so far */
-        pTo->maskLoop = pFrom->maskLoop | pWLoop->maskSelf;
-        pTo->revLoop = revMask;
-        pTo->nRow = nOut;
-        pTo->rCost = rCost;
-        pTo->rUnsorted = rUnsorted;
-        pTo->isOrdered = isOrdered;
-        memcpy(pTo->aLoop, pFrom->aLoop, sizeof(WhereLoop*)*iLoop);
-        pTo->aLoop[iLoop] = pWLoop;
-        if( nTo>=mxChoice ){
-          mxI = 0;
-          mxCost = aTo[0].rCost;
-          mxUnsorted = aTo[0].nRow;
-          for(jj=1, pTo=&aTo[1]; jj<mxChoice; jj++, pTo++){
-            if( pTo->rCost>mxCost 
-             || (pTo->rCost==mxCost && pTo->rUnsorted>mxUnsorted) 
-            ){
-              mxCost = pTo->rCost;
-              mxUnsorted = pTo->rUnsorted;
-              mxI = jj;
-            }
-          }
-        }
+      /* The following constant maps TK_xx codes into corresponding 
+      ** seek opcodes.  It depends on a particular ordering of TK_xx
+      */
+      const u8 aMoveOp[] = {
+           /* TK_GT */  OP_SeekGt,
+           /* TK_LE */  OP_SeekLe,
+           /* TK_LT */  OP_SeekLt,
+           /* TK_GE */  OP_SeekGe
+      };
+      assert( TK_LE==TK_GT+1 );      /* Make sure the ordering.. */
+      assert( TK_LT==TK_GT+2 );      /*  ... of the TK_xx values... */
+      assert( TK_GE==TK_GT+3 );      /*  ... is correcct. */
+
+      pX = pStart->pExpr;
+      assert( pX!=0 );
+      assert( pStart->leftCursor==iCur );
+      r1 = sqlite3ExprCodeTemp(pParse, pX->pRight, &rTemp);
+      sqlite3VdbeAddOp3(v, aMoveOp[pX->op-TK_GT], iCur, addrBrk, r1);
+      VdbeComment((v, "pk"));
+      sqlite3ExprCacheAffinityChange(pParse, r1, 1);
+      sqlite3ReleaseTempReg(pParse, rTemp);
+      disableTerm(pLevel, pStart);
+    }else{
+      sqlite3VdbeAddOp2(v, bRev ? OP_Last : OP_Rewind, iCur, addrBrk);
+    }
+    if( pEnd ){
+      Expr *pX;
+      pX = pEnd->pExpr;
+      assert( pX!=0 );
+      assert( pEnd->leftCursor==iCur );
+      memEndValue = ++pParse->nMem;
+      sqlite3ExprCode(pParse, pX->pRight, memEndValue);
+      if( pX->op==TK_LT || pX->op==TK_GT ){
+        testOp = bRev ? OP_Le : OP_Ge;
+      }else{
+        testOp = bRev ? OP_Lt : OP_Gt;
       }
+      disableTerm(pLevel, pEnd);
+    }
+    start = sqlite3VdbeCurrentAddr(v);
+    pLevel->op = bRev ? OP_Prev : OP_Next;
+    pLevel->p1 = iCur;
+    pLevel->p2 = start;
+    pLevel->p5 = (pStart==0 && pEnd==0) ?1:0;
+    if( testOp!=OP_Noop ){
+      iRowidReg = iReleaseReg = sqlite3GetTempReg(pParse);
+      sqlite3VdbeAddOp2(v, OP_Rowid, iCur, iRowidReg);
+      sqlite3ExprCacheStore(pParse, iCur, -1, iRowidReg);
+      sqlite3VdbeAddOp3(v, testOp, memEndValue, addrBrk, iRowidReg);
+      sqlite3VdbeChangeP5(v, SQLITE_AFF_NUMERIC | SQLITE_JUMPIFNULL);
+    }
+  }else if( pLevel->plan.wsFlags & (WHERE_COLUMN_RANGE|WHERE_COLUMN_EQ) ){
+    /* Case 3: A scan using an index.
+    **
+    **         The WHERE clause may contain zero or more equality 
+    **         terms ("==" or "IN" operators) that refer to the N
+    **         left-most columns of the index. It may also contain
+    **         inequality constraints (>, <, >= or <=) on the indexed
+    **         column that immediately follows the N equalities. Only 
+    **         the right-most column can be an inequality - the rest must
+    **         use the "==" and "IN" operators. For example, if the 
+    **         index is on (x,y,z), then the following clauses are all 
+    **         optimized:
+    **
+    **            x=5
+    **            x=5 AND y=10
+    **            x=5 AND y<10
+    **            x=5 AND y>5 AND y<10
+    **            x=5 AND y=5 AND z<=10
+    **
+    **         The z<10 term of the following cannot be used, only
+    **         the x=5 term:
+    **
+    **            x=5 AND z<10
+    **
+    **         N may be zero if there are inequality constraints.
+    **         If there are no inequality constraints, then N is at
+    **         least one.
+    **
+    **         This case is also used when there are no WHERE clause
+    **         constraints but an index is selected anyway, in order
+    **         to force the output order to conform to an ORDER BY.
+    */  
+    int aStartOp[] = {
+      0,
+      0,
+      OP_Rewind,           /* 2: (!start_constraints && startEq &&  !bRev) */
+      OP_Last,             /* 3: (!start_constraints && startEq &&   bRev) */
+      OP_SeekGt,           /* 4: (start_constraints  && !startEq && !bRev) */
+      OP_SeekLt,           /* 5: (start_constraints  && !startEq &&  bRev) */
+      OP_SeekGe,           /* 6: (start_constraints  &&  startEq && !bRev) */
+      OP_SeekLe            /* 7: (start_constraints  &&  startEq &&  bRev) */
+    };
+    int aEndOp[] = {
+      OP_Noop,             /* 0: (!end_constraints) */
+      OP_IdxGE,            /* 1: (end_constraints && !bRev) */
+      OP_IdxLT             /* 2: (end_constraints && bRev) */
+    };
+    int nEq = pLevel->plan.nEq;
+    int isMinQuery = 0;          /* If this is an optimized SELECT min(x).. */
+    int regBase;                 /* Base register holding constraint values */
+    int r1;                      /* Temp register */
+    WhereTerm *pRangeStart = 0;  /* Inequality constraint at range start */
+    WhereTerm *pRangeEnd = 0;    /* Inequality constraint at range end */
+    int startEq;                 /* True if range start uses ==, >= or <= */
+    int endEq;                   /* True if range end uses ==, >= or <= */
+    int start_constraints;       /* Start of range is constrained */
+    int nConstraint;             /* Number of constraint terms */
+    Index *pIdx;         /* The index we will be using */
+    int iIdxCur;         /* The VDBE cursor for the index */
+    int nExtraReg = 0;   /* Number of extra registers needed */
+    int op;              /* Instruction opcode */
+
+    pIdx = pLevel->plan.u.pIdx;
+    iIdxCur = pLevel->iIdxCur;
+    k = pIdx->aiColumn[nEq];     /* Column for inequality constraints */
+
+    /* If this loop satisfies a sort order (pOrderBy) request that 
+    ** was passed to this function to implement a "SELECT min(x) ..." 
+    ** query, then the caller will only allow the loop to run for
+    ** a single iteration. This means that the first row returned
+    ** should not have a NULL value stored in 'x'. If column 'x' is
+    ** the first one after the nEq equality constraints in the index,
+    ** this requires some special handling.
+    */
+    if( (wctrlFlags&WHERE_ORDERBY_MIN)!=0
+     && (pLevel->plan.wsFlags&WHERE_ORDERBY)
+     && (pIdx->nColumn>nEq)
+    ){
+      /* assert( pOrderBy->nExpr==1 ); */
+      /* assert( pOrderBy->a[0].pExpr->iColumn==pIdx->aiColumn[nEq] ); */
+      isMinQuery = 1;
+      nExtraReg = 1;
     }
 
-#ifdef WHERETRACE_ENABLED  /* >=2 */
-    if( sqlite3WhereTrace & 0x02 ){
-      sqlite3DebugPrintf("---- after round %d ----\n", iLoop);
-      for(ii=0, pTo=aTo; ii<nTo; ii++, pTo++){
-        sqlite3DebugPrintf(" %s cost=%-3d nrow=%-3d order=%c",
-           wherePathName(pTo, iLoop+1, 0), pTo->rCost, pTo->nRow,
-           pTo->isOrdered>=0 ? (pTo->isOrdered+'0') : '?');
-        if( pTo->isOrdered>0 ){
-          sqlite3DebugPrintf(" rev=0x%llx\n", pTo->revLoop);
-        }else{
-          sqlite3DebugPrintf("\n");
-        }
-      }
+    /* Find any inequality constraint terms for the start and end 
+    ** of the range. 
+    */
+    if( pLevel->plan.wsFlags & WHERE_TOP_LIMIT ){
+      pRangeEnd = findTerm(pWC, iCur, k, notReady, (WO_LT|WO_LE), pIdx);
+      nExtraReg = 1;
+    }
+    if( pLevel->plan.wsFlags & WHERE_BTM_LIMIT ){
+      pRangeStart = findTerm(pWC, iCur, k, notReady, (WO_GT|WO_GE), pIdx);
+      nExtraReg = 1;
     }
-#endif
 
-    /* Swap the roles of aFrom and aTo for the next generation */
-    pFrom = aTo;
-    aTo = aFrom;
-    aFrom = pFrom;
-    nFrom = nTo;
-  }
+    /* Generate code to evaluate all constraint terms using == or IN
+    ** and store the values of those terms in an array of registers
+    ** starting at regBase.
+    */
+    regBase = codeAllEqualityTerms(pParse, pLevel, pWC, notReady, nExtraReg);
+    addrNxt = pLevel->addrNxt;
 
-  if( nFrom==0 ){
-    sqlite3ErrorMsg(pParse, "no query solution");
-    sqlite3DbFreeNN(db, pSpace);
-    return SQLITE_ERROR;
-  }
-  
-  /* Find the lowest cost path.  pFrom will be left pointing to that path */
-  pFrom = aFrom;
-  for(ii=1; ii<nFrom; ii++){
-    if( pFrom->rCost>aFrom[ii].rCost ) pFrom = &aFrom[ii];
-  }
-  assert( pWInfo->nLevel==nLoop );
-  /* Load the lowest cost path into pWInfo */
-  for(iLoop=0; iLoop<nLoop; iLoop++){
-    WhereLevel *pLevel = pWInfo->a + iLoop;
-    pLevel->pWLoop = pWLoop = pFrom->aLoop[iLoop];
-    pLevel->iFrom = pWLoop->iTab;
-    pLevel->iTabCur = pWInfo->pTabList->a[pLevel->iFrom].iCursor;
-  }
-  if( (pWInfo->wctrlFlags & WHERE_WANT_DISTINCT)!=0
-   && (pWInfo->wctrlFlags & WHERE_DISTINCTBY)==0
-   && pWInfo->eDistinct==WHERE_DISTINCT_NOOP
-   && nRowEst
-  ){
-    Bitmask notUsed;
-    int rc = wherePathSatisfiesOrderBy(pWInfo, pWInfo->pResultSet, pFrom,
-                 WHERE_DISTINCTBY, nLoop-1, pFrom->aLoop[nLoop-1], &notUsed);
-    if( rc==pWInfo->pResultSet->nExpr ){
-      pWInfo->eDistinct = WHERE_DISTINCT_ORDERED;
+
+    /* If we are doing a reverse order scan on an ascending index, or
+    ** a forward order scan on a descending index, interchange the 
+    ** start and end terms (pRangeStart and pRangeEnd).
+    */
+    if( bRev==(pIdx->aSortOrder[nEq]==SQLITE_SO_ASC) ){
+      SWAP(WhereTerm *, pRangeEnd, pRangeStart);
     }
-  }
-  if( pWInfo->pOrderBy ){
-    if( pWInfo->wctrlFlags & WHERE_DISTINCTBY ){
-      if( pFrom->isOrdered==pWInfo->pOrderBy->nExpr ){
-        pWInfo->eDistinct = WHERE_DISTINCT_ORDERED;
-      }
-    }else{
-      pWInfo->nOBSat = pFrom->isOrdered;
-      pWInfo->revMask = pFrom->revLoop;
-      if( pWInfo->nOBSat<=0 ){
-        pWInfo->nOBSat = 0;
-        if( nLoop>0 ){
-          u32 wsFlags = pFrom->aLoop[nLoop-1]->wsFlags;
-          if( (wsFlags & WHERE_ONEROW)==0 
-           && (wsFlags&(WHERE_IPK|WHERE_COLUMN_IN))!=(WHERE_IPK|WHERE_COLUMN_IN)
-          ){
-            Bitmask m = 0;
-            int rc = wherePathSatisfiesOrderBy(pWInfo, pWInfo->pOrderBy, pFrom,
-                      WHERE_ORDERBY_LIMIT, nLoop-1, pFrom->aLoop[nLoop-1], &m);
-            testcase( wsFlags & WHERE_IPK );
-            testcase( wsFlags & WHERE_COLUMN_IN );
-            if( rc==pWInfo->pOrderBy->nExpr ){
-              pWInfo->bOrderedInnerLoop = 1;
-              pWInfo->revMask = m;
-            }
-          }
+
+    testcase( pRangeStart && pRangeStart->eOperator & WO_LE );
+    testcase( pRangeStart && pRangeStart->eOperator & WO_GE );
+    testcase( pRangeEnd && pRangeEnd->eOperator & WO_LE );
+    testcase( pRangeEnd && pRangeEnd->eOperator & WO_GE );
+    startEq = !pRangeStart || pRangeStart->eOperator & (WO_LE|WO_GE);
+    endEq =   !pRangeEnd || pRangeEnd->eOperator & (WO_LE|WO_GE);
+    start_constraints = pRangeStart || nEq>0;
+
+    /* Seek the index cursor to the start of the range. */
+    nConstraint = nEq;
+    if( pRangeStart ){
+      sqlite3ExprCode(pParse, pRangeStart->pExpr->pRight, regBase+nEq);
+      sqlite3VdbeAddOp2(v, OP_IsNull, regBase+nEq, addrNxt);
+      nConstraint++;
+    }else if( isMinQuery ){
+      sqlite3VdbeAddOp2(v, OP_Null, 0, regBase+nEq);
+      nConstraint++;
+      startEq = 0;
+      start_constraints = 1;
+    }
+    codeApplyAffinity(pParse, regBase, nConstraint, pIdx);
+    op = aStartOp[(start_constraints<<2) + (startEq<<1) + bRev];
+    assert( op!=0 );
+    testcase( op==OP_Rewind );
+    testcase( op==OP_Last );
+    testcase( op==OP_SeekGt );
+    testcase( op==OP_SeekGe );
+    testcase( op==OP_SeekLe );
+    testcase( op==OP_SeekLt );
+    sqlite3VdbeAddOp4(v, op, iIdxCur, addrNxt, regBase, 
+                      SQLITE_INT_TO_PTR(nConstraint), P4_INT32);
+
+    /* Load the value for the inequality constraint at the end of the
+    ** range (if any).
+    */
+    nConstraint = nEq;
+    if( pRangeEnd ){
+      sqlite3ExprCacheRemove(pParse, regBase+nEq);
+      sqlite3ExprCode(pParse, pRangeEnd->pExpr->pRight, regBase+nEq);
+      sqlite3VdbeAddOp2(v, OP_IsNull, regBase+nEq, addrNxt);
+      codeApplyAffinity(pParse, regBase, nEq+1, pIdx);
+      nConstraint++;
+    }
+
+    /* Top of the loop body */
+    pLevel->p2 = sqlite3VdbeCurrentAddr(v);
+
+    /* Check if the index cursor is past the end of the range. */
+    op = aEndOp[(pRangeEnd || nEq) * (1 + bRev)];
+    testcase( op==OP_Noop );
+    testcase( op==OP_IdxGE );
+    testcase( op==OP_IdxLT );
+    if( op!=OP_Noop ){
+      sqlite3VdbeAddOp4(v, op, iIdxCur, addrNxt, regBase,
+                        SQLITE_INT_TO_PTR(nConstraint), P4_INT32);
+      sqlite3VdbeChangeP5(v, endEq!=bRev ?1:0);
+    }
+
+    /* If there are inequality constraints, check that the value
+    ** of the table column that the inequality contrains is not NULL.
+    ** If it is, jump to the next iteration of the loop.
+    */
+    r1 = sqlite3GetTempReg(pParse);
+    testcase( pLevel->plan.wsFlags & WHERE_BTM_LIMIT );
+    testcase( pLevel->plan.wsFlags & WHERE_TOP_LIMIT );
+    if( pLevel->plan.wsFlags & (WHERE_BTM_LIMIT|WHERE_TOP_LIMIT) ){
+      sqlite3VdbeAddOp3(v, OP_Column, iIdxCur, nEq, r1);
+      sqlite3VdbeAddOp2(v, OP_IsNull, r1, addrCont);
+    }
+    sqlite3ReleaseTempReg(pParse, r1);
+
+    /* Seek the table cursor, if required */
+    disableTerm(pLevel, pRangeStart);
+    disableTerm(pLevel, pRangeEnd);
+    if( !omitTable ){
+      iRowidReg = iReleaseReg = sqlite3GetTempReg(pParse);
+      sqlite3VdbeAddOp2(v, OP_IdxRowid, iIdxCur, iRowidReg);
+      sqlite3ExprCacheStore(pParse, iCur, -1, iRowidReg);
+      sqlite3VdbeAddOp2(v, OP_Seek, iCur, iRowidReg);  /* Deferred seek */
+    }
+
+    /* Record the instruction used to terminate the loop. Disable 
+    ** WHERE clause terms made redundant by the index range scan.
+    */
+    pLevel->op = bRev ? OP_Prev : OP_Next;
+    pLevel->p1 = iIdxCur;
+  }else
+
+#ifndef SQLITE_OMIT_OR_OPTIMIZATION
+  if( pLevel->plan.wsFlags & WHERE_MULTI_OR ){
+    /* Case 4:  Two or more separately indexed terms connected by OR
+    **
+    ** Example:
+    **
+    **   CREATE TABLE t1(a,b,c,d);
+    **   CREATE INDEX i1 ON t1(a);
+    **   CREATE INDEX i2 ON t1(b);
+    **   CREATE INDEX i3 ON t1(c);
+    **
+    **   SELECT * FROM t1 WHERE a=5 OR b=7 OR (c=11 AND d=13)
+    **
+    ** In the example, there are three indexed terms connected by OR.
+    ** The top of the loop looks like this:
+    **
+    **          Null       1                # Zero the rowset in reg 1
+    **
+    ** Then, for each indexed term, the following. The arguments to
+    ** RowSetTest are such that the rowid of the current row is inserted
+    ** into the RowSet. If it is already present, control skips the
+    ** Gosub opcode and jumps straight to the code generated by WhereEnd().
+    **
+    **        sqlite3WhereBegin(<term>)
+    **          RowSetTest                  # Insert rowid into rowset
+    **          Gosub      2 A
+    **        sqlite3WhereEnd()
+    **
+    ** Following the above, code to terminate the loop. Label A, the target
+    ** of the Gosub above, jumps to the instruction right after the Goto.
+    **
+    **          Null       1                # Zero the rowset in reg 1
+    **          Goto       B                # The loop is finished.
+    **
+    **       A: <loop body>                 # Return data, whatever.
+    **
+    **          Return     2                # Jump back to the Gosub
+    **
+    **       B: <after the loop>
+    **
+    */
+    WhereClause *pOrWc;    /* The OR-clause broken out into subterms */
+    WhereTerm *pFinal;     /* Final subterm within the OR-clause. */
+    SrcList oneTab;        /* Shortened table list */
+
+    int regReturn = ++pParse->nMem;           /* Register used with OP_Gosub */
+    int regRowset;                            /* Register for RowSet object */
+    int regRowid;                             /* Register holding rowid */
+    int iLoopBody = sqlite3VdbeMakeLabel(v);  /* Start of loop body */
+    int iRetInit;                             /* Address of regReturn init */
+    int ii;
+   
+    pTerm = pLevel->plan.u.pTerm;
+    assert( pTerm!=0 );
+    assert( pTerm->eOperator==WO_OR );
+    assert( (pTerm->wtFlags & TERM_ORINFO)!=0 );
+    pOrWc = &pTerm->u.pOrInfo->wc;
+    pFinal = &pOrWc->a[pOrWc->nTerm-1];
+
+    /* Set up a SrcList containing just the table being scanned by this loop. */
+    oneTab.nSrc = 1;
+    oneTab.nAlloc = 1;
+    oneTab.a[0] = *pTabItem;
+
+    /* Initialize the rowset register to contain NULL. An SQL NULL is 
+    ** equivalent to an empty rowset.
+    **
+    ** Also initialize regReturn to contain the address of the instruction 
+    ** immediately following the OP_Return at the bottom of the loop. This
+    ** is required in a few obscure LEFT JOIN cases where control jumps
+    ** over the top of the loop into the body of it. In this case the 
+    ** correct response for the end-of-loop code (the OP_Return) is to 
+    ** fall through to the next instruction, just as an OP_Next does if
+    ** called on an uninitialized cursor.
+    */
+    if( (wctrlFlags & WHERE_DUPLICATES_OK)==0 ){
+      regRowset = ++pParse->nMem;
+      regRowid = ++pParse->nMem;
+      sqlite3VdbeAddOp2(v, OP_Null, 0, regRowset);
+    }
+    iRetInit = sqlite3VdbeAddOp2(v, OP_Integer, 0, regReturn);
+
+    for(ii=0; ii<pOrWc->nTerm; ii++){
+      WhereTerm *pOrTerm = &pOrWc->a[ii];
+      if( pOrTerm->leftCursor==iCur || pOrTerm->eOperator==WO_AND ){
+        WhereInfo *pSubWInfo;          /* Info for single OR-term scan */
+        /* Loop through table entries that match term pOrTerm. */
+        pSubWInfo = sqlite3WhereBegin(pParse, &oneTab, pOrTerm->pExpr, 0,
+                        WHERE_OMIT_OPEN | WHERE_OMIT_CLOSE | WHERE_FORCE_TABLE);
+        if( pSubWInfo ){
+          if( (wctrlFlags & WHERE_DUPLICATES_OK)==0 ){
+            int iSet = ((ii==pOrWc->nTerm-1)?-1:ii);
+            int r;
+            r = sqlite3ExprCodeGetColumn(pParse, pTabItem->pTab, -1, iCur, 
+                                         regRowid, 0);
+            sqlite3VdbeAddOp4(v, OP_RowSetTest, regRowset, 
+                              sqlite3VdbeCurrentAddr(v)+2,
+                              r, SQLITE_INT_TO_PTR(iSet), P4_INT32);
+          }
+          sqlite3VdbeAddOp2(v, OP_Gosub, regReturn, iLoopBody);
+
+          /* Finish the loop through table entries that match term pOrTerm. */
+          sqlite3WhereEnd(pSubWInfo);
         }
       }
     }
-    if( (pWInfo->wctrlFlags & WHERE_SORTBYGROUP)
-        && pWInfo->nOBSat==pWInfo->pOrderBy->nExpr && nLoop>0
-    ){
-      Bitmask revMask = 0;
-      int nOrder = wherePathSatisfiesOrderBy(pWInfo, pWInfo->pOrderBy, 
-          pFrom, 0, nLoop-1, pFrom->aLoop[nLoop-1], &revMask
-      );
-      assert( pWInfo->sorted==0 );
-      if( nOrder==pWInfo->pOrderBy->nExpr ){
-        pWInfo->sorted = 1;
-        pWInfo->revMask = revMask;
-      }
+    sqlite3VdbeChangeP1(v, iRetInit, sqlite3VdbeCurrentAddr(v));
+    /* sqlite3VdbeAddOp2(v, OP_Null, 0, regRowset); */
+    sqlite3VdbeAddOp2(v, OP_Goto, 0, pLevel->addrBrk);
+    sqlite3VdbeResolveLabel(v, iLoopBody);
+
+    pLevel->op = OP_Return;
+    pLevel->p1 = regReturn;
+    disableTerm(pLevel, pTerm);
+  }else
+#endif /* SQLITE_OMIT_OR_OPTIMIZATION */
+
+  {
+    /* Case 5:  There is no usable index.  We must do a complete
+    **          scan of the entire table.
+    */
+    static const u8 aStep[] = { OP_Next, OP_Prev };
+    static const u8 aStart[] = { OP_Rewind, OP_Last };
+    assert( bRev==0 || bRev==1 );
+    assert( omitTable==0 );
+    pLevel->op = aStep[bRev];
+    pLevel->p1 = iCur;
+    pLevel->p2 = 1 + sqlite3VdbeAddOp2(v, aStart[bRev], iCur, addrBrk);
+    pLevel->p5 = SQLITE_STMTSTATUS_FULLSCAN_STEP;
+  }
+  notReady &= ~getMask(pWC->pMaskSet, iCur);
+
+  /* Insert code to test every subexpression that can be completely
+  ** computed using the current set of tables.
+  */
+  k = 0;
+  for(pTerm=pWC->a, j=pWC->nTerm; j>0; j--, pTerm++){
+    Expr *pE;
+    testcase( pTerm->wtFlags & TERM_VIRTUAL );
+    testcase( pTerm->wtFlags & TERM_CODED );
+    if( pTerm->wtFlags & (TERM_VIRTUAL|TERM_CODED) ) continue;
+    if( (pTerm->prereqAll & notReady)!=0 ) continue;
+    pE = pTerm->pExpr;
+    assert( pE!=0 );
+    if( pLevel->iLeftJoin && !ExprHasProperty(pE, EP_FromJoin) ){
+      continue;
     }
+    sqlite3ExprIfFalse(pParse, pE, addrCont, SQLITE_JUMPIFNULL);
+    k = 1;
+    pTerm->wtFlags |= TERM_CODED;
   }
 
+  /* For a LEFT OUTER JOIN, generate code that will record the fact that
+  ** at least one row of the right table has matched the left table.  
+  */
+  if( pLevel->iLeftJoin ){
+    pLevel->addrFirst = sqlite3VdbeCurrentAddr(v);
+    sqlite3VdbeAddOp2(v, OP_Integer, 1, pLevel->iLeftJoin);
+    VdbeComment((v, "record LEFT JOIN hit"));
+    sqlite3ExprCacheClear(pParse);
+    for(pTerm=pWC->a, j=0; j<pWC->nTerm; j++, pTerm++){
+      testcase( pTerm->wtFlags & TERM_VIRTUAL );
+      testcase( pTerm->wtFlags & TERM_CODED );
+      if( pTerm->wtFlags & (TERM_VIRTUAL|TERM_CODED) ) continue;
+      if( (pTerm->prereqAll & notReady)!=0 ) continue;
+      assert( pTerm->pExpr );
+      sqlite3ExprIfFalse(pParse, pTerm->pExpr, addrCont, SQLITE_JUMPIFNULL);
+      pTerm->wtFlags |= TERM_CODED;
+    }
+  }
+  sqlite3ReleaseTempReg(pParse, iReleaseReg);
 
-  pWInfo->nRowOut = pFrom->nRow;
-
-  /* Free temporary memory and return success */
-  sqlite3DbFreeNN(db, pSpace);
-  return SQLITE_OK;
+  return notReady;
 }
 
+#if defined(SQLITE_TEST)
 /*
-** Most queries use only a single table (they are not joins) and have
-** simple == constraints against indexed fields.  This routine attempts
-** to plan those simple cases using much less ceremony than the
-** general-purpose query planner, and thereby yield faster sqlite3_prepare()
-** times for the common case.
-**
-** Return non-zero on success, if this query can be handled by this
-** no-frills query planner.  Return zero if this query needs the 
-** general-purpose query planner.
+** The following variable holds a text description of query plan generated
+** by the most recent call to sqlite3WhereBegin().  Each call to WhereBegin
+** overwrites the previous.  This information is used for testing and
+** analysis only.
 */
-static int whereShortCut(WhereLoopBuilder *pBuilder){
-  WhereInfo *pWInfo;
-  struct SrcList_item *pItem;
-  WhereClause *pWC;
-  WhereTerm *pTerm;
-  WhereLoop *pLoop;
-  int iCur;
-  int j;
-  Table *pTab;
-  Index *pIdx;
-
-  pWInfo = pBuilder->pWInfo;
-  if( pWInfo->wctrlFlags & WHERE_OR_SUBCLAUSE ) return 0;
-  assert( pWInfo->pTabList->nSrc>=1 );
-  pItem = pWInfo->pTabList->a;
-  pTab = pItem->pTab;
-  if( IsVirtual(pTab) ) return 0;
-  if( pItem->fg.isIndexedBy ) return 0;
-  iCur = pItem->iCursor;
-  pWC = &pWInfo->sWC;
-  pLoop = pBuilder->pNew;
-  pLoop->wsFlags = 0;
-  pLoop->nSkip = 0;
-  pTerm = sqlite3WhereFindTerm(pWC, iCur, -1, 0, WO_EQ|WO_IS, 0);
-  if( pTerm ){
-    testcase( pTerm->eOperator & WO_IS );
-    pLoop->wsFlags = WHERE_COLUMN_EQ|WHERE_IPK|WHERE_ONEROW;
-    pLoop->aLTerm[0] = pTerm;
-    pLoop->nLTerm = 1;
-    pLoop->u.btree.nEq = 1;
-    /* TUNING: Cost of a rowid lookup is 10 */
-    pLoop->rRun = 33;  /* 33==sqlite3LogEst(10) */
-  }else{
-    for(pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext){
-      int opMask;
-      assert( pLoop->aLTermSpace==pLoop->aLTerm );
-      if( !IsUniqueIndex(pIdx)
-       || pIdx->pPartIdxWhere!=0 
-       || pIdx->nKeyCol>ArraySize(pLoop->aLTermSpace) 
-      ) continue;
-      opMask = pIdx->uniqNotNull ? (WO_EQ|WO_IS) : WO_EQ;
-      for(j=0; j<pIdx->nKeyCol; j++){
-        pTerm = sqlite3WhereFindTerm(pWC, iCur, j, 0, opMask, pIdx);
-        if( pTerm==0 ) break;
-        testcase( pTerm->eOperator & WO_IS );
-        pLoop->aLTerm[j] = pTerm;
-      }
-      if( j!=pIdx->nKeyCol ) continue;
-      pLoop->wsFlags = WHERE_COLUMN_EQ|WHERE_ONEROW|WHERE_INDEXED;
-      if( pIdx->isCovering || (pItem->colUsed & ~columnsInIndex(pIdx))==0 ){
-        pLoop->wsFlags |= WHERE_IDX_ONLY;
-      }
-      pLoop->nLTerm = j;
-      pLoop->u.btree.nEq = j;
-      pLoop->u.btree.pIndex = pIdx;
-      /* TUNING: Cost of a unique index lookup is 15 */
-      pLoop->rRun = 39;  /* 39==sqlite3LogEst(15) */
-      break;
-    }
-  }
-  if( pLoop->wsFlags ){
-    pLoop->nOut = (LogEst)1;
-    pWInfo->a[0].pWLoop = pLoop;
-    assert( pWInfo->sMaskSet.n==1 && iCur==pWInfo->sMaskSet.ix[0] );
-    pLoop->maskSelf = 1; /* sqlite3WhereGetMask(&pWInfo->sMaskSet, iCur); */
-    pWInfo->a[0].iTabCur = iCur;
-    pWInfo->nRowOut = 1;
-    if( pWInfo->pOrderBy ) pWInfo->nOBSat =  pWInfo->pOrderBy->nExpr;
-    if( pWInfo->wctrlFlags & WHERE_WANT_DISTINCT ){
-      pWInfo->eDistinct = WHERE_DISTINCT_UNIQUE;
-    }
-#ifdef SQLITE_DEBUG
-    pLoop->cId = '0';
-#endif
-    return 1;
-  }
-  return 0;
-}
+char sqlite3_query_plan[BMS*2*40];  /* Text of the join */
+static int nQPlan = 0;              /* Next free slow in _query_plan[] */
+
+#endif /* SQLITE_TEST */
+
 
 /*
-** Helper function for exprIsDeterministic().
+** Free a WhereInfo structure
 */
-static int exprNodeIsDeterministic(Walker *pWalker, Expr *pExpr){
-  if( pExpr->op==TK_FUNCTION && ExprHasProperty(pExpr, EP_ConstFunc)==0 ){
-    pWalker->eCode = 0;
-    return WRC_Abort;
+static void whereInfoFree(sqlite3 *db, WhereInfo *pWInfo){
+  if( pWInfo ){
+    int i;
+    for(i=0; i<pWInfo->nLevel; i++){
+      sqlite3_index_info *pInfo = pWInfo->a[i].pIdxInfo;
+      if( pInfo ){
+        /* assert( pInfo->needToFreeIdxStr==0 || db->mallocFailed ); */
+        if( pInfo->needToFreeIdxStr ){
+          sqlite3_free(pInfo->idxStr);
+        }
+        sqlite3DbFree(db, pInfo);
+      }
+    }
+    whereClauseClear(pWInfo->pWC);
+    sqlite3DbFree(db, pWInfo);
   }
-  return WRC_Continue;
 }
 
-/*
-** Return true if the expression contains no non-deterministic SQL 
-** functions. Do not consider non-deterministic SQL functions that are 
-** part of sub-select statements.
-*/
-static int exprIsDeterministic(Expr *p){
-  Walker w;
-  memset(&w, 0, sizeof(w));
-  w.eCode = 1;
-  w.xExprCallback = exprNodeIsDeterministic;
-  w.xSelectCallback = sqlite3SelectWalkFail;
-  sqlite3WalkExpr(&w, p);
-  return w.eCode;
-}
 
 /*
 ** Generate the beginning of the loop used for WHERE clause processing.
 ** The return value is a pointer to an opaque structure that contains
 ** information needed to terminate the loop.  Later, the calling routine
 ** should invoke sqlite3WhereEnd() with the return value of this function
