static int sqlite3InitOne(sqlite3 *db, int iDb, char **pzErrMsg){
  int rc;
  int i;
  BtCursor *curMain;
  int size;
  Table *pTab;
  Db *pDb;
  char const *azArg[4];
  int meta[5];
  InitData initData;
  char const *zMasterSchema;
  char const *zMasterName = SCHEMA_TABLE(iDb);

  /*
  ** The master database table has a structure like this
  */
  static const char master_schema[] = 
     "CREATE TABLE sqlite_master(\n"
     "  type text,\n"
     "  name text,\n"
     "  tbl_name text,\n"
     "  rootpage integer,\n"
     "  sql text\n"
     ")"
  ;
#ifndef SQLITE_OMIT_TEMPDB
  static const char temp_master_schema[] = 
     "CREATE TEMP TABLE sqlite_temp_master(\n"
     "  type text,\n"
     "  name text,\n"
     "  tbl_name text,\n"
     "  rootpage integer,\n"
     "  sql text\n"
     ")"
  ;
#else
  #define temp_master_schema 0
#endif

  assert( iDb>=0 && iDb<db->nDb );
  assert( db->aDb[iDb].pSchema );
  assert( sqlite3_mutex_held(db->mutex) );
  assert( iDb==1 || sqlite3BtreeHoldsMutex(db->aDb[iDb].pBt) );

  /* zMasterSchema and zInitScript are set to point at the master schema
  ** and initialisation script appropriate for the database being
  ** initialised. zMasterName is the name of the master table.
  */
  if( !OMIT_TEMPDB && iDb==1 ){
    zMasterSchema = temp_master_schema;
  }else{
    zMasterSchema = master_schema;
  }
  zMasterName = SCHEMA_TABLE(iDb);

  /* Construct the schema tables.  */
  azArg[0] = zMasterName;
  azArg[1] = "1";
  azArg[2] = zMasterSchema;
  azArg[3] = 0;
  initData.db = db;
  initData.iDb = iDb;
  initData.rc = SQLITE_OK;
  initData.pzErrMsg = pzErrMsg;
  (void)sqlite3SafetyOff(db);
  sqlite3InitCallback(&initData, 3, (char **)azArg, 0);
  (void)sqlite3SafetyOn(db);
  if( initData.rc ){
    rc = initData.rc;
    goto error_out;
  }
  pTab = sqlite3FindTable(db, zMasterName, db->aDb[iDb].zName);
  if( pTab ){
    pTab->tabFlags |= TF_Readonly;
  }

  /* Create a cursor to hold the database open
  */
  pDb = &db->aDb[iDb];
  if( pDb->pBt==0 ){
    if( !OMIT_TEMPDB && iDb==1 ){
      DbSetProperty(db, 1, DB_SchemaLoaded);
    }
    return SQLITE_OK;
  }
  curMain = sqlite3MallocZero(sqlite3BtreeCursorSize());
  if( !curMain ){
    rc = SQLITE_NOMEM;
    goto error_out;
  }
  sqlite3BtreeEnter(pDb->pBt);
  rc = sqlite3BtreeCursor(pDb->pBt, MASTER_ROOT, 0, 0, curMain);
  if( rc==SQLITE_EMPTY ) rc = SQLITE_OK;

  /* Get the database meta information.
  **
  ** Meta values are as follows:
  **    meta[0]   Schema cookie.  Changes with each schema change.
  **    meta[1]   File format of schema layer.
  **    meta[2]   Size of the page cache.
  **    meta[3]   Use freelist if 0.  Autovacuum if greater than zero.
  **    meta[4]   Db text encoding. 1:UTF-8 2:UTF-16LE 3:UTF-16BE
  **
  ** Note: The #defined SQLITE_UTF* symbols in sqliteInt.h correspond to
  ** the possible values of meta[4].
  */
  for(i=0; rc==SQLITE_OK && i<ArraySize(meta); i++){
    rc = sqlite3BtreeGetMeta(pDb->pBt, i+1, (u32 *)&meta[i]);
  }
  if( rc ){
    sqlite3SetString(pzErrMsg, db, "%s", sqlite3ErrStr(rc));
    goto initone_error_out;
  }
  pDb->pSchema->schema_cookie = meta[BTREE_SCHEMA_VERSION-1];

  /* If opening a non-empty database, check the text encoding. For the
  ** main database, set sqlite3.enc to the encoding of the main database.
  ** For an attached db, it is an error if the encoding is not the same
  ** as sqlite3.enc.
  */
  if( meta[BTREE_TEXT_ENCODING-1] ){  /* text encoding */
    if( iDb==0 ){
      u8 encoding;
      /* If opening the main database, set ENC(db). */
      encoding = (u8)meta[BTREE_TEXT_ENCODING-1] & 3;
      if( encoding==0 ) encoding = SQLITE_UTF8;
      ENC(db) = encoding;
      db->pDfltColl = sqlite3FindCollSeq(db, SQLITE_UTF8, "BINARY", 0);
    }else{
      /* If opening an attached database, the encoding much match ENC(db) */
      if( meta[BTREE_TEXT_ENCODING-1]!=ENC(db) ){
        sqlite3SetString(pzErrMsg, db, "attached databases must use the same"
            " text encoding as main database");
        rc = SQLITE_ERROR;
        goto initone_error_out;
      }
    }
  }else{
    DbSetProperty(db, iDb, DB_Empty);
  }
  pDb->pSchema->enc = ENC(db);

  if( pDb->pSchema->cache_size==0 ){
    size = meta[BTREE_DEFAULT_CACHE_SIZE-1];
    if( size==0 ){ size = SQLITE_DEFAULT_CACHE_SIZE; }
    if( size<0 ) size = -size;
    pDb->pSchema->cache_size = size;
    sqlite3BtreeSetCacheSize(pDb->pBt, pDb->pSchema->cache_size);
  }

  /*
  ** file_format==1    Version 3.0.0.
  ** file_format==2    Version 3.1.3.  // ALTER TABLE ADD COLUMN
  ** file_format==3    Version 3.1.4.  // ditto but with non-NULL defaults
  ** file_format==4    Version 3.3.0.  // DESC indices.  Boolean constants
  */
  pDb->pSchema->file_format = (u8)meta[BTREE_FILE_FORMAT-1];
  if( pDb->pSchema->file_format==0 ){
    pDb->pSchema->file_format = 1;
  }
  if( pDb->pSchema->file_format>SQLITE_MAX_FILE_FORMAT ){
    sqlite3SetString(pzErrMsg, db, "unsupported file format");
    rc = SQLITE_ERROR;
    goto initone_error_out;
  }

  /* Ticket #2804:  When we open a database in the newer file format,
  ** clear the legacy_file_format pragma flag so that a VACUUM will
  ** not downgrade the database and thus invalidate any descending
  ** indices that the user might have created.
  */
  if( iDb==0 && meta[BTREE_FILE_FORMAT-1]>=4 ){
    db->flags &= ~SQLITE_LegacyFileFmt;
  }

  /* Read the schema information out of the schema tables
  */
  assert( db->init.busy );
  if( rc==SQLITE_EMPTY ){
    /* For an empty database, there is nothing to read */
    rc = SQLITE_OK;
  }else{
    char *zSql;
    zSql = sqlite3MPrintf(db, 
        "SELECT name, rootpage, sql FROM '%q'.%s",
        db->aDb[iDb].zName, zMasterName);
    (void)sqlite3SafetyOff(db);
#ifndef SQLITE_OMIT_AUTHORIZATION
    {
      int (*xAuth)(void*,int,const char*,const char*,const char*,const char*);
      xAuth = db->xAuth;
      db->xAuth = 0;
#endif
      rc = sqlite3_exec(db, zSql, sqlite3InitCallback, &initData, 0);
#ifndef SQLITE_OMIT_AUTHORIZATION
      db->xAuth = xAuth;
    }
#endif
    if( rc==SQLITE_OK ) rc = initData.rc;
    (void)sqlite3SafetyOn(db);
    sqlite3DbFree(db, zSql);
#ifndef SQLITE_OMIT_ANALYZE
    if( rc==SQLITE_OK ){
      sqlite3AnalysisLoad(db, iDb);
    }
#endif
  }
  if( db->mallocFailed ){
    rc = SQLITE_NOMEM;
    sqlite3ResetInternalSchema(db, 0);
  }
  if( rc==SQLITE_OK || (db->flags&SQLITE_RecoveryMode)){
    /* Black magic: If the SQLITE_RecoveryMode flag is set, then consider
    ** the schema loaded, even if errors occurred. In this situation the 
    ** current sqlite3_prepare() operation will fail, but the following one
    ** will attempt to compile the supplied statement against whatever subset
    ** of the schema was loaded before the error occurred. The primary
    ** purpose of this is to allow access to the sqlite_master table
    ** even when its contents have been corrupted.
    */
    DbSetProperty(db, iDb, DB_SchemaLoaded);
    rc = SQLITE_OK;
  }

  /* Jump here for an error that occurs after successfully allocating
  ** curMain and calling sqlite3BtreeEnter(). For an error that occurs
  ** before that point, jump to error_out.
  */
initone_error_out:
  sqlite3BtreeCloseCursor(curMain);
  sqlite3_free(curMain);
  sqlite3BtreeLeave(pDb->pBt);

error_out:
  if( rc==SQLITE_NOMEM || rc==SQLITE_IOERR_NOMEM ){
    db->mallocFailed = 1;
  }
  return rc;
}