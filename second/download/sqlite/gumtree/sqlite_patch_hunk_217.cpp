     sqlite3VdbeSetColName(v, i, COLNAME_COLUMN, zOrigCol, SQLITE_TRANSIENT);
 #else
     zType = columnType(&sNC, p, 0, 0, 0);
 #endif
     sqlite3VdbeSetColName(v, i, COLNAME_DECLTYPE, zType, SQLITE_TRANSIENT);
   }
-#endif /* SQLITE_OMIT_DECLTYPE */
+#endif /* !defined(SQLITE_OMIT_DECLTYPE) */
 }
 
+
 /*
-** Generate code that will tell the VDBE the names of columns
-** in the result set.  This information is used to provide the
-** azCol[] values in the callback.
+** Compute the column names for a SELECT statement.
+**
+** The only guarantee that SQLite makes about column names is that if the
+** column has an AS clause assigning it a name, that will be the name used.
+** That is the only documented guarantee.  However, countless applications
+** developed over the years have made baseless assumptions about column names
+** and will break if those assumptions changes.  Hence, use extreme caution
+** when modifying this routine to avoid breaking legacy.
+**
+** See Also: sqlite3ColumnsFromExprList()
+**
+** The PRAGMA short_column_names and PRAGMA full_column_names settings are
+** deprecated.  The default setting is short=ON, full=OFF.  99.9% of all
+** applications should operate this way.  Nevertheless, we need to support the
+** other modes for legacy:
+**
+**    short=OFF, full=OFF:      Column name is the text of the expression has it
+**                              originally appears in the SELECT statement.  In
+**                              other words, the zSpan of the result expression.
+**
+**    short=ON, full=OFF:       (This is the default setting).  If the result
+**                              refers directly to a table column, then the
+**                              result column name is just the table column
+**                              name: COLUMN.  Otherwise use zSpan.
+**
+**    full=ON, short=ANY:       If the result refers directly to a table column,
+**                              then the result column name with the table name
+**                              prefix, ex: TABLE.COLUMN.  Otherwise use zSpan.
 */
 static void generateColumnNames(
   Parse *pParse,      /* Parser context */
-  SrcList *pTabList,  /* List of tables */
-  ExprList *pEList    /* Expressions defining the result set */
+  Select *pSelect     /* Generate column names for this SELECT statement */
 ){
   Vdbe *v = pParse->pVdbe;
-  int i, j;
+  int i;
+  Table *pTab;
+  SrcList *pTabList;
+  ExprList *pEList;
   sqlite3 *db = pParse->db;
-  int fullNames, shortNames;
+  int fullName;    /* TABLE.COLUMN if no AS clause and is a direct table ref */
+  int srcName;     /* COLUMN or TABLE.COLUMN if no AS clause and is direct */
 
 #ifndef SQLITE_OMIT_EXPLAIN
   /* If this is an EXPLAIN, skip this step */
   if( pParse->explain ){
     return;
   }
 #endif
 
-  if( pParse->colNamesSet || NEVER(v==0) || db->mallocFailed ) return;
+  if( pParse->colNamesSet || db->mallocFailed ) return;
+  /* Column names are determined by the left-most term of a compound select */
+  while( pSelect->pPrior ) pSelect = pSelect->pPrior;
+  pTabList = pSelect->pSrc;
+  pEList = pSelect->pEList;
+  assert( v!=0 );
+  assert( pTabList!=0 );
   pParse->colNamesSet = 1;
-  fullNames = (db->flags & SQLITE_FullColNames)!=0;
-  shortNames = (db->flags & SQLITE_ShortColNames)!=0;
+  fullName = (db->flags & SQLITE_FullColNames)!=0;
+  srcName = (db->flags & SQLITE_ShortColNames)!=0 || fullName;
   sqlite3VdbeSetNumCols(v, pEList->nExpr);
   for(i=0; i<pEList->nExpr; i++){
-    Expr *p;
-    p = pEList->a[i].pExpr;
-    if( NEVER(p==0) ) continue;
+    Expr *p = pEList->a[i].pExpr;
+
+    assert( p!=0 );
+    assert( p->op!=TK_AGG_COLUMN );  /* Agg processing has not run yet */
+    assert( p->op!=TK_COLUMN || p->pTab!=0 ); /* Covering idx not yet coded */
     if( pEList->a[i].zName ){
+      /* An AS clause always takes first priority */
       char *zName = pEList->a[i].zName;
       sqlite3VdbeSetColName(v, i, COLNAME_NAME, zName, SQLITE_TRANSIENT);
-    }else if( (p->op==TK_COLUMN || p->op==TK_AGG_COLUMN) && pTabList ){
-      Table *pTab;
+    }else if( srcName && p->op==TK_COLUMN ){
       char *zCol;
       int iCol = p->iColumn;
-      for(j=0; ALWAYS(j<pTabList->nSrc); j++){
-        if( pTabList->a[j].iCursor==p->iTable ) break;
-      }
-      assert( j<pTabList->nSrc );
-      pTab = pTabList->a[j].pTab;
+      pTab = p->pTab;
+      assert( pTab!=0 );
       if( iCol<0 ) iCol = pTab->iPKey;
       assert( iCol==-1 || (iCol>=0 && iCol<pTab->nCol) );
       if( iCol<0 ){
         zCol = "rowid";
       }else{
         zCol = pTab->aCol[iCol].zName;
       }
-      if( !shortNames && !fullNames ){
-        sqlite3VdbeSetColName(v, i, COLNAME_NAME, 
-            sqlite3DbStrDup(db, pEList->a[i].zSpan), SQLITE_DYNAMIC);
-      }else if( fullNames ){
+      if( fullName ){
         char *zName = 0;
         zName = sqlite3MPrintf(db, "%s.%s", pTab->zName, zCol);
         sqlite3VdbeSetColName(v, i, COLNAME_NAME, zName, SQLITE_DYNAMIC);
       }else{
         sqlite3VdbeSetColName(v, i, COLNAME_NAME, zCol, SQLITE_TRANSIENT);
       }
     }else{
-      sqlite3VdbeSetColName(v, i, COLNAME_NAME, 
-          sqlite3DbStrDup(db, pEList->a[i].zSpan), SQLITE_DYNAMIC);
+      const char *z = pEList->a[i].zSpan;
+      z = z==0 ? sqlite3MPrintf(db, "column%d", i+1) : sqlite3DbStrDup(db, z);
+      sqlite3VdbeSetColName(v, i, COLNAME_NAME, z, SQLITE_DYNAMIC);
     }
   }
   generateColumnTypes(pParse, pTabList, pEList);
 }
 
-#ifndef SQLITE_OMIT_COMPOUND_SELECT
 /*
-** Name of the connection operator, used for error messages.
-*/
-static const char *selectOpName(int id){
-  char *z;
-  switch( id ){
-    case TK_ALL:       z = "UNION ALL";   break;
-    case TK_INTERSECT: z = "INTERSECT";   break;
-    case TK_EXCEPT:    z = "EXCEPT";      break;
-    default:           z = "UNION";       break;
-  }
-  return z;
-}
-#endif /* SQLITE_OMIT_COMPOUND_SELECT */
-
-/*
-** Given a an expression list (which is really the list of expressions
+** Given an expression list (which is really the list of expressions
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
+**
+** The only guarantee that SQLite makes about column names is that if the
+** column has an AS clause assigning it a name, that will be the name used.
+** That is the only documented guarantee.  However, countless applications
+** developed over the years have made baseless assumptions about column names
+** and will break if those assumptions changes.  Hence, use extreme caution
+** when modifying this routine to avoid breaking legacy.
+**
+** See Also: generateColumnNames()
 */
-static int selectColumnsFromExprList(
+int sqlite3ColumnsFromExprList(
   Parse *pParse,          /* Parsing context */
   ExprList *pEList,       /* Expr list from which to derive column names */
-  int *pnCol,             /* Write the number of columns here */
+  i16 *pnCol,             /* Write the number of columns here */
   Column **paCol          /* Write the new column list here */
 ){
   sqlite3 *db = pParse->db;   /* Database connection */
   int i, j;                   /* Loop counters */
-  int cnt;                    /* Index added to make the name unique */
+  u32 cnt;                    /* Index added to make the name unique */
   Column *aCol, *pCol;        /* For looping over result columns */
   int nCol;                   /* Number of columns in the result set */
-  Expr *p;                    /* Expression for a single result column */
   char *zName;                /* Column name */
   int nName;                  /* Size of name in zName[] */
+  Hash ht;                    /* Hash table of column names */
+
+  sqlite3HashInit(&ht);
+  if( pEList ){
+    nCol = pEList->nExpr;
+    aCol = sqlite3DbMallocZero(db, sizeof(aCol[0])*nCol);
+    testcase( aCol==0 );
+  }else{
+    nCol = 0;
+    aCol = 0;
+  }
+  assert( nCol==(i16)nCol );
+  *pnCol = nCol;
+  *paCol = aCol;
 
-  *pnCol = nCol = pEList->nExpr;
-  aCol = *paCol = sqlite3DbMallocZero(db, sizeof(aCol[0])*nCol);
-  if( aCol==0 ) return SQLITE_NOMEM;
-  for(i=0, pCol=aCol; i<nCol; i++, pCol++){
+  for(i=0, pCol=aCol; i<nCol && !db->mallocFailed; i++, pCol++){
     /* Get an appropriate name for the column
     */
-    p = pEList->a[i].pExpr;
-    assert( p->pRight==0 || ExprHasProperty(p->pRight, EP_IntValue)
-               || p->pRight->u.zToken==0 || p->pRight->u.zToken[0]!=0 );
     if( (zName = pEList->a[i].zName)!=0 ){
       /* If the column contains an "AS <name>" phrase, use <name> as the name */
-      zName = sqlite3DbStrDup(db, zName);
     }else{
-      Expr *pColExpr = p;  /* The expression that is the result column name */
-      Table *pTab;         /* Table associated with this expression */
-      while( pColExpr->op==TK_DOT ) pColExpr = pColExpr->pRight;
-      if( pColExpr->op==TK_COLUMN && ALWAYS(pColExpr->pTab!=0) ){
+      Expr *pColExpr = sqlite3ExprSkipCollate(pEList->a[i].pExpr);
+      while( pColExpr->op==TK_DOT ){
+        pColExpr = pColExpr->pRight;
+        assert( pColExpr!=0 );
+      }
+      if( (pColExpr->op==TK_COLUMN || pColExpr->op==TK_AGG_COLUMN)
+       && pColExpr->pTab!=0 
+      ){
         /* For columns use the column name name */
         int iCol = pColExpr->iColumn;
-        pTab = pColExpr->pTab;
+        Table *pTab = pColExpr->pTab;
         if( iCol<0 ) iCol = pTab->iPKey;
-        zName = sqlite3MPrintf(db, "%s",
-                 iCol>=0 ? pTab->aCol[iCol].zName : "rowid");
+        zName = iCol>=0 ? pTab->aCol[iCol].zName : "rowid";
       }else if( pColExpr->op==TK_ID ){
         assert( !ExprHasProperty(pColExpr, EP_IntValue) );
-        zName = sqlite3MPrintf(db, "%s", pColExpr->u.zToken);
+        zName = pColExpr->u.zToken;
       }else{
         /* Use the original text of the column expression as its name */
-        zName = sqlite3MPrintf(db, "%s", pEList->a[i].zSpan);
+        zName = pEList->a[i].zSpan;
       }
     }
-    if( db->mallocFailed ){
-      sqlite3DbFree(db, zName);
-      break;
+    if( zName ){
+      zName = sqlite3DbStrDup(db, zName);
+    }else{
+      zName = sqlite3MPrintf(db,"column%d",i+1);
     }
 
     /* Make sure the column name is unique.  If the name is not unique,
-    ** append a integer to the name so that it becomes unique.
+    ** append an integer to the name so that it becomes unique.
     */
-    nName = sqlite3Strlen30(zName);
-    for(j=cnt=0; j<i; j++){
-      if( sqlite3StrICmp(aCol[j].zName, zName)==0 ){
-        char *zNewName;
-        zName[nName] = 0;
-        zNewName = sqlite3MPrintf(db, "%s:%d", zName, ++cnt);
-        sqlite3DbFree(db, zName);
-        zName = zNewName;
-        j = -1;
-        if( zName==0 ) break;
+    cnt = 0;
+    while( zName && sqlite3HashFind(&ht, zName)!=0 ){
+      nName = sqlite3Strlen30(zName);
+      if( nName>0 ){
+        for(j=nName-1; j>0 && sqlite3Isdigit(zName[j]); j--){}
+        if( zName[j]==':' ) nName = j;
       }
+      zName = sqlite3MPrintf(db, "%.*z:%u", nName, zName, ++cnt);
+      if( cnt>3 ) sqlite3_randomness(sizeof(cnt), &cnt);
     }
     pCol->zName = zName;
+    sqlite3ColumnPropertiesFromName(0, pCol);
+    if( zName && sqlite3HashInsert(&ht, zName, pCol)==pCol ){
+      sqlite3OomFault(db);
+    }
   }
+  sqlite3HashClear(&ht);
   if( db->mallocFailed ){
     for(j=0; j<i; j++){
       sqlite3DbFree(db, aCol[j].zName);
     }
     sqlite3DbFree(db, aCol);
     *paCol = 0;
     *pnCol = 0;
-    return SQLITE_NOMEM;
+    return SQLITE_NOMEM_BKPT;
   }
   return SQLITE_OK;
 }
 
 /*
 ** Add type and collation information to a column list based on
