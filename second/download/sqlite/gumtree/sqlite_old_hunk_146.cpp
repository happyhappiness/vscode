    "ALTER TABLE %Q.'%q_rowid'  RENAME TO \"%w_rowid\";"
    , pRtree->zDb, pRtree->zName, zNewName 
    , pRtree->zDb, pRtree->zName, zNewName 
    , pRtree->zDb, pRtree->zName, zNewName
  );
  if( zSql ){
    rc = sqlite3_exec(pRtree->db, zSql, 0, 0, 0);
    sqlite3_free(zSql);
  }
  return rc;
}

static sqlite3_module rtreeModule = {
  0,                         /* iVersion */
  rtreeCreate,                /* xCreate - create a table */
  rtreeConnect,               /* xConnect - connect to an existing table */
  rtreeBestIndex,             /* xBestIndex - Determine search strategy */
  rtreeDisconnect,            /* xDisconnect - Disconnect from a table */
  rtreeDestroy,               /* xDestroy - Drop a table */
  rtreeOpen,                  /* xOpen - open a cursor */
