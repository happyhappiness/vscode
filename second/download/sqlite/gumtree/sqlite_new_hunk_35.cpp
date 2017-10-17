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
