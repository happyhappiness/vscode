   Vdbe *v = pParse->pVdbe;
   int i;
   struct AggInfo_func *pF;
   for(i=0, pF=pAggInfo->aFunc; i<pAggInfo->nFunc; i++, pF++){
     ExprList *pList = pF->pExpr->x.pList;
     assert( !ExprHasProperty(pF->pExpr, EP_xIsSelect) );
-    sqlite3VdbeAddOp2(v, OP_AggFinal, pF->iMem, pList ? pList->nExpr : 0);
-    sqlite3VdbeAppendP4(v, pF->pFunc, P4_FUNCDEF);
+    sqlite3VdbeAddOp4(v, OP_AggFinal, pF->iMem, pList ? pList->nExpr : 0, 0,
+                      (void*)pF->pFunc, P4_FUNCDEF);
   }
 }
 
 /*
 ** Update the accumulator memory cells for an aggregate based on
 ** the current cursor position.
 */
 static void updateAccumulator(Parse *pParse, AggInfo *pAggInfo){
   Vdbe *v = pParse->pVdbe;
   int i;
-  int regHit = 0;
-  int addrHitTest = 0;
   struct AggInfo_func *pF;
   struct AggInfo_col *pC;
 
   pAggInfo->directMode = 1;
+  sqlite3ExprCacheClear(pParse);
   for(i=0, pF=pAggInfo->aFunc; i<pAggInfo->nFunc; i++, pF++){
     int nArg;
     int addrNext = 0;
     int regAgg;
     ExprList *pList = pF->pExpr->x.pList;
     assert( !ExprHasProperty(pF->pExpr, EP_xIsSelect) );
     if( pList ){
       nArg = pList->nExpr;
       regAgg = sqlite3GetTempRange(pParse, nArg);
-      sqlite3ExprCodeExprList(pParse, pList, regAgg, 0, SQLITE_ECEL_DUP);
+      sqlite3ExprCodeExprList(pParse, pList, regAgg, 0);
     }else{
       nArg = 0;
       regAgg = 0;
     }
     if( pF->iDistinct>=0 ){
       addrNext = sqlite3VdbeMakeLabel(v);
-      testcase( nArg==0 );  /* Error condition */
-      testcase( nArg>1 );   /* Also an error */
+      assert( nArg==1 );
       codeDistinct(pParse, pF->iDistinct, addrNext, 1, regAgg);
     }
-    if( pF->pFunc->funcFlags & SQLITE_FUNC_NEEDCOLL ){
+    if( pF->pFunc->flags & SQLITE_FUNC_NEEDCOLL ){
       CollSeq *pColl = 0;
       struct ExprList_item *pItem;
       int j;
       assert( pList!=0 );  /* pList!=0 if pF->pFunc has NEEDCOLL */
       for(j=0, pItem=pList->a; !pColl && j<nArg; j++, pItem++){
         pColl = sqlite3ExprCollSeq(pParse, pItem->pExpr);
       }
       if( !pColl ){
         pColl = pParse->db->pDfltColl;
       }
-      if( regHit==0 && pAggInfo->nAccumulator ) regHit = ++pParse->nMem;
-      sqlite3VdbeAddOp4(v, OP_CollSeq, regHit, 0, 0, (char *)pColl, P4_COLLSEQ);
+      sqlite3VdbeAddOp4(v, OP_CollSeq, 0, 0, 0, (char *)pColl, P4_COLLSEQ);
     }
-    sqlite3VdbeAddOp3(v, OP_AggStep0, 0, regAgg, pF->iMem);
-    sqlite3VdbeAppendP4(v, pF->pFunc, P4_FUNCDEF);
+    sqlite3VdbeAddOp4(v, OP_AggStep, 0, regAgg, pF->iMem,
+                      (void*)pF->pFunc, P4_FUNCDEF);
     sqlite3VdbeChangeP5(v, (u8)nArg);
-    sqlite3ExprCacheAffinityChange(pParse, regAgg, nArg);
     sqlite3ReleaseTempRange(pParse, regAgg, nArg);
+    sqlite3ExprCacheAffinityChange(pParse, regAgg, nArg);
     if( addrNext ){
       sqlite3VdbeResolveLabel(v, addrNext);
       sqlite3ExprCacheClear(pParse);
     }
   }
-
-  /* Before populating the accumulator registers, clear the column cache.
-  ** Otherwise, if any of the required column values are already present 
-  ** in registers, sqlite3ExprCode() may use OP_SCopy to copy the value
-  ** to pC->iMem. But by the time the value is used, the original register
-  ** may have been used, invalidating the underlying buffer holding the
-  ** text or blob value. See ticket [883034dcb5].
-  **
-  ** Another solution would be to change the OP_SCopy used to copy cached
-  ** values to an OP_Copy.
-  */
-  if( regHit ){
-    addrHitTest = sqlite3VdbeAddOp1(v, OP_If, regHit); VdbeCoverage(v);
-  }
-  sqlite3ExprCacheClear(pParse);
   for(i=0, pC=pAggInfo->aCol; i<pAggInfo->nAccumulator; i++, pC++){
     sqlite3ExprCode(pParse, pC->pExpr, pC->iMem);
   }
   pAggInfo->directMode = 0;
   sqlite3ExprCacheClear(pParse);
-  if( addrHitTest ){
-    sqlite3VdbeJumpHere(v, addrHitTest);
-  }
-}
-
-/*
-** Add a single OP_Explain instruction to the VDBE to explain a simple
-** count(*) query ("SELECT count(*) FROM pTab").
-*/
-#ifndef SQLITE_OMIT_EXPLAIN
-static void explainSimpleCount(
-  Parse *pParse,                  /* Parse context */
-  Table *pTab,                    /* Table being queried */
-  Index *pIdx                     /* Index used to optimize scan, or NULL */
-){
-  if( pParse->explain==2 ){
-    int bCover = (pIdx!=0 && (HasRowid(pTab) || !IsPrimaryKeyIndex(pIdx)));
-    char *zEqp = sqlite3MPrintf(pParse->db, "SCAN TABLE %s%s%s",
-        pTab->zName,
-        bCover ? " USING COVERING INDEX " : "",
-        bCover ? pIdx->zName : ""
-    );
-    sqlite3VdbeAddOp4(
-        pParse->pVdbe, OP_Explain, pParse->iSelectId, 0, 0, zEqp, P4_DYNAMIC
-    );
-  }
-}
-#else
-# define explainSimpleCount(a,b,c)
-#endif
-
-/*
-** Context object for havingToWhereExprCb().
-*/
-struct HavingToWhereCtx {
-  Expr **ppWhere;
-  ExprList *pGroupBy;
-};
-
-/*
-** sqlite3WalkExpr() callback used by havingToWhere().
-**
-** If the node passed to the callback is a TK_AND node, return 
-** WRC_Continue to tell sqlite3WalkExpr() to iterate through child nodes.
-**
-** Otherwise, return WRC_Prune. In this case, also check if the 
-** sub-expression matches the criteria for being moved to the WHERE
-** clause. If so, add it to the WHERE clause and replace the sub-expression
-** within the HAVING expression with a constant "1".
-*/
-static int havingToWhereExprCb(Walker *pWalker, Expr *pExpr){
-  if( pExpr->op!=TK_AND ){
-    struct HavingToWhereCtx *p = pWalker->u.pHavingCtx;
-    if( sqlite3ExprIsConstantOrGroupBy(pWalker->pParse, pExpr, p->pGroupBy) ){
-      sqlite3 *db = pWalker->pParse->db;
-      Expr *pNew = sqlite3ExprAlloc(db, TK_INTEGER, &sqlite3IntTokens[1], 0);
-      if( pNew ){
-        Expr *pWhere = *(p->ppWhere);
-        SWAP(Expr, *pNew, *pExpr);
-        pNew = sqlite3ExprAnd(db, pWhere, pNew);
-        *(p->ppWhere) = pNew;
-      }
-    }
-    return WRC_Prune;
-  }
-  return WRC_Continue;
-}
-
-/*
-** Transfer eligible terms from the HAVING clause of a query, which is
-** processed after grouping, to the WHERE clause, which is processed before
-** grouping. For example, the query:
-**
-**   SELECT * FROM <tables> WHERE a=? GROUP BY b HAVING b=? AND c=?
-**
-** can be rewritten as:
-**
-**   SELECT * FROM <tables> WHERE a=? AND b=? GROUP BY b HAVING c=?
-**
-** A term of the HAVING expression is eligible for transfer if it consists
-** entirely of constants and expressions that are also GROUP BY terms that
-** use the "BINARY" collation sequence.
-*/
-static void havingToWhere(
-  Parse *pParse,
-  ExprList *pGroupBy,
-  Expr *pHaving, 
-  Expr **ppWhere
-){
-  struct HavingToWhereCtx sCtx;
-  Walker sWalker;
-
-  sCtx.ppWhere = ppWhere;
-  sCtx.pGroupBy = pGroupBy;
-
-  memset(&sWalker, 0, sizeof(sWalker));
-  sWalker.pParse = pParse;
-  sWalker.xExprCallback = havingToWhereExprCb;
-  sWalker.u.pHavingCtx = &sCtx;
-  sqlite3WalkExpr(&sWalker, pHaving);
-}
-
-/*
-** Check to see if the pThis entry of pTabList is a self-join of a prior view.
-** If it is, then return the SrcList_item for the prior view.  If it is not,
-** then return 0.
-*/
-static struct SrcList_item *isSelfJoinView(
-  SrcList *pTabList,           /* Search for self-joins in this FROM clause */
-  struct SrcList_item *pThis   /* Search for prior reference to this subquery */
-){
-  struct SrcList_item *pItem;
-  for(pItem = pTabList->a; pItem<pThis; pItem++){
-    if( pItem->pSelect==0 ) continue;
-    if( pItem->fg.viaCoroutine ) continue;
-    if( pItem->zName==0 ) continue;
-    if( sqlite3_stricmp(pItem->zDatabase, pThis->zDatabase)!=0 ) continue;
-    if( sqlite3_stricmp(pItem->zName, pThis->zName)!=0 ) continue;
-    if( sqlite3ExprCompare(0, 
-          pThis->pSelect->pWhere, pItem->pSelect->pWhere, -1) 
-    ){
-      /* The view was modified by some other optimization such as
-      ** pushDownWhereTerms() */
-      continue;
-    }
-    return pItem;
-  }
-  return 0;
 }
 
-#ifdef SQLITE_COUNTOFVIEW_OPTIMIZATION
-/*
-** Attempt to transform a query of the form
-**
-**    SELECT count(*) FROM (SELECT x FROM t1 UNION ALL SELECT y FROM t2)
-**
-** Into this:
-**
-**    SELECT (SELECT count(*) FROM t1)+(SELECT count(*) FROM t2)
-**
-** The transformation only works if all of the following are true:
-**
-**   *  The subquery is a UNION ALL of two or more terms
-**   *  There is no WHERE or GROUP BY or HAVING clauses on the subqueries
-**   *  The outer query is a simple count(*)
-**
-** Return TRUE if the optimization is undertaken.
-*/
-static int countOfViewOptimization(Parse *pParse, Select *p){
-  Select *pSub, *pPrior;
-  Expr *pExpr;
-  Expr *pCount;
-  sqlite3 *db;
-  if( (p->selFlags & SF_Aggregate)==0 ) return 0;   /* This is an aggregate */
-  if( p->pEList->nExpr!=1 ) return 0;               /* Single result column */
-  pExpr = p->pEList->a[0].pExpr;
-  if( pExpr->op!=TK_AGG_FUNCTION ) return 0;        /* Result is an aggregate */
-  if( sqlite3_stricmp(pExpr->u.zToken,"count") ) return 0;  /* Is count() */
-  if( pExpr->x.pList!=0 ) return 0;                 /* Must be count(*) */
-  if( p->pSrc->nSrc!=1 ) return 0;                  /* One table in FROM  */
-  pSub = p->pSrc->a[0].pSelect;
-  if( pSub==0 ) return 0;                           /* The FROM is a subquery */
-  if( pSub->pPrior==0 ) return 0;                   /* Must be a compound ry */
-  do{
-    if( pSub->op!=TK_ALL && pSub->pPrior ) return 0;  /* Must be UNION ALL */
-    if( pSub->pWhere ) return 0;                      /* No WHERE clause */
-    if( pSub->selFlags & SF_Aggregate ) return 0;     /* Not an aggregate */
-    pSub = pSub->pPrior;                              /* Repeat over compound */
-  }while( pSub );
-
-  /* If we reach this point then it is OK to perform the transformation */
-
-  db = pParse->db;
-  pCount = pExpr;
-  pExpr = 0;
-  pSub = p->pSrc->a[0].pSelect;
-  p->pSrc->a[0].pSelect = 0;
-  sqlite3SrcListDelete(db, p->pSrc);
-  p->pSrc = sqlite3DbMallocZero(pParse->db, sizeof(*p->pSrc));
-  while( pSub ){
-    Expr *pTerm;
-    pPrior = pSub->pPrior;
-    pSub->pPrior = 0;
-    pSub->pNext = 0;
-    pSub->selFlags |= SF_Aggregate;
-    pSub->selFlags &= ~SF_Compound;
-    pSub->nSelectRow = 0;
-    sqlite3ExprListDelete(db, pSub->pEList);
-    pTerm = pPrior ? sqlite3ExprDup(db, pCount, 0) : pCount;
-    pSub->pEList = sqlite3ExprListAppend(pParse, 0, pTerm);
-    pTerm = sqlite3PExpr(pParse, TK_SELECT, 0, 0);
-    sqlite3PExprAddSelect(pParse, pTerm, pSub);
-    if( pExpr==0 ){
-      pExpr = pTerm;
-    }else{
-      pExpr = sqlite3PExpr(pParse, TK_PLUS, pTerm, pExpr);
-    }
-    pSub = pPrior;
-  }
-  p->pEList->a[0].pExpr = pExpr;
-  p->selFlags &= ~SF_Aggregate;
-
-#if SELECTTRACE_ENABLED
-  if( sqlite3SelectTrace & 0x400 ){
-    SELECTTRACE(0x400,pParse,p,("After count-of-view optimization:\n"));
-    sqlite3TreeViewSelect(0, p, 0);
-  }
-#endif
-  return 1;
-}
-#endif /* SQLITE_COUNTOFVIEW_OPTIMIZATION */
-
 /*
 ** Generate code for the SELECT statement given in the p argument.  
 **
-** The results are returned according to the SelectDest structure.
-** See comments in sqliteInt.h for further information.
+** The results are distributed in various ways depending on the
+** contents of the SelectDest structure pointed to by argument pDest
+** as follows:
+**
+**     pDest->eDest    Result
+**     ------------    -------------------------------------------
+**     SRT_Output      Generate a row of output (using the OP_ResultRow
+**                     opcode) for each row in the result set.
+**
+**     SRT_Mem         Only valid if the result is a single column.
+**                     Store the first column of the first result row
+**                     in register pDest->iParm then abandon the rest
+**                     of the query.  This destination implies "LIMIT 1".
+**
+**     SRT_Set         The result must be a single column.  Store each
+**                     row of result as the key in table pDest->iParm. 
+**                     Apply the affinity pDest->affinity before storing
+**                     results.  Used to implement "IN (SELECT ...)".
+**
+**     SRT_Union       Store results as a key in a temporary table pDest->iParm.
+**
+**     SRT_Except      Remove results from the temporary table pDest->iParm.
+**
+**     SRT_Table       Store results in temporary table pDest->iParm.
+**                     This is like SRT_EphemTab except that the table
+**                     is assumed to already be open.
+**
+**     SRT_EphemTab    Create an temporary table pDest->iParm and store
+**                     the result there. The cursor is left open after
+**                     returning.  This is like SRT_Table except that
+**                     this destination uses OP_OpenEphemeral to create
+**                     the table first.
+**
+**     SRT_Coroutine   Generate a co-routine that returns a new row of
+**                     results each time it is invoked.  The entry point
+**                     of the co-routine is stored in register pDest->iParm.
+**
+**     SRT_Exists      Store a 1 in memory cell pDest->iParm if the result
+**                     set is not empty.
+**
+**     SRT_Discard     Throw the results away.  This is used by SELECT
+**                     statements within triggers whose only purpose is
+**                     the side-effects of functions.
 **
 ** This routine returns the number of errors.  If any errors are
 ** encountered, then an appropriate error message is left in
 ** pParse->zErrMsg.
 **
 ** This routine does NOT free the Select structure passed in.  The
