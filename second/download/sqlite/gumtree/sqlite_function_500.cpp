void sqlite3VtabFinishParse(Parse *pParse, Token *pEnd){
  Table *pTab;        /* The table being constructed */
  sqlite3 *db;        /* The database connection */
  char *zModule;      /* The module name of the table: USING modulename */
  Module *pMod = 0;

  addArgumentToVtab(pParse);
  pParse->sArg.z = 0;

  /* Lookup the module name. */
  pTab = pParse->pNewTable;
  if( pTab==0 ) return;
  db = pParse->db;
  if( pTab->nModuleArg<1 ) return;
  zModule = pTab->azModuleArg[0];
  pMod = (Module*)sqlite3HashFind(&db->aModule, zModule,
                                  sqlite3Strlen30(zModule));
  pTab->pMod = pMod;
  
  /* If the CREATE VIRTUAL TABLE statement is being entered for the
  ** first time (in other words if the virtual table is actually being
  ** created now instead of just being read out of sqlite_master) then
  ** do additional initialization work and store the statement text
  ** in the sqlite_master table.
  */
  if( !db->init.busy ){
    char *zStmt;
    char *zWhere;
    int iDb;
    Vdbe *v;

    /* Compute the complete text of the CREATE VIRTUAL TABLE statement */
    if( pEnd ){
      pParse->sNameToken.n = (int)(pEnd->z - pParse->sNameToken.z) + pEnd->n;
    }
    zStmt = sqlite3MPrintf(db, "CREATE VIRTUAL TABLE %T", &pParse->sNameToken);

    /* A slot for the record has already been allocated in the 
    ** SQLITE_MASTER table.  We just need to update that slot with all
    ** the information we've collected.  
    **
    ** The VM register number pParse->regRowid holds the rowid of an
    ** entry in the sqlite_master table tht was created for this vtab
    ** by sqlite3StartTable().
    */
    iDb = sqlite3SchemaToIndex(db, pTab->pSchema);
    sqlite3NestedParse(pParse,
      "UPDATE %Q.%s "
         "SET type='table', name=%Q, tbl_name=%Q, rootpage=0, sql=%Q "
       "WHERE rowid=#%d",
      db->aDb[iDb].zName, SCHEMA_TABLE(iDb),
      pTab->zName,
      pTab->zName,
      zStmt,
      pParse->regRowid
    );
    sqlite3DbFree(db, zStmt);
    v = sqlite3GetVdbe(pParse);
    sqlite3ChangeCookie(pParse, iDb);

    sqlite3VdbeAddOp2(v, OP_Expire, 0, 0);
    zWhere = sqlite3MPrintf(db, "name='%q'", pTab->zName);
    sqlite3VdbeAddOp4(v, OP_ParseSchema, iDb, 1, 0, zWhere, P4_DYNAMIC);
    sqlite3VdbeAddOp4(v, OP_VCreate, iDb, 0, 0, 
                         pTab->zName, sqlite3Strlen30(pTab->zName) + 1);
  }

  /* If we are rereading the sqlite_master table create the in-memory
  ** record of the table. If the module has already been registered,
  ** also call the xConnect method here.
  */
  else {
    Table *pOld;
    Schema *pSchema = pTab->pSchema;
    const char *zName = pTab->zName;
    int nName = sqlite3Strlen30(zName);
    pOld = sqlite3HashInsert(&pSchema->tblHash, zName, nName, pTab);
    if( pOld ){
      db->mallocFailed = 1;
      assert( pTab==pOld );  /* Malloc must have failed inside HashInsert() */
      return;
    }
    pSchema->db = pParse->db;
    pParse->pNewTable = 0;
  }
}