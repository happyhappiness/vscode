*/
void sqlite3FinishTrigger(
  Parse *pParse,          /* Parser context */
  TriggerStep *pStepList, /* The triggered program */
  Token *pAll             /* Token that describes the complete CREATE TRIGGER */
){
  Trigger *pTrig = pParse->pNewTrigger;    /* Trigger being finished */
  char *zName;                             /* Name of trigger */
  sqlite3 *db = pParse->db;                /* The database */
  DbFixer sFix;
  int iDb;                                 /* Database containing the trigger */
  Token nameToken;           /* Trigger name for error reporting */

  pTrig = pParse->pNewTrigger;
  pParse->pNewTrigger = 0;
  if( NEVER(pParse->nErr) || !pTrig ) goto triggerfinish_cleanup;
  zName = pTrig->name;
  iDb = sqlite3SchemaToIndex(pParse->db, pTrig->pSchema);
  pTrig->step_list = pStepList;
  while( pStepList ){
    pStepList->pTrig = pTrig;
    pStepList = pStepList->pNext;
  }
  nameToken.z = pTrig->name;
  nameToken.n = sqlite3Strlen30(nameToken.z);
  if( sqlite3FixInit(&sFix, pParse, iDb, "trigger", &nameToken) 
          && sqlite3FixTriggerStep(&sFix, pTrig->step_list) ){
    goto triggerfinish_cleanup;
  }

  /* if we are not initializing, and this trigger is not on a TEMP table, 
  ** build the sqlite_master entry
  */
  if( !db->init.busy ){
    Vdbe *v;
    char *z;

    /* Make an entry in the sqlite_master table */
    v = sqlite3GetVdbe(pParse);
    if( v==0 ) goto triggerfinish_cleanup;
    sqlite3BeginWriteOperation(pParse, 0, iDb);
    z = sqlite3DbStrNDup(db, (char*)pAll->z, pAll->n);
    sqlite3NestedParse(pParse,
       "INSERT INTO %Q.%s VALUES('trigger',%Q,%Q,0,'CREATE TRIGGER %q')",
       db->aDb[iDb].zName, SCHEMA_TABLE(iDb), zName,
       pTrig->table, z);
    sqlite3DbFree(db, z);
    sqlite3ChangeCookie(pParse, iDb);
    sqlite3VdbeAddOp4(v, OP_ParseSchema, iDb, 0, 0, sqlite3MPrintf(
        db, "type='trigger' AND name='%q'", zName), P4_DYNAMIC
    );
  }

  if( db->init.busy ){
    Trigger *pLink = pTrig;
    Hash *pHash = &db->aDb[iDb].pSchema->trigHash;
    pTrig = sqlite3HashInsert(pHash, zName, sqlite3Strlen30(zName), pTrig);
    if( pTrig ){
      db->mallocFailed = 1;
    }else if( pLink->pSchema==pLink->pTabSchema ){
      Table *pTab;
      int n = sqlite3Strlen30(pLink->table);
      pTab = sqlite3HashFind(&pLink->pTabSchema->tblHash, pLink->table, n);
      assert( pTab!=0 );
      pLink->pNext = pTab->pTrigger;
      pTab->pTrigger = pLink;
    }
  }

