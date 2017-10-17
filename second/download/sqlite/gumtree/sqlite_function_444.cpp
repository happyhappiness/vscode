static int selectExpander(Walker *pWalker, Select *p){
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
      return WRC_Abort;
    }
  }

  /* Process NATURAL keywords, and ON and USING clauses of joins.
  */
  if( db->mallocFailed || sqliteProcessJoin(pParse, p) ){
    return WRC_Abort;
  }

  /* For every "*" that occurs in the column list, insert the names of
  ** all columns in all tables.  And for every TABLE.* insert the names
  ** of all columns in TABLE.  The parser inserted a special expression
  ** with the TK_ALL operator for each "*" that it found in the column list.
  ** The following code just has to locate the TK_ALL expressions and expand
  ** each one to the list of all columns in all tables.
  **
  ** The first loop just checks to see if there are any "*" operators
  ** that need expanding.
  */
  for(k=0; k<pEList->nExpr; k++){
    Expr *pE = pEList->a[k].pExpr;
    if( pE->op==TK_ALL ) break;
    assert( pE->op!=TK_DOT || pE->pRight!=0 );
    assert( pE->op!=TK_DOT || (pE->pLeft!=0 && pE->pLeft->op==TK_ID) );
    if( pE->op==TK_DOT && pE->pRight->op==TK_ALL ) break;
  }
  if( k<pEList->nExpr ){
    /*
    ** If we get here it means the result set contains one or more "*"
    ** operators that need to be expanded.  Loop through each expression
    ** in the result set and expand them one by one.
    */
    struct ExprList_item *a = pEList->a;
    ExprList *pNew = 0;
    int flags = pParse->db->flags;
    int longNames = (flags & SQLITE_FullColNames)!=0
                      && (flags & SQLITE_ShortColNames)==0;

    for(k=0; k<pEList->nExpr; k++){
      Expr *pE = a[k].pExpr;
      assert( pE->op!=TK_DOT || pE->pRight!=0 );
      if( pE->op!=TK_ALL && (pE->op!=TK_DOT || pE->pRight->op!=TK_ALL) ){
        /* This particular expression does not need to be expanded.
        */
        pNew = sqlite3ExprListAppend(pParse, pNew, a[k].pExpr);
        if( pNew ){
          pNew->a[pNew->nExpr-1].zName = a[k].zName;
          pNew->a[pNew->nExpr-1].zSpan = a[k].zSpan;
          a[k].zName = 0;
          a[k].zSpan = 0;
        }
        a[k].pExpr = 0;
      }else{
        /* This expression is a "*" or a "TABLE.*" and needs to be
        ** expanded. */
        int tableSeen = 0;      /* Set to 1 when TABLE matches */
        char *zTName;            /* text of name of TABLE */
        if( pE->op==TK_DOT ){
          assert( pE->pLeft!=0 );
          assert( !ExprHasProperty(pE->pLeft, EP_IntValue) );
          zTName = pE->pLeft->u.zToken;
        }else{
          zTName = 0;
        }
        for(i=0, pFrom=pTabList->a; i<pTabList->nSrc; i++, pFrom++){
          Table *pTab = pFrom->pTab;
          char *zTabName = pFrom->zAlias;
          if( zTabName==0 ){
            zTabName = pTab->zName;
          }
          if( db->mallocFailed ) break;
          if( zTName && sqlite3StrICmp(zTName, zTabName)!=0 ){
            continue;
          }
          tableSeen = 1;
          for(j=0; j<pTab->nCol; j++){
            Expr *pExpr, *pRight;
            char *zName = pTab->aCol[j].zName;
            char *zColname;  /* The computed column name */
            char *zToFree;   /* Malloced string that needs to be freed */
            Token sColname;  /* Computed column name as a token */

            /* If a column is marked as 'hidden' (currently only possible
            ** for virtual tables), do not include it in the expanded
            ** result-set list.
            */
            if( IsHiddenColumn(&pTab->aCol[j]) ){
              assert(IsVirtual(pTab));
              continue;
            }

            if( i>0 && zTName==0 ){
              struct SrcList_item *pLeft = &pTabList->a[i-1];
              if( (pLeft[1].jointype & JT_NATURAL)!=0 &&
                        columnIndex(pLeft->pTab, zName)>=0 ){
                /* In a NATURAL join, omit the join columns from the 
                ** table on the right */
                continue;
              }
              if( sqlite3IdListIndex(pLeft[1].pUsing, zName)>=0 ){
                /* In a join with a USING clause, omit columns in the
                ** using clause from the table on the right. */
                continue;
              }
            }
            pRight = sqlite3Expr(db, TK_ID, zName);
            zColname = zName;
            zToFree = 0;
            if( longNames || pTabList->nSrc>1 ){
              Expr *pLeft;
              pLeft = sqlite3Expr(db, TK_ID, zTabName);
              pExpr = sqlite3PExpr(pParse, TK_DOT, pLeft, pRight, 0);
              if( longNames ){
                zColname = sqlite3MPrintf(db, "%s.%s", zTabName, zName);
                zToFree = zColname;
              }
            }else{
              pExpr = pRight;
            }
            pNew = sqlite3ExprListAppend(pParse, pNew, pExpr);
            sColname.z = zColname;
            sColname.n = sqlite3Strlen30(zColname);
            sqlite3ExprListSetName(pParse, pNew, &sColname, 0);
            sqlite3DbFree(db, zToFree);
          }
        }
        if( !tableSeen ){
          if( zTName ){
            sqlite3ErrorMsg(pParse, "no such table: %s", zTName);
          }else{
            sqlite3ErrorMsg(pParse, "no tables specified");
          }
        }
      }
    }
    sqlite3ExprListDelete(db, pEList);
    p->pEList = pNew;
  }
#if SQLITE_MAX_COLUMN
  if( p->pEList && p->pEList->nExpr>db->aLimit[SQLITE_LIMIT_COLUMN] ){
    sqlite3ErrorMsg(pParse, "too many columns in result set");
  }
#endif
  return WRC_Continue;
}