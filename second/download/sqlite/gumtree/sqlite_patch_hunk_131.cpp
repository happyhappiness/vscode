 static void createMask(WhereMaskSet *pMaskSet, int iCursor){
   assert( pMaskSet->n < ArraySize(pMaskSet->ix) );
   pMaskSet->ix[pMaskSet->n++] = iCursor;
 }
 
 /*
-** Advance to the next WhereTerm that matches according to the criteria
-** established when the pScan object was initialized by whereScanInit().
-** Return NULL if there are no more matching WhereTerms.
-*/
-static WhereTerm *whereScanNext(WhereScan *pScan){
-  int iCur;            /* The cursor on the LHS of the term */
-  i16 iColumn;         /* The column on the LHS of the term.  -1 for IPK */
-  Expr *pX;            /* An expression being tested */
-  WhereClause *pWC;    /* Shorthand for pScan->pWC */
-  WhereTerm *pTerm;    /* The term being tested */
-  int k = pScan->k;    /* Where to start scanning */
-
-  assert( pScan->iEquiv<=pScan->nEquiv );
-  pWC = pScan->pWC;
-  while(1){
-    iColumn = pScan->aiColumn[pScan->iEquiv-1];
-    iCur = pScan->aiCur[pScan->iEquiv-1];
-    assert( pWC!=0 );
-    do{
-      for(pTerm=pWC->a+k; k<pWC->nTerm; k++, pTerm++){
-        if( pTerm->leftCursor==iCur
-         && pTerm->u.leftColumn==iColumn
-         && (iColumn!=XN_EXPR
-             || sqlite3ExprCompareSkip(pTerm->pExpr->pLeft,
-                                       pScan->pIdxExpr,iCur)==0)
-         && (pScan->iEquiv<=1 || !ExprHasProperty(pTerm->pExpr, EP_FromJoin))
-        ){
-          if( (pTerm->eOperator & WO_EQUIV)!=0
-           && pScan->nEquiv<ArraySize(pScan->aiCur)
-           && (pX = sqlite3ExprSkipCollate(pTerm->pExpr->pRight))->op==TK_COLUMN
-          ){
-            int j;
-            for(j=0; j<pScan->nEquiv; j++){
-              if( pScan->aiCur[j]==pX->iTable
-               && pScan->aiColumn[j]==pX->iColumn ){
-                  break;
-              }
-            }
-            if( j==pScan->nEquiv ){
-              pScan->aiCur[j] = pX->iTable;
-              pScan->aiColumn[j] = pX->iColumn;
-              pScan->nEquiv++;
-            }
-          }
-          if( (pTerm->eOperator & pScan->opMask)!=0 ){
-            /* Verify the affinity and collating sequence match */
-            if( pScan->zCollName && (pTerm->eOperator & WO_ISNULL)==0 ){
-              CollSeq *pColl;
-              Parse *pParse = pWC->pWInfo->pParse;
-              pX = pTerm->pExpr;
-              if( !sqlite3IndexAffinityOk(pX, pScan->idxaff) ){
-                continue;
-              }
-              assert(pX->pLeft);
-              pColl = sqlite3BinaryCompareCollSeq(pParse,
-                                                  pX->pLeft, pX->pRight);
-              if( pColl==0 ) pColl = pParse->db->pDfltColl;
-              if( sqlite3StrICmp(pColl->zName, pScan->zCollName) ){
-                continue;
-              }
-            }
-            if( (pTerm->eOperator & (WO_EQ|WO_IS))!=0
-             && (pX = pTerm->pExpr->pRight)->op==TK_COLUMN
-             && pX->iTable==pScan->aiCur[0]
-             && pX->iColumn==pScan->aiColumn[0]
-            ){
-              testcase( pTerm->eOperator & WO_IS );
-              continue;
-            }
-            pScan->pWC = pWC;
-            pScan->k = k+1;
-            return pTerm;
-          }
-        }
-      }
-      pWC = pWC->pOuter;
-      k = 0;
-    }while( pWC!=0 );
-    if( pScan->iEquiv>=pScan->nEquiv ) break;
-    pWC = pScan->pOrigWC;
-    k = 0;
-    pScan->iEquiv++;
+** This routine walks (recursively) an expression tree and generates
+** a bitmask indicating which tables are used in that expression
+** tree.
+**
+** In order for this routine to work, the calling function must have
+** previously invoked sqlite3ResolveExprNames() on the expression.  See
+** the header comment on that routine for additional information.
+** The sqlite3ResolveExprNames() routines looks for column names and
+** sets their opcodes to TK_COLUMN and their Expr.iTable fields to
+** the VDBE cursor number of the table.  This routine just has to
+** translate the cursor numbers into bitmask values and OR all
+** the bitmasks together.
+*/
+static Bitmask exprListTableUsage(WhereMaskSet*, ExprList*);
+static Bitmask exprSelectTableUsage(WhereMaskSet*, Select*);
+static Bitmask exprTableUsage(WhereMaskSet *pMaskSet, Expr *p){
+  Bitmask mask = 0;
+  if( p==0 ) return 0;
+  if( p->op==TK_COLUMN ){
+    mask = getMask(pMaskSet, p->iTable);
+    return mask;
+  }
+  mask = exprTableUsage(pMaskSet, p->pRight);
+  mask |= exprTableUsage(pMaskSet, p->pLeft);
+  if( ExprHasProperty(p, EP_xIsSelect) ){
+    mask |= exprSelectTableUsage(pMaskSet, p->x.pSelect);
+  }else{
+    mask |= exprListTableUsage(pMaskSet, p->x.pList);
   }
-  return 0;
+  return mask;
+}
+static Bitmask exprListTableUsage(WhereMaskSet *pMaskSet, ExprList *pList){
+  int i;
+  Bitmask mask = 0;
+  if( pList ){
+    for(i=0; i<pList->nExpr; i++){
+      mask |= exprTableUsage(pMaskSet, pList->a[i].pExpr);
+    }
+  }
+  return mask;
 }
+static Bitmask exprSelectTableUsage(WhereMaskSet *pMaskSet, Select *pS){
+  Bitmask mask = 0;
+  while( pS ){
+    mask |= exprListTableUsage(pMaskSet, pS->pEList);
+    mask |= exprListTableUsage(pMaskSet, pS->pGroupBy);
+    mask |= exprListTableUsage(pMaskSet, pS->pOrderBy);
+    mask |= exprTableUsage(pMaskSet, pS->pWhere);
+    mask |= exprTableUsage(pMaskSet, pS->pHaving);
+    pS = pS->pPrior;
+  }
+  return mask;
+}
+
+/*
+** Return TRUE if the given operator is one of the operators that is
+** allowed for an indexable WHERE clause term.  The allowed operators are
+** "=", "<", ">", "<=", ">=", and "IN".
+*/
+static int allowedOp(int op){
+  assert( TK_GT>TK_EQ && TK_GT<TK_GE );
+  assert( TK_LT>TK_EQ && TK_LT<TK_GE );
+  assert( TK_LE>TK_EQ && TK_LE<TK_GE );
+  assert( TK_GE==TK_EQ+4 );
+  return op==TK_IN || (op>=TK_EQ && op<=TK_GE) || op==TK_ISNULL;
+}
+
+/*
+** Swap two objects of type TYPE.
+*/
+#define SWAP(TYPE,A,B) {TYPE t=A; A=B; B=t;}
 
 /*
-** Initialize a WHERE clause scanner object.  Return a pointer to the
-** first match.  Return NULL if there are no matches.
+** Commute a comparison operator.  Expressions of the form "X op Y"
+** are converted into "Y op X".
 **
-** The scanner will be searching the WHERE clause pWC.  It will look
-** for terms of the form "X <op> <expr>" where X is column iColumn of table
-** iCur.   Or if pIdx!=0 then X is column iColumn of index pIdx.  pIdx
-** must be one of the indexes of table iCur.
-**
-** The <op> must be one of the operators described by opMask.
-**
-** If the search is for X and the WHERE clause contains terms of the
-** form X=Y then this routine might also return terms of the form
-** "Y <op> <expr>".  The number of levels of transitivity is limited,
-** but is enough to handle most commonly occurring SQL statements.
-**
-** If X is not the INTEGER PRIMARY KEY then X must be compatible with
-** index pIdx.
-*/
-static WhereTerm *whereScanInit(
-  WhereScan *pScan,       /* The WhereScan object being initialized */
-  WhereClause *pWC,       /* The WHERE clause to be scanned */
-  int iCur,               /* Cursor to scan for */
-  int iColumn,            /* Column to scan for */
-  u32 opMask,             /* Operator(s) to scan for */
-  Index *pIdx             /* Must be compatible with this index */
-){
-  pScan->pOrigWC = pWC;
-  pScan->pWC = pWC;
-  pScan->pIdxExpr = 0;
-  pScan->idxaff = 0;
-  pScan->zCollName = 0;
-  if( pIdx ){
-    int j = iColumn;
-    iColumn = pIdx->aiColumn[j];
-    if( iColumn==XN_EXPR ){
-      pScan->pIdxExpr = pIdx->aColExpr->a[j].pExpr;
-      pScan->zCollName = pIdx->azColl[j];
-    }else if( iColumn==pIdx->pTable->iPKey ){
-      iColumn = XN_ROWID;
-    }else if( iColumn>=0 ){
-      pScan->idxaff = pIdx->pTable->aCol[iColumn].affinity;
-      pScan->zCollName = pIdx->azColl[j];
-    }
-  }else if( iColumn==XN_EXPR ){
-    return 0;
+** If a collation sequence is associated with either the left or right
+** side of the comparison, it remains associated with the same side after
+** the commutation. So "Y collate NOCASE op X" becomes 
+** "X collate NOCASE op Y". This is because any collation sequence on
+** the left hand side of a comparison overrides any collation sequence 
+** attached to the right. For the same reason the EP_ExpCollate flag
+** is not commuted.
+*/
+static void exprCommute(Parse *pParse, Expr *pExpr){
+  u16 expRight = (pExpr->pRight->flags & EP_ExpCollate);
+  u16 expLeft = (pExpr->pLeft->flags & EP_ExpCollate);
+  assert( allowedOp(pExpr->op) && pExpr->op!=TK_IN );
+  pExpr->pRight->pColl = sqlite3ExprCollSeq(pParse, pExpr->pRight);
+  pExpr->pLeft->pColl = sqlite3ExprCollSeq(pParse, pExpr->pLeft);
+  SWAP(CollSeq*,pExpr->pRight->pColl,pExpr->pLeft->pColl);
+  pExpr->pRight->flags = (pExpr->pRight->flags & ~EP_ExpCollate) | expLeft;
+  pExpr->pLeft->flags = (pExpr->pLeft->flags & ~EP_ExpCollate) | expRight;
+  SWAP(Expr*,pExpr->pRight,pExpr->pLeft);
+  if( pExpr->op>=TK_GT ){
+    assert( TK_LT==TK_GT+2 );
+    assert( TK_GE==TK_LE+2 );
+    assert( TK_GT>TK_EQ );
+    assert( TK_GT<TK_LE );
+    assert( pExpr->op>=TK_GT && pExpr->op<=TK_GE );
+    pExpr->op = ((pExpr->op-TK_GT)^2)+TK_GT;
+  }
+}
+
+/*
+** Translate from TK_xx operator to WO_xx bitmask.
+*/
+static u16 operatorMask(int op){
+  u16 c;
+  assert( allowedOp(op) );
+  if( op==TK_IN ){
+    c = WO_IN;
+  }else if( op==TK_ISNULL ){
+    c = WO_ISNULL;
+  }else{
+    assert( (WO_EQ<<(op-TK_EQ)) < 0x7fff );
+    c = (u16)(WO_EQ<<(op-TK_EQ));
   }
-  pScan->opMask = opMask;
-  pScan->k = 0;
-  pScan->aiCur[0] = iCur;
-  pScan->aiColumn[0] = iColumn;
-  pScan->nEquiv = 1;
-  pScan->iEquiv = 1;
-  return whereScanNext(pScan);
+  assert( op!=TK_ISNULL || c==WO_ISNULL );
+  assert( op!=TK_IN || c==WO_IN );
+  assert( op!=TK_EQ || c==WO_EQ );
+  assert( op!=TK_LT || c==WO_LT );
+  assert( op!=TK_LE || c==WO_LE );
+  assert( op!=TK_GT || c==WO_GT );
+  assert( op!=TK_GE || c==WO_GE );
+  return c;
 }
 
 /*
 ** Search for a term in the WHERE clause that is of the form "X <op> <expr>"
-** where X is a reference to the iColumn of table iCur or of index pIdx
-** if pIdx!=0 and <op> is one of the WO_xx operator codes specified by
-** the op parameter.  Return a pointer to the term.  Return 0 if not found.
-**
-** If pIdx!=0 then it must be one of the indexes of table iCur.  
-** Search for terms matching the iColumn-th column of pIdx
-** rather than the iColumn-th column of table iCur.
-**
-** The term returned might by Y=<expr> if there is another constraint in
-** the WHERE clause that specifies that X=Y.  Any such constraints will be
-** identified by the WO_EQUIV bit in the pTerm->eOperator field.  The
-** aiCur[]/iaColumn[] arrays hold X and all its equivalents. There are 11
-** slots in aiCur[]/aiColumn[] so that means we can look for X plus up to 10
-** other equivalent values.  Hence a search for X will return <expr> if X=A1
-** and A1=A2 and A2=A3 and ... and A9=A10 and A10=<expr>.
-**
-** If there are multiple terms in the WHERE clause of the form "X <op> <expr>"
-** then try for the one with no dependencies on <expr> - in other words where
-** <expr> is a constant expression of some kind.  Only return entries of
-** the form "X <op> Y" where Y is a column in another table if no terms of
-** the form "X <op> <const-expr>" exist.   If no terms with a constant RHS
-** exist, try to return a term that does not use WO_EQUIV.
+** where X is a reference to the iColumn of table iCur and <op> is one of
+** the WO_xx operator codes specified by the op parameter.
+** Return a pointer to the term.  Return 0 if not found.
 */
-WhereTerm *sqlite3WhereFindTerm(
+static WhereTerm *findTerm(
   WhereClause *pWC,     /* The WHERE clause to be searched */
   int iCur,             /* Cursor number of LHS */
   int iColumn,          /* Column number of LHS */
   Bitmask notReady,     /* RHS must not overlap with this mask */
   u32 op,               /* Mask of WO_xx values describing operator */
   Index *pIdx           /* Must be compatible with this index, if not NULL */
 ){
-  WhereTerm *pResult = 0;
-  WhereTerm *p;
-  WhereScan scan;
+  WhereTerm *pTerm;
+  int k;
+  assert( iCur>=0 );
+  op &= WO_ALL;
+  for(pTerm=pWC->a, k=pWC->nTerm; k; k--, pTerm++){
+    if( pTerm->leftCursor==iCur
+       && (pTerm->prereqRight & notReady)==0
+       && pTerm->u.leftColumn==iColumn
+       && (pTerm->eOperator & op)!=0
+    ){
+      if( pIdx && pTerm->eOperator!=WO_ISNULL ){
+        Expr *pX = pTerm->pExpr;
+        CollSeq *pColl;
+        char idxaff;
+        int j;
+        Parse *pParse = pWC->pParse;
+
+        idxaff = pIdx->pTable->aCol[iColumn].affinity;
+        if( !sqlite3IndexAffinityOk(pX, idxaff) ) continue;
+
+        /* Figure out the collation sequence required from an index for
+        ** it to be useful for optimising expression pX. Store this
+        ** value in variable pColl.
+        */
+        assert(pX->pLeft);
+        pColl = sqlite3BinaryCompareCollSeq(pParse, pX->pLeft, pX->pRight);
+        assert(pColl || pParse->nErr);
 
-  p = whereScanInit(&scan, pWC, iCur, iColumn, op, pIdx);
-  op &= WO_EQ|WO_IS;
-  while( p ){
-    if( (p->prereqRight & notReady)==0 ){
-      if( p->prereqRight==0 && (p->eOperator&op)!=0 ){
-        testcase( p->eOperator & WO_IS );
-        return p;
+        for(j=0; pIdx->aiColumn[j]!=iColumn; j++){
+          if( NEVER(j>=pIdx->nColumn) ) return 0;
+        }
+        if( pColl && sqlite3StrICmp(pColl->zName, pIdx->azColl[j]) ) continue;
       }
-      if( pResult==0 ) pResult = p;
+      return pTerm;
     }
-    p = whereScanNext(&scan);
   }
-  return pResult;
+  return 0;
 }
 
+/* Forward reference */
+static void exprAnalyze(SrcList*, WhereClause*, int);
+
 /*
-** This function searches pList for an entry that matches the iCol-th column
-** of index pIdx.
+** Call exprAnalyze on all terms in a WHERE clause.  
+**
 **
-** If such an expression is found, its index in pList->a[] is returned. If
-** no expression is found, -1 is returned.
 */
-static int findIndexCol(
-  Parse *pParse,                  /* Parse context */
-  ExprList *pList,                /* Expression list to search */
-  int iBase,                      /* Cursor for table associated with pIdx */
-  Index *pIdx,                    /* Index to match column of */
-  int iCol                        /* Column of index to match */
+static void exprAnalyzeAll(
+  SrcList *pTabList,       /* the FROM clause */
+  WhereClause *pWC         /* the WHERE clause to be analyzed */
 ){
   int i;
-  const char *zColl = pIdx->azColl[iCol];
-
-  for(i=0; i<pList->nExpr; i++){
-    Expr *p = sqlite3ExprSkipCollate(pList->a[i].pExpr);
-    if( p->op==TK_COLUMN
-     && p->iColumn==pIdx->aiColumn[iCol]
-     && p->iTable==iBase
-    ){
-      CollSeq *pColl = sqlite3ExprNNCollSeq(pParse, pList->a[i].pExpr);
-      if( 0==sqlite3StrICmp(pColl->zName, zColl) ){
-        return i;
-      }
-    }
-  }
-
-  return -1;
-}
-
-/*
-** Return TRUE if the iCol-th column of index pIdx is NOT NULL
-*/
-static int indexColumnNotNull(Index *pIdx, int iCol){
-  int j;
-  assert( pIdx!=0 );
-  assert( iCol>=0 && iCol<pIdx->nColumn );
-  j = pIdx->aiColumn[iCol];
-  if( j>=0 ){
-    return pIdx->pTable->aCol[j].notNull;
-  }else if( j==(-1) ){
-    return 1;
-  }else{
-    assert( j==(-2) );
-    return 0;  /* Assume an indexed expression can always yield a NULL */
-
+  for(i=pWC->nTerm-1; i>=0; i--){
+    exprAnalyze(pTabList, pWC, i);
   }
 }
 
+#ifndef SQLITE_OMIT_LIKE_OPTIMIZATION
 /*
-** Return true if the DISTINCT expression-list passed as the third argument
-** is redundant.
+** Check to see if the given expression is a LIKE or GLOB operator that
+** can be optimized using inequality constraints.  Return TRUE if it is
+** so and false if not.
 **
-** A DISTINCT list is redundant if any subset of the columns in the
-** DISTINCT list are collectively unique and individually non-null.
+** In order for the operator to be optimizible, the RHS must be a string
+** literal that does not begin with a wildcard.  
 */
-static int isDistinctRedundant(
-  Parse *pParse,            /* Parsing context */
-  SrcList *pTabList,        /* The FROM clause */
-  WhereClause *pWC,         /* The WHERE clause */
-  ExprList *pDistinct       /* The result set that needs to be DISTINCT */
+static int isLikeOrGlob(
+  Parse *pParse,    /* Parsing and code generating context */
+  Expr *pExpr,      /* Test this expression */
+  int *pnPattern,   /* Number of non-wildcard prefix characters */
+  int *pisComplete, /* True if the only wildcard is % in the last character */
+  int *pnoCase      /* True if uppercase is equivalent to lowercase */
 ){
-  Table *pTab;
-  Index *pIdx;
-  int i;                          
-  int iBase;
-
-  /* If there is more than one table or sub-select in the FROM clause of
-  ** this query, then it will not be possible to show that the DISTINCT 
-  ** clause is redundant. */
-  if( pTabList->nSrc!=1 ) return 0;
-  iBase = pTabList->a[0].iCursor;
-  pTab = pTabList->a[0].pTab;
-
-  /* If any of the expressions is an IPK column on table iBase, then return 
-  ** true. Note: The (p->iTable==iBase) part of this test may be false if the
-  ** current SELECT is a correlated sub-query.
-  */
-  for(i=0; i<pDistinct->nExpr; i++){
-    Expr *p = sqlite3ExprSkipCollate(pDistinct->a[i].pExpr);
-    if( p->op==TK_COLUMN && p->iTable==iBase && p->iColumn<0 ) return 1;
-  }
+  const char *z;             /* String on RHS of LIKE operator */
+  Expr *pRight, *pLeft;      /* Right and left size of LIKE operator */
+  ExprList *pList;           /* List of operands to the LIKE operator */
+  int c;                     /* One character in z[] */
+  int cnt;                   /* Number of non-wildcard prefix characters */
+  char wc[3];                /* Wildcard characters */
+  CollSeq *pColl;            /* Collating sequence for LHS */
+  sqlite3 *db = pParse->db;  /* Database connection */
 
-  /* Loop through all indices on the table, checking each to see if it makes
-  ** the DISTINCT qualifier redundant. It does so if:
-  **
-  **   1. The index is itself UNIQUE, and
-  **
-  **   2. All of the columns in the index are either part of the pDistinct
-  **      list, or else the WHERE clause contains a term of the form "col=X",
-  **      where X is a constant value. The collation sequences of the
-  **      comparison and select-list expressions must match those of the index.
-  **
-  **   3. All of those index columns for which the WHERE clause does not
-  **      contain a "col=X" term are subject to a NOT NULL constraint.
-  */
-  for(pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext){
-    if( !IsUniqueIndex(pIdx) ) continue;
-    for(i=0; i<pIdx->nKeyCol; i++){
-      if( 0==sqlite3WhereFindTerm(pWC, iBase, i, ~(Bitmask)0, WO_EQ, pIdx) ){
-        if( findIndexCol(pParse, pDistinct, iBase, pIdx, i)<0 ) break;
-        if( indexColumnNotNull(pIdx, i)==0 ) break;
-      }
-    }
-    if( i==pIdx->nKeyCol ){
-      /* This index implies that the DISTINCT qualifier is redundant. */
-      return 1;
+  if( !sqlite3IsLikeFunction(db, pExpr, pnoCase, wc) ){
+    return 0;
+  }
+#ifdef SQLITE_EBCDIC
+  if( *pnoCase ) return 0;
+#endif
+  pList = pExpr->x.pList;
+  pRight = pList->a[0].pExpr;
+  if( pRight->op!=TK_STRING ){
+    return 0;
+  }
+  pLeft = pList->a[1].pExpr;
+  if( pLeft->op!=TK_COLUMN ){
+    return 0;
+  }
+  pColl = sqlite3ExprCollSeq(pParse, pLeft);
+  assert( pColl!=0 || pLeft->iColumn==-1 );
+  if( pColl==0 ) return 0;
+  if( (pColl->type!=SQLITE_COLL_BINARY || *pnoCase) &&
+      (pColl->type!=SQLITE_COLL_NOCASE || !*pnoCase) ){
+    return 0;
+  }
+  if( sqlite3ExprAffinity(pLeft)!=SQLITE_AFF_TEXT ) return 0;
+  z = pRight->u.zToken;
+  cnt = 0;
+  if( ALWAYS(z) ){
+    while( (c=z[cnt])!=0 && c!=wc[0] && c!=wc[1] && c!=wc[2] ){
+      cnt++;
     }
   }
-
-  return 0;
+  if( cnt==0 || c==0 || 255==(u8)z[cnt-1] ){
+    return 0;
+  }
+  *pisComplete = z[cnt]==wc[0] && z[cnt+1]==0;
+  *pnPattern = cnt;
+  return 1;
 }
+#endif /* SQLITE_OMIT_LIKE_OPTIMIZATION */
 
 
+#ifndef SQLITE_OMIT_VIRTUALTABLE
 /*
-** Estimate the logarithm of the input value to base 2.
-*/
-static LogEst estLog(LogEst N){
-  return N<=10 ? 0 : sqlite3LogEst(N) - 33;
-}
-
-/*
-** Convert OP_Column opcodes to OP_Copy in previously generated code.
+** Check to see if the given expression is of the form
 **
-** This routine runs over generated VDBE code and translates OP_Column
-** opcodes into OP_Copy when the table is being accessed via co-routine 
-** instead of via table lookup.
+**         column MATCH expr
 **
-** If the bIncrRowid parameter is 0, then any OP_Rowid instructions on
-** cursor iTabCur are transformed into OP_Null. Or, if bIncrRowid is non-zero,
-** then each OP_Rowid is transformed into an instruction to increment the
-** value stored in its output register.
+** If it is then return TRUE.  If not, return FALSE.
 */
-static void translateColumnToCopy(
-  Parse *pParse,      /* Parsing context */
-  int iStart,         /* Translate from this opcode to the end */
-  int iTabCur,        /* OP_Column/OP_Rowid references to this table */
-  int iRegister,      /* The first column is in this register */
-  int bIncrRowid      /* If non-zero, transform OP_rowid to OP_AddImm(1) */
+static int isMatchOfColumn(
+  Expr *pExpr      /* Test this expression */
 ){
-  Vdbe *v = pParse->pVdbe;
-  VdbeOp *pOp = sqlite3VdbeGetOp(v, iStart);
-  int iEnd = sqlite3VdbeCurrentAddr(v);
-  if( pParse->db->mallocFailed ) return;
-  for(; iStart<iEnd; iStart++, pOp++){
-    if( pOp->p1!=iTabCur ) continue;
-    if( pOp->opcode==OP_Column ){
-      pOp->opcode = OP_Copy;
-      pOp->p1 = pOp->p2 + iRegister;
-      pOp->p2 = pOp->p3;
-      pOp->p3 = 0;
-    }else if( pOp->opcode==OP_Rowid ){
-      if( bIncrRowid ){
-        /* Increment the value stored in the P2 operand of the OP_Rowid. */
-        pOp->opcode = OP_AddImm;
-        pOp->p1 = pOp->p2;
-        pOp->p2 = 1;
-      }else{
-        pOp->opcode = OP_Null;
-        pOp->p1 = 0;
-        pOp->p3 = 0;
-      }
-    }
-  }
-}
+  ExprList *pList;
 
-/*
-** Two routines for printing the content of an sqlite3_index_info
-** structure.  Used for testing and debugging only.  If neither
-** SQLITE_TEST or SQLITE_DEBUG are defined, then these routines
-** are no-ops.
-*/
-#if !defined(SQLITE_OMIT_VIRTUALTABLE) && defined(WHERETRACE_ENABLED)
-static void TRACE_IDX_INPUTS(sqlite3_index_info *p){
-  int i;
-  if( !sqlite3WhereTrace ) return;
-  for(i=0; i<p->nConstraint; i++){
-    sqlite3DebugPrintf("  constraint[%d]: col=%d termid=%d op=%d usabled=%d\n",
-       i,
-       p->aConstraint[i].iColumn,
-       p->aConstraint[i].iTermOffset,
-       p->aConstraint[i].op,
-       p->aConstraint[i].usable);
+  if( pExpr->op!=TK_FUNCTION ){
+    return 0;
   }
-  for(i=0; i<p->nOrderBy; i++){
-    sqlite3DebugPrintf("  orderby[%d]: col=%d desc=%d\n",
-       i,
-       p->aOrderBy[i].iColumn,
-       p->aOrderBy[i].desc);
+  if( sqlite3StrICmp(pExpr->u.zToken,"match")!=0 ){
+    return 0;
   }
-}
-static void TRACE_IDX_OUTPUTS(sqlite3_index_info *p){
-  int i;
-  if( !sqlite3WhereTrace ) return;
-  for(i=0; i<p->nConstraint; i++){
-    sqlite3DebugPrintf("  usage[%d]: argvIdx=%d omit=%d\n",
-       i,
-       p->aConstraintUsage[i].argvIndex,
-       p->aConstraintUsage[i].omit);
+  pList = pExpr->x.pList;
+  if( pList->nExpr!=2 ){
+    return 0;
   }
-  sqlite3DebugPrintf("  idxNum=%d\n", p->idxNum);
-  sqlite3DebugPrintf("  idxStr=%s\n", p->idxStr);
-  sqlite3DebugPrintf("  orderByConsumed=%d\n", p->orderByConsumed);
-  sqlite3DebugPrintf("  estimatedCost=%g\n", p->estimatedCost);
-  sqlite3DebugPrintf("  estimatedRows=%lld\n", p->estimatedRows);
-}
-#else
-#define TRACE_IDX_INPUTS(A)
-#define TRACE_IDX_OUTPUTS(A)
-#endif
-
-#ifndef SQLITE_OMIT_AUTOMATIC_INDEX
-/*
-** Return TRUE if the WHERE clause term pTerm is of a form where it
-** could be used with an index to access pSrc, assuming an appropriate
-** index existed.
-*/
-static int termCanDriveIndex(
-  WhereTerm *pTerm,              /* WHERE clause term to check */
-  struct SrcList_item *pSrc,     /* Table we are trying to access */
-  Bitmask notReady               /* Tables in outer loops of the join */
-){
-  char aff;
-  if( pTerm->leftCursor!=pSrc->iCursor ) return 0;
-  if( (pTerm->eOperator & (WO_EQ|WO_IS))==0 ) return 0;
-  if( (pSrc->fg.jointype & JT_LEFT) 
-   && !ExprHasProperty(pTerm->pExpr, EP_FromJoin)
-   && (pTerm->eOperator & WO_IS)
-  ){
-    /* Cannot use an IS term from the WHERE clause as an index driver for
-    ** the RHS of a LEFT JOIN. Such a term can only be used if it is from
-    ** the ON clause.  */
+  if( pList->a[1].pExpr->op != TK_COLUMN ){
     return 0;
   }
-  if( (pTerm->prereqRight & notReady)!=0 ) return 0;
-  if( pTerm->u.leftColumn<0 ) return 0;
-  aff = pSrc->pTab->aCol[pTerm->u.leftColumn].affinity;
-  if( !sqlite3IndexAffinityOk(pTerm->pExpr, aff) ) return 0;
-  testcase( pTerm->pExpr->op==TK_IS );
   return 1;
 }
-#endif
+#endif /* SQLITE_OMIT_VIRTUALTABLE */
 
+/*
+** If the pBase expression originated in the ON or USING clause of
+** a join, then transfer the appropriate markings over to derived.
+*/
+static void transferJoinMarkings(Expr *pDerived, Expr *pBase){
+  pDerived->flags |= pBase->flags & EP_FromJoin;
+  pDerived->iRightJoinTable = pBase->iRightJoinTable;
+}
 
-#ifndef SQLITE_OMIT_AUTOMATIC_INDEX
+#if !defined(SQLITE_OMIT_OR_OPTIMIZATION) && !defined(SQLITE_OMIT_SUBQUERY)
 /*
-** Generate code to construct the Index object for an automatic index
-** and to set up the WhereLevel object pLevel so that the code generator
-** makes use of the automatic index.
+** Analyze a term that consists of two or more OR-connected
+** subterms.  So in:
+**
+**     ... WHERE  (a=5) AND (b=7 OR c=9 OR d=13) AND (d=13)
+**                          ^^^^^^^^^^^^^^^^^^^^
+**
+** This routine analyzes terms such as the middle term in the above example.
+** A WhereOrTerm object is computed and attached to the term under
+** analysis, regardless of the outcome of the analysis.  Hence:
+**
+**     WhereTerm.wtFlags   |=  TERM_ORINFO
+**     WhereTerm.u.pOrInfo  =  a dynamically allocated WhereOrTerm object
+**
+** The term being analyzed must have two or more of OR-connected subterms.
+** A single subterm might be a set of AND-connected sub-subterms.
+** Examples of terms under analysis:
+**
+**     (A)     t1.x=t2.y OR t1.x=t2.z OR t1.y=15 OR t1.z=t3.a+5
+**     (B)     x=expr1 OR expr2=x OR x=expr3
+**     (C)     t1.x=t2.y OR (t1.x=t2.z AND t1.y=15)
+**     (D)     x=expr1 OR (y>11 AND y<22 AND z LIKE '*hello*')
+**     (E)     (p.a=1 AND q.b=2 AND r.c=3) OR (p.x=4 AND q.y=5 AND r.z=6)
+**
+** CASE 1:
+**
+** If all subterms are of the form T.C=expr for some single column of C
+** a single table T (as shown in example B above) then create a new virtual
+** term that is an equivalent IN expression.  In other words, if the term
+** being analyzed is:
+**
+**      x = expr1  OR  expr2 = x  OR  x = expr3
+**
+** then create a new virtual term like this:
+**
+**      x IN (expr1,expr2,expr3)
+**
+** CASE 2:
+**
+** If all subterms are indexable by a single table T, then set
+**
+**     WhereTerm.eOperator              =  WO_OR
+**     WhereTerm.u.pOrInfo->indexable  |=  the cursor number for table T
+**
+** A subterm is "indexable" if it is of the form
+** "T.C <op> <expr>" where C is any column of table T and 
+** <op> is one of "=", "<", "<=", ">", ">=", "IS NULL", or "IN".
+** A subterm is also indexable if it is an AND of two or more
+** subsubterms at least one of which is indexable.  Indexable AND 
+** subterms have their eOperator set to WO_AND and they have
+** u.pAndInfo set to a dynamically allocated WhereAndTerm object.
+**
+** From another point of view, "indexable" means that the subterm could
+** potentially be used with an index if an appropriate index exists.
+** This analysis does not consider whether or not the index exists; that
+** is something the bestIndex() routine will determine.  This analysis
+** only looks at whether subterms appropriate for indexing exist.
+**
+** All examples A through E above all satisfy case 2.  But if a term
+** also statisfies case 1 (such as B) we know that the optimizer will
+** always prefer case 1, so in that case we pretend that case 2 is not
+** satisfied.
+**
+** It might be the case that multiple tables are indexable.  For example,
+** (E) above is indexable on tables P, Q, and R.
+**
+** Terms that satisfy case 2 are candidates for lookup by using
+** separate indices to find rowids for each subterm and composing
+** the union of all rowids using a RowSet object.  This is similar
+** to "bitmap indices" in other database engines.
+**
+** OTHERWISE:
+**
+** If neither case 1 nor case 2 apply, then leave the eOperator set to
+** zero.  This term is not useful for search.
 */
-static void constructAutomaticIndex(
-  Parse *pParse,              /* The parsing context */
-  WhereClause *pWC,           /* The WHERE clause */
-  struct SrcList_item *pSrc,  /* The FROM clause term to get the next index */
-  Bitmask notReady,           /* Mask of cursors that are not available */
-  WhereLevel *pLevel          /* Write new index here */
+static void exprAnalyzeOrTerm(
+  SrcList *pSrc,            /* the FROM clause */
+  WhereClause *pWC,         /* the complete WHERE clause */
+  int idxTerm               /* Index of the OR-term to be analyzed */
 ){
-  int nKeyCol;                /* Number of columns in the constructed index */
-  WhereTerm *pTerm;           /* A single term of the WHERE clause */
-  WhereTerm *pWCEnd;          /* End of pWC->a[] */
-  Index *pIdx;                /* Object describing the transient index */
-  Vdbe *v;                    /* Prepared statement under construction */
-  int addrInit;               /* Address of the initialization bypass jump */
-  Table *pTable;              /* The table being indexed */
-  int addrTop;                /* Top of the index fill loop */
-  int regRecord;              /* Register holding an index record */
-  int n;                      /* Column counter */
-  int i;                      /* Loop counter */
-  int mxBitCol;               /* Maximum column in pSrc->colUsed */
-  CollSeq *pColl;             /* Collating sequence to on a column */
-  WhereLoop *pLoop;           /* The Loop object */
-  char *zNotUsed;             /* Extra space on the end of pIdx */
-  Bitmask idxCols;            /* Bitmap of columns used for indexing */
-  Bitmask extraCols;          /* Bitmap of additional columns */
-  u8 sentWarning = 0;         /* True if a warnning has been issued */
-  Expr *pPartial = 0;         /* Partial Index Expression */
-  int iContinue = 0;          /* Jump here to skip excluded rows */
-  struct SrcList_item *pTabItem;  /* FROM clause term being indexed */
-  int addrCounter = 0;        /* Address where integer counter is initialized */
-  int regBase;                /* Array of registers where record is assembled */
+  Parse *pParse = pWC->pParse;            /* Parser context */
+  sqlite3 *db = pParse->db;               /* Database connection */
+  WhereTerm *pTerm = &pWC->a[idxTerm];    /* The term to be analyzed */
+  Expr *pExpr = pTerm->pExpr;             /* The expression of the term */
+  WhereMaskSet *pMaskSet = pWC->pMaskSet; /* Table use masks */
+  int i;                                  /* Loop counters */
+  WhereClause *pOrWc;       /* Breakup of pTerm into subterms */
+  WhereTerm *pOrTerm;       /* A Sub-term within the pOrWc */
+  WhereOrInfo *pOrInfo;     /* Additional information associated with pTerm */
+  Bitmask chngToIN;         /* Tables that might satisfy case 1 */
+  Bitmask indexable;        /* Tables that are indexable, satisfying case 2 */
 
-  /* Generate code to skip over the creation and initialization of the
-  ** transient index on 2nd and subsequent iterations of the loop. */
-  v = pParse->pVdbe;
-  assert( v!=0 );
-  addrInit = sqlite3VdbeAddOp0(v, OP_Once); VdbeCoverage(v);
+  /*
+  ** Break the OR clause into its separate subterms.  The subterms are
+  ** stored in a WhereClause structure containing within the WhereOrInfo
+  ** object that is attached to the original OR clause term.
+  */
+  assert( (pTerm->wtFlags & (TERM_DYNAMIC|TERM_ORINFO|TERM_ANDINFO))==0 );
+  assert( pExpr->op==TK_OR );
+  pTerm->u.pOrInfo = pOrInfo = sqlite3DbMallocZero(db, sizeof(*pOrInfo));
+  if( pOrInfo==0 ) return;
+  pTerm->wtFlags |= TERM_ORINFO;
+  pOrWc = &pOrInfo->wc;
+  whereClauseInit(pOrWc, pWC->pParse, pMaskSet);
+  whereSplit(pOrWc, pExpr, TK_OR);
+  exprAnalyzeAll(pSrc, pOrWc);
+  if( db->mallocFailed ) return;
+  assert( pOrWc->nTerm>=2 );
 
-  /* Count the number of columns that will be added to the index
-  ** and used to match WHERE clause constraints */
-  nKeyCol = 0;
-  pTable = pSrc->pTab;
-  pWCEnd = &pWC->a[pWC->nTerm];
-  pLoop = pLevel->pWLoop;
-  idxCols = 0;
-  for(pTerm=pWC->a; pTerm<pWCEnd; pTerm++){
-    Expr *pExpr = pTerm->pExpr;
-    assert( !ExprHasProperty(pExpr, EP_FromJoin)    /* prereq always non-zero */
-         || pExpr->iRightJoinTable!=pSrc->iCursor   /*   for the right-hand   */
-         || pLoop->prereq!=0 );                     /*   table of a LEFT JOIN */
-    if( pLoop->prereq==0
-     && (pTerm->wtFlags & TERM_VIRTUAL)==0
-     && !ExprHasProperty(pExpr, EP_FromJoin)
-     && sqlite3ExprIsTableConstant(pExpr, pSrc->iCursor) ){
-      pPartial = sqlite3ExprAnd(pParse->db, pPartial,
-                                sqlite3ExprDup(pParse->db, pExpr, 0));
-    }
-    if( termCanDriveIndex(pTerm, pSrc, notReady) ){
-      int iCol = pTerm->u.leftColumn;
-      Bitmask cMask = iCol>=BMS ? MASKBIT(BMS-1) : MASKBIT(iCol);
-      testcase( iCol==BMS );
-      testcase( iCol==BMS-1 );
-      if( !sentWarning ){
-        sqlite3_log(SQLITE_WARNING_AUTOINDEX,
-            "automatic index on %s(%s)", pTable->zName,
-            pTable->aCol[iCol].zName);
-        sentWarning = 1;
-      }
-      if( (idxCols & cMask)==0 ){
-        if( whereLoopResize(pParse->db, pLoop, nKeyCol+1) ){
-          goto end_auto_index_create;
+  /*
+  ** Compute the set of tables that might satisfy cases 1 or 2.
+  */
+  indexable = ~(Bitmask)0;
+  chngToIN = ~(pWC->vmask);
+  for(i=pOrWc->nTerm-1, pOrTerm=pOrWc->a; i>=0 && indexable; i--, pOrTerm++){
+    if( (pOrTerm->eOperator & WO_SINGLE)==0 ){
+      WhereAndInfo *pAndInfo;
+      assert( pOrTerm->eOperator==0 );
+      assert( (pOrTerm->wtFlags & (TERM_ANDINFO|TERM_ORINFO))==0 );
+      chngToIN = 0;
+      pAndInfo = sqlite3DbMallocRaw(db, sizeof(*pAndInfo));
+      if( pAndInfo ){
+        WhereClause *pAndWC;
+        WhereTerm *pAndTerm;
+        int j;
+        Bitmask b = 0;
+        pOrTerm->u.pAndInfo = pAndInfo;
+        pOrTerm->wtFlags |= TERM_ANDINFO;
+        pOrTerm->eOperator = WO_AND;
+        pAndWC = &pAndInfo->wc;
+        whereClauseInit(pAndWC, pWC->pParse, pMaskSet);
+        whereSplit(pAndWC, pOrTerm->pExpr, TK_AND);
+        exprAnalyzeAll(pSrc, pAndWC);
+        testcase( db->mallocFailed );
+        if( !db->mallocFailed ){
+          for(j=0, pAndTerm=pAndWC->a; j<pAndWC->nTerm; j++, pAndTerm++){
+            assert( pAndTerm->pExpr );
+            if( allowedOp(pAndTerm->pExpr->op) ){
+              b |= getMask(pMaskSet, pAndTerm->leftCursor);
+            }
+          }
         }
-        pLoop->aLTerm[nKeyCol++] = pTerm;
-        idxCols |= cMask;
+        indexable &= b;
       }
-    }
-  }
-  assert( nKeyCol>0 );
-  pLoop->u.btree.nEq = pLoop->nLTerm = nKeyCol;
-  pLoop->wsFlags = WHERE_COLUMN_EQ | WHERE_IDX_ONLY | WHERE_INDEXED
-                     | WHERE_AUTO_INDEX;
-
-  /* Count the number of additional columns needed to create a
-  ** covering index.  A "covering index" is an index that contains all
-  ** columns that are needed by the query.  With a covering index, the
-  ** original table never needs to be accessed.  Automatic indices must
-  ** be a covering index because the index will not be updated if the
-  ** original table changes and the index and table cannot both be used
-  ** if they go out of sync.
-  */
-  extraCols = pSrc->colUsed & (~idxCols | MASKBIT(BMS-1));
-  mxBitCol = MIN(BMS-1,pTable->nCol);
-  testcase( pTable->nCol==BMS-1 );
-  testcase( pTable->nCol==BMS-2 );
-  for(i=0; i<mxBitCol; i++){
-    if( extraCols & MASKBIT(i) ) nKeyCol++;
-  }
-  if( pSrc->colUsed & MASKBIT(BMS-1) ){
-    nKeyCol += pTable->nCol - BMS + 1;
-  }
-
-  /* Construct the Index object to describe this index */
-  pIdx = sqlite3AllocateIndexObject(pParse->db, nKeyCol+1, 0, &zNotUsed);
-  if( pIdx==0 ) goto end_auto_index_create;
-  pLoop->u.btree.pIndex = pIdx;
-  pIdx->zName = "auto-index";
-  pIdx->pTable = pTable;
-  n = 0;
-  idxCols = 0;
-  for(pTerm=pWC->a; pTerm<pWCEnd; pTerm++){
-    if( termCanDriveIndex(pTerm, pSrc, notReady) ){
-      int iCol = pTerm->u.leftColumn;
-      Bitmask cMask = iCol>=BMS ? MASKBIT(BMS-1) : MASKBIT(iCol);
-      testcase( iCol==BMS-1 );
-      testcase( iCol==BMS );
-      if( (idxCols & cMask)==0 ){
-        Expr *pX = pTerm->pExpr;
-        idxCols |= cMask;
-        pIdx->aiColumn[n] = pTerm->u.leftColumn;
-        pColl = sqlite3BinaryCompareCollSeq(pParse, pX->pLeft, pX->pRight);
-        pIdx->azColl[n] = pColl ? pColl->zName : sqlite3StrBINARY;
-        n++;
+    }else if( pOrTerm->wtFlags & TERM_COPIED ){
+      /* Skip this term for now.  We revisit it when we process the
+      ** corresponding TERM_VIRTUAL term */
+    }else{
+      Bitmask b;
+      b = getMask(pMaskSet, pOrTerm->leftCursor);
+      if( pOrTerm->wtFlags & TERM_VIRTUAL ){
+        WhereTerm *pOther = &pOrWc->a[pOrTerm->iParent];
+        b |= getMask(pMaskSet, pOther->leftCursor);
+      }
+      indexable &= b;
+      if( pOrTerm->eOperator!=WO_EQ ){
+        chngToIN = 0;
+      }else{
+        chngToIN &= b;
       }
     }
   }
-  assert( (u32)n==pLoop->u.btree.nEq );
 
-  /* Add additional columns needed to make the automatic index into
-  ** a covering index */
-  for(i=0; i<mxBitCol; i++){
-    if( extraCols & MASKBIT(i) ){
-      pIdx->aiColumn[n] = i;
-      pIdx->azColl[n] = sqlite3StrBINARY;
-      n++;
-    }
-  }
-  if( pSrc->colUsed & MASKBIT(BMS-1) ){
-    for(i=BMS-1; i<pTable->nCol; i++){
-      pIdx->aiColumn[n] = i;
-      pIdx->azColl[n] = sqlite3StrBINARY;
-      n++;
-    }
-  }
-  assert( n==nKeyCol );
-  pIdx->aiColumn[n] = XN_ROWID;
-  pIdx->azColl[n] = sqlite3StrBINARY;
-
-  /* Create the automatic index */
-  assert( pLevel->iIdxCur>=0 );
-  pLevel->iIdxCur = pParse->nTab++;
-  sqlite3VdbeAddOp2(v, OP_OpenAutoindex, pLevel->iIdxCur, nKeyCol+1);
-  sqlite3VdbeSetP4KeyInfo(pParse, pIdx);
-  VdbeComment((v, "for %s", pTable->zName));
-
-  /* Fill the automatic index with content */
-  sqlite3ExprCachePush(pParse);
-  pTabItem = &pWC->pWInfo->pTabList->a[pLevel->iFrom];
-  if( pTabItem->fg.viaCoroutine ){
-    int regYield = pTabItem->regReturn;
-    addrCounter = sqlite3VdbeAddOp2(v, OP_Integer, 0, 0);
-    sqlite3VdbeAddOp3(v, OP_InitCoroutine, regYield, 0, pTabItem->addrFillSub);
-    addrTop =  sqlite3VdbeAddOp1(v, OP_Yield, regYield);
-    VdbeCoverage(v);
-    VdbeComment((v, "next row of \"%s\"", pTabItem->pTab->zName));
-  }else{
-    addrTop = sqlite3VdbeAddOp1(v, OP_Rewind, pLevel->iTabCur); VdbeCoverage(v);
-  }
-  if( pPartial ){
-    iContinue = sqlite3VdbeMakeLabel(v);
-    sqlite3ExprIfFalse(pParse, pPartial, iContinue, SQLITE_JUMPIFNULL);
-    pLoop->wsFlags |= WHERE_PARTIALIDX;
-  }
-  regRecord = sqlite3GetTempReg(pParse);
-  regBase = sqlite3GenerateIndexKey(
-      pParse, pIdx, pLevel->iTabCur, regRecord, 0, 0, 0, 0
-  );
-  sqlite3VdbeAddOp2(v, OP_IdxInsert, pLevel->iIdxCur, regRecord);
-  sqlite3VdbeChangeP5(v, OPFLAG_USESEEKRESULT);
-  if( pPartial ) sqlite3VdbeResolveLabel(v, iContinue);
-  if( pTabItem->fg.viaCoroutine ){
-    sqlite3VdbeChangeP2(v, addrCounter, regBase+n);
-    testcase( pParse->db->mallocFailed );
-    translateColumnToCopy(pParse, addrTop, pLevel->iTabCur,
-                          pTabItem->regResult, 1);
-    sqlite3VdbeGoto(v, addrTop);
-    pTabItem->fg.viaCoroutine = 0;
-  }else{
-    sqlite3VdbeAddOp2(v, OP_Next, pLevel->iTabCur, addrTop+1); VdbeCoverage(v);
-  }
-  sqlite3VdbeChangeP5(v, SQLITE_STMTSTATUS_AUTOINDEX);
-  sqlite3VdbeJumpHere(v, addrTop);
-  sqlite3ReleaseTempReg(pParse, regRecord);
-  sqlite3ExprCachePop(pParse);
-  
-  /* Jump here when skipping the initialization */
-  sqlite3VdbeJumpHere(v, addrInit);
+  /*
+  ** Record the set of tables that satisfy case 2.  The set might be
+  ** empty.
+  */
+  pOrInfo->indexable = indexable;
+  pTerm->eOperator = indexable==0 ? 0 : WO_OR;
 
-end_auto_index_create:
-  sqlite3ExprDelete(pParse->db, pPartial);
-}
-#endif /* SQLITE_OMIT_AUTOMATIC_INDEX */
+  /*
+  ** chngToIN holds a set of tables that *might* satisfy case 1.  But
+  ** we have to do some additional checking to see if case 1 really
+  ** is satisfied.
+  **
+  ** chngToIN will hold either 0, 1, or 2 bits.  The 0-bit case means
+  ** that there is no possibility of transforming the OR clause into an
+  ** IN operator because one or more terms in the OR clause contain
+  ** something other than == on a column in the single table.  The 1-bit
+  ** case means that every term of the OR clause is of the form
+  ** "table.column=expr" for some single table.  The one bit that is set
+  ** will correspond to the common table.  We still need to check to make
+  ** sure the same column is used on all terms.  The 2-bit case is when
+  ** the all terms are of the form "table1.column=table2.column".  It
+  ** might be possible to form an IN operator with either table1.column
+  ** or table2.column as the LHS if either is common to every term of
+  ** the OR clause.
+  **
+  ** Note that terms of the form "table.column1=table.column2" (the
+  ** same table on both sizes of the ==) cannot be optimized.
+  */
+  if( chngToIN ){
+    int okToChngToIN = 0;     /* True if the conversion to IN is valid */
+    int iColumn = -1;         /* Column index on lhs of IN operator */
+    int iCursor = -1;         /* Table cursor common to all terms */
+    int j = 0;                /* Loop counter */
+
+    /* Search for a table and column that appears on one side or the
+    ** other of the == operator in every subterm.  That table and column
+    ** will be recorded in iCursor and iColumn.  There might not be any
+    ** such table and column.  Set okToChngToIN if an appropriate table
+    ** and column is found but leave okToChngToIN false if not found.
+    */
+    for(j=0; j<2 && !okToChngToIN; j++){
+      pOrTerm = pOrWc->a;
+      for(i=pOrWc->nTerm-1; i>=0; i--, pOrTerm++){
+        assert( pOrTerm->eOperator==WO_EQ );
+        pOrTerm->wtFlags &= ~TERM_OR_OK;
+        if( pOrTerm->leftCursor==iCursor ){
+          /* This is the 2-bit case and we are on the second iteration and
+          ** current term is from the first iteration.  So skip this term. */
+          assert( j==1 );
+          continue;
+        }
+        if( (chngToIN & getMask(pMaskSet, pOrTerm->leftCursor))==0 ){
+          /* This term must be of the form t1.a==t2.b where t2 is in the
+          ** chngToIN set but t1 is not.  This term will be either preceeded
+          ** or follwed by an inverted copy (t2.b==t1.a).  Skip this term 
+          ** and use its inversion. */
+          testcase( pOrTerm->wtFlags & TERM_COPIED );
+          testcase( pOrTerm->wtFlags & TERM_VIRTUAL );
+          assert( pOrTerm->wtFlags & (TERM_COPIED|TERM_VIRTUAL) );
+          continue;
+        }
+        iColumn = pOrTerm->u.leftColumn;
+        iCursor = pOrTerm->leftCursor;
+        break;
+      }
+      if( i<0 ){
+        /* No candidate table+column was found.  This can only occur
+        ** on the second iteration */
+        assert( j==1 );
+        assert( (chngToIN&(chngToIN-1))==0 );
+        assert( chngToIN==getMask(pMaskSet, iCursor) );
+        break;
+      }
+      testcase( j==1 );
 
-#ifndef SQLITE_OMIT_VIRTUALTABLE
-/*
-** Allocate and populate an sqlite3_index_info structure. It is the 
-** responsibility of the caller to eventually release the structure
-** by passing the pointer returned by this function to sqlite3_free().
-*/
-static sqlite3_index_info *allocateIndexInfo(
-  Parse *pParse,
+      /* We have found a candidate table and column.  Check to see if that
+      ** table and column is common to every term in the OR clause */
+      okToChngToIN = 1;
+      for(; i>=0 && okToChngToIN; i--, pOrTerm++){
+        assert( pOrTerm->eOperator==WO_EQ );
+        if( pOrTerm->leftCursor!=iCursor ){
+          pOrTerm->wtFlags &= ~TERM_OR_OK;
+        }else if( pOrTerm->u.leftColumn!=iColumn ){
+          okToChngToIN = 0;
+        }else{
+          int affLeft, affRight;
+          /* If the right-hand side is also a column, then the affinities
+          ** of both right and left sides must be such that no type
+          ** conversions are required on the right.  (Ticket #2249)
+          */
+          affRight = sqlite3ExprAffinity(pOrTerm->pExpr->pRight);
+          affLeft = sqlite3ExprAffinity(pOrTerm->pExpr->pLeft);
+          if( affRight!=0 && affRight!=affLeft ){
+            okToChngToIN = 0;
+          }else{
+            pOrTerm->wtFlags |= TERM_OR_OK;
+          }
+        }
+      }
+    }
+
+    /* At this point, okToChngToIN is true if original pTerm satisfies
+    ** case 1.  In that case, construct a new virtual term that is 
+    ** pTerm converted into an IN operator.
+    */
+    if( okToChngToIN ){
+      Expr *pDup;            /* A transient duplicate expression */
+      ExprList *pList = 0;   /* The RHS of the IN operator */
+      Expr *pLeft = 0;       /* The LHS of the IN operator */
+      Expr *pNew;            /* The complete IN operator */
+
+      for(i=pOrWc->nTerm-1, pOrTerm=pOrWc->a; i>=0; i--, pOrTerm++){
+        if( (pOrTerm->wtFlags & TERM_OR_OK)==0 ) continue;
+        assert( pOrTerm->eOperator==WO_EQ );
+        assert( pOrTerm->leftCursor==iCursor );
+        assert( pOrTerm->u.leftColumn==iColumn );
+        pDup = sqlite3ExprDup(db, pOrTerm->pExpr->pRight, 0);
+        pList = sqlite3ExprListAppend(pWC->pParse, pList, pDup);
+        pLeft = pOrTerm->pExpr->pLeft;
+      }
+      assert( pLeft!=0 );
+      pDup = sqlite3ExprDup(db, pLeft, 0);
+      pNew = sqlite3PExpr(pParse, TK_IN, pDup, 0, 0);
+      if( pNew ){
+        int idxNew;
+        transferJoinMarkings(pNew, pExpr);
+        assert( !ExprHasProperty(pNew, EP_xIsSelect) );
+        pNew->x.pList = pList;
+        idxNew = whereClauseInsert(pWC, pNew, TERM_VIRTUAL|TERM_DYNAMIC);
+        testcase( idxNew==0 );
+        exprAnalyze(pSrc, pWC, idxNew);
+        pTerm = &pWC->a[idxTerm];
+        pWC->a[idxNew].iParent = idxTerm;
+        pTerm->nChild = 1;
+      }else{
+        sqlite3ExprListDelete(db, pList);
+      }
+      pTerm->eOperator = 0;  /* case 1 trumps case 2 */
+    }
+  }
+}
+#endif /* !SQLITE_OMIT_OR_OPTIMIZATION && !SQLITE_OMIT_SUBQUERY */
+
+
+/*
+** The input to this routine is an WhereTerm structure with only the
+** "pExpr" field filled in.  The job of this routine is to analyze the
+** subexpression and populate all the other fields of the WhereTerm
+** structure.
+**
+** If the expression is of the form "<expr> <op> X" it gets commuted
+** to the standard form of "X <op> <expr>".
+**
+** If the expression is of the form "X <op> Y" where both X and Y are
+** columns, then the original expression is unchanged and a new virtual
+** term of the form "Y <op> X" is added to the WHERE clause and
+** analyzed separately.  The original term is marked with TERM_COPIED
+** and the new term is marked with TERM_DYNAMIC (because it's pExpr
+** needs to be freed with the WhereClause) and TERM_VIRTUAL (because it
+** is a commuted copy of a prior term.)  The original term has nChild=1
+** and the copy has idxParent set to the index of the original term.
+*/
+static void exprAnalyze(
+  SrcList *pSrc,            /* the FROM clause */
+  WhereClause *pWC,         /* the WHERE clause */
+  int idxTerm               /* Index of the term to be analyzed */
+){
+  WhereTerm *pTerm;                /* The term to be analyzed */
+  WhereMaskSet *pMaskSet;          /* Set of table index masks */
+  Expr *pExpr;                     /* The expression to be analyzed */
+  Bitmask prereqLeft;              /* Prerequesites of the pExpr->pLeft */
+  Bitmask prereqAll;               /* Prerequesites of pExpr */
+  Bitmask extraRight = 0;
+  int nPattern;
+  int isComplete;
+  int noCase;
+  int op;                          /* Top-level operator.  pExpr->op */
+  Parse *pParse = pWC->pParse;     /* Parsing context */
+  sqlite3 *db = pParse->db;        /* Database connection */
+
+  if( db->mallocFailed ){
+    return;
+  }
+  pTerm = &pWC->a[idxTerm];
+  pMaskSet = pWC->pMaskSet;
+  pExpr = pTerm->pExpr;
+  prereqLeft = exprTableUsage(pMaskSet, pExpr->pLeft);
+  op = pExpr->op;
+  if( op==TK_IN ){
+    assert( pExpr->pRight==0 );
+    if( ExprHasProperty(pExpr, EP_xIsSelect) ){
+      pTerm->prereqRight = exprSelectTableUsage(pMaskSet, pExpr->x.pSelect);
+    }else{
+      pTerm->prereqRight = exprListTableUsage(pMaskSet, pExpr->x.pList);
+    }
+  }else if( op==TK_ISNULL ){
+    pTerm->prereqRight = 0;
+  }else{
+    pTerm->prereqRight = exprTableUsage(pMaskSet, pExpr->pRight);
+  }
+  prereqAll = exprTableUsage(pMaskSet, pExpr);
+  if( ExprHasProperty(pExpr, EP_FromJoin) ){
+    Bitmask x = getMask(pMaskSet, pExpr->iRightJoinTable);
+    prereqAll |= x;
+    extraRight = x-1;  /* ON clause terms may not be used with an index
+                       ** on left table of a LEFT JOIN.  Ticket #3015 */
+  }
+  pTerm->prereqAll = prereqAll;
+  pTerm->leftCursor = -1;
+  pTerm->iParent = -1;
+  pTerm->eOperator = 0;
+  if( allowedOp(op) && (pTerm->prereqRight & prereqLeft)==0 ){
+    Expr *pLeft = pExpr->pLeft;
+    Expr *pRight = pExpr->pRight;
+    if( pLeft->op==TK_COLUMN ){
+      pTerm->leftCursor = pLeft->iTable;
+      pTerm->u.leftColumn = pLeft->iColumn;
+      pTerm->eOperator = operatorMask(op);
+    }
+    if( pRight && pRight->op==TK_COLUMN ){
+      WhereTerm *pNew;
+      Expr *pDup;
+      if( pTerm->leftCursor>=0 ){
+        int idxNew;
+        pDup = sqlite3ExprDup(db, pExpr, 0);
+        if( db->mallocFailed ){
+          sqlite3ExprDelete(db, pDup);
+          return;
+        }
+        idxNew = whereClauseInsert(pWC, pDup, TERM_VIRTUAL|TERM_DYNAMIC);
+        if( idxNew==0 ) return;
+        pNew = &pWC->a[idxNew];
+        pNew->iParent = idxTerm;
+        pTerm = &pWC->a[idxTerm];
+        pTerm->nChild = 1;
+        pTerm->wtFlags |= TERM_COPIED;
+      }else{
+        pDup = pExpr;
+        pNew = pTerm;
+      }
+      exprCommute(pParse, pDup);
+      pLeft = pDup->pLeft;
+      pNew->leftCursor = pLeft->iTable;
+      pNew->u.leftColumn = pLeft->iColumn;
+      pNew->prereqRight = prereqLeft;
+      pNew->prereqAll = prereqAll;
+      pNew->eOperator = operatorMask(pDup->op);
+    }
+  }
+
+#ifndef SQLITE_OMIT_BETWEEN_OPTIMIZATION
+  /* If a term is the BETWEEN operator, create two new virtual terms
+  ** that define the range that the BETWEEN implements.  For example:
+  **
+  **      a BETWEEN b AND c
+  **
+  ** is converted into:
+  **
+  **      (a BETWEEN b AND c) AND (a>=b) AND (a<=c)
+  **
+  ** The two new terms are added onto the end of the WhereClause object.
+  ** The new terms are "dynamic" and are children of the original BETWEEN
+  ** term.  That means that if the BETWEEN term is coded, the children are
+  ** skipped.  Or, if the children are satisfied by an index, the original
+  ** BETWEEN term is skipped.
+  */
+  else if( pExpr->op==TK_BETWEEN && pWC->op==TK_AND ){
+    ExprList *pList = pExpr->x.pList;
+    int i;
+    static const u8 ops[] = {TK_GE, TK_LE};
+    assert( pList!=0 );
+    assert( pList->nExpr==2 );
+    for(i=0; i<2; i++){
+      Expr *pNewExpr;
+      int idxNew;
+      pNewExpr = sqlite3PExpr(pParse, ops[i], 
+                             sqlite3ExprDup(db, pExpr->pLeft, 0),
+                             sqlite3ExprDup(db, pList->a[i].pExpr, 0), 0);
+      idxNew = whereClauseInsert(pWC, pNewExpr, TERM_VIRTUAL|TERM_DYNAMIC);
+      testcase( idxNew==0 );
+      exprAnalyze(pSrc, pWC, idxNew);
+      pTerm = &pWC->a[idxTerm];
+      pWC->a[idxNew].iParent = idxTerm;
+    }
+    pTerm->nChild = 2;
+  }
+#endif /* SQLITE_OMIT_BETWEEN_OPTIMIZATION */
+
+#if !defined(SQLITE_OMIT_OR_OPTIMIZATION) && !defined(SQLITE_OMIT_SUBQUERY)
+  /* Analyze a term that is composed of two or more subterms connected by
+  ** an OR operator.
+  */
+  else if( pExpr->op==TK_OR ){
+    assert( pWC->op==TK_AND );
+    exprAnalyzeOrTerm(pSrc, pWC, idxTerm);
+  }
+#endif /* SQLITE_OMIT_OR_OPTIMIZATION */
+
+#ifndef SQLITE_OMIT_LIKE_OPTIMIZATION
+  /* Add constraints to reduce the search space on a LIKE or GLOB
+  ** operator.
+  **
+  ** A like pattern of the form "x LIKE 'abc%'" is changed into constraints
+  **
+  **          x>='abc' AND x<'abd' AND x LIKE 'abc%'
+  **
+  ** The last character of the prefix "abc" is incremented to form the
+  ** termination condition "abd".
+  */
+  if( isLikeOrGlob(pParse, pExpr, &nPattern, &isComplete, &noCase)
+         && pWC->op==TK_AND ){
+    Expr *pLeft, *pRight;
+    Expr *pStr1, *pStr2;
+    Expr *pNewExpr1, *pNewExpr2;
+    int idxNew1, idxNew2;
+
+    pLeft = pExpr->x.pList->a[1].pExpr;
+    pRight = pExpr->x.pList->a[0].pExpr;
+    pStr1 = sqlite3Expr(db, TK_STRING, pRight->u.zToken);
+    if( pStr1 ) pStr1->u.zToken[nPattern] = 0;
+    pStr2 = sqlite3ExprDup(db, pStr1, 0);
+    if( !db->mallocFailed ){
+      u8 c, *pC;       /* Last character before the first wildcard */
+      pC = (u8*)&pStr2->u.zToken[nPattern-1];
+      c = *pC;
+      if( noCase ){
+        /* The point is to increment the last character before the first
+        ** wildcard.  But if we increment '@', that will push it into the
+        ** alphabetic range where case conversions will mess up the 
+        ** inequality.  To avoid this, make sure to also run the full
+        ** LIKE on all candidate expressions by clearing the isComplete flag
+        */
+        if( c=='A'-1 ) isComplete = 0;
+
+        c = sqlite3UpperToLower[c];
+      }
+      *pC = c + 1;
+    }
+    pNewExpr1 = sqlite3PExpr(pParse, TK_GE, sqlite3ExprDup(db,pLeft,0),pStr1,0);
+    idxNew1 = whereClauseInsert(pWC, pNewExpr1, TERM_VIRTUAL|TERM_DYNAMIC);
+    testcase( idxNew1==0 );
+    exprAnalyze(pSrc, pWC, idxNew1);
+    pNewExpr2 = sqlite3PExpr(pParse, TK_LT, sqlite3ExprDup(db,pLeft,0),pStr2,0);
+    idxNew2 = whereClauseInsert(pWC, pNewExpr2, TERM_VIRTUAL|TERM_DYNAMIC);
+    testcase( idxNew2==0 );
+    exprAnalyze(pSrc, pWC, idxNew2);
+    pTerm = &pWC->a[idxTerm];
+    if( isComplete ){
+      pWC->a[idxNew1].iParent = idxTerm;
+      pWC->a[idxNew2].iParent = idxTerm;
+      pTerm->nChild = 2;
+    }
+  }
+#endif /* SQLITE_OMIT_LIKE_OPTIMIZATION */
+
+#ifndef SQLITE_OMIT_VIRTUALTABLE
+  /* Add a WO_MATCH auxiliary term to the constraint set if the
+  ** current expression is of the form:  column MATCH expr.
+  ** This information is used by the xBestIndex methods of
+  ** virtual tables.  The native query optimizer does not attempt
+  ** to do anything with MATCH functions.
+  */
+  if( isMatchOfColumn(pExpr) ){
+    int idxNew;
+    Expr *pRight, *pLeft;
+    WhereTerm *pNewTerm;
+    Bitmask prereqColumn, prereqExpr;
+
+    pRight = pExpr->x.pList->a[0].pExpr;
+    pLeft = pExpr->x.pList->a[1].pExpr;
+    prereqExpr = exprTableUsage(pMaskSet, pRight);
+    prereqColumn = exprTableUsage(pMaskSet, pLeft);
+    if( (prereqExpr & prereqColumn)==0 ){
+      Expr *pNewExpr;
+      pNewExpr = sqlite3PExpr(pParse, TK_MATCH, 
+                              0, sqlite3ExprDup(db, pRight, 0), 0);
+      idxNew = whereClauseInsert(pWC, pNewExpr, TERM_VIRTUAL|TERM_DYNAMIC);
+      testcase( idxNew==0 );
+      pNewTerm = &pWC->a[idxNew];
+      pNewTerm->prereqRight = prereqExpr;
+      pNewTerm->leftCursor = pLeft->iTable;
+      pNewTerm->u.leftColumn = pLeft->iColumn;
+      pNewTerm->eOperator = WO_MATCH;
+      pNewTerm->iParent = idxTerm;
+      pTerm = &pWC->a[idxTerm];
+      pTerm->nChild = 1;
+      pTerm->wtFlags |= TERM_COPIED;
+      pNewTerm->prereqAll = pTerm->prereqAll;
+    }
+  }
+#endif /* SQLITE_OMIT_VIRTUALTABLE */
+
+  /* Prevent ON clause terms of a LEFT JOIN from being used to drive
+  ** an index for tables to the left of the join.
+  */
+  pTerm->prereqRight |= extraRight;
+}
+
+/*
+** Return TRUE if any of the expressions in pList->a[iFirst...] contain
+** a reference to any table other than the iBase table.
+*/
+static int referencesOtherTables(
+  ExprList *pList,          /* Search expressions in ths list */
+  WhereMaskSet *pMaskSet,   /* Mapping from tables to bitmaps */
+  int iFirst,               /* Be searching with the iFirst-th expression */
+  int iBase                 /* Ignore references to this table */
+){
+  Bitmask allowed = ~getMask(pMaskSet, iBase);
+  while( iFirst<pList->nExpr ){
+    if( (exprTableUsage(pMaskSet, pList->a[iFirst++].pExpr)&allowed)!=0 ){
+      return 1;
+    }
+  }
+  return 0;
+}
+
+
+/*
+** This routine decides if pIdx can be used to satisfy the ORDER BY
+** clause.  If it can, it returns 1.  If pIdx cannot satisfy the
+** ORDER BY clause, this routine returns 0.
+**
+** pOrderBy is an ORDER BY clause from a SELECT statement.  pTab is the
+** left-most table in the FROM clause of that same SELECT statement and
+** the table has a cursor number of "base".  pIdx is an index on pTab.
+**
+** nEqCol is the number of columns of pIdx that are used as equality
+** constraints.  Any of these columns may be missing from the ORDER BY
+** clause and the match can still be a success.
+**
+** All terms of the ORDER BY that match against the index must be either
+** ASC or DESC.  (Terms of the ORDER BY clause past the end of a UNIQUE
+** index do not need to satisfy this constraint.)  The *pbRev value is
+** set to 1 if the ORDER BY clause is all DESC and it is set to 0 if
+** the ORDER BY clause is all ASC.
+*/
+static int isSortingIndex(
+  Parse *pParse,          /* Parsing context */
+  WhereMaskSet *pMaskSet, /* Mapping from table cursor numbers to bitmaps */
+  Index *pIdx,            /* The index we are testing */
+  int base,               /* Cursor number for the table to be sorted */
+  ExprList *pOrderBy,     /* The ORDER BY clause */
+  int nEqCol,             /* Number of index columns with == constraints */
+  int *pbRev              /* Set to 1 if ORDER BY is DESC */
+){
+  int i, j;                       /* Loop counters */
+  int sortOrder = 0;              /* XOR of index and ORDER BY sort direction */
+  int nTerm;                      /* Number of ORDER BY terms */
+  struct ExprList_item *pTerm;    /* A term of the ORDER BY clause */
+  sqlite3 *db = pParse->db;
+
+  assert( pOrderBy!=0 );
+  nTerm = pOrderBy->nExpr;
+  assert( nTerm>0 );
+
+  /* Match terms of the ORDER BY clause against columns of
+  ** the index.
+  **
+  ** Note that indices have pIdx->nColumn regular columns plus
+  ** one additional column containing the rowid.  The rowid column
+  ** of the index is also allowed to match against the ORDER BY
+  ** clause.
+  */
+  for(i=j=0, pTerm=pOrderBy->a; j<nTerm && i<=pIdx->nColumn; i++){
+    Expr *pExpr;       /* The expression of the ORDER BY pTerm */
+    CollSeq *pColl;    /* The collating sequence of pExpr */
+    int termSortOrder; /* Sort order for this term */
+    int iColumn;       /* The i-th column of the index.  -1 for rowid */
+    int iSortOrder;    /* 1 for DESC, 0 for ASC on the i-th index term */
+    const char *zColl; /* Name of the collating sequence for i-th index term */
+
+    pExpr = pTerm->pExpr;
+    if( pExpr->op!=TK_COLUMN || pExpr->iTable!=base ){
+      /* Can not use an index sort on anything that is not a column in the
+      ** left-most table of the FROM clause */
+      break;
+    }
+    pColl = sqlite3ExprCollSeq(pParse, pExpr);
+    if( !pColl ){
+      pColl = db->pDfltColl;
+    }
+    if( i<pIdx->nColumn ){
+      iColumn = pIdx->aiColumn[i];
+      if( iColumn==pIdx->pTable->iPKey ){
+        iColumn = -1;
+      }
+      iSortOrder = pIdx->aSortOrder[i];
+      zColl = pIdx->azColl[i];
+    }else{
+      iColumn = -1;
+      iSortOrder = 0;
+      zColl = pColl->zName;
+    }
+    if( pExpr->iColumn!=iColumn || sqlite3StrICmp(pColl->zName, zColl) ){
+      /* Term j of the ORDER BY clause does not match column i of the index */
+      if( i<nEqCol ){
+        /* If an index column that is constrained by == fails to match an
+        ** ORDER BY term, that is OK.  Just ignore that column of the index
+        */
+        continue;
+      }else if( i==pIdx->nColumn ){
+        /* Index column i is the rowid.  All other terms match. */
+        break;
+      }else{
+        /* If an index column fails to match and is not constrained by ==
+        ** then the index cannot satisfy the ORDER BY constraint.
+        */
+        return 0;
+      }
+    }
+    assert( pIdx->aSortOrder!=0 );
+    assert( pTerm->sortOrder==0 || pTerm->sortOrder==1 );
+    assert( iSortOrder==0 || iSortOrder==1 );
+    termSortOrder = iSortOrder ^ pTerm->sortOrder;
+    if( i>nEqCol ){
+      if( termSortOrder!=sortOrder ){
+        /* Indices can only be used if all ORDER BY terms past the
+        ** equality constraints are all either DESC or ASC. */
+        return 0;
+      }
+    }else{
+      sortOrder = termSortOrder;
+    }
+    j++;
+    pTerm++;
+    if( iColumn<0 && !referencesOtherTables(pOrderBy, pMaskSet, j, base) ){
+      /* If the indexed column is the primary key and everything matches
+      ** so far and none of the ORDER BY terms to the right reference other
+      ** tables in the join, then we are assured that the index can be used 
+      ** to sort because the primary key is unique and so none of the other
+      ** columns will make any difference
+      */
+      j = nTerm;
+    }
+  }
+
+  *pbRev = sortOrder!=0;
+  if( j>=nTerm ){
+    /* All terms of the ORDER BY clause are covered by this index so
+    ** this index can be used for sorting. */
+    return 1;
+  }
+  if( pIdx->onError!=OE_None && i==pIdx->nColumn
+      && !referencesOtherTables(pOrderBy, pMaskSet, j, base) ){
+    /* All terms of this index match some prefix of the ORDER BY clause
+    ** and the index is UNIQUE and no terms on the tail of the ORDER BY
+    ** clause reference other tables in a join.  If this is all true then
+    ** the order by clause is superfluous. */
+    return 1;
+  }
+  return 0;
+}
+
+/*
+** Check table to see if the ORDER BY clause in pOrderBy can be satisfied
+** by sorting in order of ROWID.  Return true if so and set *pbRev to be
+** true for reverse ROWID and false for forward ROWID order.
+*/
+static int sortableByRowid(
+  int base,               /* Cursor number for table to be sorted */
+  ExprList *pOrderBy,     /* The ORDER BY clause */
+  WhereMaskSet *pMaskSet, /* Mapping from table cursors to bitmaps */
+  int *pbRev              /* Set to 1 if ORDER BY is DESC */
+){
+  Expr *p;
+
+  assert( pOrderBy!=0 );
+  assert( pOrderBy->nExpr>0 );
+  p = pOrderBy->a[0].pExpr;
+  if( p->op==TK_COLUMN && p->iTable==base && p->iColumn==-1
+    && !referencesOtherTables(pOrderBy, pMaskSet, 1, base) ){
+    *pbRev = pOrderBy->a[0].sortOrder;
+    return 1;
+  }
+  return 0;
+}
+
+/*
+** Prepare a crude estimate of the logarithm of the input value.
+** The results need not be exact.  This is only used for estimating
+** the total cost of performing operations with O(logN) or O(NlogN)
+** complexity.  Because N is just a guess, it is no great tragedy if
+** logN is a little off.
+*/
+static double estLog(double N){
+  double logN = 1;
+  double x = 10;
+  while( N>x ){
+    logN += 1;
+    x *= 10;
+  }
+  return logN;
+}
+
+/*
+** Two routines for printing the content of an sqlite3_index_info
+** structure.  Used for testing and debugging only.  If neither
+** SQLITE_TEST or SQLITE_DEBUG are defined, then these routines
+** are no-ops.
+*/
+#if !defined(SQLITE_OMIT_VIRTUALTABLE) && defined(SQLITE_DEBUG)
+static void TRACE_IDX_INPUTS(sqlite3_index_info *p){
+  int i;
+  if( !sqlite3WhereTrace ) return;
+  for(i=0; i<p->nConstraint; i++){
+    sqlite3DebugPrintf("  constraint[%d]: col=%d termid=%d op=%d usabled=%d\n",
+       i,
+       p->aConstraint[i].iColumn,
+       p->aConstraint[i].iTermOffset,
+       p->aConstraint[i].op,
+       p->aConstraint[i].usable);
+  }
+  for(i=0; i<p->nOrderBy; i++){
+    sqlite3DebugPrintf("  orderby[%d]: col=%d desc=%d\n",
+       i,
+       p->aOrderBy[i].iColumn,
+       p->aOrderBy[i].desc);
+  }
+}
+static void TRACE_IDX_OUTPUTS(sqlite3_index_info *p){
+  int i;
+  if( !sqlite3WhereTrace ) return;
+  for(i=0; i<p->nConstraint; i++){
+    sqlite3DebugPrintf("  usage[%d]: argvIdx=%d omit=%d\n",
+       i,
+       p->aConstraintUsage[i].argvIndex,
+       p->aConstraintUsage[i].omit);
+  }
+  sqlite3DebugPrintf("  idxNum=%d\n", p->idxNum);
+  sqlite3DebugPrintf("  idxStr=%s\n", p->idxStr);
+  sqlite3DebugPrintf("  orderByConsumed=%d\n", p->orderByConsumed);
+  sqlite3DebugPrintf("  estimatedCost=%g\n", p->estimatedCost);
+}
+#else
+#define TRACE_IDX_INPUTS(A)
+#define TRACE_IDX_OUTPUTS(A)
+#endif
+
+/* 
+** Required because bestIndex() is called by bestOrClauseIndex() 
+*/
+static void bestIndex(
+    Parse*, WhereClause*, struct SrcList_item*, Bitmask, ExprList*, WhereCost*);
+
+/*
+** This routine attempts to find an scanning strategy that can be used 
+** to optimize an 'OR' expression that is part of a WHERE clause. 
+**
+** The table associated with FROM clause term pSrc may be either a
+** regular B-Tree table or a virtual table.
+*/
+static void bestOrClauseIndex(
+  Parse *pParse,              /* The parsing context */
+  WhereClause *pWC,           /* The WHERE clause */
+  struct SrcList_item *pSrc,  /* The FROM clause term to search */
+  Bitmask notReady,           /* Mask of cursors that are not available */
+  ExprList *pOrderBy,         /* The ORDER BY clause */
+  WhereCost *pCost            /* Lowest cost query plan */
+){
+#ifndef SQLITE_OMIT_OR_OPTIMIZATION
+  const int iCur = pSrc->iCursor;   /* The cursor of the table to be accessed */
+  const Bitmask maskSrc = getMask(pWC->pMaskSet, iCur);  /* Bitmask for pSrc */
+  WhereTerm * const pWCEnd = &pWC->a[pWC->nTerm];        /* End of pWC->a[] */
+  WhereTerm *pTerm;                 /* A single term of the WHERE clause */
+
+  /* Search the WHERE clause terms for a usable WO_OR term. */
+  for(pTerm=pWC->a; pTerm<pWCEnd; pTerm++){
+    if( pTerm->eOperator==WO_OR 
+     && ((pTerm->prereqAll & ~maskSrc) & notReady)==0
+     && (pTerm->u.pOrInfo->indexable & maskSrc)!=0 
+    ){
+      WhereClause * const pOrWC = &pTerm->u.pOrInfo->wc;
+      WhereTerm * const pOrWCEnd = &pOrWC->a[pOrWC->nTerm];
+      WhereTerm *pOrTerm;
+      int flags = WHERE_MULTI_OR;
+      double rTotal = 0;
+      double nRow = 0;
+
+      for(pOrTerm=pOrWC->a; pOrTerm<pOrWCEnd; pOrTerm++){
+        WhereCost sTermCost;
+        WHERETRACE(("... Multi-index OR testing for term %d of %d....\n", 
+          (pOrTerm - pOrWC->a), (pTerm - pWC->a)
+        ));
+        if( pOrTerm->eOperator==WO_AND ){
+          WhereClause *pAndWC = &pOrTerm->u.pAndInfo->wc;
+          bestIndex(pParse, pAndWC, pSrc, notReady, 0, &sTermCost);
+        }else if( pOrTerm->leftCursor==iCur ){
+          WhereClause tempWC;
+          tempWC.pParse = pWC->pParse;
+          tempWC.pMaskSet = pWC->pMaskSet;
+          tempWC.op = TK_AND;
+          tempWC.a = pOrTerm;
+          tempWC.nTerm = 1;
+          bestIndex(pParse, &tempWC, pSrc, notReady, 0, &sTermCost);
+        }else{
+          continue;
+        }
+        rTotal += sTermCost.rCost;
+        nRow += sTermCost.nRow;
+        if( rTotal>=pCost->rCost ) break;
+      }
+
+      /* If there is an ORDER BY clause, increase the scan cost to account 
+      ** for the cost of the sort. */
+      if( pOrderBy!=0 ){
+        rTotal += nRow*estLog(nRow);
+        WHERETRACE(("... sorting increases OR cost to %.9g\n", rTotal));
+      }
+
+      /* If the cost of scanning using this OR term for optimization is
+      ** less than the current cost stored in pCost, replace the contents
+      ** of pCost. */
+      WHERETRACE(("... multi-index OR cost=%.9g nrow=%.9g\n", rTotal, nRow));
+      if( rTotal<pCost->rCost ){
+        pCost->rCost = rTotal;
+        pCost->nRow = nRow;
+        pCost->plan.wsFlags = flags;
+        pCost->plan.u.pTerm = pTerm;
+      }
+    }
+  }
+#endif /* SQLITE_OMIT_OR_OPTIMIZATION */
+}
+
+#ifndef SQLITE_OMIT_VIRTUALTABLE
+/*
+** Allocate and populate an sqlite3_index_info structure. It is the 
+** responsibility of the caller to eventually release the structure
+** by passing the pointer returned by this function to sqlite3_free().
+*/
+static sqlite3_index_info *allocateIndexInfo(
+  Parse *pParse, 
   WhereClause *pWC,
-  Bitmask mUnusable,              /* Ignore terms with these prereqs */
   struct SrcList_item *pSrc,
-  ExprList *pOrderBy,
-  u16 *pmNoOmit                   /* Mask of terms not to omit */
+  ExprList *pOrderBy
 ){
   int i, j;
   int nTerm;
   struct sqlite3_index_constraint *pIdxCons;
   struct sqlite3_index_orderby *pIdxOrderBy;
   struct sqlite3_index_constraint_usage *pUsage;
   WhereTerm *pTerm;
   int nOrderBy;
   sqlite3_index_info *pIdxInfo;
-  u16 mNoOmit = 0;
+
+  WHERETRACE(("Recomputing index info for %s...\n", pSrc->pTab->zName));
 
   /* Count the number of possible WHERE clause constraints referring
   ** to this virtual table */
   for(i=nTerm=0, pTerm=pWC->a; i<pWC->nTerm; i++, pTerm++){
     if( pTerm->leftCursor != pSrc->iCursor ) continue;
-    if( pTerm->prereqRight & mUnusable ) continue;
-    assert( IsPowerOfTwo(pTerm->eOperator & ~WO_EQUIV) );
-    testcase( pTerm->eOperator & WO_IN );
-    testcase( pTerm->eOperator & WO_ISNULL );
-    testcase( pTerm->eOperator & WO_IS );
-    testcase( pTerm->eOperator & WO_ALL );
-    if( (pTerm->eOperator & ~(WO_EQUIV))==0 ) continue;
-    if( pTerm->wtFlags & TERM_VNULL ) continue;
-    assert( pTerm->u.leftColumn>=(-1) );
+    assert( (pTerm->eOperator&(pTerm->eOperator-1))==0 );
+    testcase( pTerm->eOperator==WO_IN );
+    testcase( pTerm->eOperator==WO_ISNULL );
+    if( pTerm->eOperator & (WO_IN|WO_ISNULL) ) continue;
     nTerm++;
   }
 
   /* If the ORDER BY clause contains only columns in the current 
   ** virtual table then allocate space for the aOrderBy part of
   ** the sqlite3_index_info structure.
   */
   nOrderBy = 0;
   if( pOrderBy ){
-    int n = pOrderBy->nExpr;
-    for(i=0; i<n; i++){
+    for(i=0; i<pOrderBy->nExpr; i++){
       Expr *pExpr = pOrderBy->a[i].pExpr;
       if( pExpr->op!=TK_COLUMN || pExpr->iTable!=pSrc->iCursor ) break;
     }
-    if( i==n){
-      nOrderBy = n;
+    if( i==pOrderBy->nExpr ){
+      nOrderBy = pOrderBy->nExpr;
     }
   }
 
   /* Allocate the sqlite3_index_info structure
   */
   pIdxInfo = sqlite3DbMallocZero(pParse->db, sizeof(*pIdxInfo)
                            + (sizeof(*pIdxCons) + sizeof(*pUsage))*nTerm
                            + sizeof(*pIdxOrderBy)*nOrderBy );
   if( pIdxInfo==0 ){
     sqlite3ErrorMsg(pParse, "out of memory");
+    /* (double)0 In case of SQLITE_OMIT_FLOATING_POINT... */
     return 0;
   }
 
   /* Initialize the structure.  The sqlite3_index_info structure contains
   ** many fields that are declared "const" to prevent xBestIndex from
   ** changing them.  We have to do some funky casting in order to
