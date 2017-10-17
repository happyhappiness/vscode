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
