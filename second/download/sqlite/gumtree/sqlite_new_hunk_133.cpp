**        goto start
**      fi
**    end
**
** ORDER BY CLAUSE PROCESSING
**
** *ppOrderBy is a pointer to the ORDER BY clause of a SELECT statement,
** if there is one.  If there is no ORDER BY clause or if this routine
** is called from an UPDATE or DELETE statement, then ppOrderBy is NULL.
**
** If an index can be used so that the natural output order of the table
** scan is correct for the ORDER BY clause, then that index is used and
** *ppOrderBy is set to NULL.  This is an optimization that prevents an
** unnecessary sort of the result set if an index appropriate for the
** ORDER BY clause already exists.
**
** If the where clause loops cannot be arranged to provide the correct
** output order, then the *ppOrderBy is unchanged.
*/
WhereInfo *sqlite3WhereBegin(
  Parse *pParse,        /* The parser context */
  SrcList *pTabList,    /* A list of all tables to be scanned */
  Expr *pWhere,         /* The WHERE clause */
  ExprList **ppOrderBy, /* An ORDER BY clause, or NULL */
  u16 wctrlFlags        /* One of the WHERE_* flags defined in sqliteInt.h */
){
  int i;                     /* Loop counter */
  int nByteWInfo;            /* Num. bytes allocated for WhereInfo struct */
  WhereInfo *pWInfo;         /* Will become the return value of this function */
  Vdbe *v = pParse->pVdbe;   /* The virtual database engine */
  Bitmask notReady;          /* Cursors that are not yet positioned */
  WhereMaskSet *pMaskSet;    /* The expression mask set */
  WhereClause *pWC;               /* Decomposition of the WHERE clause */
  struct SrcList_item *pTabItem;  /* A single entry from pTabList */
  WhereLevel *pLevel;             /* A single level in the pWInfo list */
  int iFrom;                      /* First unused FROM clause element */
  int andFlags;              /* AND-ed combination of all pWC->a[].wtFlags */
  sqlite3 *db;               /* Database connection */

  /* The number of tables in the FROM clause is limited by the number of
  ** bits in a Bitmask 
  */
  if( pTabList->nSrc>BMS ){
    sqlite3ErrorMsg(pParse, "at most %d tables in a join", BMS);
    return 0;
  }

  /* Allocate and initialize the WhereInfo structure that will become the
  ** return value. A single allocation is used to store the WhereInfo
  ** struct, the contents of WhereInfo.a[], the WhereClause structure
  ** and the WhereMaskSet structure. Since WhereClause contains an 8-byte
  ** field (type Bitmask) it must be aligned on an 8-byte boundary on
  ** some architectures. Hence the ROUND8() below.
  */
  db = pParse->db;
  nByteWInfo = ROUND8(sizeof(WhereInfo)+(pTabList->nSrc-1)*sizeof(WhereLevel));
  pWInfo = sqlite3DbMallocZero(db, 
      nByteWInfo + 
      sizeof(WhereClause) +
      sizeof(WhereMaskSet)
  );
  if( db->mallocFailed ){
    goto whereBeginError;
  }
  pWInfo->nLevel = pTabList->nSrc;
  pWInfo->pParse = pParse;
  pWInfo->pTabList = pTabList;
  pWInfo->iBreak = sqlite3VdbeMakeLabel(v);
  pWInfo->pWC = pWC = (WhereClause *)&((u8 *)pWInfo)[nByteWInfo];
  pWInfo->wctrlFlags = wctrlFlags;
  pMaskSet = (WhereMaskSet*)&pWC[1];

  /* Split the WHERE clause into separate subexpressions where each
  ** subexpression is separated by an AND operator.
  */
  initMaskSet(pMaskSet);
  whereClauseInit(pWC, pParse, pMaskSet);
  sqlite3ExprCodeConstants(pParse, pWhere);
  whereSplit(pWC, pWhere, TK_AND);
    
  /* Special case: a WHERE clause that is constant.  Evaluate the
  ** expression and either jump over all of the code or fall thru.
  */
  if( pWhere && (pTabList->nSrc==0 || sqlite3ExprIsConstantNotJoin(pWhere)) ){
    sqlite3ExprIfFalse(pParse, pWhere, pWInfo->iBreak, SQLITE_JUMPIFNULL);
    pWhere = 0;
  }

  /* Assign a bit from the bitmask to every term in the FROM clause.
  **
  ** When assigning bitmask values to FROM clause cursors, it must be
  ** the case that if X is the bitmask for the N-th FROM clause term then
  ** the bitmask for all FROM clause terms to the left of the N-th term
  ** is (X-1).   An expression from the ON clause of a LEFT JOIN can use
  ** its Expr.iRightJoinTable value to find the bitmask of the right table
  ** of the join.  Subtracting one from the right table bitmask gives a
  ** bitmask for all tables to the left of the join.  Knowing the bitmask
  ** for all tables to the left of a left join is important.  Ticket #3015.
  **
  ** Configure the WhereClause.vmask variable so that bits that correspond
  ** to virtual table cursors are set. This is used to selectively disable 
  ** the OR-to-IN transformation in exprAnalyzeOrTerm(). It is not helpful 
  ** with virtual tables.
  */
  assert( pWC->vmask==0 && pMaskSet->n==0 );
  for(i=0; i<pTabList->nSrc; i++){
    createMask(pMaskSet, pTabList->a[i].iCursor);
    if( ALWAYS(pTabList->a[i].pTab) && IsVirtual(pTabList->a[i].pTab) ){
      pWC->vmask |= ((Bitmask)1 << i);
    }
  }
#ifndef NDEBUG
  {
    Bitmask toTheLeft = 0;
    for(i=0; i<pTabList->nSrc; i++){
      Bitmask m = getMask(pMaskSet, pTabList->a[i].iCursor);
      assert( (m-1)==toTheLeft );
      toTheLeft |= m;
    }
  }
#endif

  /* Analyze all of the subexpressions.  Note that exprAnalyze() might
  ** add new virtual terms onto the end of the WHERE clause.  We do not
  ** want to analyze these virtual terms, so start analyzing at the end
  ** and work forward so that the added virtual terms are never processed.
  */
  exprAnalyzeAll(pTabList, pWC);
  if( db->mallocFailed ){
    goto whereBeginError;
  }

  /* Chose the best index to use for each table in the FROM clause.
  **
  ** This loop fills in the following fields:
  **
  **   pWInfo->a[].pIdx      The index to use for this level of the loop.
  **   pWInfo->a[].wsFlags   WHERE_xxx flags associated with pIdx
  **   pWInfo->a[].nEq       The number of == and IN constraints
  **   pWInfo->a[].iFrom     Which term of the FROM clause is being coded
  **   pWInfo->a[].iTabCur   The VDBE cursor for the database table
  **   pWInfo->a[].iIdxCur   The VDBE cursor for the index
  **   pWInfo->a[].pTerm     When wsFlags==WO_OR, the OR-clause term
  **
  ** This loop also figures out the nesting order of tables in the FROM
  ** clause.
  */
  notReady = ~(Bitmask)0;
  pTabItem = pTabList->a;
  pLevel = pWInfo->a;
  andFlags = ~0;
  WHERETRACE(("*** Optimizer Start ***\n"));
  for(i=iFrom=0, pLevel=pWInfo->a; i<pTabList->nSrc; i++, pLevel++){
    WhereCost bestPlan;         /* Most efficient plan seen so far */
    Index *pIdx;                /* Index for FROM table at pTabItem */
    int j;                      /* For looping over FROM tables */
    int bestJ = 0;              /* The value of j */
    Bitmask m;                  /* Bitmask value for j or bestJ */
    int once = 0;               /* True when first table is seen */

    memset(&bestPlan, 0, sizeof(bestPlan));
    bestPlan.rCost = SQLITE_BIG_DBL;
    for(j=iFrom, pTabItem=&pTabList->a[j]; j<pTabList->nSrc; j++, pTabItem++){
      int doNotReorder;    /* True if this table should not be reordered */
      WhereCost sCost;     /* Cost information from best[Virtual]Index() */
      ExprList *pOrderBy;  /* ORDER BY clause for index to optimize */

      doNotReorder =  (pTabItem->jointype & (JT_LEFT|JT_CROSS))!=0;
      if( once && doNotReorder ) break;
      m = getMask(pMaskSet, pTabItem->iCursor);
      if( (m & notReady)==0 ){
        if( j==iFrom ) iFrom++;
        continue;
      }
      pOrderBy = ((i==0 && ppOrderBy )?*ppOrderBy:0);

      assert( pTabItem->pTab );
#ifndef SQLITE_OMIT_VIRTUALTABLE
      if( IsVirtual(pTabItem->pTab) ){
        sqlite3_index_info **pp = &pWInfo->a[j].pIdxInfo;
        bestVirtualIndex(pParse, pWC, pTabItem, notReady, pOrderBy, &sCost, pp);
      }else 
#endif
      {
        bestBtreeIndex(pParse, pWC, pTabItem, notReady, pOrderBy, &sCost);
      }
      if( once==0 || sCost.rCost<bestPlan.rCost ){
        once = 1;
        bestPlan = sCost;
        bestJ = j;
      }
      if( doNotReorder ) break;
    }
    assert( once );
    assert( notReady & getMask(pMaskSet, pTabList->a[bestJ].iCursor) );
    WHERETRACE(("*** Optimizer selects table %d for loop %d\n", bestJ,
           pLevel-pWInfo->a));
    if( (bestPlan.plan.wsFlags & WHERE_ORDERBY)!=0 ){
      *ppOrderBy = 0;
    }
    andFlags &= bestPlan.plan.wsFlags;
    pLevel->plan = bestPlan.plan;
    if( bestPlan.plan.wsFlags & WHERE_INDEXED ){
      pLevel->iIdxCur = pParse->nTab++;
    }else{
      pLevel->iIdxCur = -1;
    }
    notReady &= ~getMask(pMaskSet, pTabList->a[bestJ].iCursor);
    pLevel->iFrom = (u8)bestJ;

    /* Check that if the table scanned by this loop iteration had an
    ** INDEXED BY clause attached to it, that the named index is being
    ** used for the scan. If not, then query compilation has failed.
    ** Return an error.
    */
    pIdx = pTabList->a[bestJ].pIndex;
    if( pIdx ){
      if( (bestPlan.plan.wsFlags & WHERE_INDEXED)==0 ){
        sqlite3ErrorMsg(pParse, "cannot use index: %s", pIdx->zName);
        goto whereBeginError;
      }else{
        /* If an INDEXED BY clause is used, the bestIndex() function is
        ** guaranteed to find the index specified in the INDEXED BY clause
        ** if it find an index at all. */
        assert( bestPlan.plan.u.pIdx==pIdx );
      }
    }
  }
  WHERETRACE(("*** Optimizer Finished ***\n"));
  if( pParse->nErr || db->mallocFailed ){
    goto whereBeginError;
  }

  /* If the total query only selects a single row, then the ORDER BY
  ** clause is irrelevant.
  */
  if( (andFlags & WHERE_UNIQUE)!=0 && ppOrderBy ){
    *ppOrderBy = 0;
  }

  /* If the caller is an UPDATE or DELETE statement that is requesting
  ** to use a one-pass algorithm, determine if this is appropriate.
  ** The one-pass algorithm only works if the WHERE clause constraints
  ** the statement to update a single row.
  */
  assert( (wctrlFlags & WHERE_ONEPASS_DESIRED)==0 || pWInfo->nLevel==1 );
  if( (wctrlFlags & WHERE_ONEPASS_DESIRED)!=0 && (andFlags & WHERE_UNIQUE)!=0 ){
    pWInfo->okOnePass = 1;
    pWInfo->a[0].plan.wsFlags &= ~WHERE_IDX_ONLY;
  }

  /* Open all tables in the pTabList and any indices selected for
  ** searching those tables.
  */
  sqlite3CodeVerifySchema(pParse, -1); /* Insert the cookie verifier Goto */
  for(i=0, pLevel=pWInfo->a; i<pTabList->nSrc; i++, pLevel++){
    Table *pTab;     /* Table to open */
    int iDb;         /* Index of database containing table/index */

#ifndef SQLITE_OMIT_EXPLAIN
    if( pParse->explain==2 ){
      char *zMsg;
      struct SrcList_item *pItem = &pTabList->a[pLevel->iFrom];
      zMsg = sqlite3MPrintf(db, "TABLE %s", pItem->zName);
      if( pItem->zAlias ){
        zMsg = sqlite3MAppendf(db, zMsg, "%s AS %s", zMsg, pItem->zAlias);
      }
      if( (pLevel->plan.wsFlags & WHERE_INDEXED)!=0 ){
        zMsg = sqlite3MAppendf(db, zMsg, "%s WITH INDEX %s",
           zMsg, pLevel->plan.u.pIdx->zName);
      }else if( pLevel->plan.wsFlags & WHERE_MULTI_OR ){
        zMsg = sqlite3MAppendf(db, zMsg, "%s VIA MULTI-INDEX UNION", zMsg);
      }else if( pLevel->plan.wsFlags & (WHERE_ROWID_EQ|WHERE_ROWID_RANGE) ){
        zMsg = sqlite3MAppendf(db, zMsg, "%s USING PRIMARY KEY", zMsg);
      }
#ifndef SQLITE_OMIT_VIRTUALTABLE
      else if( (pLevel->plan.wsFlags & WHERE_VIRTUALTABLE)!=0 ){
        sqlite3_index_info *pVtabIdx = pLevel->plan.u.pVtabIdx;
        zMsg = sqlite3MAppendf(db, zMsg, "%s VIRTUAL TABLE INDEX %d:%s", zMsg,
                    pVtabIdx->idxNum, pVtabIdx->idxStr);
      }
#endif
      if( pLevel->plan.wsFlags & WHERE_ORDERBY ){
        zMsg = sqlite3MAppendf(db, zMsg, "%s ORDER BY", zMsg);
      }
      sqlite3VdbeAddOp4(v, OP_Explain, i, pLevel->iFrom, 0, zMsg, P4_DYNAMIC);
    }
#endif /* SQLITE_OMIT_EXPLAIN */
    pTabItem = &pTabList->a[pLevel->iFrom];
    pTab = pTabItem->pTab;
    iDb = sqlite3SchemaToIndex(pParse->db, pTab->pSchema);
    if( (pTab->tabFlags & TF_Ephemeral)!=0 || pTab->pSelect ) continue;
#ifndef SQLITE_OMIT_VIRTUALTABLE
    if( (pLevel->plan.wsFlags & WHERE_VIRTUALTABLE)!=0 ){
      int iCur = pTabItem->iCursor;
      sqlite3VdbeAddOp4(v, OP_VOpen, iCur, 0, 0,
                        (const char*)pTab->pVtab, P4_VTAB);
    }else
#endif
    if( (pLevel->plan.wsFlags & WHERE_IDX_ONLY)==0
         && (wctrlFlags & WHERE_OMIT_OPEN)==0 ){
      int op = pWInfo->okOnePass ? OP_OpenWrite : OP_OpenRead;
      sqlite3OpenTable(pParse, pTabItem->iCursor, iDb, pTab, op);
      if( !pWInfo->okOnePass && pTab->nCol<BMS ){
        Bitmask b = pTabItem->colUsed;
        int n = 0;
        for(; b; b=b>>1, n++){}
        sqlite3VdbeChangeP4(v, sqlite3VdbeCurrentAddr(v)-1, SQLITE_INT_TO_PTR(n), P4_INT32);
        assert( n<=pTab->nCol );
      }
    }else{
      sqlite3TableLock(pParse, iDb, pTab->tnum, 0, pTab->zName);
    }
    pLevel->iTabCur = pTabItem->iCursor;
    if( (pLevel->plan.wsFlags & WHERE_INDEXED)!=0 ){
      Index *pIx = pLevel->plan.u.pIdx;
      KeyInfo *pKey = sqlite3IndexKeyinfo(pParse, pIx);
      int iIdxCur = pLevel->iIdxCur;
      assert( pIx->pSchema==pTab->pSchema );
      assert( iIdxCur>=0 );
      sqlite3VdbeAddOp4(v, OP_OpenRead, iIdxCur, pIx->tnum, iDb,
                        (char*)pKey, P4_KEYINFO_HANDOFF);
      VdbeComment((v, "%s", pIx->zName));
    }
    sqlite3CodeVerifySchema(pParse, iDb);
  }
  pWInfo->iTop = sqlite3VdbeCurrentAddr(v);

  /* Generate the code to do the search.  Each iteration of the for
  ** loop below generates code for a single nested loop of the VM
  ** program.
  */
  notReady = ~(Bitmask)0;
  for(i=0; i<pTabList->nSrc; i++){
    notReady = codeOneLoopStart(pWInfo, i, wctrlFlags, notReady);
    pWInfo->iContinue = pWInfo->a[i].addrCont;
  }

#ifdef SQLITE_TEST  /* For testing and debugging use only */
  /* Record in the query plan information about the current table
  ** and the index used to access it (if any).  If the table itself
  ** is not used, its name is just '{}'.  If no index is used
  ** the index is listed as "{}".  If the primary key is used the
  ** index name is '*'.
  */
  for(i=0; i<pTabList->nSrc; i++){
    char *z;
    int n;
    pLevel = &pWInfo->a[i];
    pTabItem = &pTabList->a[pLevel->iFrom];
    z = pTabItem->zAlias;
    if( z==0 ) z = pTabItem->pTab->zName;
    n = sqlite3Strlen30(z);
    if( n+nQPlan < sizeof(sqlite3_query_plan)-10 ){
      if( pLevel->plan.wsFlags & WHERE_IDX_ONLY ){
        memcpy(&sqlite3_query_plan[nQPlan], "{}", 2);
        nQPlan += 2;
      }else{
        memcpy(&sqlite3_query_plan[nQPlan], z, n);
        nQPlan += n;
      }
      sqlite3_query_plan[nQPlan++] = ' ';
    }
    testcase( pLevel->plan.wsFlags & WHERE_ROWID_EQ );
    testcase( pLevel->plan.wsFlags & WHERE_ROWID_RANGE );
    if( pLevel->plan.wsFlags & (WHERE_ROWID_EQ|WHERE_ROWID_RANGE) ){
      memcpy(&sqlite3_query_plan[nQPlan], "* ", 2);
      nQPlan += 2;
    }else if( (pLevel->plan.wsFlags & WHERE_INDEXED)!=0 ){
      n = sqlite3Strlen30(pLevel->plan.u.pIdx->zName);
      if( n+nQPlan < sizeof(sqlite3_query_plan)-2 ){
        memcpy(&sqlite3_query_plan[nQPlan], pLevel->plan.u.pIdx->zName, n);
        nQPlan += n;
        sqlite3_query_plan[nQPlan++] = ' ';
      }
    }else{
      memcpy(&sqlite3_query_plan[nQPlan], "{} ", 3);
      nQPlan += 3;
    }
  }
  while( nQPlan>0 && sqlite3_query_plan[nQPlan-1]==' ' ){
    sqlite3_query_plan[--nQPlan] = 0;
  }
  sqlite3_query_plan[nQPlan] = 0;
  nQPlan = 0;
#endif /* SQLITE_TEST // Testing and debugging use only */

  /* Record the continuation address in the WhereInfo structure.  Then
  ** clean up and return.
  */
  return pWInfo;

  /* Jump here if malloc fails */
whereBeginError:
  whereInfoFree(db, pWInfo);
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
  SrcList *pTabList = pWInfo->pTabList;
  sqlite3 *db = pParse->db;

  /* Generate loop termination code.
  */
  sqlite3ExprCacheClear(pParse);
  for(i=pTabList->nSrc-1; i>=0; i--){
    pLevel = &pWInfo->a[i];
    sqlite3VdbeResolveLabel(v, pLevel->addrCont);
    if( pLevel->op!=OP_Noop ){
      sqlite3VdbeAddOp2(v, pLevel->op, pLevel->p1, pLevel->p2);
      sqlite3VdbeChangeP5(v, pLevel->p5);
    }
    if( pLevel->plan.wsFlags & WHERE_IN_ABLE && pLevel->u.in.nIn>0 ){
      struct InLoop *pIn;
      int j;
      sqlite3VdbeResolveLabel(v, pLevel->addrNxt);
      for(j=pLevel->u.in.nIn, pIn=&pLevel->u.in.aInLoop[j-1]; j>0; j--, pIn--){
        sqlite3VdbeJumpHere(v, pIn->addrInTop+1);
        sqlite3VdbeAddOp2(v, OP_Next, pIn->iCur, pIn->addrInTop);
        sqlite3VdbeJumpHere(v, pIn->addrInTop-1);
      }
      sqlite3DbFree(db, pLevel->u.in.aInLoop);
    }
    sqlite3VdbeResolveLabel(v, pLevel->addrBrk);
    if( pLevel->iLeftJoin ){
      int addr;
      addr = sqlite3VdbeAddOp1(v, OP_IfPos, pLevel->iLeftJoin);
      sqlite3VdbeAddOp1(v, OP_NullRow, pTabList->a[i].iCursor);
      if( pLevel->iIdxCur>=0 ){
        sqlite3VdbeAddOp1(v, OP_NullRow, pLevel->iIdxCur);
      }
      if( pLevel->op==OP_Return ){
        sqlite3VdbeAddOp2(v, OP_Gosub, pLevel->p1, pLevel->addrFirst);
      }else{
        sqlite3VdbeAddOp2(v, OP_Goto, 0, pLevel->addrFirst);
      }
      sqlite3VdbeJumpHere(v, addr);
    }
  }

  /* The "break" point is here, just past the end of the outer loop.
  ** Set it.
  */
  sqlite3VdbeResolveLabel(v, pWInfo->iBreak);

  /* Close all of the cursors that were opened by sqlite3WhereBegin.
  */
  for(i=0, pLevel=pWInfo->a; i<pTabList->nSrc; i++, pLevel++){
    struct SrcList_item *pTabItem = &pTabList->a[pLevel->iFrom];
    Table *pTab = pTabItem->pTab;
    assert( pTab!=0 );
    if( (pTab->tabFlags & TF_Ephemeral)!=0 || pTab->pSelect ) continue;
    if( (pWInfo->wctrlFlags & WHERE_OMIT_CLOSE)==0 ){
      if( !pWInfo->okOnePass && (pLevel->plan.wsFlags & WHERE_IDX_ONLY)==0 ){
        sqlite3VdbeAddOp1(v, OP_Close, pTabItem->iCursor);
      }
      if( (pLevel->plan.wsFlags & WHERE_INDEXED)!=0 ){
        sqlite3VdbeAddOp1(v, OP_Close, pLevel->iIdxCur);
      }
    }

    /* If this scan uses an index, make code substitutions to read data
    ** from the index in preference to the table. Sometimes, this means
    ** the table need never be read from. This is a performance boost,
    ** as the vdbe level waits until the table is read before actually
    ** seeking the table cursor to the record corresponding to the current
    ** position in the index.
    ** 
    ** Calls to the code generator in between sqlite3WhereBegin and
    ** sqlite3WhereEnd will have created code that references the table
    ** directly.  This loop scans all that code looking for opcodes
    ** that reference the table and converts them into opcodes that
    ** reference the index.
    */
    if( (pLevel->plan.wsFlags & WHERE_INDEXED)!=0 && !db->mallocFailed){
      int k, j, last;
      VdbeOp *pOp;
      Index *pIdx = pLevel->plan.u.pIdx;
      int useIndexOnly = pLevel->plan.wsFlags & WHERE_IDX_ONLY;

      assert( pIdx!=0 );
      pOp = sqlite3VdbeGetOp(v, pWInfo->iTop);
      last = sqlite3VdbeCurrentAddr(v);
      for(k=pWInfo->iTop; k<last; k++, pOp++){
        if( pOp->p1!=pLevel->iTabCur ) continue;
        if( pOp->opcode==OP_Column ){
          for(j=0; j<pIdx->nColumn; j++){
            if( pOp->p2==pIdx->aiColumn[j] ){
              pOp->p2 = j;
              pOp->p1 = pLevel->iIdxCur;
              break;
            }
          }
          assert(!useIndexOnly || j<pIdx->nColumn);
        }else if( pOp->opcode==OP_Rowid ){
          pOp->p1 = pLevel->iIdxCur;
          pOp->opcode = OP_IdxRowid;
        }else if( pOp->opcode==OP_NullRow && useIndexOnly ){
          pOp->opcode = OP_Noop;
        }
      }
    }
  }

  /* Final cleanup
  */
  whereInfoFree(db, pWInfo);
  return;
}
