 **        goto start
 **      fi
 **    end
 **
 ** ORDER BY CLAUSE PROCESSING
 **
-** *ppOrderBy is a pointer to the ORDER BY clause of a SELECT statement,
+** pOrderBy is a pointer to the ORDER BY clause (or the GROUP BY clause
+** if the WHERE_GROUPBY flag is set in wctrlFlags) of a SELECT statement
 ** if there is one.  If there is no ORDER BY clause or if this routine
-** is called from an UPDATE or DELETE statement, then ppOrderBy is NULL.
+** is called from an UPDATE or DELETE statement, then pOrderBy is NULL.
 **
-** If an index can be used so that the natural output order of the table
-** scan is correct for the ORDER BY clause, then that index is used and
-** *ppOrderBy is set to NULL.  This is an optimization that prevents an
-** unnecessary sort of the result set if an index appropriate for the
-** ORDER BY clause already exists.
-**
-** If the where clause loops cannot be arranged to provide the correct
-** output order, then the *ppOrderBy is unchanged.
+** The iIdxCur parameter is the cursor number of an index.  If 
+** WHERE_OR_SUBCLAUSE is set, iIdxCur is the cursor number of an index
+** to use for OR clause processing.  The WHERE clause should use this
+** specific cursor.  If WHERE_ONEPASS_DESIRED is set, then iIdxCur is
+** the first cursor in an array of cursors for all indices.  iIdxCur should
+** be used to compute the appropriate cursor depending on which index is
+** used.
 */
 WhereInfo *sqlite3WhereBegin(
-  Parse *pParse,        /* The parser context */
-  SrcList *pTabList,    /* A list of all tables to be scanned */
-  Expr *pWhere,         /* The WHERE clause */
-  ExprList **ppOrderBy, /* An ORDER BY clause, or NULL */
-  u16 wctrlFlags        /* One of the WHERE_* flags defined in sqliteInt.h */
+  Parse *pParse,          /* The parser context */
+  SrcList *pTabList,      /* FROM clause: A list of all tables to be scanned */
+  Expr *pWhere,           /* The WHERE clause */
+  ExprList *pOrderBy,     /* An ORDER BY (or GROUP BY) clause, or NULL */
+  ExprList *pResultSet,   /* Query result set.  Req'd for DISTINCT */
+  u16 wctrlFlags,         /* The WHERE_* flags defined in sqliteInt.h */
+  int iAuxArg             /* If WHERE_OR_SUBCLAUSE is set, index cursor number
+                          ** If WHERE_USE_LIMIT, then the limit amount */
 ){
-  int i;                     /* Loop counter */
   int nByteWInfo;            /* Num. bytes allocated for WhereInfo struct */
+  int nTabList;              /* Number of elements in pTabList */
   WhereInfo *pWInfo;         /* Will become the return value of this function */
   Vdbe *v = pParse->pVdbe;   /* The virtual database engine */
   Bitmask notReady;          /* Cursors that are not yet positioned */
+  WhereLoopBuilder sWLB;     /* The WhereLoop builder */
   WhereMaskSet *pMaskSet;    /* The expression mask set */
-  WhereClause *pWC;               /* Decomposition of the WHERE clause */
-  struct SrcList_item *pTabItem;  /* A single entry from pTabList */
-  WhereLevel *pLevel;             /* A single level in the pWInfo list */
-  int iFrom;                      /* First unused FROM clause element */
-  int andFlags;              /* AND-ed combination of all pWC->a[].wtFlags */
+  WhereLevel *pLevel;        /* A single level in pWInfo->a[] */
+  WhereLoop *pLoop;          /* Pointer to a single WhereLoop object */
+  int ii;                    /* Loop counter */
   sqlite3 *db;               /* Database connection */
+  int rc;                    /* Return code */
+  u8 bFordelete = 0;         /* OPFLAG_FORDELETE or zero, as appropriate */
+
+  assert( (wctrlFlags & WHERE_ONEPASS_MULTIROW)==0 || (
+        (wctrlFlags & WHERE_ONEPASS_DESIRED)!=0 
+     && (wctrlFlags & WHERE_OR_SUBCLAUSE)==0 
+  ));
+
+  /* Only one of WHERE_OR_SUBCLAUSE or WHERE_USE_LIMIT */
+  assert( (wctrlFlags & WHERE_OR_SUBCLAUSE)==0
+            || (wctrlFlags & WHERE_USE_LIMIT)==0 );
+
+  /* Variable initialization */
+  db = pParse->db;
+  memset(&sWLB, 0, sizeof(sWLB));
+
+  /* An ORDER/GROUP BY clause of more than 63 terms cannot be optimized */
+  testcase( pOrderBy && pOrderBy->nExpr==BMS-1 );
+  if( pOrderBy && pOrderBy->nExpr>=BMS ) pOrderBy = 0;
+  sWLB.pOrderBy = pOrderBy;
+
+  /* Disable the DISTINCT optimization if SQLITE_DistinctOpt is set via
+  ** sqlite3_test_ctrl(SQLITE_TESTCTRL_OPTIMIZATIONS,...) */
+  if( OptimizationDisabled(db, SQLITE_DistinctOpt) ){
+    wctrlFlags &= ~WHERE_WANT_DISTINCT;
+  }
 
   /* The number of tables in the FROM clause is limited by the number of
   ** bits in a Bitmask 
   */
+  testcase( pTabList->nSrc==BMS );
   if( pTabList->nSrc>BMS ){
     sqlite3ErrorMsg(pParse, "at most %d tables in a join", BMS);
     return 0;
   }
 
+  /* This function normally generates a nested loop for all tables in 
+  ** pTabList.  But if the WHERE_OR_SUBCLAUSE flag is set, then we should
+  ** only generate code for the first table in pTabList and assume that
+  ** any cursors associated with subsequent tables are uninitialized.
+  */
+  nTabList = (wctrlFlags & WHERE_OR_SUBCLAUSE) ? 1 : pTabList->nSrc;
+
   /* Allocate and initialize the WhereInfo structure that will become the
   ** return value. A single allocation is used to store the WhereInfo
   ** struct, the contents of WhereInfo.a[], the WhereClause structure
   ** and the WhereMaskSet structure. Since WhereClause contains an 8-byte
   ** field (type Bitmask) it must be aligned on an 8-byte boundary on
   ** some architectures. Hence the ROUND8() below.
   */
-  db = pParse->db;
-  nByteWInfo = ROUND8(sizeof(WhereInfo)+(pTabList->nSrc-1)*sizeof(WhereLevel));
-  pWInfo = sqlite3DbMallocZero(db, 
-      nByteWInfo + 
-      sizeof(WhereClause) +
-      sizeof(WhereMaskSet)
-  );
+  nByteWInfo = ROUND8(sizeof(WhereInfo)+(nTabList-1)*sizeof(WhereLevel));
+  pWInfo = sqlite3DbMallocRawNN(db, nByteWInfo + sizeof(WhereLoop));
   if( db->mallocFailed ){
+    sqlite3DbFree(db, pWInfo);
+    pWInfo = 0;
     goto whereBeginError;
   }
-  pWInfo->nLevel = pTabList->nSrc;
   pWInfo->pParse = pParse;
   pWInfo->pTabList = pTabList;
-  pWInfo->iBreak = sqlite3VdbeMakeLabel(v);
-  pWInfo->pWC = pWC = (WhereClause *)&((u8 *)pWInfo)[nByteWInfo];
+  pWInfo->pOrderBy = pOrderBy;
+  pWInfo->pWhere = pWhere;
+  pWInfo->pResultSet = pResultSet;
+  pWInfo->aiCurOnePass[0] = pWInfo->aiCurOnePass[1] = -1;
+  pWInfo->nLevel = nTabList;
+  pWInfo->iBreak = pWInfo->iContinue = sqlite3VdbeMakeLabel(v);
   pWInfo->wctrlFlags = wctrlFlags;
-  pMaskSet = (WhereMaskSet*)&pWC[1];
+  pWInfo->iLimit = iAuxArg;
+  pWInfo->savedNQueryLoop = pParse->nQueryLoop;
+  memset(&pWInfo->nOBSat, 0, 
+         offsetof(WhereInfo,sWC) - offsetof(WhereInfo,nOBSat));
+  memset(&pWInfo->a[0], 0, sizeof(WhereLoop)+nTabList*sizeof(WhereLevel));
+  assert( pWInfo->eOnePass==ONEPASS_OFF );  /* ONEPASS defaults to OFF */
+  pMaskSet = &pWInfo->sMaskSet;
+  sWLB.pWInfo = pWInfo;
+  sWLB.pWC = &pWInfo->sWC;
+  sWLB.pNew = (WhereLoop*)(((char*)pWInfo)+nByteWInfo);
+  assert( EIGHT_BYTE_ALIGNMENT(sWLB.pNew) );
+  whereLoopInit(sWLB.pNew);
+#ifdef SQLITE_DEBUG
+  sWLB.pNew->cId = '*';
+#endif
 
   /* Split the WHERE clause into separate subexpressions where each
   ** subexpression is separated by an AND operator.
   */
   initMaskSet(pMaskSet);
-  whereClauseInit(pWC, pParse, pMaskSet);
-  sqlite3ExprCodeConstants(pParse, pWhere);
-  whereSplit(pWC, pWhere, TK_AND);
+  sqlite3WhereClauseInit(&pWInfo->sWC, pWInfo);
+  sqlite3WhereSplit(&pWInfo->sWC, pWhere, TK_AND);
     
-  /* Special case: a WHERE clause that is constant.  Evaluate the
-  ** expression and either jump over all of the code or fall thru.
+  /* Special case: No FROM clause
   */
-  if( pWhere && (pTabList->nSrc==0 || sqlite3ExprIsConstantNotJoin(pWhere)) ){
-    sqlite3ExprIfFalse(pParse, pWhere, pWInfo->iBreak, SQLITE_JUMPIFNULL);
-    pWhere = 0;
+  if( nTabList==0 ){
+    if( pOrderBy ) pWInfo->nOBSat = pOrderBy->nExpr;
+    if( wctrlFlags & WHERE_WANT_DISTINCT ){
+      pWInfo->eDistinct = WHERE_DISTINCT_UNIQUE;
+    }
+  }else{
+    /* Assign a bit from the bitmask to every term in the FROM clause.
+    **
+    ** The N-th term of the FROM clause is assigned a bitmask of 1<<N.
+    **
+    ** The rule of the previous sentence ensures thta if X is the bitmask for
+    ** a table T, then X-1 is the bitmask for all other tables to the left of T.
+    ** Knowing the bitmask for all tables to the left of a left join is
+    ** important.  Ticket #3015.
+    **
+    ** Note that bitmasks are created for all pTabList->nSrc tables in
+    ** pTabList, not just the first nTabList tables.  nTabList is normally
+    ** equal to pTabList->nSrc but might be shortened to 1 if the
+    ** WHERE_OR_SUBCLAUSE flag is set.
+    */
+    ii = 0;
+    do{
+      createMask(pMaskSet, pTabList->a[ii].iCursor);
+      sqlite3WhereTabFuncArgs(pParse, &pTabList->a[ii], &pWInfo->sWC);
+    }while( (++ii)<pTabList->nSrc );
+  #ifdef SQLITE_DEBUG
+    {
+      Bitmask mx = 0;
+      for(ii=0; ii<pTabList->nSrc; ii++){
+        Bitmask m = sqlite3WhereGetMask(pMaskSet, pTabList->a[ii].iCursor);
+        assert( m>=mx );
+        mx = m;
+      }
+    }
+  #endif
   }
-
-  /* Assign a bit from the bitmask to every term in the FROM clause.
+  
+  /* Analyze all of the subexpressions. */
+  sqlite3WhereExprAnalyze(pTabList, &pWInfo->sWC);
+  if( db->mallocFailed ) goto whereBeginError;
+
+  /* Special case: WHERE terms that do not refer to any tables in the join
+  ** (constant expressions). Evaluate each such term, and jump over all the
+  ** generated code if the result is not true.  
   **
-  ** When assigning bitmask values to FROM clause cursors, it must be
-  ** the case that if X is the bitmask for the N-th FROM clause term then
-  ** the bitmask for all FROM clause terms to the left of the N-th term
-  ** is (X-1).   An expression from the ON clause of a LEFT JOIN can use
-  ** its Expr.iRightJoinTable value to find the bitmask of the right table
-  ** of the join.  Subtracting one from the right table bitmask gives a
-  ** bitmask for all tables to the left of the join.  Knowing the bitmask
-  ** for all tables to the left of a left join is important.  Ticket #3015.
+  ** Do not do this if the expression contains non-deterministic functions
+  ** that are not within a sub-select. This is not strictly required, but
+  ** preserves SQLite's legacy behaviour in the following two cases:
   **
-  ** Configure the WhereClause.vmask variable so that bits that correspond
-  ** to virtual table cursors are set. This is used to selectively disable 
-  ** the OR-to-IN transformation in exprAnalyzeOrTerm(). It is not helpful 
-  ** with virtual tables.
+  **   FROM ... WHERE random()>0;           -- eval random() once per row
+  **   FROM ... WHERE (SELECT random())>0;  -- eval random() once overall
   */
-  assert( pWC->vmask==0 && pMaskSet->n==0 );
-  for(i=0; i<pTabList->nSrc; i++){
-    createMask(pMaskSet, pTabList->a[i].iCursor);
-    if( ALWAYS(pTabList->a[i].pTab) && IsVirtual(pTabList->a[i].pTab) ){
-      pWC->vmask |= ((Bitmask)1 << i);
+  for(ii=0; ii<sWLB.pWC->nTerm; ii++){
+    WhereTerm *pT = &sWLB.pWC->a[ii];
+    if( pT->prereqAll==0 && (nTabList==0 || exprIsDeterministic(pT->pExpr)) ){
+      sqlite3ExprIfFalse(pParse, pT->pExpr, pWInfo->iBreak, SQLITE_JUMPIFNULL);
+      pT->wtFlags |= TERM_CODED;
     }
   }
-#ifndef NDEBUG
-  {
-    Bitmask toTheLeft = 0;
-    for(i=0; i<pTabList->nSrc; i++){
-      Bitmask m = getMask(pMaskSet, pTabList->a[i].iCursor);
-      assert( (m-1)==toTheLeft );
-      toTheLeft |= m;
+
+  if( wctrlFlags & WHERE_WANT_DISTINCT ){
+    if( isDistinctRedundant(pParse, pTabList, &pWInfo->sWC, pResultSet) ){
+      /* The DISTINCT marking is pointless.  Ignore it. */
+      pWInfo->eDistinct = WHERE_DISTINCT_UNIQUE;
+    }else if( pOrderBy==0 ){
+      /* Try to ORDER BY the result set to make distinct processing easier */
+      pWInfo->wctrlFlags |= WHERE_DISTINCTBY;
+      pWInfo->pOrderBy = pResultSet;
     }
   }
-#endif
 
-  /* Analyze all of the subexpressions.  Note that exprAnalyze() might
-  ** add new virtual terms onto the end of the WHERE clause.  We do not
-  ** want to analyze these virtual terms, so start analyzing at the end
-  ** and work forward so that the added virtual terms are never processed.
-  */
-  exprAnalyzeAll(pTabList, pWC);
-  if( db->mallocFailed ){
-    goto whereBeginError;
+  /* Construct the WhereLoop objects */
+#if defined(WHERETRACE_ENABLED)
+  if( sqlite3WhereTrace & 0xffff ){
+    sqlite3DebugPrintf("*** Optimizer Start *** (wctrlFlags: 0x%x",wctrlFlags);
+    if( wctrlFlags & WHERE_USE_LIMIT ){
+      sqlite3DebugPrintf(", limit: %d", iAuxArg);
+    }
+    sqlite3DebugPrintf(")\n");
   }
+  if( sqlite3WhereTrace & 0x100 ){ /* Display all terms of the WHERE clause */
+    sqlite3WhereClausePrint(sWLB.pWC);
+  }
+#endif
 
-  /* Chose the best index to use for each table in the FROM clause.
-  **
-  ** This loop fills in the following fields:
-  **
-  **   pWInfo->a[].pIdx      The index to use for this level of the loop.
-  **   pWInfo->a[].wsFlags   WHERE_xxx flags associated with pIdx
-  **   pWInfo->a[].nEq       The number of == and IN constraints
-  **   pWInfo->a[].iFrom     Which term of the FROM clause is being coded
-  **   pWInfo->a[].iTabCur   The VDBE cursor for the database table
-  **   pWInfo->a[].iIdxCur   The VDBE cursor for the index
-  **   pWInfo->a[].pTerm     When wsFlags==WO_OR, the OR-clause term
-  **
-  ** This loop also figures out the nesting order of tables in the FROM
-  ** clause.
-  */
-  notReady = ~(Bitmask)0;
-  pTabItem = pTabList->a;
-  pLevel = pWInfo->a;
-  andFlags = ~0;
-  WHERETRACE(("*** Optimizer Start ***\n"));
-  for(i=iFrom=0, pLevel=pWInfo->a; i<pTabList->nSrc; i++, pLevel++){
-    WhereCost bestPlan;         /* Most efficient plan seen so far */
-    Index *pIdx;                /* Index for FROM table at pTabItem */
-    int j;                      /* For looping over FROM tables */
-    int bestJ = 0;              /* The value of j */
-    Bitmask m;                  /* Bitmask value for j or bestJ */
-    int once = 0;               /* True when first table is seen */
-
-    memset(&bestPlan, 0, sizeof(bestPlan));
-    bestPlan.rCost = SQLITE_BIG_DBL;
-    for(j=iFrom, pTabItem=&pTabList->a[j]; j<pTabList->nSrc; j++, pTabItem++){
-      int doNotReorder;    /* True if this table should not be reordered */
-      WhereCost sCost;     /* Cost information from best[Virtual]Index() */
-      ExprList *pOrderBy;  /* ORDER BY clause for index to optimize */
-
-      doNotReorder =  (pTabItem->jointype & (JT_LEFT|JT_CROSS))!=0;
-      if( once && doNotReorder ) break;
-      m = getMask(pMaskSet, pTabItem->iCursor);
-      if( (m & notReady)==0 ){
-        if( j==iFrom ) iFrom++;
-        continue;
+  if( nTabList!=1 || whereShortCut(&sWLB)==0 ){
+    rc = whereLoopAddAll(&sWLB);
+    if( rc ) goto whereBeginError;
+  
+#ifdef WHERETRACE_ENABLED
+    if( sqlite3WhereTrace ){    /* Display all of the WhereLoop objects */
+      WhereLoop *p;
+      int i;
+      static const char zLabel[] = "0123456789abcdefghijklmnopqrstuvwyxz"
+                                             "ABCDEFGHIJKLMNOPQRSTUVWYXZ";
+      for(p=pWInfo->pLoops, i=0; p; p=p->pNextLoop, i++){
+        p->cId = zLabel[i%(sizeof(zLabel)-1)];
+        whereLoopPrint(p, sWLB.pWC);
       }
-      pOrderBy = ((i==0 && ppOrderBy )?*ppOrderBy:0);
-
-      assert( pTabItem->pTab );
-#ifndef SQLITE_OMIT_VIRTUALTABLE
-      if( IsVirtual(pTabItem->pTab) ){
-        sqlite3_index_info **pp = &pWInfo->a[j].pIdxInfo;
-        bestVirtualIndex(pParse, pWC, pTabItem, notReady, pOrderBy, &sCost, pp);
-      }else 
+    }
 #endif
-      {
-        bestBtreeIndex(pParse, pWC, pTabItem, notReady, pOrderBy, &sCost);
-      }
-      if( once==0 || sCost.rCost<bestPlan.rCost ){
-        once = 1;
-        bestPlan = sCost;
-        bestJ = j;
-      }
-      if( doNotReorder ) break;
-    }
-    assert( once );
-    assert( notReady & getMask(pMaskSet, pTabList->a[bestJ].iCursor) );
-    WHERETRACE(("*** Optimizer selects table %d for loop %d\n", bestJ,
-           pLevel-pWInfo->a));
-    if( (bestPlan.plan.wsFlags & WHERE_ORDERBY)!=0 ){
-      *ppOrderBy = 0;
-    }
-    andFlags &= bestPlan.plan.wsFlags;
-    pLevel->plan = bestPlan.plan;
-    if( bestPlan.plan.wsFlags & WHERE_INDEXED ){
-      pLevel->iIdxCur = pParse->nTab++;
-    }else{
-      pLevel->iIdxCur = -1;
-    }
-    notReady &= ~getMask(pMaskSet, pTabList->a[bestJ].iCursor);
-    pLevel->iFrom = (u8)bestJ;
-
-    /* Check that if the table scanned by this loop iteration had an
-    ** INDEXED BY clause attached to it, that the named index is being
-    ** used for the scan. If not, then query compilation has failed.
-    ** Return an error.
-    */
-    pIdx = pTabList->a[bestJ].pIndex;
-    if( pIdx ){
-      if( (bestPlan.plan.wsFlags & WHERE_INDEXED)==0 ){
-        sqlite3ErrorMsg(pParse, "cannot use index: %s", pIdx->zName);
-        goto whereBeginError;
-      }else{
-        /* If an INDEXED BY clause is used, the bestIndex() function is
-        ** guaranteed to find the index specified in the INDEXED BY clause
-        ** if it find an index at all. */
-        assert( bestPlan.plan.u.pIdx==pIdx );
-      }
+  
+    wherePathSolver(pWInfo, 0);
+    if( db->mallocFailed ) goto whereBeginError;
+    if( pWInfo->pOrderBy ){
+       wherePathSolver(pWInfo, pWInfo->nRowOut+1);
+       if( db->mallocFailed ) goto whereBeginError;
     }
   }
-  WHERETRACE(("*** Optimizer Finished ***\n"));
-  if( pParse->nErr || db->mallocFailed ){
+  if( pWInfo->pOrderBy==0 && (db->flags & SQLITE_ReverseOrder)!=0 ){
+     pWInfo->revMask = ALLBITS;
+  }
+  if( pParse->nErr || NEVER(db->mallocFailed) ){
     goto whereBeginError;
   }
-
-  /* If the total query only selects a single row, then the ORDER BY
-  ** clause is irrelevant.
-  */
-  if( (andFlags & WHERE_UNIQUE)!=0 && ppOrderBy ){
-    *ppOrderBy = 0;
+#ifdef WHERETRACE_ENABLED
+  if( sqlite3WhereTrace ){
+    sqlite3DebugPrintf("---- Solution nRow=%d", pWInfo->nRowOut);
+    if( pWInfo->nOBSat>0 ){
+      sqlite3DebugPrintf(" ORDERBY=%d,0x%llx", pWInfo->nOBSat, pWInfo->revMask);
+    }
+    switch( pWInfo->eDistinct ){
+      case WHERE_DISTINCT_UNIQUE: {
+        sqlite3DebugPrintf("  DISTINCT=unique");
+        break;
+      }
+      case WHERE_DISTINCT_ORDERED: {
+        sqlite3DebugPrintf("  DISTINCT=ordered");
+        break;
+      }
+      case WHERE_DISTINCT_UNORDERED: {
+        sqlite3DebugPrintf("  DISTINCT=unordered");
+        break;
+      }
+    }
+    sqlite3DebugPrintf("\n");
+    for(ii=0; ii<pWInfo->nLevel; ii++){
+      whereLoopPrint(pWInfo->a[ii].pWLoop, sWLB.pWC);
+    }
+  }
+#endif
+  /* Attempt to omit tables from the join that do not effect the result */
+  if( pWInfo->nLevel>=2
+   && pResultSet!=0
+   && OptimizationEnabled(db, SQLITE_OmitNoopJoin)
+  ){
+    Bitmask tabUsed = sqlite3WhereExprListUsage(pMaskSet, pResultSet);
+    if( sWLB.pOrderBy ){
+      tabUsed |= sqlite3WhereExprListUsage(pMaskSet, sWLB.pOrderBy);
+    }
+    while( pWInfo->nLevel>=2 ){
+      WhereTerm *pTerm, *pEnd;
+      pLoop = pWInfo->a[pWInfo->nLevel-1].pWLoop;
+      if( (pWInfo->pTabList->a[pLoop->iTab].fg.jointype & JT_LEFT)==0 ) break;
+      if( (wctrlFlags & WHERE_WANT_DISTINCT)==0
+       && (pLoop->wsFlags & WHERE_ONEROW)==0
+      ){
+        break;
+      }
+      if( (tabUsed & pLoop->maskSelf)!=0 ) break;
+      pEnd = sWLB.pWC->a + sWLB.pWC->nTerm;
+      for(pTerm=sWLB.pWC->a; pTerm<pEnd; pTerm++){
+        if( (pTerm->prereqAll & pLoop->maskSelf)!=0
+         && !ExprHasProperty(pTerm->pExpr, EP_FromJoin)
+        ){
+          break;
+        }
+      }
+      if( pTerm<pEnd ) break;
+      WHERETRACE(0xffff, ("-> drop loop %c not used\n", pLoop->cId));
+      pWInfo->nLevel--;
+      nTabList--;
+    }
   }
+  WHERETRACE(0xffff,("*** Optimizer Finished ***\n"));
+  pWInfo->pParse->nQueryLoop += pWInfo->nRowOut;
 
   /* If the caller is an UPDATE or DELETE statement that is requesting
   ** to use a one-pass algorithm, determine if this is appropriate.
-  ** The one-pass algorithm only works if the WHERE clause constraints
-  ** the statement to update a single row.
   */
   assert( (wctrlFlags & WHERE_ONEPASS_DESIRED)==0 || pWInfo->nLevel==1 );
-  if( (wctrlFlags & WHERE_ONEPASS_DESIRED)!=0 && (andFlags & WHERE_UNIQUE)!=0 ){
-    pWInfo->okOnePass = 1;
-    pWInfo->a[0].plan.wsFlags &= ~WHERE_IDX_ONLY;
+  if( (wctrlFlags & WHERE_ONEPASS_DESIRED)!=0 ){
+    int wsFlags = pWInfo->a[0].pWLoop->wsFlags;
+    int bOnerow = (wsFlags & WHERE_ONEROW)!=0;
+    if( bOnerow
+     || ((wctrlFlags & WHERE_ONEPASS_MULTIROW)!=0
+           && 0==(wsFlags & WHERE_VIRTUALTABLE))
+    ){
+      pWInfo->eOnePass = bOnerow ? ONEPASS_SINGLE : ONEPASS_MULTI;
+      if( HasRowid(pTabList->a[0].pTab) && (wsFlags & WHERE_IDX_ONLY) ){
+        if( wctrlFlags & WHERE_ONEPASS_MULTIROW ){
+          bFordelete = OPFLAG_FORDELETE;
+        }
+        pWInfo->a[0].pWLoop->wsFlags = (wsFlags & ~WHERE_IDX_ONLY);
+      }
+    }
   }
 
   /* Open all tables in the pTabList and any indices selected for
   ** searching those tables.
   */
-  sqlite3CodeVerifySchema(pParse, -1); /* Insert the cookie verifier Goto */
-  for(i=0, pLevel=pWInfo->a; i<pTabList->nSrc; i++, pLevel++){
+  for(ii=0, pLevel=pWInfo->a; ii<nTabList; ii++, pLevel++){
     Table *pTab;     /* Table to open */
     int iDb;         /* Index of database containing table/index */
+    struct SrcList_item *pTabItem;
 
-#ifndef SQLITE_OMIT_EXPLAIN
-    if( pParse->explain==2 ){
-      char *zMsg;
-      struct SrcList_item *pItem = &pTabList->a[pLevel->iFrom];
-      zMsg = sqlite3MPrintf(db, "TABLE %s", pItem->zName);
-      if( pItem->zAlias ){
-        zMsg = sqlite3MAppendf(db, zMsg, "%s AS %s", zMsg, pItem->zAlias);
-      }
-      if( (pLevel->plan.wsFlags & WHERE_INDEXED)!=0 ){
-        zMsg = sqlite3MAppendf(db, zMsg, "%s WITH INDEX %s",
-           zMsg, pLevel->plan.u.pIdx->zName);
-      }else if( pLevel->plan.wsFlags & WHERE_MULTI_OR ){
-        zMsg = sqlite3MAppendf(db, zMsg, "%s VIA MULTI-INDEX UNION", zMsg);
-      }else if( pLevel->plan.wsFlags & (WHERE_ROWID_EQ|WHERE_ROWID_RANGE) ){
-        zMsg = sqlite3MAppendf(db, zMsg, "%s USING PRIMARY KEY", zMsg);
-      }
-#ifndef SQLITE_OMIT_VIRTUALTABLE
-      else if( (pLevel->plan.wsFlags & WHERE_VIRTUALTABLE)!=0 ){
-        sqlite3_index_info *pVtabIdx = pLevel->plan.u.pVtabIdx;
-        zMsg = sqlite3MAppendf(db, zMsg, "%s VIRTUAL TABLE INDEX %d:%s", zMsg,
-                    pVtabIdx->idxNum, pVtabIdx->idxStr);
-      }
-#endif
-      if( pLevel->plan.wsFlags & WHERE_ORDERBY ){
-        zMsg = sqlite3MAppendf(db, zMsg, "%s ORDER BY", zMsg);
-      }
-      sqlite3VdbeAddOp4(v, OP_Explain, i, pLevel->iFrom, 0, zMsg, P4_DYNAMIC);
-    }
-#endif /* SQLITE_OMIT_EXPLAIN */
     pTabItem = &pTabList->a[pLevel->iFrom];
     pTab = pTabItem->pTab;
-    iDb = sqlite3SchemaToIndex(pParse->db, pTab->pSchema);
-    if( (pTab->tabFlags & TF_Ephemeral)!=0 || pTab->pSelect ) continue;
+    iDb = sqlite3SchemaToIndex(db, pTab->pSchema);
+    pLoop = pLevel->pWLoop;
+    if( (pTab->tabFlags & TF_Ephemeral)!=0 || pTab->pSelect ){
+      /* Do nothing */
+    }else
 #ifndef SQLITE_OMIT_VIRTUALTABLE
-    if( (pLevel->plan.wsFlags & WHERE_VIRTUALTABLE)!=0 ){
+    if( (pLoop->wsFlags & WHERE_VIRTUALTABLE)!=0 ){
+      const char *pVTab = (const char *)sqlite3GetVTable(db, pTab);
       int iCur = pTabItem->iCursor;
-      sqlite3VdbeAddOp4(v, OP_VOpen, iCur, 0, 0,
-                        (const char*)pTab->pVtab, P4_VTAB);
+      sqlite3VdbeAddOp4(v, OP_VOpen, iCur, 0, 0, pVTab, P4_VTAB);
+    }else if( IsVirtual(pTab) ){
+      /* noop */
     }else
 #endif
-    if( (pLevel->plan.wsFlags & WHERE_IDX_ONLY)==0
-         && (wctrlFlags & WHERE_OMIT_OPEN)==0 ){
-      int op = pWInfo->okOnePass ? OP_OpenWrite : OP_OpenRead;
+    if( (pLoop->wsFlags & WHERE_IDX_ONLY)==0
+         && (wctrlFlags & WHERE_OR_SUBCLAUSE)==0 ){
+      int op = OP_OpenRead;
+      if( pWInfo->eOnePass!=ONEPASS_OFF ){
+        op = OP_OpenWrite;
+        pWInfo->aiCurOnePass[0] = pTabItem->iCursor;
+      };
       sqlite3OpenTable(pParse, pTabItem->iCursor, iDb, pTab, op);
-      if( !pWInfo->okOnePass && pTab->nCol<BMS ){
+      assert( pTabItem->iCursor==pLevel->iTabCur );
+      testcase( pWInfo->eOnePass==ONEPASS_OFF && pTab->nCol==BMS-1 );
+      testcase( pWInfo->eOnePass==ONEPASS_OFF && pTab->nCol==BMS );
+      if( pWInfo->eOnePass==ONEPASS_OFF && pTab->nCol<BMS && HasRowid(pTab) ){
         Bitmask b = pTabItem->colUsed;
         int n = 0;
         for(; b; b=b>>1, n++){}
-        sqlite3VdbeChangeP4(v, sqlite3VdbeCurrentAddr(v)-1, SQLITE_INT_TO_PTR(n), P4_INT32);
+        sqlite3VdbeChangeP4(v, -1, SQLITE_INT_TO_PTR(n), P4_INT32);
         assert( n<=pTab->nCol );
       }
+#ifdef SQLITE_ENABLE_CURSOR_HINTS
+      if( pLoop->u.btree.pIndex!=0 ){
+        sqlite3VdbeChangeP5(v, OPFLAG_SEEKEQ|bFordelete);
+      }else
+#endif
+      {
+        sqlite3VdbeChangeP5(v, bFordelete);
+      }
+#ifdef SQLITE_ENABLE_COLUMN_USED_MASK
+      sqlite3VdbeAddOp4Dup8(v, OP_ColumnsUsed, pTabItem->iCursor, 0, 0,
+                            (const u8*)&pTabItem->colUsed, P4_INT64);
+#endif
     }else{
       sqlite3TableLock(pParse, iDb, pTab->tnum, 0, pTab->zName);
     }
-    pLevel->iTabCur = pTabItem->iCursor;
-    if( (pLevel->plan.wsFlags & WHERE_INDEXED)!=0 ){
-      Index *pIx = pLevel->plan.u.pIdx;
-      KeyInfo *pKey = sqlite3IndexKeyinfo(pParse, pIx);
-      int iIdxCur = pLevel->iIdxCur;
+    if( pLoop->wsFlags & WHERE_INDEXED ){
+      Index *pIx = pLoop->u.btree.pIndex;
+      int iIndexCur;
+      int op = OP_OpenRead;
+      /* iAuxArg is always set to a positive value if ONEPASS is possible */
+      assert( iAuxArg!=0 || (pWInfo->wctrlFlags & WHERE_ONEPASS_DESIRED)==0 );
+      if( !HasRowid(pTab) && IsPrimaryKeyIndex(pIx)
+       && (wctrlFlags & WHERE_OR_SUBCLAUSE)!=0
+      ){
+        /* This is one term of an OR-optimization using the PRIMARY KEY of a
+        ** WITHOUT ROWID table.  No need for a separate index */
+        iIndexCur = pLevel->iTabCur;
+        op = 0;
+      }else if( pWInfo->eOnePass!=ONEPASS_OFF ){
+        Index *pJ = pTabItem->pTab->pIndex;
+        iIndexCur = iAuxArg;
+        assert( wctrlFlags & WHERE_ONEPASS_DESIRED );
+        while( ALWAYS(pJ) && pJ!=pIx ){
+          iIndexCur++;
+          pJ = pJ->pNext;
+        }
+        op = OP_OpenWrite;
+        pWInfo->aiCurOnePass[1] = iIndexCur;
+      }else if( iAuxArg && (wctrlFlags & WHERE_OR_SUBCLAUSE)!=0 ){
+        iIndexCur = iAuxArg;
+        op = OP_ReopenIdx;
+      }else{
+        iIndexCur = pParse->nTab++;
+      }
+      pLevel->iIdxCur = iIndexCur;
       assert( pIx->pSchema==pTab->pSchema );
-      assert( iIdxCur>=0 );
-      sqlite3VdbeAddOp4(v, OP_OpenRead, iIdxCur, pIx->tnum, iDb,
-                        (char*)pKey, P4_KEYINFO_HANDOFF);
-      VdbeComment((v, "%s", pIx->zName));
+      assert( iIndexCur>=0 );
+      if( op ){
+        sqlite3VdbeAddOp3(v, op, iIndexCur, pIx->tnum, iDb);
+        sqlite3VdbeSetP4KeyInfo(pParse, pIx);
+        if( (pLoop->wsFlags & WHERE_CONSTRAINT)!=0
+         && (pLoop->wsFlags & (WHERE_COLUMN_RANGE|WHERE_SKIPSCAN))==0
+         && (pWInfo->wctrlFlags&WHERE_ORDERBY_MIN)==0
+         && pWInfo->eDistinct!=WHERE_DISTINCT_ORDERED
+        ){
+          sqlite3VdbeChangeP5(v, OPFLAG_SEEKEQ); /* Hint to COMDB2 */
+        }
+        VdbeComment((v, "%s", pIx->zName));
+#ifdef SQLITE_ENABLE_COLUMN_USED_MASK
+        {
+          u64 colUsed = 0;
+          int ii, jj;
+          for(ii=0; ii<pIx->nColumn; ii++){
+            jj = pIx->aiColumn[ii];
+            if( jj<0 ) continue;
+            if( jj>63 ) jj = 63;
+            if( (pTabItem->colUsed & MASKBIT(jj))==0 ) continue;
+            colUsed |= ((u64)1)<<(ii<63 ? ii : 63);
+          }
+          sqlite3VdbeAddOp4Dup8(v, OP_ColumnsUsed, iIndexCur, 0, 0,
+                                (u8*)&colUsed, P4_INT64);
+        }
+#endif /* SQLITE_ENABLE_COLUMN_USED_MASK */
+      }
     }
-    sqlite3CodeVerifySchema(pParse, iDb);
+    if( iDb>=0 ) sqlite3CodeVerifySchema(pParse, iDb);
   }
   pWInfo->iTop = sqlite3VdbeCurrentAddr(v);
+  if( db->mallocFailed ) goto whereBeginError;
 
   /* Generate the code to do the search.  Each iteration of the for
   ** loop below generates code for a single nested loop of the VM
   ** program.
   */
   notReady = ~(Bitmask)0;
-  for(i=0; i<pTabList->nSrc; i++){
-    notReady = codeOneLoopStart(pWInfo, i, wctrlFlags, notReady);
-    pWInfo->iContinue = pWInfo->a[i].addrCont;
-  }
-
-#ifdef SQLITE_TEST  /* For testing and debugging use only */
-  /* Record in the query plan information about the current table
-  ** and the index used to access it (if any).  If the table itself
-  ** is not used, its name is just '{}'.  If no index is used
-  ** the index is listed as "{}".  If the primary key is used the
-  ** index name is '*'.
-  */
-  for(i=0; i<pTabList->nSrc; i++){
-    char *z;
-    int n;
-    pLevel = &pWInfo->a[i];
-    pTabItem = &pTabList->a[pLevel->iFrom];
-    z = pTabItem->zAlias;
-    if( z==0 ) z = pTabItem->pTab->zName;
-    n = sqlite3Strlen30(z);
-    if( n+nQPlan < sizeof(sqlite3_query_plan)-10 ){
-      if( pLevel->plan.wsFlags & WHERE_IDX_ONLY ){
-        memcpy(&sqlite3_query_plan[nQPlan], "{}", 2);
-        nQPlan += 2;
-      }else{
-        memcpy(&sqlite3_query_plan[nQPlan], z, n);
-        nQPlan += n;
-      }
-      sqlite3_query_plan[nQPlan++] = ' ';
+  for(ii=0; ii<nTabList; ii++){
+    int addrExplain;
+    int wsFlags;
+    pLevel = &pWInfo->a[ii];
+    wsFlags = pLevel->pWLoop->wsFlags;
+#ifndef SQLITE_OMIT_AUTOMATIC_INDEX
+    if( (pLevel->pWLoop->wsFlags & WHERE_AUTO_INDEX)!=0 ){
+      constructAutomaticIndex(pParse, &pWInfo->sWC,
+                &pTabList->a[pLevel->iFrom], notReady, pLevel);
+      if( db->mallocFailed ) goto whereBeginError;
     }
-    testcase( pLevel->plan.wsFlags & WHERE_ROWID_EQ );
-    testcase( pLevel->plan.wsFlags & WHERE_ROWID_RANGE );
-    if( pLevel->plan.wsFlags & (WHERE_ROWID_EQ|WHERE_ROWID_RANGE) ){
-      memcpy(&sqlite3_query_plan[nQPlan], "* ", 2);
-      nQPlan += 2;
-    }else if( (pLevel->plan.wsFlags & WHERE_INDEXED)!=0 ){
-      n = sqlite3Strlen30(pLevel->plan.u.pIdx->zName);
-      if( n+nQPlan < sizeof(sqlite3_query_plan)-2 ){
-        memcpy(&sqlite3_query_plan[nQPlan], pLevel->plan.u.pIdx->zName, n);
-        nQPlan += n;
-        sqlite3_query_plan[nQPlan++] = ' ';
-      }
-    }else{
-      memcpy(&sqlite3_query_plan[nQPlan], "{} ", 3);
-      nQPlan += 3;
+#endif
+    addrExplain = sqlite3WhereExplainOneScan(
+        pParse, pTabList, pLevel, ii, pLevel->iFrom, wctrlFlags
+    );
+    pLevel->addrBody = sqlite3VdbeCurrentAddr(v);
+    notReady = sqlite3WhereCodeOneLoopStart(pWInfo, ii, notReady);
+    pWInfo->iContinue = pLevel->addrCont;
+    if( (wsFlags&WHERE_MULTI_OR)==0 && (wctrlFlags&WHERE_OR_SUBCLAUSE)==0 ){
+      sqlite3WhereAddScanStatus(v, pTabList, pLevel, addrExplain);
     }
   }
-  while( nQPlan>0 && sqlite3_query_plan[nQPlan-1]==' ' ){
-    sqlite3_query_plan[--nQPlan] = 0;
-  }
-  sqlite3_query_plan[nQPlan] = 0;
-  nQPlan = 0;
-#endif /* SQLITE_TEST // Testing and debugging use only */
 
-  /* Record the continuation address in the WhereInfo structure.  Then
-  ** clean up and return.
-  */
+  /* Done. */
+  VdbeModuleComment((v, "Begin WHERE-core"));
   return pWInfo;
 
   /* Jump here if malloc fails */
 whereBeginError:
-  whereInfoFree(db, pWInfo);
+  if( pWInfo ){
+    pParse->nQueryLoop = pWInfo->savedNQueryLoop;
+    whereInfoFree(db, pWInfo);
+  }
   return 0;
 }
 
 /*
 ** Generate the end of the WHERE loop.  See comments on 
 ** sqlite3WhereBegin() for additional information.
 */
 void sqlite3WhereEnd(WhereInfo *pWInfo){
   Parse *pParse = pWInfo->pParse;
   Vdbe *v = pParse->pVdbe;
   int i;
   WhereLevel *pLevel;
+  WhereLoop *pLoop;
   SrcList *pTabList = pWInfo->pTabList;
   sqlite3 *db = pParse->db;
 
   /* Generate loop termination code.
   */
+  VdbeModuleComment((v, "End WHERE-core"));
   sqlite3ExprCacheClear(pParse);
-  for(i=pTabList->nSrc-1; i>=0; i--){
+  for(i=pWInfo->nLevel-1; i>=0; i--){
+    int addr;
     pLevel = &pWInfo->a[i];
-    sqlite3VdbeResolveLabel(v, pLevel->addrCont);
+    pLoop = pLevel->pWLoop;
     if( pLevel->op!=OP_Noop ){
-      sqlite3VdbeAddOp2(v, pLevel->op, pLevel->p1, pLevel->p2);
+#ifndef SQLITE_DISABLE_SKIPAHEAD_DISTINCT
+      int addrSeek = 0;
+      Index *pIdx;
+      int n;
+      if( pWInfo->eDistinct==WHERE_DISTINCT_ORDERED
+       && (pLoop->wsFlags & WHERE_INDEXED)!=0
+       && (pIdx = pLoop->u.btree.pIndex)->hasStat1
+       && (n = pLoop->u.btree.nIdxCol)>0
+       && pIdx->aiRowLogEst[n]>=36
+      ){
+        int r1 = pParse->nMem+1;
+        int j, op;
+        for(j=0; j<n; j++){
+          sqlite3VdbeAddOp3(v, OP_Column, pLevel->iIdxCur, j, r1+j);
+        }
+        pParse->nMem += n+1;
+        op = pLevel->op==OP_Prev ? OP_SeekLT : OP_SeekGT;
+        addrSeek = sqlite3VdbeAddOp4Int(v, op, pLevel->iIdxCur, 0, r1, n);
+        VdbeCoverageIf(v, op==OP_SeekLT);
+        VdbeCoverageIf(v, op==OP_SeekGT);
+        sqlite3VdbeAddOp2(v, OP_Goto, 1, pLevel->p2);
+      }
+#endif /* SQLITE_DISABLE_SKIPAHEAD_DISTINCT */
+      /* The common case: Advance to the next row */
+      sqlite3VdbeResolveLabel(v, pLevel->addrCont);
+      sqlite3VdbeAddOp3(v, pLevel->op, pLevel->p1, pLevel->p2, pLevel->p3);
       sqlite3VdbeChangeP5(v, pLevel->p5);
+      VdbeCoverage(v);
+      VdbeCoverageIf(v, pLevel->op==OP_Next);
+      VdbeCoverageIf(v, pLevel->op==OP_Prev);
+      VdbeCoverageIf(v, pLevel->op==OP_VNext);
+#ifndef SQLITE_DISABLE_SKIPAHEAD_DISTINCT
+      if( addrSeek ) sqlite3VdbeJumpHere(v, addrSeek);
+#endif
+    }else{
+      sqlite3VdbeResolveLabel(v, pLevel->addrCont);
     }
-    if( pLevel->plan.wsFlags & WHERE_IN_ABLE && pLevel->u.in.nIn>0 ){
+    if( pLoop->wsFlags & WHERE_IN_ABLE && pLevel->u.in.nIn>0 ){
       struct InLoop *pIn;
       int j;
       sqlite3VdbeResolveLabel(v, pLevel->addrNxt);
       for(j=pLevel->u.in.nIn, pIn=&pLevel->u.in.aInLoop[j-1]; j>0; j--, pIn--){
         sqlite3VdbeJumpHere(v, pIn->addrInTop+1);
-        sqlite3VdbeAddOp2(v, OP_Next, pIn->iCur, pIn->addrInTop);
+        if( pIn->eEndLoopOp!=OP_Noop ){
+          sqlite3VdbeAddOp2(v, pIn->eEndLoopOp, pIn->iCur, pIn->addrInTop);
+          VdbeCoverage(v);
+          VdbeCoverageIf(v, pIn->eEndLoopOp==OP_PrevIfOpen);
+          VdbeCoverageIf(v, pIn->eEndLoopOp==OP_NextIfOpen);
+        }
         sqlite3VdbeJumpHere(v, pIn->addrInTop-1);
       }
-      sqlite3DbFree(db, pLevel->u.in.aInLoop);
     }
     sqlite3VdbeResolveLabel(v, pLevel->addrBrk);
+    if( pLevel->addrSkip ){
+      sqlite3VdbeGoto(v, pLevel->addrSkip);
+      VdbeComment((v, "next skip-scan on %s", pLoop->u.btree.pIndex->zName));
+      sqlite3VdbeJumpHere(v, pLevel->addrSkip);
+      sqlite3VdbeJumpHere(v, pLevel->addrSkip-2);
+    }
+#ifndef SQLITE_LIKE_DOESNT_MATCH_BLOBS
+    if( pLevel->addrLikeRep ){
+      sqlite3VdbeAddOp2(v, OP_DecrJumpZero, (int)(pLevel->iLikeRepCntr>>1),
+                        pLevel->addrLikeRep);
+      VdbeCoverage(v);
+    }
+#endif
     if( pLevel->iLeftJoin ){
-      int addr;
-      addr = sqlite3VdbeAddOp1(v, OP_IfPos, pLevel->iLeftJoin);
-      sqlite3VdbeAddOp1(v, OP_NullRow, pTabList->a[i].iCursor);
-      if( pLevel->iIdxCur>=0 ){
+      int ws = pLoop->wsFlags;
+      addr = sqlite3VdbeAddOp1(v, OP_IfPos, pLevel->iLeftJoin); VdbeCoverage(v);
+      assert( (ws & WHERE_IDX_ONLY)==0 || (ws & WHERE_INDEXED)!=0 );
+      if( (ws & WHERE_IDX_ONLY)==0 ){
+        sqlite3VdbeAddOp1(v, OP_NullRow, pTabList->a[i].iCursor);
+      }
+      if( (ws & WHERE_INDEXED) 
+       || ((ws & WHERE_MULTI_OR) && pLevel->u.pCovidx) 
+      ){
         sqlite3VdbeAddOp1(v, OP_NullRow, pLevel->iIdxCur);
       }
       if( pLevel->op==OP_Return ){
         sqlite3VdbeAddOp2(v, OP_Gosub, pLevel->p1, pLevel->addrFirst);
       }else{
-        sqlite3VdbeAddOp2(v, OP_Goto, 0, pLevel->addrFirst);
+        sqlite3VdbeGoto(v, pLevel->addrFirst);
       }
       sqlite3VdbeJumpHere(v, addr);
     }
+    VdbeModuleComment((v, "End WHERE-loop%d: %s", i,
+                     pWInfo->pTabList->a[pLevel->iFrom].pTab->zName));
   }
 
   /* The "break" point is here, just past the end of the outer loop.
   ** Set it.
   */
   sqlite3VdbeResolveLabel(v, pWInfo->iBreak);
 
-  /* Close all of the cursors that were opened by sqlite3WhereBegin.
-  */
-  for(i=0, pLevel=pWInfo->a; i<pTabList->nSrc; i++, pLevel++){
+  assert( pWInfo->nLevel<=pTabList->nSrc );
+  for(i=0, pLevel=pWInfo->a; i<pWInfo->nLevel; i++, pLevel++){
+    int k, last;
+    VdbeOp *pOp;
+    Index *pIdx = 0;
     struct SrcList_item *pTabItem = &pTabList->a[pLevel->iFrom];
     Table *pTab = pTabItem->pTab;
     assert( pTab!=0 );
-    if( (pTab->tabFlags & TF_Ephemeral)!=0 || pTab->pSelect ) continue;
-    if( (pWInfo->wctrlFlags & WHERE_OMIT_CLOSE)==0 ){
-      if( !pWInfo->okOnePass && (pLevel->plan.wsFlags & WHERE_IDX_ONLY)==0 ){
-        sqlite3VdbeAddOp1(v, OP_Close, pTabItem->iCursor);
-      }
-      if( (pLevel->plan.wsFlags & WHERE_INDEXED)!=0 ){
-        sqlite3VdbeAddOp1(v, OP_Close, pLevel->iIdxCur);
-      }
+    pLoop = pLevel->pWLoop;
+
+    /* For a co-routine, change all OP_Column references to the table of
+    ** the co-routine into OP_Copy of result contained in a register.
+    ** OP_Rowid becomes OP_Null.
+    */
+    if( pTabItem->fg.viaCoroutine ){
+      testcase( pParse->db->mallocFailed );
+      translateColumnToCopy(pParse, pLevel->addrBody, pLevel->iTabCur,
+                            pTabItem->regResult, 0);
+      continue;
     }
 
-    /* If this scan uses an index, make code substitutions to read data
-    ** from the index in preference to the table. Sometimes, this means
-    ** the table need never be read from. This is a performance boost,
-    ** as the vdbe level waits until the table is read before actually
-    ** seeking the table cursor to the record corresponding to the current
-    ** position in the index.
+    /* If this scan uses an index, make VDBE code substitutions to read data
+    ** from the index instead of from the table where possible.  In some cases
+    ** this optimization prevents the table from ever being read, which can
+    ** yield a significant performance boost.
     ** 
     ** Calls to the code generator in between sqlite3WhereBegin and
     ** sqlite3WhereEnd will have created code that references the table
     ** directly.  This loop scans all that code looking for opcodes
     ** that reference the table and converts them into opcodes that
     ** reference the index.
     */
-    if( (pLevel->plan.wsFlags & WHERE_INDEXED)!=0 && !db->mallocFailed){
-      int k, j, last;
-      VdbeOp *pOp;
-      Index *pIdx = pLevel->plan.u.pIdx;
-      int useIndexOnly = pLevel->plan.wsFlags & WHERE_IDX_ONLY;
-
-      assert( pIdx!=0 );
-      pOp = sqlite3VdbeGetOp(v, pWInfo->iTop);
+    if( pLoop->wsFlags & (WHERE_INDEXED|WHERE_IDX_ONLY) ){
+      pIdx = pLoop->u.btree.pIndex;
+    }else if( pLoop->wsFlags & WHERE_MULTI_OR ){
+      pIdx = pLevel->u.pCovidx;
+    }
+    if( pIdx
+     && (pWInfo->eOnePass==ONEPASS_OFF || !HasRowid(pIdx->pTable))
+     && !db->mallocFailed
+    ){
       last = sqlite3VdbeCurrentAddr(v);
-      for(k=pWInfo->iTop; k<last; k++, pOp++){
+      k = pLevel->addrBody;
+      pOp = sqlite3VdbeGetOp(v, k);
+      for(; k<last; k++, pOp++){
         if( pOp->p1!=pLevel->iTabCur ) continue;
         if( pOp->opcode==OP_Column ){
-          for(j=0; j<pIdx->nColumn; j++){
-            if( pOp->p2==pIdx->aiColumn[j] ){
-              pOp->p2 = j;
-              pOp->p1 = pLevel->iIdxCur;
-              break;
-            }
+          int x = pOp->p2;
+          assert( pIdx->pTable==pTab );
+          if( !HasRowid(pTab) ){
+            Index *pPk = sqlite3PrimaryKeyIndex(pTab);
+            x = pPk->aiColumn[x];
+            assert( x>=0 );
           }
-          assert(!useIndexOnly || j<pIdx->nColumn);
+          x = sqlite3ColumnOfIndex(pIdx, x);
+          if( x>=0 ){
+            pOp->p2 = x;
+            pOp->p1 = pLevel->iIdxCur;
+          }
+          assert( (pLoop->wsFlags & WHERE_IDX_ONLY)==0 || x>=0 
+              || pWInfo->eOnePass );
         }else if( pOp->opcode==OP_Rowid ){
           pOp->p1 = pLevel->iIdxCur;
           pOp->opcode = OP_IdxRowid;
-        }else if( pOp->opcode==OP_NullRow && useIndexOnly ){
-          pOp->opcode = OP_Noop;
+        }else if( pOp->opcode==OP_IfNullRow ){
+          pOp->p1 = pLevel->iIdxCur;
         }
       }
     }
   }
 
   /* Final cleanup
   */
+  pParse->nQueryLoop = pWInfo->savedNQueryLoop;
   whereInfoFree(db, pWInfo);
   return;
 }
