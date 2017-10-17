void sqlite3EndTable(
  Parse *pParse,          /* Parse context */
  Token *pCons,           /* The ',' token after the last column defn. */
  Token *pEnd,            /* The final ')' token in the CREATE TABLE */
  Select *pSelect         /* Select from a "CREATE ... AS SELECT" */
){
  Table *p;
  sqlite3 *db = pParse->db;
  int iDb;

  if( (pEnd==0 && pSelect==0) || db->mallocFailed ){
    return;
  }
  p = pParse->pNewTable;
  if( p==0 ) return;

  assert( !db->init.busy || !pSelect );

  iDb = sqlite3SchemaToIndex(db, p->pSchema);

#ifndef SQLITE_OMIT_CHECK
  /* Resolve names in all CHECK constraint expressions.
  */
  if( p->pCheck ){
    SrcList sSrc;                   /* Fake SrcList for pParse->pNewTable */
    NameContext sNC;                /* Name context for pParse->pNewTable */

    memset(&sNC, 0, sizeof(sNC));
    memset(&sSrc, 0, sizeof(sSrc));
    sSrc.nSrc = 1;
    sSrc.a[0].zName = p->zName;
    sSrc.a[0].pTab = p;
    sSrc.a[0].iCursor = -1;
    sNC.pParse = pParse;
    sNC.pSrcList = &sSrc;
    sNC.isCheck = 1;
    if( sqlite3ResolveExprNames(&sNC, p->pCheck) ){
      return;
    }
  }
#endif /* !defined(SQLITE_OMIT_CHECK) */

  /* If the db->init.busy is 1 it means we are reading the SQL off the
  ** "sqlite_master" or "sqlite_temp_master" table on the disk.
  ** So do not write to the disk again.  Extract the root page number
  ** for the table from the db->init.newTnum field.  (The page number
  ** should have been put there by the sqliteOpenCb routine.)
  */
  if( db->init.busy ){
    p->tnum = db->init.newTnum;
  }

  /* If not initializing, then create a record for the new table
  ** in the SQLITE_MASTER table of the database.
  **
  ** If this is a TEMPORARY table, write the entry into the auxiliary
  ** file instead of into the main database file.
  */
  if( !db->init.busy ){
    int n;
    Vdbe *v;
    char *zType;    /* "view" or "table" */
    char *zType2;   /* "VIEW" or "TABLE" */
    char *zStmt;    /* Text of the CREATE TABLE or CREATE VIEW statement */

    v = sqlite3GetVdbe(pParse);
    if( NEVER(v==0) ) return;

    sqlite3VdbeAddOp1(v, OP_Close, 0);

    /* 
    ** Initialize zType for the new view or table.
    */
    if( p->pSelect==0 ){
      /* A regular table */
      zType = "table";
      zType2 = "TABLE";
#ifndef SQLITE_OMIT_VIEW
    }else{
      /* A view */
      zType = "view";
      zType2 = "VIEW";
#endif
    }

    /* If this is a CREATE TABLE xx AS SELECT ..., execute the SELECT
    ** statement to populate the new table. The root-page number for the
    ** new table is in register pParse->regRoot.
    **
    ** Once the SELECT has been coded by sqlite3Select(), it is in a
    ** suitable state to query for the column names and types to be used
    ** by the new table.
    **
    ** A shared-cache write-lock is not required to write to the new table,
    ** as a schema-lock must have already been obtained to create it. Since
    ** a schema-lock excludes all other database users, the write-lock would
    ** be redundant.
    */
    if( pSelect ){
      SelectDest dest;
      Table *pSelTab;

      assert(pParse->nTab==1);
      sqlite3VdbeAddOp3(v, OP_OpenWrite, 1, pParse->regRoot, iDb);
      sqlite3VdbeChangeP5(v, 1);
      pParse->nTab = 2;
      sqlite3SelectDestInit(&dest, SRT_Table, 1);
      sqlite3Select(pParse, pSelect, &dest);
      sqlite3VdbeAddOp1(v, OP_Close, 1);
      if( pParse->nErr==0 ){
        pSelTab = sqlite3ResultSetOfSelect(pParse, pSelect);
        if( pSelTab==0 ) return;
        assert( p->aCol==0 );
        p->nCol = pSelTab->nCol;
        p->aCol = pSelTab->aCol;
        pSelTab->nCol = 0;
        pSelTab->aCol = 0;
        sqlite3DeleteTable(pSelTab);
      }
    }

    /* Compute the complete text of the CREATE statement */
    if( pSelect ){
      zStmt = createTableStmt(db, p);
    }else{
      n = (int)(pEnd->z - pParse->sNameToken.z) + 1;
      zStmt = sqlite3MPrintf(db, 
          "CREATE %s %.*s", zType2, n, pParse->sNameToken.z
      );
    }

    /* A slot for the record has already been allocated in the 
    ** SQLITE_MASTER table.  We just need to update that slot with all
    ** the information we've collected.
    */
    sqlite3NestedParse(pParse,
      "UPDATE %Q.%s "
         "SET type='%s', name=%Q, tbl_name=%Q, rootpage=#%d, sql=%Q "
       "WHERE rowid=#%d",
      db->aDb[iDb].zName, SCHEMA_TABLE(iDb),
      zType,
      p->zName,
      p->zName,
      pParse->regRoot,
      zStmt,
      pParse->regRowid
    );
    sqlite3DbFree(db, zStmt);
    sqlite3ChangeCookie(pParse, iDb);

#ifndef SQLITE_OMIT_AUTOINCREMENT
    /* Check to see if we need to create an sqlite_sequence table for
    ** keeping track of autoincrement keys.
    */
    if( p->tabFlags & TF_Autoincrement ){
      Db *pDb = &db->aDb[iDb];
      if( pDb->pSchema->pSeqTab==0 ){
        sqlite3NestedParse(pParse,
          "CREATE TABLE %Q.sqlite_sequence(name,seq)",
          pDb->zName
        );
      }
    }
#endif

    /* Reparse everything to update our internal data structures */
    sqlite3VdbeAddOp4(v, OP_ParseSchema, iDb, 0, 0,
        sqlite3MPrintf(db, "tbl_name='%q'",p->zName), P4_DYNAMIC);
  }


  /* Add the table to the in-memory representation of the database.
  */
  if( db->init.busy ){
    Table *pOld;
    Schema *pSchema = p->pSchema;
    pOld = sqlite3HashInsert(&pSchema->tblHash, p->zName,
                             sqlite3Strlen30(p->zName),p);
    if( pOld ){
      assert( p==pOld );  /* Malloc must have failed inside HashInsert() */
      db->mallocFailed = 1;
      return;
    }
    pParse->pNewTable = 0;
    db->nTable++;
    db->flags |= SQLITE_InternChanges;

#ifndef SQLITE_OMIT_ALTERTABLE
    if( !p->pSelect ){
      const char *zName = (const char *)pParse->sNameToken.z;
      int nName;
      assert( !pSelect && pCons && pEnd );
      if( pCons->z==0 ){
        pCons = pEnd;
      }
      nName = (int)((const char *)pCons->z - zName);
      p->addColOffset = 13 + sqlite3Utf8CharLen(zName, nName);
    }
#endif
  }
}