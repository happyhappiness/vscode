    sqlite3VdbeSetColName(v, i, COLNAME_COLUMN, zOrigCol, SQLITE_TRANSIENT);
#else
    zType = columnType(&sNC, p, 0, 0, 0);
#endif
    sqlite3VdbeSetColName(v, i, COLNAME_DECLTYPE, zType, SQLITE_TRANSIENT);
  }
#endif /* SQLITE_OMIT_DECLTYPE */
}

/*
** Generate code that will tell the VDBE the names of columns
** in the result set.  This information is used to provide the
** azCol[] values in the callback.
*/
static void generateColumnNames(
  Parse *pParse,      /* Parser context */
  SrcList *pTabList,  /* List of tables */
  ExprList *pEList    /* Expressions defining the result set */
){
  Vdbe *v = pParse->pVdbe;
  int i, j;
  sqlite3 *db = pParse->db;
  int fullNames, shortNames;

#ifndef SQLITE_OMIT_EXPLAIN
  /* If this is an EXPLAIN, skip this step */
  if( pParse->explain ){
    return;
  }
#endif

  if( pParse->colNamesSet || NEVER(v==0) || db->mallocFailed ) return;
  pParse->colNamesSet = 1;
  fullNames = (db->flags & SQLITE_FullColNames)!=0;
  shortNames = (db->flags & SQLITE_ShortColNames)!=0;
  sqlite3VdbeSetNumCols(v, pEList->nExpr);
  for(i=0; i<pEList->nExpr; i++){
    Expr *p;
    p = pEList->a[i].pExpr;
    if( NEVER(p==0) ) continue;
    if( pEList->a[i].zName ){
      char *zName = pEList->a[i].zName;
      sqlite3VdbeSetColName(v, i, COLNAME_NAME, zName, SQLITE_TRANSIENT);
    }else if( (p->op==TK_COLUMN || p->op==TK_AGG_COLUMN) && pTabList ){
      Table *pTab;
      char *zCol;
      int iCol = p->iColumn;
      for(j=0; ALWAYS(j<pTabList->nSrc); j++){
        if( pTabList->a[j].iCursor==p->iTable ) break;
      }
      assert( j<pTabList->nSrc );
      pTab = pTabList->a[j].pTab;
      if( iCol<0 ) iCol = pTab->iPKey;
      assert( iCol==-1 || (iCol>=0 && iCol<pTab->nCol) );
      if( iCol<0 ){
        zCol = "rowid";
      }else{
        zCol = pTab->aCol[iCol].zName;
      }
      if( !shortNames && !fullNames ){
        sqlite3VdbeSetColName(v, i, COLNAME_NAME, 
            sqlite3DbStrDup(db, pEList->a[i].zSpan), SQLITE_DYNAMIC);
      }else if( fullNames ){
        char *zName = 0;
        zName = sqlite3MPrintf(db, "%s.%s", pTab->zName, zCol);
        sqlite3VdbeSetColName(v, i, COLNAME_NAME, zName, SQLITE_DYNAMIC);
      }else{
        sqlite3VdbeSetColName(v, i, COLNAME_NAME, zCol, SQLITE_TRANSIENT);
      }
    }else{
      sqlite3VdbeSetColName(v, i, COLNAME_NAME, 
          sqlite3DbStrDup(db, pEList->a[i].zSpan), SQLITE_DYNAMIC);
    }
  }
  generateColumnTypes(pParse, pTabList, pEList);
}

#ifndef SQLITE_OMIT_COMPOUND_SELECT
/*
** Name of the connection operator, used for error messages.
*/
static const char *selectOpName(int id){
  char *z;
  switch( id ){
    case TK_ALL:       z = "UNION ALL";   break;
    case TK_INTERSECT: z = "INTERSECT";   break;
    case TK_EXCEPT:    z = "EXCEPT";      break;
    default:           z = "UNION";       break;
  }
  return z;
}
#endif /* SQLITE_OMIT_COMPOUND_SELECT */

/*
** Given a an expression list (which is really the list of expressions
** that form the result set of a SELECT statement) compute appropriate
** column names for a table that would hold the expression list.
**
** All column names will be unique.
**
** Only the column names are computed.  Column.zType, Column.zColl,
** and other fields of Column are zeroed.
**
** Return SQLITE_OK on success.  If a memory allocation error occurs,
** store NULL in *paCol and 0 in *pnCol and return SQLITE_NOMEM.
*/
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

/*
** Add type and collation information to a column list based on
