static int selectColumnsFromExprList(
  Parse *pParse,          /* Parsing context */
  ExprList *pEList,       /* Expr list from which to derive column names */
  int *pnCol,             /* Write the number of columns here */
  Column **paCol          /* Write the new column list here */
){
  sqlite3 *db = pParse->db;   /* Database connection */
  int i, j;                   /* Loop counters */
  int cnt;                    /* Index added to make the name unique */
  Column *aCol, *pCol;        /* For looping over result columns */
  int nCol;                   /* Number of columns in the result set */
  Expr *p;                    /* Expression for a single result column */
  char *zName;                /* Column name */
  int nName;                  /* Size of name in zName[] */

  *pnCol = nCol = pEList->nExpr;
  aCol = *paCol = sqlite3DbMallocZero(db, sizeof(aCol[0])*nCol);
  if( aCol==0 ) return SQLITE_NOMEM;
  for(i=0, pCol=aCol; i<nCol; i++, pCol++){
    /* Get an appropriate name for the column
    */
    p = pEList->a[i].pExpr;
    assert( p->pRight==0 || ExprHasProperty(p->pRight, EP_IntValue)
               || p->pRight->u.zToken==0 || p->pRight->u.zToken[0]!=0 );
    if( (zName = pEList->a[i].zName)!=0 ){
      /* If the column contains an "AS <name>" phrase, use <name> as the name */
      zName = sqlite3DbStrDup(db, zName);
    }else{
      Expr *pColExpr = p;  /* The expression that is the result column name */
      Table *pTab;         /* Table associated with this expression */
      while( pColExpr->op==TK_DOT ) pColExpr = pColExpr->pRight;
      if( pColExpr->op==TK_COLUMN && ALWAYS(pColExpr->pTab!=0) ){
        /* For columns use the column name name */
        int iCol = pColExpr->iColumn;
        pTab = pColExpr->pTab;
        if( iCol<0 ) iCol = pTab->iPKey;
        zName = sqlite3MPrintf(db, "%s",
                 iCol>=0 ? pTab->aCol[iCol].zName : "rowid");
      }else if( pColExpr->op==TK_ID ){
        assert( !ExprHasProperty(pColExpr, EP_IntValue) );
        zName = sqlite3MPrintf(db, "%s", pColExpr->u.zToken);
      }else{
        /* Use the original text of the column expression as its name */
        zName = sqlite3MPrintf(db, "%s", pEList->a[i].zSpan);
      }
    }
    if( db->mallocFailed ){
      sqlite3DbFree(db, zName);
      break;
    }

    /* Make sure the column name is unique.  If the name is not unique,
    ** append a integer to the name so that it becomes unique.
    */
    nName = sqlite3Strlen30(zName);
    for(j=cnt=0; j<i; j++){
      if( sqlite3StrICmp(aCol[j].zName, zName)==0 ){
        char *zNewName;
        zName[nName] = 0;
        zNewName = sqlite3MPrintf(db, "%s:%d", zName, ++cnt);
        sqlite3DbFree(db, zName);
        zName = zNewName;
        j = -1;
        if( zName==0 ) break;
      }
    }
    pCol->zName = zName;
  }
  if( db->mallocFailed ){
    for(j=0; j<i; j++){
      sqlite3DbFree(db, aCol[j].zName);
    }
    sqlite3DbFree(db, aCol);
    *paCol = 0;
    *pnCol = 0;
    return SQLITE_NOMEM;
  }
  return SQLITE_OK;
}