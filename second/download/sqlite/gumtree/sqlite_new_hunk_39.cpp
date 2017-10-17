  if( p->pWhere ) return 0;              /* Has no WHERE clause */
  pSrc = p->pSrc;
  assert( pSrc!=0 );
  if( pSrc->nSrc!=1 ) return 0;          /* Single term in FROM clause */
  if( pSrc->a[0].pSelect ) return 0;     /* FROM is not a subquery or view */
  pTab = pSrc->a[0].pTab;
  if( NEVER(pTab==0) ) return 0;
  assert( pTab->pSelect==0 );            /* FROM clause is not a view */
  if( IsVirtual(pTab) ) return 0;        /* FROM clause not a virtual table */
  pEList = p->pEList;
  if( pEList->nExpr!=1 ) return 0;       /* One column in the result set */
  if( pEList->a[0].pExpr->op!=TK_COLUMN ) return 0; /* Result is a column */
  return 1;
}
#endif /* SQLITE_OMIT_SUBQUERY */

/*
** This function is used by the implementation of the IN (...) operator.
** It's job is to find or create a b-tree structure that may be used
** either to test for membership of the (...) set or to iterate through
** its members, skipping duplicates.
**
** The index of the cursor opened on the b-tree (database table, database index 
** or ephermal table) is stored in pX->iTable before this function returns.
** The returned value of this function indicates the b-tree type, as follows:
**
**   IN_INDEX_ROWID - The cursor was opened on a database table.
**   IN_INDEX_INDEX - The cursor was opened on a database index.
**   IN_INDEX_EPH -   The cursor was opened on a specially created and
**                    populated epheremal table.
**
** An existing b-tree may only be used if the SELECT is of the simple
** form:
**
**     SELECT <column> FROM <table>
**
** If the prNotFound parameter is 0, then the b-tree will be used to iterate
** through the set members, skipping any duplicates. In this case an
** epheremal table must be used unless the selected <column> is guaranteed
** to be unique - either because it is an INTEGER PRIMARY KEY or it
** has a UNIQUE constraint or UNIQUE index.
**
** If the prNotFound parameter is not 0, then the b-tree will be used 
** for fast set membership tests. In this case an epheremal table must 
** be used unless <column> is an INTEGER PRIMARY KEY or an index can 
** be found with <column> as its left-most column.
**
** When the b-tree is being used for membership tests, the calling function
** needs to know whether or not the structure contains an SQL NULL 
** value in order to correctly evaluate expressions like "X IN (Y, Z)".
** If there is a chance that the b-tree might contain a NULL value at
** runtime, then a register is allocated and the register number written
** to *prNotFound. If there is no chance that the b-tree contains a
** NULL value, then *prNotFound is left unchanged.
**
** If a register is allocated and its location stored in *prNotFound, then
** its initial value is NULL. If the b-tree does not remain constant
** for the duration of the query (i.e. the SELECT that generates the b-tree
** is a correlated subquery) then the value of the allocated register is
** reset to NULL each time the b-tree is repopulated. This allows the
** caller to use vdbe code equivalent to the following:
**
**   if( register==NULL ){
**     has_null = <test if data structure contains null>
**     register = 1
**   }
**
** in order to avoid running the <test if data structure contains null>
** test more often than is necessary.
*/
#ifndef SQLITE_OMIT_SUBQUERY
int sqlite3FindInIndex(Parse *pParse, Expr *pX, int *prNotFound){
  Select *p;                            /* SELECT to the right of IN operator */
  int eType = 0;                        /* Type of RHS table. IN_INDEX_* */
  int iTab = pParse->nTab++;            /* Cursor of the RHS table */
  int mustBeUnique = (prNotFound==0);   /* True if RHS must be unique */

  /* Check to see if an existing table or index can be used to
  ** satisfy the query.  This is preferable to generating a new 
  ** ephemeral table.
  */
  p = (ExprHasProperty(pX, EP_xIsSelect) ? pX->x.pSelect : 0);
  if( ALWAYS(pParse->nErr==0) && isCandidateForInOpt(p) ){
    sqlite3 *db = pParse->db;              /* Database connection */
    Expr *pExpr = p->pEList->a[0].pExpr;   /* Expression <column> */
    int iCol = pExpr->iColumn;             /* Index of column <column> */
    Vdbe *v = sqlite3GetVdbe(pParse);      /* Virtual machine being coded */
    Table *pTab = p->pSrc->a[0].pTab;      /* Table <table>. */
    int iDb;                               /* Database idx for pTab */
   
    /* Code an OP_VerifyCookie and OP_TableLock for <table>. */
    iDb = sqlite3SchemaToIndex(db, pTab->pSchema);
    sqlite3CodeVerifySchema(pParse, iDb);
    sqlite3TableLock(pParse, iDb, pTab->tnum, 0, pTab->zName);

    /* This function is only called from two places. In both cases the vdbe
    ** has already been allocated. So assume sqlite3GetVdbe() is always
    ** successful here.
    */
    assert(v);
    if( iCol<0 ){
      int iMem = ++pParse->nMem;
      int iAddr;
      sqlite3VdbeUsesBtree(v, iDb);

      iAddr = sqlite3VdbeAddOp1(v, OP_If, iMem);
      sqlite3VdbeAddOp2(v, OP_Integer, 1, iMem);

      sqlite3OpenTable(pParse, iTab, iDb, pTab, OP_OpenRead);
      eType = IN_INDEX_ROWID;

      sqlite3VdbeJumpHere(v, iAddr);
    }else{
      Index *pIdx;                         /* Iterator variable */

      /* The collation sequence used by the comparison. If an index is to
      ** be used in place of a temp-table, it must be ordered according
      ** to this collation sequence.  */
      CollSeq *pReq = sqlite3BinaryCompareCollSeq(pParse, pX->pLeft, pExpr);

      /* Check that the affinity that will be used to perform the 
      ** comparison is the same as the affinity of the column. If
      ** it is not, it is not possible to use any index.
      */
      char aff = comparisonAffinity(pX);
      int affinity_ok = (pTab->aCol[iCol].affinity==aff||aff==SQLITE_AFF_NONE);

      for(pIdx=pTab->pIndex; pIdx && eType==0 && affinity_ok; pIdx=pIdx->pNext){
        if( (pIdx->aiColumn[0]==iCol)
         && sqlite3FindCollSeq(db, ENC(db), pIdx->azColl[0], 0)==pReq
         && (!mustBeUnique || (pIdx->nColumn==1 && pIdx->onError!=OE_None))
        ){
          int iMem = ++pParse->nMem;
          int iAddr;
          char *pKey;
  
          pKey = (char *)sqlite3IndexKeyinfo(pParse, pIdx);
          iDb = sqlite3SchemaToIndex(db, pIdx->pSchema);
          sqlite3VdbeUsesBtree(v, iDb);

          iAddr = sqlite3VdbeAddOp1(v, OP_If, iMem);
          sqlite3VdbeAddOp2(v, OP_Integer, 1, iMem);
  
          sqlite3VdbeAddOp4(v, OP_OpenRead, iTab, pIdx->tnum, iDb,
                               pKey,P4_KEYINFO_HANDOFF);
          VdbeComment((v, "%s", pIdx->zName));
          eType = IN_INDEX_INDEX;

          sqlite3VdbeJumpHere(v, iAddr);
          if( prNotFound && !pTab->aCol[iCol].notNull ){
            *prNotFound = ++pParse->nMem;
          }
        }
      }
    }
  }

  if( eType==0 ){
    /* Could not found an existing able or index to use as the RHS b-tree.
    ** We will have to generate an ephemeral table to do the job.
    */
    int rMayHaveNull = 0;
    eType = IN_INDEX_EPH;
    if( prNotFound ){
      *prNotFound = rMayHaveNull = ++pParse->nMem;
    }else if( pX->pLeft->iColumn<0 && !ExprHasAnyProperty(pX, EP_xIsSelect) ){
      eType = IN_INDEX_ROWID;
    }
    sqlite3CodeSubselect(pParse, pX, rMayHaveNull, eType==IN_INDEX_ROWID);
  }else{
    pX->iTable = iTab;
  }
  return eType;
}
#endif

/*
** Generate code for scalar subqueries used as an expression
** and IN operators.  Examples:
**
**     (SELECT a FROM b)          -- subquery
**     EXISTS (SELECT a FROM b)   -- EXISTS subquery
**     x IN (4,5,11)              -- IN operator with list on right-hand side
**     x IN (SELECT a FROM b)     -- IN operator with subquery on the right
**
