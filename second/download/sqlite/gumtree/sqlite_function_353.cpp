void sqlite3CreateIndex(
  Parse *pParse,     /* All information about this parse */
  Token *pName1,     /* First part of index name. May be NULL */
  Token *pName2,     /* Second part of index name. May be NULL */
  SrcList *pTblName, /* Table to index. Use pParse->pNewTable if 0 */
  ExprList *pList,   /* A list of columns to be indexed */
  int onError,       /* OE_Abort, OE_Ignore, OE_Replace, or OE_None */
  Token *pStart,     /* The CREATE token that begins this statement */
  Token *pEnd,       /* The ")" that closes the CREATE INDEX statement */
  int sortOrder,     /* Sort order of primary key when pList==NULL */
  int ifNotExist     /* Omit error if index already exists */
){
  Table *pTab = 0;     /* Table to be indexed */
  Index *pIndex = 0;   /* The index to be created */
  char *zName = 0;     /* Name of the index */
  int nName;           /* Number of characters in zName */
  int i, j;
  Token nullId;        /* Fake token for an empty ID list */
  DbFixer sFix;        /* For assigning database names to pTable */
  int sortOrderMask;   /* 1 to honor DESC in index.  0 to ignore. */
  sqlite3 *db = pParse->db;
  Db *pDb;             /* The specific table containing the indexed database */
  int iDb;             /* Index of the database that is being written */
  Token *pName = 0;    /* Unqualified name of the index to create */
  struct ExprList_item *pListItem; /* For looping over pList */
  int nCol;
  int nExtra = 0;
  char *zExtra;

  assert( pStart==0 || pEnd!=0 ); /* pEnd must be non-NULL if pStart is */
  assert( pParse->nErr==0 );      /* Never called with prior errors */
  if( db->mallocFailed || IN_DECLARE_VTAB ){
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

#ifndef SQLITE_OMIT_TEMPDB
    /* If the index name was unqualified, check if the the table
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

    if( sqlite3FixInit(&sFix, pParse, iDb, "index", pName) &&
        sqlite3FixSrcList(&sFix, pTblName)
    ){
      /* Because the parser constructs pTblName from a single identifier,
      ** sqlite3FixSrcList can never fail. */
      assert(0);
    }
    pTab = sqlite3LocateTable(pParse, 0, pTblName->a[0].zName, 
        pTblName->a[0].zDatabase);
    if( !pTab || db->mallocFailed ) goto exit_create_index;
    assert( db->aDb[iDb].pSchema==pTab->pSchema );
  }else{
    assert( pName==0 );
    pTab = pParse->pNewTable;
    if( !pTab ) goto exit_create_index;
    iDb = sqlite3SchemaToIndex(db, pTab->pSchema);
  }
  pDb = &db->aDb[iDb];

  assert( pTab!=0 );
  assert( pParse->nErr==0 );
  if( sqlite3StrNICmp(pTab->zName, "sqlite_", 7)==0 
       && memcmp(&pTab->zName[7],"altertab_",9)!=0 ){
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
    if( SQLITE_OK!=sqlite3CheckObjectName(pParse, zName) ){
      goto exit_create_index;
    }
    if( !db->init.busy ){
      if( sqlite3FindTable(db, zName, 0)!=0 ){
        sqlite3ErrorMsg(pParse, "there is already a table named %s", zName);
        goto exit_create_index;
      }
    }
    if( sqlite3FindIndex(db, zName, pDb->zName)!=0 ){
      if( !ifNotExist ){
        sqlite3ErrorMsg(pParse, "index %s already exists", zName);
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
  }

  /* Check for authorization to create an index.
  */
#ifndef SQLITE_OMIT_AUTHORIZATION
  {
    const char *zDb = pDb->zName;
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
    nullId.z = pTab->aCol[pTab->nCol-1].zName;
    nullId.n = sqlite3Strlen30((char*)nullId.z);
    pList = sqlite3ExprListAppend(pParse, 0, 0);
    if( pList==0 ) goto exit_create_index;
    sqlite3ExprListSetName(pParse, pList, &nullId, 0);
    pList->a[0].sortOrder = (u8)sortOrder;
  }

  /* Figure out how many bytes of space are required to store explicitly
  ** specified collation sequence names.
  */
  for(i=0; i<pList->nExpr; i++){
    Expr *pExpr = pList->a[i].pExpr;
    if( pExpr ){
      CollSeq *pColl = pExpr->pColl;
      /* Either pColl!=0 or there was an OOM failure.  But if an OOM
      ** failure we have quit before reaching this point. */
      if( ALWAYS(pColl) ){
        nExtra += (1 + sqlite3Strlen30(pColl->zName));
      }
    }
  }

  /* 
  ** Allocate the index structure. 
  */
  nName = sqlite3Strlen30(zName);
  nCol = pList->nExpr;
  pIndex = sqlite3DbMallocZero(db, 
      sizeof(Index) +              /* Index structure  */
      sizeof(int)*nCol +           /* Index.aiColumn   */
      sizeof(int)*(nCol+1) +       /* Index.aiRowEst   */
      sizeof(char *)*nCol +        /* Index.azColl     */
      sizeof(u8)*nCol +            /* Index.aSortOrder */
      nName + 1 +                  /* Index.zName      */
      nExtra                       /* Collation sequence names */
  );
  if( db->mallocFailed ){
    goto exit_create_index;
  }
  pIndex->azColl = (char**)(&pIndex[1]);
  pIndex->aiColumn = (int *)(&pIndex->azColl[nCol]);
  pIndex->aiRowEst = (unsigned *)(&pIndex->aiColumn[nCol]);
  pIndex->aSortOrder = (u8 *)(&pIndex->aiRowEst[nCol+1]);
  pIndex->zName = (char *)(&pIndex->aSortOrder[nCol]);
  zExtra = (char *)(&pIndex->zName[nName+1]);
  memcpy(pIndex->zName, zName, nName+1);
  pIndex->pTable = pTab;
  pIndex->nColumn = pList->nExpr;
  pIndex->onError = (u8)onError;
  pIndex->autoIndex = (u8)(pName==0);
  pIndex->pSchema = db->aDb[iDb].pSchema;

  /* Check to see if we should honor DESC requests on index columns
  */
  if( pDb->pSchema->file_format>=4 ){
    sortOrderMask = -1;   /* Honor DESC */
  }else{
    sortOrderMask = 0;    /* Ignore DESC */
  }

  /* Scan the names of the columns of the table to be indexed and
  ** load the column indices into the Index structure.  Report an error
  ** if any column is not found.
  **
  ** TODO:  Add a test to make sure that the same column is not named
  ** more than once within the same index.  Only the first instance of
  ** the column will ever be used by the optimizer.  Note that using the
  ** same column more than once cannot be an error because that would 
  ** break backwards compatibility - it needs to be a warning.
  */
  for(i=0, pListItem=pList->a; i<pList->nExpr; i++, pListItem++){
    const char *zColName = pListItem->zName;
    Column *pTabCol;
    int requestedSortOrder;
    char *zColl;                   /* Collation sequence name */

    for(j=0, pTabCol=pTab->aCol; j<pTab->nCol; j++, pTabCol++){
      if( sqlite3StrICmp(zColName, pTabCol->zName)==0 ) break;
    }
    if( j>=pTab->nCol ){
      sqlite3ErrorMsg(pParse, "table %s has no column named %s",
        pTab->zName, zColName);
      goto exit_create_index;
    }
    pIndex->aiColumn[i] = j;
    /* Justification of the ALWAYS(pListItem->pExpr->pColl):  Because of
    ** the way the "idxlist" non-terminal is constructed by the parser,
    ** if pListItem->pExpr is not null then either pListItem->pExpr->pColl
    ** must exist or else there must have been an OOM error.  But if there
    ** was an OOM error, we would never reach this point. */
    if( pListItem->pExpr && ALWAYS(pListItem->pExpr->pColl) ){
      int nColl;
      zColl = pListItem->pExpr->pColl->zName;
      nColl = sqlite3Strlen30(zColl) + 1;
      assert( nExtra>=nColl );
      memcpy(zExtra, zColl, nColl);
      zColl = zExtra;
      zExtra += nColl;
      nExtra -= nColl;
    }else{
      zColl = pTab->aCol[j].zColl;
      if( !zColl ){
        zColl = db->pDfltColl->zName;
      }
    }
    if( !db->init.busy && !sqlite3LocateCollSeq(pParse, zColl) ){
      goto exit_create_index;
    }
    pIndex->azColl[i] = zColl;
    requestedSortOrder = pListItem->sortOrder & sortOrderMask;
    pIndex->aSortOrder[i] = (u8)requestedSortOrder;
  }
  sqlite3DefaultRowEst(pIndex);

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
      assert( pIdx->onError!=OE_None );
      assert( pIdx->autoIndex );
      assert( pIndex->onError!=OE_None );

      if( pIdx->nColumn!=pIndex->nColumn ) continue;
      for(k=0; k<pIdx->nColumn; k++){
        const char *z1;
        const char *z2;
        if( pIdx->aiColumn[k]!=pIndex->aiColumn[k] ) break;
        z1 = pIdx->azColl[k];
        z2 = pIndex->azColl[k];
        if( z1!=z2 && sqlite3StrICmp(z1, z2) ) break;
      }
      if( k==pIdx->nColumn ){
        if( pIdx->onError!=pIndex->onError ){
          /* This constraint creates the same index as a previous
          ** constraint specified somewhere in the CREATE TABLE statement.
          ** However the ON CONFLICT clauses are different. If both this 
          ** constraint and the previous equivalent constraint have explicit
          ** ON CONFLICT clauses this is an error. Otherwise, use the
          ** explicitly specified behaviour for the index.
          */
          if( !(pIdx->onError==OE_Default || pIndex->onError==OE_Default) ){
            sqlite3ErrorMsg(pParse, 
                "conflicting ON CONFLICT clauses specified", 0);
          }
          if( pIdx->onError==OE_Default ){
            pIdx->onError = pIndex->onError;
          }
        }
        goto exit_create_index;
      }
    }
  }

  /* Link the new Index structure to its table and to the other
  ** in-memory database structures. 
  */
  if( db->init.busy ){
    Index *p;
    p = sqlite3HashInsert(&pIndex->pSchema->idxHash, 
                          pIndex->zName, sqlite3Strlen30(pIndex->zName),
                          pIndex);
    if( p ){
      assert( p==pIndex );  /* Malloc must have failed */
      db->mallocFailed = 1;
      goto exit_create_index;
    }
    db->flags |= SQLITE_InternChanges;
    if( pTblName!=0 ){
      pIndex->tnum = db->init.newTnum;
    }
  }

  /* If the db->init.busy is 0 then create the index on disk.  This
  ** involves writing the index into the master table and filling in the
  ** index with the current table contents.
  **
  ** The db->init.busy is 0 when the user first enters a CREATE INDEX 
  ** command.  db->init.busy is 1 when a database is opened and 
  ** CREATE INDEX statements are read out of the master table.  In
  ** the latter case the index already exists on disk, which is why
  ** we don't want to recreate it.
  **
  ** If pTblName==0 it means this index is generated as a primary key
  ** or UNIQUE constraint of a CREATE TABLE statement.  Since the table
  ** has just been created, it contains no data and the index initialization
  ** step can be skipped.
  */
  else{ /* if( db->init.busy==0 ) */
    Vdbe *v;
    char *zStmt;
    int iMem = ++pParse->nMem;

    v = sqlite3GetVdbe(pParse);
    if( v==0 ) goto exit_create_index;


    /* Create the rootpage for the index
    */
    sqlite3BeginWriteOperation(pParse, 1, iDb);
    sqlite3VdbeAddOp2(v, OP_CreateIndex, iDb, iMem);

    /* Gather the complete text of the CREATE INDEX statement into
    ** the zStmt variable
    */
    if( pStart ){
      assert( pEnd!=0 );
      /* A named index with an explicit CREATE INDEX statement */
      zStmt = sqlite3MPrintf(db, "CREATE%s INDEX %.*s",
        onError==OE_None ? "" : " UNIQUE",
        pEnd->z - pName->z + 1,
        pName->z);
    }else{
      /* An automatic index created by a PRIMARY KEY or UNIQUE constraint */
      /* zStmt = sqlite3MPrintf(""); */
      zStmt = 0;
    }

    /* Add an entry in sqlite_master for this index
    */
    sqlite3NestedParse(pParse, 
        "INSERT INTO %Q.%s VALUES('index',%Q,%Q,#%d,%Q);",
        db->aDb[iDb].zName, SCHEMA_TABLE(iDb),
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
      sqlite3VdbeAddOp4(v, OP_ParseSchema, iDb, 0, 0,
         sqlite3MPrintf(db, "name='%q'", pIndex->zName), P4_DYNAMIC);
      sqlite3VdbeAddOp1(v, OP_Expire, 0);
    }
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
  if( pIndex ){
    sqlite3_free(pIndex->zColAff);
    sqlite3DbFree(db, pIndex);
  }
  sqlite3ExprListDelete(db, pList);
  sqlite3SrcListDelete(db, pTblName);
  sqlite3DbFree(db, zName);
  return;
}