  Parse *pParse = pWalker->pParse;
  int i, j, k;
  SrcList *pTabList;
  ExprList *pEList;
  struct SrcList_item *pFrom;
  sqlite3 *db = pParse->db;
  Expr *pE, *pRight, *pExpr;
  u16 selFlags = p->selFlags;

  p->selFlags |= SF_Expanded;
  if( db->mallocFailed  ){
    return WRC_Abort;
  }
  if( NEVER(p->pSrc==0) || (selFlags & SF_Expanded)!=0 ){
    return WRC_Prune;
  }
  pTabList = p->pSrc;
  pEList = p->pEList;
  if( OK_IF_ALWAYS_TRUE(p->pWith) ){
    sqlite3WithPush(pParse, p->pWith, 0);
  }

  /* Make sure cursor numbers have been assigned to all entries in
  ** the FROM clause of the SELECT statement.
  */
  sqlite3SrcListAssignCursors(pParse, pTabList);

  /* Look up every table named in the FROM clause of the select.  If
  ** an entry of the FROM clause is a subquery instead of a table or view,
  ** then create a transient table structure to describe the subquery.
  */
  for(i=0, pFrom=pTabList->a; i<pTabList->nSrc; i++, pFrom++){
    Table *pTab;
    assert( pFrom->fg.isRecursive==0 || pFrom->pTab!=0 );
    if( pFrom->fg.isRecursive ) continue;
    assert( pFrom->pTab==0 );
#ifndef SQLITE_OMIT_CTE
    if( withExpand(pWalker, pFrom) ) return WRC_Abort;
    if( pFrom->pTab ) {} else
#endif
    if( pFrom->zName==0 ){
#ifndef SQLITE_OMIT_SUBQUERY
      Select *pSel = pFrom->pSelect;
      /* A sub-query in the FROM clause of a SELECT */
      assert( pSel!=0 );
      assert( pFrom->pTab==0 );
      if( sqlite3WalkSelect(pWalker, pSel) ) return WRC_Abort;
      pFrom->pTab = pTab = sqlite3DbMallocZero(db, sizeof(Table));
      if( pTab==0 ) return WRC_Abort;
      pTab->nTabRef = 1;
      if( pFrom->zAlias ){
        pTab->zName = sqlite3DbStrDup(db, pFrom->zAlias);
      }else{
        pTab->zName = sqlite3MPrintf(db, "subquery_%p", (void*)pTab);
      }
      while( pSel->pPrior ){ pSel = pSel->pPrior; }
      sqlite3ColumnsFromExprList(pParse, pSel->pEList,&pTab->nCol,&pTab->aCol);
      pTab->iPKey = -1;
      pTab->nRowLogEst = 200; assert( 200==sqlite3LogEst(1048576) );
      pTab->tabFlags |= TF_Ephemeral;
#endif
    }else{
      /* An ordinary table or view name in the FROM clause */
      assert( pFrom->pTab==0 );
      pFrom->pTab = pTab = sqlite3LocateTableItem(pParse, 0, pFrom);
      if( pTab==0 ) return WRC_Abort;
      if( pTab->nTabRef>=0xffff ){
        sqlite3ErrorMsg(pParse, "too many references to \"%s\": max 65535",
           pTab->zName);
        pFrom->pTab = 0;
        return WRC_Abort;
      }
      pTab->nTabRef++;
      if( !IsVirtual(pTab) && cannotBeFunction(pParse, pFrom) ){
        return WRC_Abort;
      }
#if !defined(SQLITE_OMIT_VIEW) || !defined (SQLITE_OMIT_VIRTUALTABLE)
      if( IsVirtual(pTab) || pTab->pSelect ){
        i16 nCol;
        if( sqlite3ViewGetColumnNames(pParse, pTab) ) return WRC_Abort;
        assert( pFrom->pSelect==0 );
        pFrom->pSelect = sqlite3SelectDup(db, pTab->pSelect, 0);
        sqlite3SelectSetName(pFrom->pSelect, pTab->zName);
        nCol = pTab->nCol;
        pTab->nCol = -1;
        sqlite3WalkSelect(pWalker, pFrom->pSelect);
        pTab->nCol = nCol;
      }
#endif
    }

    /* Locate the index named by the INDEXED BY clause, if any. */
    if( sqlite3IndexedByLookup(pParse, pFrom) ){
