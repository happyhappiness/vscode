      db = 0;
      goto opendb_out;
    }
  }
  sqlite3_mutex_enter(db->mutex);
  db->errMask = 0xff;
  db->priorNewRowid = 0;
  db->nDb = 2;
  db->magic = SQLITE_MAGIC_BUSY;
  db->aDb = db->aDbStatic;

  assert( sizeof(db->aLimit)==sizeof(aHardLimit) );
  memcpy(db->aLimit, aHardLimit, sizeof(db->aLimit));
  db->autoCommit = 1;
  db->nextAutovac = -1;
  db->nextPagesize = 0;
  db->flags |= SQLITE_ShortColNames
#if SQLITE_DEFAULT_FILE_FORMAT<4
                 | SQLITE_LegacyFileFmt
#endif
#ifdef SQLITE_ENABLE_LOAD_EXTENSION
                 | SQLITE_LoadExtension
#endif
      ;
  sqlite3HashInit(&db->aCollSeq);
#ifndef SQLITE_OMIT_VIRTUALTABLE
  sqlite3HashInit(&db->aModule);
#endif

  db->pVfs = sqlite3_vfs_find(zVfs);
  if( !db->pVfs ){
    rc = SQLITE_ERROR;
    sqlite3Error(db, rc, "no such vfs: %s", zVfs);
    goto opendb_out;
  }

  /* Add the default collation sequence BINARY. BINARY works for both UTF-8
  ** and UTF-16, so add a version for each to avoid any unnecessary
  ** conversions. The only error that can occur here is a malloc() failure.
  */
  createCollation(db, "BINARY", SQLITE_UTF8, 0, binCollFunc, 0);
  createCollation(db, "BINARY", SQLITE_UTF16BE, 0, binCollFunc, 0);
  createCollation(db, "BINARY", SQLITE_UTF16LE, 0, binCollFunc, 0);
  createCollation(db, "RTRIM", SQLITE_UTF8, (void*)1, binCollFunc, 0);
  if( db->mallocFailed ){
    goto opendb_out;
  }
  db->pDfltColl = sqlite3FindCollSeq(db, SQLITE_UTF8, "BINARY", 0);
  assert( db->pDfltColl!=0 );

  /* Also add a UTF-8 case-insensitive collation sequence. */
  createCollation(db, "NOCASE", SQLITE_UTF8, 0, nocaseCollatingFunc, 0);

  /* Set flags on the built-in collating sequences */
  db->pDfltColl->type = SQLITE_COLL_BINARY;
  pColl = sqlite3FindCollSeq(db, SQLITE_UTF8, "NOCASE", 0);
  if( pColl ){
    pColl->type = SQLITE_COLL_NOCASE;
  }

  /* Open the backend database driver */
  db->openFlags = flags;
  rc = sqlite3BtreeFactory(db, zFilename, 0, SQLITE_DEFAULT_CACHE_SIZE, 
                           flags | SQLITE_OPEN_MAIN_DB,
                           &db->aDb[0].pBt);
  if( rc!=SQLITE_OK ){
    if( rc==SQLITE_IOERR_NOMEM ){
      rc = SQLITE_NOMEM;
    }
    sqlite3Error(db, rc, 0);
    goto opendb_out;
  }
  db->aDb[0].pSchema = sqlite3SchemaGet(db, db->aDb[0].pBt);
  db->aDb[1].pSchema = sqlite3SchemaGet(db, 0);


  /* The default safety_level for the main database is 'full'; for the temp
  ** database it is 'NONE'. This matches the pager layer defaults.  
  */
  db->aDb[0].zName = "main";
  db->aDb[0].safety_level = 3;
#ifndef SQLITE_OMIT_TEMPDB
  db->aDb[1].zName = "temp";
  db->aDb[1].safety_level = 1;
#endif

  db->magic = SQLITE_MAGIC_OPEN;
  if( db->mallocFailed ){
    goto opendb_out;
  }

  /* Register all built-in functions, but do not attempt to read the
  ** database schema yet. This is delayed until the first time the database
  ** is accessed.
  */
  sqlite3Error(db, SQLITE_OK, 0);
  sqlite3RegisterBuiltinFunctions(db);

  /* Load automatic extensions - extensions that have been registered
  ** using the sqlite3_automatic_extension() API.
  */
  sqlite3AutoLoadExtensions(db);
  rc = sqlite3_errcode(db);
  if( rc!=SQLITE_OK ){
    goto opendb_out;
  }

#ifdef SQLITE_ENABLE_FTS1
  if( !db->mallocFailed ){
    extern int sqlite3Fts1Init(sqlite3*);
    rc = sqlite3Fts1Init(db);
