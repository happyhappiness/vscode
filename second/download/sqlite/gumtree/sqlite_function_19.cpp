static char *fulltextSchema(
  int nColumn,                  /* Number of columns */
  const char *const* azColumn,  /* List of columns */
  const char *zTableName        /* Name of the table */
){
  int i;
  char *zSchema, *zNext;
  const char *zSep = "(";
  zSchema = sqlite3_mprintf("CREATE TABLE x");
  for(i=0; i<nColumn; i++){
    zNext = sqlite3_mprintf("%s%s%Q", zSchema, zSep, azColumn[i]);
    sqlite3_free(zSchema);
    zSchema = zNext;
    zSep = ",";
  }
  zNext = sqlite3_mprintf("%s,%Q HIDDEN", zSchema, zTableName);
  sqlite3_free(zSchema);
  zSchema = zNext;
  zNext = sqlite3_mprintf("%s,docid HIDDEN)", zSchema);
  sqlite3_free(zSchema);
  return zNext;
}