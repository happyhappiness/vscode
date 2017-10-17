void sqlite3VtabFinishParse(Parse *pParse, Token *pEnd){
  Table *pTab = pParse->pNewTable;  /* The table being constructed */
  sqlite3 *db = pParse->db;         /* The database connection */

  if( pTab==0 ) return;
  addArgumentToVtab(pParse);
  pParse->sArg.z = 0;
  if( pTab->nModuleArg<1 ) return;
  
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
    int iReg;
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
      db->aDb[iDb].zDbSName, MASTER_NAME,
      pTab->zName,
      pTab->zName,
      zStmt,
      pParse->regRowid
    );
    sqlite3DbFree(db, zStmt);
    v = sqlite3GetVdbe(pParse);
    sqlite3ChangeCookie(pParse, iDb);

    sqlite3VdbeAddOp0(v, OP_Expire);
    zWhere = sqlite3MPrintf(db, "name='%q' AND type='table'", pTab->zName);
    sqlite3VdbeAddParseSchemaOp(v, iDb, zWhere);

    iReg = ++pParse->nMem;
    sqlite3VdbeLoadString(v, iReg, pTab->zName);
    sqlite3VdbeAddOp2(v, OP_VCreate, iDb, iReg);
  }

  /* If we are rereading the sqlite_master table create the in-memory
  ** record of the table. The xConnect() method is not called until
  ** the first time the virtual table is used in an SQL statement. This
  ** allows a schema that contains virtual tables to be loaded before
  ** the required virtual table implementations are registered.  */
  else {
    Table *pOld;
    Schema *pSchema = pTab->pSchema;
    const char *zName = pTab->zName;
    assert( sqlite3SchemaMutexHeld(db, 0, pSchema) );
    pOld = sqlite3HashInsert(&pSchema->tblHash, zName, pTab);
    if( pOld ){
      sqlite3OomFault(db);
      assert( pTab==pOld );  /* Malloc must have failed inside HashInsert() */
      return;
    }
    pParse->pNewTable = 0;
  }
}