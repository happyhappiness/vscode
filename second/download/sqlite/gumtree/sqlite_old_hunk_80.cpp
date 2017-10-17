  /* Clean up and return
  */
  sqlite3ExprDelete(db, pExpr->pLeft);
  pExpr->pLeft = 0;
  sqlite3ExprDelete(db, pExpr->pRight);
  pExpr->pRight = 0;
  pExpr->op = (isTrigger ? TK_TRIGGER : TK_COLUMN);
  ExprSetProperty(pExpr, EP_Leaf);
lookupname_end:
  if( cnt==1 ){
    assert( pNC!=0 );
    if( !ExprHasProperty(pExpr, EP_Alias) ){
      sqlite3AuthRead(pParse, pExpr, pSchema, pNC->pSrcList);
    }
    /* Increment the nRef value on all name contexts from TopNC up to
    ** the point where the name matched. */
    for(;;){
      assert( pTopNC!=0 );
      pTopNC->nRef++;
      if( pTopNC==pNC ) break;
      pTopNC = pTopNC->pNext;
    }
    return WRC_Prune;
  } else {
    return WRC_Abort;
  }
}

/*
** Allocate and return a pointer to an expression to load the column iCol
** from datasource iSrc in SrcList pSrc.
*/
Expr *sqlite3CreateColumnExpr(sqlite3 *db, SrcList *pSrc, int iSrc, int iCol){
  Expr *p = sqlite3ExprAlloc(db, TK_COLUMN, 0, 0);
  if( p ){
    struct SrcList_item *pItem = &pSrc->a[iSrc];
    p->pTab = pItem->pTab;
    p->iTable = pItem->iCursor;
    if( p->pTab->iPKey==iCol ){
      p->iColumn = -1;
    }else{
      p->iColumn = (ynVar)iCol;
      testcase( iCol==BMS );
      testcase( iCol==BMS-1 );
      pItem->colUsed |= ((Bitmask)1)<<(iCol>=BMS ? BMS-1 : iCol);
    }
  }
  return p;
}

/*
** Report an error that an expression is not valid for some set of
** pNC->ncFlags values determined by validMask.
*/
static void notValid(
  Parse *pParse,       /* Leave error message here */
  NameContext *pNC,    /* The name context */
  const char *zMsg,    /* Type of error */
  int validMask        /* Set of contexts for which prohibited */
){
  assert( (validMask&~(NC_IsCheck|NC_PartIdx|NC_IdxExpr))==0 );
  if( (pNC->ncFlags & validMask)!=0 ){
    const char *zIn = "partial index WHERE clauses";
    if( pNC->ncFlags & NC_IdxExpr )      zIn = "index expressions";
#ifndef SQLITE_OMIT_CHECK
    else if( pNC->ncFlags & NC_IsCheck ) zIn = "CHECK constraints";
#endif
    sqlite3ErrorMsg(pParse, "%s prohibited in %s", zMsg, zIn);
  }
}

/*
** Expression p should encode a floating point value between 1.0 and 0.0.
** Return 1024 times this value.  Or return -1 if p is not a floating point
** value between 1.0 and 0.0.
*/
static int exprProbability(Expr *p){
  double r = -1.0;
  if( p->op!=TK_FLOAT ) return -1;
  sqlite3AtoF(p->u.zToken, &r, sqlite3Strlen30(p->u.zToken), SQLITE_UTF8);
  assert( r>=0.0 );
  if( r>1.0 ) return -1;
  return (int)(r*134217728.0);
}

/*
** This routine is callback for sqlite3WalkExpr().
**
** Resolve symbolic names into TK_COLUMN operators for the current
** node in the expression tree.  Return 0 to continue the search down
** the tree or 2 to abort the tree walk.
**
