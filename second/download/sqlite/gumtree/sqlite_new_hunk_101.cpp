** use.  sqlite3SafetyCheckSickOrOk() allows a db pointer that failed to
** open properly and is not fit for general use but which can be
** used as an argument to sqlite3_errmsg() or sqlite3_close().
*/
int sqlite3SafetyCheckOk(sqlite3 *db){
  u32 magic;
  if( db==0 ) return 0;
  magic = db->magic;
  if( magic!=SQLITE_MAGIC_OPEN 
#ifdef SQLITE_DEBUG
     && magic!=SQLITE_MAGIC_BUSY
#endif
  ){
    return 0;
  }else{
    return 1;
  }
}
int sqlite3SafetyCheckSickOrOk(sqlite3 *db){
  u32 magic;
  magic = db->magic;
  if( magic!=SQLITE_MAGIC_SICK &&
      magic!=SQLITE_MAGIC_OPEN &&
      magic!=SQLITE_MAGIC_BUSY ) return 0;
  return 1;
}
