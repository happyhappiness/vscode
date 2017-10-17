  Parse *pParse = pWalker->pParse;
  int i, j, k;
  SrcList *pTabList;
  ExprList *pEList;
  struct SrcList_item *pFrom;
  sqlite3 *db = pParse->db;

  if( db->mallocFailed  ){
    return WRC_Abort;
  }
  if( NEVER(p->pSrc==0) || (p->selFlags & SF_Expanded)!=0 ){
    return WRC_Prune;
  }
  p->selFlags |= SF_Expanded;
  pTabList = p->pSrc;
  pEList = p->pEList;

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
    if( pFrom->pTab!=0 ){
      /* This statement has already been prepared.  There is no need
      ** to go further. */
      assert( i==0 );
      return WRC_Prune;
    }
    if( pFrom->zName==0 ){
#ifndef SQLITE_OMIT_SUBQUERY
      Select *pSel = pFrom->pSelect;
      /* A sub-query in the FROM clause of a SELECT */
      assert( pSel!=0 );
      assert( pFrom->pTab==0 );
      sqlite3WalkSelect(pWalker, pSel);
      pFrom->pTab = pTab = sqlite3DbMallocZero(db, sizeof(Table));
      if( pTab==0 ) return WRC_Abort;
      pTab->dbMem = db->lookaside.bEnabled ? db : 0;
      pTab->nRef = 1;
      pTab->zName = sqlite3MPrintf(db, "sqlite_subquery_%p_", (void*)pTab);
      while( pSel->pPrior ){ pSel = pSel->pPrior; }
      selectColumnsFromExprList(pParse, pSel->pEList, &pTab->nCol, &pTab->aCol);
      pTab->iPKey = -1;
      pTab->tabFlags |= TF_Ephemeral;
#endif
    }else{
      /* An ordinary table or view name in the FROM clause */
      assert( pFrom->pTab==0 );
      pFrom->pTab = pTab = 
        sqlite3LocateTable(pParse,0,pFrom->zName,pFrom->zDatabase);
      if( pTab==0 ) return WRC_Abort;
      pTab->nRef++;
#if !defined(SQLITE_OMIT_VIEW) || !defined (SQLITE_OMIT_VIRTUALTABLE)
      if( pTab->pSelect || IsVirtual(pTab) ){
        /* We reach here if the named table is a really a view */
        if( sqlite3ViewGetColumnNames(pParse, pTab) ) return WRC_Abort;
        assert( pFrom->pSelect==0 );
        pFrom->pSelect = sqlite3SelectDup(db, pTab->pSelect, 0);
        sqlite3WalkSelect(pWalker, pFrom->pSelect);
      }
#endif
    }

    /* Locate the index named by the INDEXED BY clause, if any. */
    if( sqlite3IndexedByLookup(pParse, pFrom) ){
