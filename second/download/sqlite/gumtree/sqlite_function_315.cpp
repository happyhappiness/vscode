static char *whereTempTriggers(Parse *pParse, Table *pTab){
  Trigger *pTrig;
  char *zWhere = 0;
  char *tmp = 0;
  const Schema *pTempSchema = pParse->db->aDb[1].pSchema; /* Temp db schema */

  /* If the table is not located in the temp-db (in which case NULL is 
  ** returned, loop through the tables list of triggers. For each trigger
  ** that is not part of the temp-db schema, add a clause to the WHERE 
  ** expression being built up in zWhere.
  */
  if( pTab->pSchema!=pTempSchema ){
    sqlite3 *db = pParse->db;
    for(pTrig=sqlite3TriggerList(pParse, pTab); pTrig; pTrig=pTrig->pNext){
      if( pTrig->pSchema==pTempSchema ){
        if( !zWhere ){
          zWhere = sqlite3MPrintf(db, "name=%Q", pTrig->name);
        }else{
          tmp = zWhere;
          zWhere = sqlite3MPrintf(db, "%s OR name=%Q", zWhere, pTrig->name);
          sqlite3DbFree(db, tmp);
        }
      }
    }
  }
  return zWhere;
}