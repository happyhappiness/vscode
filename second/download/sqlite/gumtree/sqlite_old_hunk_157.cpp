  if( db->nDb>=db->aLimit[SQLITE_LIMIT_ATTACHED]+2 ){
    zErrDyn = sqlite3MPrintf(db, "too many attached databases - max %d", 
      db->aLimit[SQLITE_LIMIT_ATTACHED]
    );
    goto attach_error;
  }
  if( !db->autoCommit ){
    zErrDyn = sqlite3MPrintf(db, "cannot ATTACH database within transaction");
    goto attach_error;
  }
  for(i=0; i<db->nDb; i++){
    char *z = db->aDb[i].zName;
    assert( z && zName );
    if( sqlite3StrICmp(z, zName)==0 ){
      zErrDyn = sqlite3MPrintf(db, "database %s is already in use", zName);
      goto attach_error;
    }
  }

  /* Allocate the new entry in the db->aDb[] array and initialise the schema
  ** hash tables.
  */
  if( db->aDb==db->aDbStatic ){
    aNew = sqlite3DbMallocRaw(db, sizeof(db->aDb[0])*3 );
    if( aNew==0 ) return;
    memcpy(aNew, db->aDb, sizeof(db->aDb[0])*2);
  }else{
    aNew = sqlite3DbRealloc(db, db->aDb, sizeof(db->aDb[0])*(db->nDb+1) );
    if( aNew==0 ) return;
  }
  db->aDb = aNew;
  aNew = &db->aDb[db->nDb];
  memset(aNew, 0, sizeof(*aNew));

  /* Open the database file. If the btree is successfully opened, use
  ** it to obtain the database schema. At this point the schema may
  ** or may not be initialised.
  */
  rc = sqlite3BtreeFactory(db, zFile, 0, SQLITE_DEFAULT_CACHE_SIZE,
                           db->openFlags | SQLITE_OPEN_MAIN_DB,
                           &aNew->pBt);
  db->nDb++;
  if( rc==SQLITE_CONSTRAINT ){
    rc = SQLITE_ERROR;
    zErrDyn = sqlite3MPrintf(db, "database is already attached");
  }else if( rc==SQLITE_OK ){
    Pager *pPager;
    aNew->pSchema = sqlite3SchemaGet(db, aNew->pBt);
    if( !aNew->pSchema ){
      rc = SQLITE_NOMEM;
    }else if( aNew->pSchema->file_format && aNew->pSchema->enc!=ENC(db) ){
      zErrDyn = sqlite3MPrintf(db, 
        "attached databases must use the same text encoding as main database");
      rc = SQLITE_ERROR;
    }
    pPager = sqlite3BtreePager(aNew->pBt);
    sqlite3PagerLockingMode(pPager, db->dfltLockMode);
    sqlite3PagerJournalMode(pPager, db->dfltJournalMode);
  }
  aNew->zName = sqlite3DbStrDup(db, zName);
  aNew->safety_level = 3;

#if SQLITE_HAS_CODEC
  {
    extern int sqlite3CodecAttach(sqlite3*, int, const void*, int);
    extern void sqlite3CodecGetKey(sqlite3*, int, void**, int*);
    int nKey;
    char *zKey;
    int t = sqlite3_value_type(argv[2]);
    switch( t ){
