static int fulltextRename(
  sqlite3_vtab *pVtab,
  const char *zName
){
  fulltext_vtab *p = (fulltext_vtab *)pVtab;
  int rc = SQLITE_NOMEM;
  char *zSql = sqlite3_mprintf(
    "ALTER TABLE %Q.'%q_content'  RENAME TO '%q_content';"
    "ALTER TABLE %Q.'%q_segments' RENAME TO '%q_segments';"
    "ALTER TABLE %Q.'%q_segdir'   RENAME TO '%q_segdir';"
    , p->zDb, p->zName, zName 
    , p->zDb, p->zName, zName 
    , p->zDb, p->zName, zName
  );
  if( zSql ){
    rc = sqlite3_exec(p->db, zSql, 0, 0, 0);
    sqlite3_free(zSql);
  }
  return rc;
}