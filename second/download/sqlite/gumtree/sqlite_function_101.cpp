void sqlite3CreateIndex(
  Parse *pParse,     /* All information about this parse */
  Token *pName1,     /* First part of index name. May be NULL */
  Token *pName2,     /* Second part of index name. May be NULL */
  SrcList *pTblName, /* Table to index. Use pParse->pNewTable if 0 */
  ExprList *pList,   /* A list of columns to be indexed */
  int onError,       /* OE_Abort, OE_Ignore, OE_Replace, or OE_None */
  Token *pStart,     /* The CREATE token that begins this statement */
  Expr *pPIWhere,    /* WHERE clause for partial indices */
  int sortOrder,     /* Sort order of primary key when pList==NULL */
  int ifNotExist,    /* Omit error if index already exists */
  u8 idxType         /* The index type */
){
  Table *pTab = 0;     /* Table to be indexed */
  Index *pIndex = 0;   /* The index to be created */
  char *zName = 0;     /* Name of the index */
  int nName;           /* Number of characters in zName */
  int i, j;
  DbFixer sFix;        /* For assigning database names to pTable */
  int sortOrderMask;   /* 1 to honor DESC in index.  0 to ignore. */
  sqlite3 *db = pParse->db;
  Db *pDb;             /* The specific table containing the indexed database */
  int iDb;             /* Index of the database that is being written */
  Token *pName = 0;    /* Unqualified name of the index to create */
  struct ExprList_item *pListItem; /* For looping over pList */
  int nExtra = 0;                  /* Space allocated for zExtra[] */
  int nExtraCol;                   /* Number of extra columns needed */
  char *zExtra = 0;                /* Extra space after the Index object */
  Index *pPk = 0;      /* PRIMARY KEY index for WITHOUT ROWID tables */

  if( db->mallocFailed || pParse->nErr>0 ){
    goto exit_create_index;
  }
  if( IN_DECLARE_VTAB && idxType!=SQLITE_IDXTYPE_PRIMARYKEY ){
    goto exit_create_index;
  }
  if( SQLITE_OK!=sqlite3ReadSchema(pParse) ){
    goto exit_create_index;
  }

  /*
  ** Find the table that is to be indexed.  Return early if not found.
  */
  if( pTblName!=0 ){

    /* Use the two-part index name to determine the database 
    ** to search for the table. 'Fix' the table name to this db
    ** before looking up the table.
    */
    assert( pName1 && pName2 );
    iDb = sqlite3TwoPartName(pParse, pName1, pName2, &pName);
    if( iDb<0 ) goto exit_create_index;
    assert( pName && pName->z );

#ifndef SQLITE_OMIT_TEMPDB
    /* If the index name was unqualified, check if the table
    ** is a temp table. If so, set the database to 1. Do not do this
    ** if initialising a database schema.
    */
    if( !db->init.busy ){
      pTab = sqlite3SrcListLookup(pParse, pTblName);
      if( pName2->n==0 && pTab && pTab->pSchema==db->aDb[1].pSchema ){
        iDb = 1;
      }
    }
#endif

    sqlite3FixInit(&sFix, pParse, iDb, "index", pName);
    if( sqlite3FixSrcList(&sFix, pTblName) ){
      /* Because the parser constructs pTblName from a single identifier,
      ** sqlite3FixSrcList can never fail. */
      assert(0);
    }
    pTab = sqlite3LocateTableItem(pParse, 0, &pTblName->a[0]);
    assert( db->mallocFailed==0 || pTab==0 );
    if( pTab==0 ) goto exit_create_index;
    if( iDb==1 && db->aDb[iDb].pSchema!=pTab->pSchema ){
      sqlite3ErrorMsg(pParse, 
           "cannot create a TEMP index on non-TEMP table \"%s\"",
           pTab->zName);
      goto exit_create_index;
    }
    if( !HasRowid(pTab) ) pPk = sqlite3PrimaryKeyIndex(pTab);
  }else{
    assert( pName==0 );
    assert( pStart==0 );
    pTab = pParse->pNewTable;
    if( !pTab ) goto exit_create_index;
    iDb = sqlite3SchemaToIndex(db, pTab->pSchema);
  }
  pDb = &db->aDb[iDb];

  assert( pTab!=0 );
  assert( pParse->nErr==0 );
  if( sqlite3StrNICmp(pTab->zName, "sqlite_", 7)==0 
       && db->init.busy==0
#if SQLITE_USER_AUTHENTICATION
       && sqlite3UserAuthTable(pTab->zName)==0
#endif
       && sqlite3StrNICmp(&pTab->zName[7],"altertab_",9)!=0 ){
    sqlite3ErrorMsg(pParse, "table %s may not be indexed", pTab->zName);
    goto exit_create_index;
  }
#ifndef SQLITE_OMIT_VIEW
  if( pTab->pSelect ){
    sqlite3ErrorMsg(pParse, "views may not be indexed");
    goto exit_create_index;
  }
#endif
#ifndef SQLITE_OMIT_VIRTUALTABLE
  if( IsVirtual(pTab) ){
    sqlite3ErrorMsg(pParse, "virtual tables may not be indexed");
    goto exit_create_index;
  }
#endif

  /*
  ** Find the name of the index.  Make sure there is not already another
  ** index or table with the same name.  
  **
  ** Exception:  If we are reading the names of permanent indices from the
  ** sqlite_master table (because some other process changed the schema) and
  ** one of the index names collides with the name of a temporary table or
  ** index, then we will continue to process this index.
  **
  ** If pName==0 it means that we are
  ** dealing with a primary key or UNIQUE constraint.  We have to invent our
  ** own name.
  */
  if( pName ){
    zName = sqlite3NameFromToken(db, pName);
    if( zName==0 ) goto exit_create_index;
    assert( pName->z!=0 );
    if( SQLITE_OK!=sqlite3CheckObjectName(pParse, zName) ){
      goto exit_create_index;
    }
    if( !db->init.busy ){
      if( sqlite3FindTable(db, zName, 0)!=0 ){
        sqlite3ErrorMsg(pParse, "there is already a table named %s", zName);
        goto exit_create_index;
      }
    }
    if( sqlite3FindIndex(db, zName, pDb->zDbSName)!=0 ){
      if( !ifNotExist ){
        sqlite3ErrorMsg(pParse, "index %s already exists", zName);
      }else{
        assert( !db->init.busy );
        sqlite3CodeVerifySchema(pParse, iDb);
      }
      goto exit_create_index;
    }
  }else{
    int n;
    Index *pLoop;
    for(pLoop=pTab->pIndex, n=1; pLoop; pLoop=pLoop->pNext, n++){}
    zName = sqlite3MPrintf(db, "sqlite_autoindex_%s_%d", pTab->zName, n);
    if( zName==0 ){
      goto exit_create_index;
    }

    /* Automatic index names generated from within sqlite3_declare_vtab()
    ** must have names that are distinct from normal automatic index names.
    ** The following statement converts "sqlite3_autoindex..." into
    ** "sqlite3_butoindex..." in order to make the names distinct.
    ** The "vtab_err.test" test demonstrates the need of this statement. */
    if( IN_DECLARE_VTAB ) zName[7]++;
  }

  /* Check for authorization to create an index.
  */
#ifndef SQLITE_OMIT_AUTHORIZATION
  {
    const char *zDb = pDb->zDbSName;
    if( sqlite3AuthCheck(pParse, SQLITE_INSERT, SCHEMA_TABLE(iDb), 0, zDb) ){
      goto exit_create_index;
    }
    i = SQLITE_CREATE_INDEX;
    if( !OMIT_TEMPDB && iDb==1 ) i = SQLITE_CREATE_TEMP_INDEX;
    if( sqlite3AuthCheck(pParse, i, zName, pTab->zName, zDb) ){
      goto exit_create_index;
    }
  }
#endif

  /* If pList==0, it means this routine was called to make a primary
  ** key out of the last column added to the table under construction.
  ** So create a fake list to simulate this.
  */
  if( pList==0 ){
    Token prevCol;
    sqlite3TokenInit(&prevCol, pTab->aCol[pTab->nCol-1].zName);
    pList = sqlite3ExprListAppend(pParse, 0,
              sqlite3ExprAlloc(db, TK_ID, &prevCol, 0));
    if( pList==0 ) goto exit_create_index;
    assert( pList->nExpr==1 );
    sqlite3ExprListSetSortOrder(pList, sortOrder);
  }else{
    sqlite3ExprListCheckLength(pParse, pList, "index");
  }

  /* Figure out how many bytes of space are required to store explicitly
  ** specified collation sequence names.
  */
  for(i=0; i<pList->nExpr; i++){
    Expr *pExpr = pList->a[i].pExpr;
    assert( pExpr!=0 );
    if( pExpr->op==TK_COLLATE ){
      nExtra += (1 + sqlite3Strlen30(pExpr->u.zToken));
    }
  }

  /* 
  ** Allocate the index structure. 
  */
  nName = sqlite3Strlen30(zName);
  nExtraCol = pPk ? pPk->nKeyCol : 1;
  pIndex = sqlite3AllocateIndexObject(db, pList->nExpr + nExtraCol,
                                      nName + nExtra + 1, &zExtra);
  if( db->mallocFailed ){
    goto exit_create_index;
  }
  assert( EIGHT_BYTE_ALIGNMENT(pIndex->aiRowLogEst) );
  assert( EIGHT_BYTE_ALIGNMENT(pIndex->azColl) );
  pIndex->zName = zExtra;
  zExtra += nName + 1;
  memcpy(pIndex->zName, zName, nName+1);
  pIndex->pTable = pTab;
  pIndex->onError = (u8)onError;
  pIndex->uniqNotNull = onError!=OE_None;
  pIndex->idxType = idxType;
  pIndex->pSchema = db->aDb[iDb].pSchema;
  pIndex->nKeyCol = pList->nExpr;
  if( pPIWhere ){
    sqlite3ResolveSelfReference(pParse, pTab, NC_PartIdx, pPIWhere, 0);
    pIndex->pPartIdxWhere = pPIWhere;
    pPIWhere = 0;
  }
  assert( sqlite3SchemaMutexHeld(db, iDb, 0) );

  /* Check to see if we should honor DESC requests on index columns
  */
  if( pDb->pSchema->file_format>=4 ){
    sortOrderMask = -1;   /* Honor DESC */
  }else{
    sortOrderMask = 0;    /* Ignore DESC */
  }

  /* Analyze the list of expressions that form the terms of the index and
  ** report any errors.  In the common case where the expression is exactly
  ** a table column, store that column in aiColumn[].  For general expressions,
  ** populate pIndex->aColExpr and store XN_EXPR (-2) in aiColumn[].
  **
  ** TODO: Issue a warning if two or more columns of the index are identical.
  ** TODO: Issue a warning if the table primary key is used as part of the
  ** index key.
  */
  for(i=0, pListItem=pList->a; i<pList->nExpr; i++, pListItem++){
    Expr *pCExpr;                  /* The i-th index expression */
    int requestedSortOrder;        /* ASC or DESC on the i-th expression */
    const char *zColl;             /* Collation sequence name */

    sqlite3StringToId(pListItem->pExpr);
    sqlite3ResolveSelfReference(pParse, pTab, NC_IdxExpr, pListItem->pExpr, 0);
    if( pParse->nErr ) goto exit_create_index;
    pCExpr = sqlite3ExprSkipCollate(pListItem->pExpr);
    if( pCExpr->op!=TK_COLUMN ){
      if( pTab==pParse->pNewTable ){
        sqlite3ErrorMsg(pParse, "expressions prohibited in PRIMARY KEY and "
                                "UNIQUE constraints");
        goto exit_create_index;
      }
      if( pIndex->aColExpr==0 ){
        ExprList *pCopy = sqlite3ExprListDup(db, pList, 0);
        pIndex->aColExpr = pCopy;
        if( !db->mallocFailed ){
          assert( pCopy!=0 );
          pListItem = &pCopy->a[i];
        }
      }
      j = XN_EXPR;
      pIndex->aiColumn[i] = XN_EXPR;
      pIndex->uniqNotNull = 0;
    }else{
      j = pCExpr->iColumn;
      assert( j<=0x7fff );
      if( j<0 ){
        j = pTab->iPKey;
      }else if( pTab->aCol[j].notNull==0 ){
        pIndex->uniqNotNull = 0;
      }
      pIndex->aiColumn[i] = (i16)j;
    }
    zColl = 0;
    if( pListItem->pExpr->op==TK_COLLATE ){
      int nColl;
      zColl = pListItem->pExpr->u.zToken;
      nColl = sqlite3Strlen30(zColl) + 1;
      assert( nExtra>=nColl );
      memcpy(zExtra, zColl, nColl);
      zColl = zExtra;
      zExtra += nColl;
      nExtra -= nColl;
    }else if( j>=0 ){
      zColl = pTab->aCol[j].zColl;
    }
    if( !zColl ) zColl = sqlite3StrBINARY;
    if( !db->init.busy && !sqlite3LocateCollSeq(pParse, zColl) ){
      goto exit_create_index;
    }
    pIndex->azColl[i] = zColl;
    requestedSortOrder = pListItem->sortOrder & sortOrderMask;
    pIndex->aSortOrder[i] = (u8)requestedSortOrder;
  }

  /* Append the table key to the end of the index.  For WITHOUT ROWID
  ** tables (when pPk!=0) this will be the declared PRIMARY KEY.  For
  ** normal tables (when pPk==0) this will be the rowid.
  */
  if( pPk ){
    for(j=0; j<pPk->nKeyCol; j++){
      int x = pPk->aiColumn[j];
      assert( x>=0 );
      if( hasColumn(pIndex->aiColumn, pIndex->nKeyCol, x) ){
        pIndex->nColumn--; 
      }else{
        pIndex->aiColumn[i] = x;
        pIndex->azColl[i] = pPk->azColl[j];
        pIndex->aSortOrder[i] = pPk->aSortOrder[j];
        i++;
      }
    }
    assert( i==pIndex->nColumn );
  }else{
    pIndex->aiColumn[i] = XN_ROWID;
    pIndex->azColl[i] = sqlite3StrBINARY;
  }
  sqlite3DefaultRowEst(pIndex);
  if( pParse->pNewTable==0 ) estimateIndexWidth(pIndex);

  /* If this index contains every column of its table, then mark
  ** it as a covering index */
  assert( HasRowid(pTab) 
      || pTab->iPKey<0 || sqlite3ColumnOfIndex(pIndex, pTab->iPKey)>=0 );
  if( pTblName!=0 && pIndex->nColumn>=pTab->nCol ){
    pIndex->isCovering = 1;
    for(j=0; j<pTab->nCol; j++){
      if( j==pTab->iPKey ) continue;
      if( sqlite3ColumnOfIndex(pIndex,j)>=0 ) continue;
      pIndex->isCovering = 0;
      break;
    }
  }

  if( pTab==pParse->pNewTable ){
    /* This routine has been called to create an automatic index as a
    ** result of a PRIMARY KEY or UNIQUE clause on a column definition, or
    ** a PRIMARY KEY or UNIQUE clause following the column definitions.
    ** i.e. one of:
    **
    ** CREATE TABLE t(x PRIMARY KEY, y);
    ** CREATE TABLE t(x, y, UNIQUE(x, y));
    **
    ** Either way, check to see if the table already has such an index. If
    ** so, don't bother creating this one. This only applies to
    ** automatically created indices. Users can do as they wish with
    ** explicit indices.
    **
    ** Two UNIQUE or PRIMARY KEY constraints are considered equivalent
    ** (and thus suppressing the second one) even if they have different
    ** sort orders.
    **
    ** If there are different collating sequences or if the columns of
    ** the constraint occur in different orders, then the constraints are
    ** considered distinct and both result in separate indices.
    */
    Index *pIdx;
    for(pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext){
      int k;
      assert( IsUniqueIndex(pIdx) );
      assert( pIdx->idxType!=SQLITE_IDXTYPE_APPDEF );
      assert( IsUniqueIndex(pIndex) );

      if( pIdx->nKeyCol!=pIndex->nKeyCol ) continue;
      for(k=0; k<pIdx->nKeyCol; k++){
        const char *z1;
        const char *z2;
        assert( pIdx->aiColumn[k]>=0 );
        if( pIdx->aiColumn[k]!=pIndex->aiColumn[k] ) break;
        z1 = pIdx->azColl[k];
        z2 = pIndex->azColl[k];
        if( sqlite3StrICmp(z1, z2) ) break;
      }
      if( k==pIdx->nKeyCol ){
        if( pIdx->onError!=pIndex->onError ){
          /* This constraint creates the same index as a previous
          ** constraint specified somewhere in the CREATE TABLE statement.
          ** However the ON CONFLICT clauses are different. If both this 
          ** constraint and the previous equivalent constraint have explicit
          ** ON CONFLICT clauses this is an error. Otherwise, use the
          ** explicitly specified behavior for the index.
          */
          if( !(pIdx->onError==OE_Default || pIndex->onError==OE_Default) ){
            sqlite3ErrorMsg(pParse, 
                "conflicting ON CONFLICT clauses specified", 0);
          }
          if( pIdx->onError==OE_Default ){
            pIdx->onError = pIndex->onError;
          }
        }
        if( idxType==SQLITE_IDXTYPE_PRIMARYKEY ) pIdx->idxType = idxType;
        goto exit_create_index;
      }
    }
  }

  /* Link the new Index structure to its table and to the other
  ** in-memory database structures. 
  */
  assert( pParse->nErr==0 );
  if( db->init.busy ){
    Index *p;
    assert( !IN_DECLARE_VTAB );
    assert( sqlite3SchemaMutexHeld(db, 0, pIndex->pSchema) );
    p = sqlite3HashInsert(&pIndex->pSchema->idxHash, 
                          pIndex->zName, pIndex);
    if( p ){
      assert( p==pIndex );  /* Malloc must have failed */
      sqlite3OomFault(db);
      goto exit_create_index;
    }
    db->mDbFlags |= DBFLAG_SchemaChange;
    if( pTblName!=0 ){
      pIndex->tnum = db->init.newTnum;
    }
  }

  /* If this is the initial CREATE INDEX statement (or CREATE TABLE if the
  ** index is an implied index for a UNIQUE or PRIMARY KEY constraint) then
  ** emit code to allocate the index rootpage on disk and make an entry for
  ** the index in the sqlite_master table and populate the index with
  ** content.  But, do not do this if we are simply reading the sqlite_master
  ** table to parse the schema, or if this index is the PRIMARY KEY index
  ** of a WITHOUT ROWID table.
  **
  ** If pTblName==0 it means this index is generated as an implied PRIMARY KEY
  ** or UNIQUE index in a CREATE TABLE statement.  Since the table
  ** has just been created, it contains no data and the index initialization
  ** step can be skipped.
  */
  else if( HasRowid(pTab) || pTblName!=0 ){
    Vdbe *v;
    char *zStmt;
    int iMem = ++pParse->nMem;

    v = sqlite3GetVdbe(pParse);
    if( v==0 ) goto exit_create_index;

    sqlite3BeginWriteOperation(pParse, 1, iDb);

    /* Create the rootpage for the index using CreateIndex. But before
    ** doing so, code a Noop instruction and store its address in 
    ** Index.tnum. This is required in case this index is actually a 
    ** PRIMARY KEY and the table is actually a WITHOUT ROWID table. In 
    ** that case the convertToWithoutRowidTable() routine will replace
    ** the Noop with a Goto to jump over the VDBE code generated below. */
    pIndex->tnum = sqlite3VdbeAddOp0(v, OP_Noop);
    sqlite3VdbeAddOp3(v, OP_CreateBtree, iDb, iMem, BTREE_BLOBKEY);

    /* Gather the complete text of the CREATE INDEX statement into
    ** the zStmt variable
    */
    if( pStart ){
      int n = (int)(pParse->sLastToken.z - pName->z) + pParse->sLastToken.n;
      if( pName->z[n-1]==';' ) n--;
      /* A named index with an explicit CREATE INDEX statement */
      zStmt = sqlite3MPrintf(db, "CREATE%s INDEX %.*s",
        onError==OE_None ? "" : " UNIQUE", n, pName->z);
    }else{
      /* An automatic index created by a PRIMARY KEY or UNIQUE constraint */
      /* zStmt = sqlite3MPrintf(""); */
      zStmt = 0;
    }

    /* Add an entry in sqlite_master for this index
    */
    sqlite3NestedParse(pParse, 
        "INSERT INTO %Q.%s VALUES('index',%Q,%Q,#%d,%Q);",
        db->aDb[iDb].zDbSName, MASTER_NAME,
        pIndex->zName,
        pTab->zName,
        iMem,
        zStmt
    );
    sqlite3DbFree(db, zStmt);

    /* Fill the index with data and reparse the schema. Code an OP_Expire
    ** to invalidate all pre-compiled statements.
    */
    if( pTblName ){
      sqlite3RefillIndex(pParse, pIndex, iMem);
      sqlite3ChangeCookie(pParse, iDb);
      sqlite3VdbeAddParseSchemaOp(v, iDb,
         sqlite3MPrintf(db, "name='%q' AND type='index'", pIndex->zName));
      sqlite3VdbeAddOp0(v, OP_Expire);
    }

    sqlite3VdbeJumpHere(v, pIndex->tnum);
  }

  /* When adding an index to the list of indices for a table, make
  ** sure all indices labeled OE_Replace come after all those labeled
  ** OE_Ignore.  This is necessary for the correct constraint check
  ** processing (in sqlite3GenerateConstraintChecks()) as part of
  ** UPDATE and INSERT statements.  
  */
  if( db->init.busy || pTblName==0 ){
    if( onError!=OE_Replace || pTab->pIndex==0
         || pTab->pIndex->onError==OE_Replace){
      pIndex->pNext = pTab->pIndex;
      pTab->pIndex = pIndex;
    }else{
      Index *pOther = pTab->pIndex;
      while( pOther->pNext && pOther->pNext->onError!=OE_Replace ){
        pOther = pOther->pNext;
      }
      pIndex->pNext = pOther->pNext;
      pOther->pNext = pIndex;
    }
    pIndex = 0;
  }

  /* Clean up before exiting */
exit_create_index:
  if( pIndex ) freeIndex(db, pIndex);
  sqlite3ExprDelete(db, pPIWhere);
  sqlite3ExprListDelete(db, pList);
  sqlite3SrcListDelete(db, pTblName);
  sqlite3DbFree(db, zName);
}